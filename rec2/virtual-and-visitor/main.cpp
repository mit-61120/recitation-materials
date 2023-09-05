#include <iostream>

class Visitor;

struct Shape {
  virtual int numSides() const = 0;

  virtual std::string color() const = 0;

  virtual void accept(Visitor &b) const = 0;
};

struct Circle : Shape {
  int numSides() const override { return 0; }

  std::string color() const override { return "green"; }

  void accept(Visitor &v) const override;
};

struct Rectangle : Shape {
  int numSides() const override { return 4; }

  std::string color() const override { return "red"; }

  void accept(Visitor &v) const override;
};

struct Square : Rectangle {
  std::string color() const override { return "blue"; }
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
    std::cout << "drawing " << s.color() << " square" << std::endl;
  }

  void visit(const Circle &s) override {
    std::cout << "drawing " << s.color() << " circle" << std::endl;
  }

  void visit(const Rectangle &s) override {
    std::cout << "drawing " << s.color() << " rectangle" << std::endl;
  }
};

class ColorCollector : public Visitor {
 public:
  void visit(const Square &s) override { std::cout << s.color() << std::endl; }

  void visit(const Circle &s) override { std::cout << s.color() << std::endl; }

  void visit(const Rectangle &s) override {
    std::cout << s.color() << std::endl;
  }
};

void Circle::accept(Visitor &v) const { v.visit(*this); }

void Rectangle::accept(Visitor &v) const { v.visit(*this); }

void draw(const Shape &shape) {
  DrawingBoard b;
  shape.accept(b);
}

void colors(const Shape &shape) {
  ColorCollector c;
  shape.accept(c);
}

int main() {
  Circle c;
  Square s;
  Rectangle r;
  draw(c);
  colors(c);
  draw(r);
  colors(r);
  draw(s);
  colors(s);
  return 0;
}
