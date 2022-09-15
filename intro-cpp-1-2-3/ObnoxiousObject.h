#pragma once
#include <iostream>

class ObnoxiousObject {
public:
    int id;

    inline static int max_id{0};

    ObnoxiousObject() : id(max_id++) {
        std::cout << "Created " << id << std::endl;
    }

    ObnoxiousObject(const ObnoxiousObject &o) : id(max_id++) {
        std::cout << "Copied " << o.id << " into " << id << std::endl;
    }

    ObnoxiousObject &operator=(const ObnoxiousObject &o) {
        std::cout << "Copy assigned " << o.id << " into " << id << std::endl;
        return *this;
    }

    ObnoxiousObject(ObnoxiousObject &&o) noexcept: id(max_id++) {
        std::cout << "Moved " << o.id << " into " << id << std::endl;
    }

    ObnoxiousObject &operator=(ObnoxiousObject &&o) noexcept {
        std::cout << "Move assigned " << o.id << " into " << id << std::endl;
        return *this;
    }

    ~ObnoxiousObject() {
        std::cout << "Destructed " << id << std::endl;
    }
};
