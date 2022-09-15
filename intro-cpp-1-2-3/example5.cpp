/**
 * Example 5:
 * - inheritance
 * - virtual functions/polymorphism
 * - more references
 */
#include <iostream>
#include <vector>
#include <algorithm>

class Road {
public:
    virtual int speedLimit() = 0;

    virtual auto trucksAllowed() -> bool { return true; }
};

class Highway : public Road {
public:
    int speedLimit() override {
        return 55;
    }
};

class Interstate : public Highway {
public:
    int speedLimit() override {
        return 65;
    }
};

class Parkway : public Highway {
public:

    auto trucksAllowed() -> bool override {
        return false;
    }
};

// bool canDriveOn1(Road road, bool isTruck) {
//     return !isTruck || road.trucksAllowed();
// }

bool canDriveOn2(Highway road, bool isTruck) {
    return !isTruck || road.trucksAllowed();
}

bool canDriveOn3(Road &road, bool isTruck) {
    return !isTruck || road.trucksAllowed();
}

int main() {
    Interstate I95;
    Parkway MemorialDrive;

    std::cout << "I95 speed limit: " << I95.speedLimit() << std::endl;
    std::cout << "I95 speed limit: " << I95.speedLimit() << std::endl;

    std::cout << "Trucks can drive on I95?" << canDriveOn2(I95, true);
    std::cout << "Trucks can drive on I95?" << canDriveOn3(I95, true);
    std::cout << "Trucks can drive on Mem?" << canDriveOn2(MemorialDrive, true);
    std::cout << "Trucks can drive on Mem?" << canDriveOn3(MemorialDrive, true);
}
