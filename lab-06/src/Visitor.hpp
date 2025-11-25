#pragma once

#include "NPC.hpp"
#include "Observer.hpp"

#include <vector>
#include <memory>
#include <cmath>
#include <unordered_set>
#include <string>

/*
 Abstract Visitor interface — нужно для accept(...) и для override в BattleVisitor
*/
class Visitor {
public:
    virtual ~Visitor() = default;
    virtual void visit(Squirrel& s) = 0;
    virtual void visit(Elf& e) = 0;
    virtual void visit(Bandit& b) = 0;
};

/*
 BattleVisitor — реализует боевой цикл. Для удобства содержит метод run(),
 который сам делает попарный перебор NPC, проверяет дистанцию и применяет правила.
*/
class BattleVisitor : public Visitor {
public:
    BattleVisitor(std::vector<std::shared_ptr<NPC>>& npcs,
                  std::vector<Observer*>& observers,
                  double distance);

    void visit(Squirrel& s) override;
    void visit(Elf& e) override;
    void visit(Bandit& b) override;

    // Запустить полный цикл боёв (весь раунд).
    void run();

private:
    std::vector<std::shared_ptr<NPC>>& npcsRef;
    std::vector<Observer*>& observersRef;
    double maxDistance;

    size_t attackerIndex{0};
    size_t defenderIndex{0};
    std::vector<size_t> latestFightDeaths;

    double distBetween(const NPC& a, const NPC& b) const;
    std::vector<size_t> resolveFight(NPC& attacker, size_t attackerIdx,
                                     NPC& defender, size_t defenderIdx);
    bool canKill(NPCType attacker, NPCType defender) const;
    void notifyKill(const std::string& killer, const std::string& victim);
};
