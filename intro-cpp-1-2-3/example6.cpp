#include "ObnoxiousObject.h"
#include <iostream>

void doSomething(ObnoxiousObject obj) {
    std::cout << obj.id << " passed to doSomething" << std::endl;
}

void doSomethingElse(const ObnoxiousObject &obj) {
    std::cout << obj.id << " passed to doSomethingElse" << std::endl;
}

int main() {
    ObnoxiousObject objA;
    auto objB = objA;

    auto objC = std::move(objA);

    doSomething(objC);
    doSomething(std::move(objB));

    doSomething(ObnoxiousObject{});
    doSomethingElse(ObnoxiousObject{});
}