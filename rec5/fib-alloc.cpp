#include <argparse/argparse.hpp>
#include <cassert>
#include <iostream>
#include <memory>
#include <memory_resource>
#include <vector>

// static and in separate class so that all template instantiations of
// counting_allocator use the same counter
class alloc_counter {
 public:
  static inline unsigned long long total_memory;
};

/// counting allocator wraps a std::allocator to track allocations and count the
/// current allocated size.
template <typename T>
class counting_allocator : alloc_counter {
 public:
  ~counting_allocator() = default;

  using pointer = T *;
  using const_pointer = const T *;
  using value_type = T;
  using size_type = size_t;
  using difference_type = ptrdiff_t;

  pointer allocate(size_type n) {
    total_memory += (n * sizeof(T));
    return allocator.allocate(n);
  }

  pointer allocate(size_type n, const void *cvp) {
    total_memory += (n * sizeof(T));
    return allocator.allocate(n, cvp);
  }

  void deallocate(pointer p, size_type n) {
    total_memory -= (n * sizeof(T));
    return allocator.deallocate(p, n);
  }

 private:
  std::allocator<T> allocator;
};

template <typename T, typename U>
bool operator==(const counting_allocator<T> &, const U &) {
  return true;
}

int main(int argc, const char *argv[]) {
#ifdef NDEBUG
  std::cout << "Release!" << std::endl;
#else
  std::cout << "Debug!" << std::endl;
#endif

  argparse::ArgumentParser program{"fib"};
  program.add_argument("N")
      .help("index of fibonacci number to compute")
      .scan<'i', int>();

  program.parse_args(argc, argv);
  auto N = program.get<int>("N");

  std::vector<unsigned int, counting_allocator<unsigned int>> fib({0, 1});

  // compute fibonacci mod 2^32
  for (int i = 2; i <= N; ++i) {
    fib.push_back(fib[i - 1] + fib[i - 2]);
  }

  assert(N < 2 || fib[2] == 1);
  assert(fib.size() == N + 1);

  std::cout << N << "th fibonacci number mod 2^32:" << fib[N] << std::endl;
  std::cout << "Memory used: " << alloc_counter::total_memory << "B"
            << std::endl;
  std::cout << "Vector capacity: " << fib.capacity() << std::endl;

  return 0;
}
