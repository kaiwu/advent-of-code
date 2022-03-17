#pragma once
#include <functional>
#include <map>

#include "common.h"

namespace aoc2015 {

struct result {
  enum {
    c_unknown,
    c_value,
  } type;
  uint16_t value;

  result op_and(result other) {
    if (type == c_value && other.type == c_value) {
      return result{c_value, uint16_t(value & other.value)};
    }
    return {c_unknown, 0};
  }

  result op_or(result other) {
    if (type == c_value && other.type == c_value) {
      return result{c_value, uint16_t(value | other.value)};
    }
    return {c_unknown, 0};
  }

  result op_leftshift(result other) {
    if (type == c_value && other.type == c_value) {
      return result{c_value, uint16_t(value << other.value)};
    }
    return {c_unknown, 0};
  }

  result op_rightshift(result other) {
    if (type == c_value && other.type == c_value) {
      return result{c_value, uint16_t(value >> other.value)};
    }
    return {c_unknown, 0};
  }

  result op_not() {
    if (type == c_value) {
      return result{c_value, uint16_t(~value)};
    }
    return {c_unknown, 0};
  }
};

struct cals {
  std::map<line_view, std::function<result()>> calls;

  bool is_value(line_view v, uint16_t* x) const noexcept {
    const char* p = v.line;
    while (p != v.line + v.length) {
      if (*p >= '0' && *p <= '9') {
        *x = *x * 10 + *p - '0';
        p++;
      } else {
        return false;
      }
    }
    return true;
  }

  result compute(line_view w) const noexcept {
    // std::cout << "compute " << w << std::endl;
    uint16_t x = 0;
    if (is_value(w, &x)) {
      return {result::c_value, x};
    } else {
      auto it = calls.find(w);
      return it != calls.end() ? it->second() : result{result::c_unknown, 0};
    }
  }

  std::function<result()> op_and(line_view& x, line_view& y) const noexcept {
    return [&x, &y, this]() -> result { return compute(x).op_and(compute(y)); };
  }

  std::function<result()> op_or(line_view& x, line_view& y) const noexcept {
    return [&x, &y, this]() -> result { return compute(x).op_or(compute(y)); };
  }

  std::function<result()> op_leftshift(line_view& x, line_view& y) const noexcept {
    return [&x, &y, this]() -> result { return compute(x).op_leftshift(compute(y)); };
  }

  std::function<result()> op_rightshift(line_view& x, line_view& y) const noexcept {
    return [&x, &y, this]() -> result { return compute(x).op_rightshift(compute(y)); };
  }

  std::function<result()> op_not(line_view& x, line_view& y) const noexcept {
    return [&x, this]() -> result { return compute(x).op_not(); };
  }

  std::function<result()> op_value(line_view& x, line_view& y) const noexcept {
    return [&x, this]() -> result { return compute(x); };
  }

  std::function<result()> parse(line_view line, line_view* x, line_view* y, line_view* w) const noexcept {
    static struct _ {
      std::function<result()> (cals::*op)(line_view&, line_view&) const noexcept;
      const char* label;
    } ops[] = {
        {&cals::op_and, "AND"},
        {&cals::op_or, "OR"},
        {&cals::op_leftshift, "LSHIFT"},
        {&cals::op_rightshift, "RSHIFT"},
    };
    const char* arrow = line.contains("->");
    *w = line_view(arrow + 3, line.line + line.length);

    for (auto op : ops) {
      const char* p = line.contains(op.label);
      if (p != nullptr) {
        *x = line_view(line.line, p - 1);
        *y = line_view(p + strlen(op.label) + 1, arrow - 1);
        return (this->*op.op)(*x, *y);
      }
    }

    const char* p = line.contains("NOT");
    if (p != nullptr) {
      *x = line_view(p + 4, arrow - 1);
      return op_not(*x, *y);
    }

    *x = line_view(line.line, arrow - 1);
    return op_value(*x, *y);
  }

  void parse(line_view line) {
    line_view* x = new line_view();
    line_view* y = new line_view();
    line_view* w = new line_view();
    auto f = parse(line, x, y, w);
    calls.insert({*w, f});
  }
};

} // namespace aoc2015
