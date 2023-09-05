/**
 * Example 3:
 * - algorithm
 * - for-range loop (reference)
 * - lambdas?
 */
#include <algorithm>
#include <iostream>

int main() {
  // feeling fancy
  std::cout << "Enter a word you want printed in Latin: ";

  std::string input;
  std::cin >> input;

  for (auto &chr : input) {
    if (chr == 'u') {
      chr = 'v';
    }
  }

  std::cout << input << std::endl;

  // another way
  std::string output;
  std::transform(input.begin(), input.end(), std::back_inserter(output),
                 [](char c) { return c == 'u' ? 'v' : c; });

  // even better
  std::replace(input.begin(), input.end(), 'u', 'v');
}
