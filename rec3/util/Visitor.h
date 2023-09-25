#pragma once

#include <tuple>

namespace util {
namespace detail {
template <typename T>
class VisitorOfOne {
 public:
  virtual void visit(T const &) = 0;
};

}  // namespace detail

template <typename... Ts>
class Visitor : detail::VisitorOfOne<Ts>... {
 public:
  using Types = std::tuple<Ts...>;

  using detail::VisitorOfOne<Ts>::visit...;
};
}  // namespace util
