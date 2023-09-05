#include <chrono>
#include <iostream>

constexpr long LENGTH = 2000000;
double array[16 * LENGTH], out[8 * LENGTH];  // make sure they're not removed

int main(int argc, char *argv[]) {
  if (argc <= 1) return -1;
  double factor = std::stod(argv[1]);

  for (int i = 0; i < 16 * LENGTH; ++i) {
    array[i] = factor * i;
  }

  std::chrono::nanoseconds duration[10];

  for (auto &j : duration) {
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 8 * LENGTH; ++i) {
      out[i] = array[i] + array[8 * LENGTH + i];
    }

    auto end = std::chrono::high_resolution_clock::now();
    j = end - start;
  }

  for (auto d : duration) {
    std::cout
        << std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(
               d)
               .count()
        << "ms" << std::endl;
  }

  std::cout << std::endl;
  std::cout << out[8 * LENGTH - 1] << std::endl;
  return 0;
}
