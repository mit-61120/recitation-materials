#pragma once

#include <string>

class User {
public:
    std::string name;
    unsigned int age;

    void birthday();
    bool operator<(const User &other) const;
};
