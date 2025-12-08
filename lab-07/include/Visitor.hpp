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
    virtual void visit(Orc& o) = 0;
    virtual void visit(Squirrel& s) = 0;
    virtual void visit(Druid& d) = 0;
    virtual void visit(Elf& e) = 0;
    virtual void visit(Dragon& dr) = 0;
    virtual void visit(Bear& b) = 0;
    virtual void visit(Bandit& ba) = 0;
    virtual void visit(Werewolf& w) = 0;
    virtual void visit(Princess& p) = 0;
    virtual void visit(Toad& t) = 0;
    virtual void visit(Slaver& sl) = 0;
    virtual void visit(Pegasus& pe) = 0;
    virtual void visit(Bittern& bi) = 0;
    virtual void visit(Desman& de) = 0;
    virtual void visit(Bull& bu) = 0;
    virtual void visit(Knight& k) = 0;
};

/*
 BattleVisitor — реализует боевой цикл с кубиками
*/
class BattleVisitor : public Visitor {
public:
    BattleVisitor(std::vector<std::shared_ptr<NPC>>& npcs);

    void visit(Orc& o) override;
    void visit(Squirrel& s) override;
    void visit(Druid& d) override;
    void visit(Elf& e) override;
    void visit(Dragon& dr) override;
    void visit(Bear& b) override;
    void visit(Bandit& ba) override;
    void visit(Werewolf& w) override;
    void visit(Princess& p) override;
    void visit(Toad& t) override;
    void visit(Slaver& sl) override;
    void visit(Pegasus& pe) override;
    void visit(Bittern& bi) override;
    void visit(Desman& de) override;
    void visit(Bull& bu) override;
    void visit(Knight& k) override;

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

