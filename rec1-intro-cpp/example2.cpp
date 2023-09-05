/**
 * Example 2:
 * - map (std namespace)
 */
#include <iostream>
#include <map>

int main() {
  std::map<std::string, int> ages = {
      {"Luka", 23}, {"Matt", 19}, {"Claire", 51}, {"X AE", 2}};

  std::cout << "Whose age do you want to know?" << std::endl;
  std::string name;
  std::cin >> name;

  if (ages.find(name) != ages.end()) {
    std::cout << name << "'s age is " << ages[name] << std::endl;
  } else {
    std::cout << "I've never heard of this person in my life!" << std::endl;
  }

  std::cout << ages.size() << std::endl;
  if (ages["John"] == 0) {
    std::cout << "John is born" << std::endl;
  }
  std::cout << ages.size() << std::endl;

  return 0;
}
