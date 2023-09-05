#pragma once

#include <cstdint>
#include <memory>
#include <string>

struct Visitor;

class Expr {
 public:
  virtual ~Expr() = default;                  // do nothing destructor
  virtual void accept(Visitor *v) const = 0;  // empty accept method.
};

typedef std::shared_ptr<Expr> ExprPtr;

struct Add final : public Expr {
  ExprPtr a, b;
  ~Add() = default;  // Releases a and b, so they will be deleted if no other
                     // (shared) ptrs point to those objects
  Add(const ExprPtr &_a, const ExprPtr &_b) : a(_a), b(_b) {}
  void accept(Visitor *v) const override;
};

struct Int final : public Expr {
  int64_t value;
  // ~Int() = default; // Optional
  Int(int64_t _value) : value(_value) {}
  void accept(Visitor *v) const override;
};

struct Var final : public Expr {
  std::string name;
  Var(const std::string &_name) : name(_name) {}
  void accept(Visitor *v) const override;
};
