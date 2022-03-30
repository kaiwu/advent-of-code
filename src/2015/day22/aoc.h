#pragma once
#include "common.h"
#include <set>
#include <vector>

namespace aoc2015 {

struct wizard {
  int hitpoints;
  int armor;
  int mana;

  bool alive() const noexcept { return mana > 0 && hitpoints > 0; }
};

struct spell {
  virtual int cost() = 0;
  virtual void apply(wizard&) = 0;
  virtual void unapply(wizard&) = 0;
};

struct magic_missile : public spell {
  virtual int cost() override { return 53; };
  virtual void apply(wizard& w) override { w.hitpoints -= 4; }
  virtual void unapply(wizard& w) override { w.hitpoints += 4; }
};

struct drain_heal : public spell {
  virtual int cost() override { return 73; };
  virtual void apply(wizard& w) override { w.hitpoints += 2; }
  virtual void unapply(wizard& w) override { w.hitpoints -= 2; }
};

struct drain_hurt : public spell {
  virtual int cost() override { return 0; };
  virtual void apply(wizard& w) override { w.hitpoints -= 2; }
  virtual void unapply(wizard& w) override { w.hitpoints += 2; }
};

struct shield : public spell {
  int armor;
  virtual int cost() override { return 113; };
  virtual void apply(wizard& w) override {
    armor = w.armor;
    w.armor = 7;
  }
  virtual void unapply(wizard& w) override { w.armor = armor; }
};

struct poison : public spell {
  virtual int cost() override { return 173; };
  virtual void apply(wizard& w) override { w.hitpoints -= 3; }
  virtual void unapply(wizard& w) override { w.hitpoints += 3; }
};

struct recharge : public spell {
  virtual int cost() override { return 229; };
  virtual void apply(wizard& w) override { w.mana += 101; }
  virtual void unapply(wizard& w) override { w.mana -= 101; }
};

struct arena {};

} // namespace aoc2015
