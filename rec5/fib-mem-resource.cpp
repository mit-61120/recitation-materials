#include <argparse/argparse.hpp>
#include <cassert>
#include <iostream>
#include <memory>
#include <memory_resource>
#include <vector>

/// counting resource wraps a memory resource to track allocations and count the
/// current allocated size.
class counting_resource : public std::pmr::memory_resource {
 public:
  ///
  /// \param underlying the underlying resource to use for allocation
  explicit counting_resource(
      std::pmr::memory_resource &underlying = *std::pmr::get_default_resource())
      : underlying(underlying) {}

  ~counting_resource() override = default;

  [[nodiscard]] unsigned long long size() const { return size_; }

 private:
  void *do_allocate(size_t bytes, size_t alignment) override {
    this->size_ += bytes;
    return underlying.allocate(bytes, alignment);
  }

  void do_deallocate(void *p, size_t bytes, size_t alignment) override {
    this->size_ -= bytes;
    return underlying.deallocate(p, bytes, alignment);
  }

  [[nodiscard]] bool do_is_equal(
      const memory_resource &other) const noexcept override {
    return this == &other;
  }

  memory_resource &underlying;
  unsigned long long size_{0};
};

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

  counting_resource memResource;
  std::pmr::polymorphic_allocator<unsigned int> allocator(&memResource);
  std::pmr::vector<unsigned int> fib({0, 1}, allocator);

  // compute fibonacci mod 2^32
  for (int i = 2; i <= N; ++i) {
    fib.push_back(fib[i - 1] + fib[i - 2]);
  }

  assert(N < 2 || fib[2] == 1);
  assert(fib.size() == N + 1);

  std::cout << N << "th fibonacci number mod 2^32:" << fib[N] << std::endl;
  std::cout << "Memory used: " << memResource.size() << "B" << std::endl;
  std::cout << "Vector capacity: " << fib.capacity() << std::endl;

  return 0;
}
