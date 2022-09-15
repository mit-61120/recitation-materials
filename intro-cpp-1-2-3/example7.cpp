#include "ObnoxiousObject.h"

#include <iostream>
#include <memory>

void doSomething(ObnoxiousObject obj) {
    std::cout << obj.id << " passed to doSomething" << std::endl;
}

void doSomethingElse(const ObnoxiousObject &obj) {
    std::cout << obj.id << " passed to doSomethingElse" << std::endl;
}

std::unique_ptr<ObnoxiousObject> doSomething(std::unique_ptr<ObnoxiousObject> obj) {
    std::cout << obj->id << " passed to doSomething" << std::endl;
    return obj;
}

std::unique_ptr<ObnoxiousObject> doSomethingElse(std::unique_ptr<ObnoxiousObject> obj) {
    std::cout << obj->id << " passed to doSomethingElse" << std::endl;
    return obj;
}



int main() {

    auto objD = std::make_unique<ObnoxiousObject>();

    auto objE = doSomething(std::move(objD));
    auto objF = doSomethingElse(std::move(objD));
}