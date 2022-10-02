#include <iostream>

class Visitor;

struct Shape {
    virtual int numSides() const {
        return -1;
    };

    virtual std::string color() const = 0;

    virtual void accept(Visitor& b) const = 0;
};

struct Circle : Shape {
    int numSides()  const {
        return 0;
    }

    std::string color() const override {
        return "green";
    }

    void accept(Visitor &v) const override;
};

struct Rectangle : Shape {
    int numSides() const {
        return 4;
    }

    std::string color() const override {
        return "red";
    }

    void accept(Visitor &v) const override;
};

struct Square : Rectangle {
    std::string color() const override {
        return "blue";
    }
};

class Visitor {
public:
    virtual void visit(const Square &s) = 0;

    virtual void visit(const Circle &s) = 0;

    virtual void visit(const Rectangle &s) = 0;
};

class DrawingBoard : public Visitor {
public:
    void visit(const Square &s) override {
        std::cout << "drawing square" << std::endl;
    }

    void visit(const Circle &s) override {
        std::cout << "drawing square" << std::endl;
    }

    void visit(const Rectangle &s) override {
        std::cout << "drawing square" << std::endl;
    }
};

class ColorCollector : public Visitor {
public:
    void visit(const Square &s) override {
        std::cout << s.color() << std::endl;
    }

    void visit(const Circle &s) override {
        std::cout << s.color() << std::endl;
    }

    void visit(const Rectangle &s) override {
        std::cout << s.color() << std::endl;
    }
};

void Circle::accept(Visitor &v) const {
    v.visit(*this);
}

void draw(const Shape &shape) {
    std::cout << "numSides: " << shape.numSides() << std::endl;

    DrawingBoard b;
    shape.draw(b);
}

int main() {

    Circle c;
    Square s;
    Rectangle r;
    draw(c);
    draw(r);
    draw(s);

    std::cout << "Hello, World!" << std::endl;
    std::cout << "numSides: " << c.numSides() << std::endl;

    return 0;
}
