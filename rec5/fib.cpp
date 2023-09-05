#include <argparse/argparse.hpp>
#include <cassert>
#include <iostream>
#include <vector>

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

  // compute fibonacci mod 2^32
  std::vector<unsigned int> fib = {0, 1};
  for (int i = 2; i <= N; ++i) {
    fib.push_back(fib[i - 1] + fib[i - 2]);
  }

  assert(N < 2 || fib[2] == 1);
  assert(fib.size() == N + 1);

  std::cout << N << "th fibonacci number mod 2^32:" << fib[N] << std::endl;

  return 0;
}
