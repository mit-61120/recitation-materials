/**
 * Example 1:
 * - basic output and input
 * - strings
 * - vector
 * - basic types
 */
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    cout << "What's your name?" << endl;

    string name;
    cin >> name;

    cout << "Hello, " << name << "." << endl;

    if (name == "Luka") {
        cout << "I know you!" << endl;
    }

    vector<int> elements{0, 1, 1, 2, 3, 5, 8, 13};

    for (auto element: elements) {
        cout << element << " ";
    }
    cout << std::endl;



    int number = -5; // 32 bits but varies by platform. if you need exact value, use specific types
    unsigned long long largeNumber = 5; // non-negative with maximum size (64-bits)
    bool logical = false;
    char character = 'a'; // 8 bits
    float realNumber = 0.3f; // 32-bit IEEE floating-point
    double realNumberDoublePrecision = 5.3; // 64-bit IEEE floating-point


    return 0;
}
