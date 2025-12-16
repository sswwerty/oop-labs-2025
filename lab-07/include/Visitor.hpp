#pragma once

#include "NPC.hpp"
#include <vector>
#include <memory>
#include <cmath>
#include <unordered_set>
#include <string>
#include <mutex>
#include <queue>

/*
 Abstract Visitor interface
*/
class Visitor {
public:
    virtual ~Visitor() = default;
    virtual void visit(Elf& e) = 0;
    virtual void visit(Squirrel& s) = 0;
    virtual void visit(Bandit& ba) = 0;
};

/*
 BattleVisitor — реализует боевой цикл с кубиками
*/
class BattleVisitor : public Visitor {
public:
    BattleVisitor(std::vector<std::shared_ptr<NPC>>& npcs);

    void visit(Elf& e) override;
    void visit(Squirrel& s) override;
    void visit(Bandit& ba) override;

    // Обработать бой с кубиками
    void processBattle(size_t attackerIdx, size_t defenderIdx);

public:
    size_t attackerIndex{0};
    size_t defenderIndex{0};

private:
    std::vector<std::shared_ptr<NPC>>& npcsRef;

    double distBetween(const NPC& a, const NPC& b) const;
    bool canKill(NPCType attacker, NPCType defender) const;
    int rollDice() const; // Бросает 6-гранный кубик (1-6)
};

