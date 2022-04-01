#pragma once
#include "common.h"
#include <set>
#include <stack>
#include <vector>

namespace aoc2015 {

enum class stype {
  magic_missile = 0,
  drain,
  shield,
  poison,
  recharge,
};

struct spell;
struct wizard {
  int hitpoints;
  int armor;
  int mana;
  std::stack<spell*> spells[5];

  bool alive() const noexcept { return mana > 0 && hitpoints > 0; }
};

struct spell {
  wizard* w;
  spell(wizard* wp) : w(wp) {}
  virtual int cost() = 0;
  virtual void apply(wizard&) = 0;
  virtual void unapply(wizard&) = 0;
};

struct magic_missile : public spell {
  magic_missile(wizard* w) : spell(w) {}
  virtual int cost() override { return 53; };
  virtual void apply(wizard& w) override { w.hitpoints -= 4; }
  virtual void unapply(wizard& w) override { w.hitpoints += 4; }
};

struct drain : public spell {
  drain(wizard* w) : spell(w) {}
  virtual int cost() override { return 73; };
  virtual void apply(wizard& w) override {
    w.hitpoints -= 2;
    this->w->hitpoints += 2;
  }
  virtual void unapply(wizard& w) override {
    w.hitpoints += 2;
    this->w->hitpoints -= 2;
  }
};

struct shield : public spell {
  int armor;
  shield(wizard* w) : spell(w) {}
  virtual int cost() override { return 113; };
  virtual void apply(wizard& w) override {
    armor = w.armor;
    w.armor = 7;
  }
  virtual void unapply(wizard& w) override { w.armor = armor; }
};

struct poison : public spell {
  poison(wizard* w) : spell(w) {}
  virtual int cost() override { return 173; };
  virtual void apply(wizard& w) override { w.hitpoints -= 3; }
  virtual void unapply(wizard& w) override { w.hitpoints += 3; }
};

struct recharge : public spell {
  recharge(wizard* w) : spell(w) {}
  virtual int cost() override { return 229; };
  virtual void apply(wizard& w) override { w.mana += 101; }
  virtual void unapply(wizard& w) override { w.mana -= 101; }
};

struct arena {
  void apply(wizard* w) {
    for (int i = 0; i < 5; i++) {
      if (!w->spells[i].empty()) {
        spell* s = w->spells[i].top();
        s->apply(*w);
        w->spells[i].pop();
      }
    }
  }

  // before cast needs to check
  // 1 spell s is not active, stack is empty
  // 2 w2 has enough mana
  void cast(int s, wizard* w1, wizard* w2) {
    switch (stype(s)) {
    case stype::magic_missile:
      w1->spells[s].emplace(new magic_missile{w2});
      w2->mana -= w1->spells[s].top()->cost();
      break;
    case stype::drain:
      w1->spells[s].emplace(new drain{w2});
      w2->mana -= w1->spells[s].top()->cost();
      break;
    case stype::shield:
      for (int i = 0; i < 6; i++) {
        w2->spells[s].emplace(new shield{w2});
      }
      w2->mana -= w2->spells[s].top()->cost();
      break;
    case stype::poison:
      for (int i = 0; i < 6; i++) {
        w1->spells[s].emplace(new poison{w2});
      }
      w2->mana -= w1->spells[s].top()->cost();
      break;
    case stype::recharge:
      for (int i = 0; i < 5; i++) {
        w1->spells[s].emplace(new recharge{w2});
      }
      w2->mana -= w1->spells[s].top()->cost();
      break;
    }
  }
};

} // namespace aoc2015
