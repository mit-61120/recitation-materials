/**
 * Example 4:
 * - classes
 * - references
 */

// your own includes first
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "User.h"

void birthday2(User &user) { user.age++; }

int main() {
  std::vector<User> users{
      {"Luka", 23}, {"Matt", 19}, {"Claire", 51}, {"X AE", 2}};

  const std::vector users2{
      User{"Luka", 23}, {"Matt", 19}, {"Claire", 51}, {"X AE", 2}};

  std::cout << users[0].age << std::endl;
  users[0].birthday();
  std::cout << users[0].age << std::endl;

  std::cout << users[1].age << std::endl;
  birthday2(users[1]);
  std::cout << users[1].age << std::endl;

  // TODO find all users whose names start with L or M (inclusive) and output
  // them
}
