#pragma once
#include "common.h"
#include <set>
#include <string.h>
#include <vector>

namespace aoc2015 {

struct wizard {
  int hitpoints;
  int armor;
  int mana;

  bool alive() const noexcept { return mana > 0 && hitpoints > 0; }
};

struct spell {
  int turns;
  spell(int t) : turns(t) {}
  virtual int cost() = 0;
  virtual void apply(wizard&, wizard&) = 0;
};

struct magic_missile : public spell {
  magic_missile() : spell(1) {}
  virtual int cost() override { return 53; };
  virtual void apply(wizard& w1, wizard& w2) override {
    if (turns-- > 0) {
      w2.hitpoints -= 4;
    }
  }
};

struct drain : public spell {
  drain() : spell(1) {}
  virtual int cost() override { return 73; };
  virtual void apply(wizard& w1, wizard& w2) override {
    if (turns-- > 0) {
      w1.hitpoints += 1;
      w2.hitpoints -= 2;
    }
  }
};

struct shield : public spell {
  shield() : spell(6) {}
  virtual int cost() override { return 113; };
  virtual void apply(wizard& w1, wizard& w2) override {
    if (turns-- > 0) {
      w1.armor = 7;
    }
  }
};

struct poison : public spell {
  poison() : spell(6) {}
  virtual int cost() override { return 173; };
  virtual void apply(wizard& w1, wizard& w2) override {
    if (turns-- > 0) {
      w2.hitpoints -= 3;
    }
  }
};

struct recharge : public spell {
  recharge() : spell(5) {}
  virtual int cost() override { return 229; };
  virtual void apply(wizard& w1, wizard& w2) override {
    if (turns-- > 0) {
      w1.mana += 101;
    }
  }
};

// boss
// Hit Points: 55
// Damage: 8
struct bossfight : public spell {
  bossfight() : spell(INT32_MAX) {}
  virtual int cost() override { return 0; };
  virtual void apply(wizard& w1, wizard& w2) override {
    int d = 8 - w1.armor;
    w1.hitpoints -= d < 1 ? 1 : d;
  }
};

struct arena {
  // backtrace
  void fight(int turn, wizard& w1, wizard& w2, std::set<spell*>& active, int* least) {}
};

} // namespace aoc2015
