/**
 * Example 8:
 * - std::shared_ptr
 */

#include <iostream>
#include <memory>
#include <functional>
#include <utility>

class Console {
public:
    std::string name;

    template<typename T>
    void print(const T &str) {
        std::cout << name << ": " << str << std::endl;
    };
};

class Application {
public:
    void registerCallback(std::function<void()> f) {
        callback = std::move(f);
    }

    void runCallback() {
        callback();
    }

private:
    std::function<void()> callback;
};


void addCallback(Application &app) {
    auto console = std::make_unique<Console>(Console{"console1"});

    app.registerCallback([&console]() {
        console->print("Callback!");
    });

    console->print("Callback created!");
}


int main() {
    Application app;
    addCallback(app);

    // later somewhere else
    app.runCallback();
}