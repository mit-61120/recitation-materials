/**
 * Example 4:
 * - classes
 * - references
 */

// your own includes first
#include "User.h"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

void birthday2(User &user) {
    user.age++;
}
/*
bool operator<(const User &u, const User &u2) {
    return u.name < u2.name || u.age < u2.age;
}
  */

int main() {
    std::vector<User> users{
            {"Luka",   23},
            {"Matt",   19},
            {"Claire", 51},
            {"X AE",   2}
    };

    const std::vector users2{
            User{"Luka", 23},
            {"Matt", 19},
            {"Claire", 51},
            {"X AE", 2}
    };

    std::cout << users[0].age << std::endl;
    users[0].birthday();
    std::cout << users[0].age << std::endl;

    std::cout << users[1].age << std::endl;
    birthday2(users[1]);
    std::cout << users[1].age << std::endl;

    // TODO find all users whose names start with L or M (inclusive) and output them
    std::vector<User> lmUsers;
    std::copy_if(users.begin(), users.end(), std::back_inserter(lmUsers), [](const User &u) -> bool {
        return u.name[0] == 'L' || u.name[0] == 'M';
    });

    std::sort(users.begin(), users.end());
    std::vector lmUsers2(std::lower_bound(users.begin(), users.end(), User{"L", 0}), std::upper_bound(users.begin(), users.end(), User{"M"}));

    std::cout << lmUsers.size() << std::endl;
    std::cout << (users2[0] < users2[1]) << std::endl;
}
