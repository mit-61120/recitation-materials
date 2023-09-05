/**
 * Example 5:
 * - inheritance
 * - virtual functions/polymorphism/overloading
 * - more references
 */
#include <algorithm>
#include <iostream>
#include <vector>

class Road {
 public:
  virtual int speedLimit() = 0;

  virtual auto trucksAllowed() -> bool { return true; }
};

class Highway : public Road {
 public:
  int speedLimit() override { return 35; }
};

class Interstate : public Highway {
 public:
  int speedLimit() override { return 65; }
};

class Parkway : public Highway {
 public:
  auto trucksAllowed() -> bool override { return false; }
};

// This doesn't work
// bool canDriveOn1(Road road, bool isTruck) {
//     return !isTruck || road.trucksAllowed();
// }

// This works, doesn't dynamically dispatch
bool canDriveOn2(Highway road, bool isTruck) {
  return !isTruck || road.trucksAllowed();
}

// This dynamically dispatches
bool canDriveOn3(Road &road, bool isTruck) {
  return !isTruck || road.trucksAllowed();
}

// Be careful of overloads...
bool canDriveOnOverloaded(Highway road, bool isTruck) {
  return !isTruck || road.trucksAllowed();
}
bool canDriveOnOverloaded(Road &road, bool isTruck) {
  return !isTruck || road.trucksAllowed();
}

int main() {
  Interstate I95;
  Parkway MemorialDrive;

  // Try to guess the outputs of these.
  std::cout << "I95 speed limit: " << I95.speedLimit() << std::endl;
  std::cout << "I95 speed limit: " << static_cast<Highway&>(I95).speedLimit() << std::endl;
  std::cout << "I95 speed limit: " << static_cast<Highway*>(&I95)->speedLimit() << std::endl;
  std::cout << "I95 speed limit: " << static_cast<Highway>(I95).speedLimit() << std::endl;
  std::cout << "Mem speed limit: " << MemorialDrive.speedLimit() << std::endl;

  std::cout << "Trucks can drive on I95? " << canDriveOn2(I95, true) << std::endl;
  std::cout << "Trucks can drive on I95? " << canDriveOn3(I95, true) << std::endl;
  std::cout << "Trucks can drive on I95? " << canDriveOnOverloaded(I95, true) << std::endl;
  std::cout << "Trucks can drive on Mem? " << canDriveOn2(MemorialDrive, true) << std::endl;
  std::cout << "Trucks can drive on Mem? " << canDriveOn3(MemorialDrive, true) << std::endl;
  std::cout << "Trucks can drive on Mem? " << canDriveOnOverloaded(MemorialDrive, true) << std::endl;
}
