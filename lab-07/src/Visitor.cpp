#include "Visitor.hpp"
#include <algorithm>
#include <random>
#include <chrono>

BattleVisitor::BattleVisitor(std::vector<std::shared_ptr<NPC>>& npcs)
    : npcsRef(npcs) {}

void BattleVisitor::visit(Elf& e) {
    processBattle(attackerIndex, defenderIndex);
}

void BattleVisitor::visit(Squirrel& s) {
    processBattle(attackerIndex, defenderIndex);
}

void BattleVisitor::visit(Bandit& ba) {
    processBattle(attackerIndex, defenderIndex);
}

double BattleVisitor::distBetween(const NPC& a, const NPC& b) const {
    double dx = a.getX() - b.getX();
    double dy = a.getY() - b.getY();
    return std::sqrt(dx*dx + dy*dy);
}

int BattleVisitor::rollDice() const {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(1, 6);
    return dis(gen);
}

bool BattleVisitor::canKill(NPCType attacker, NPCType defender) const {
    // Таблица убиваемости для трех типов: Эльф, Белка, Разбойник
    // Эльф может убивать: Белку, Разбойника
    if (attacker == NPCType::ELF) {
        return defender == NPCType::SQUIRREL || defender == NPCType::BANDIT;
    }
    
    // Белка может убивать: Эльфа, Разбойника
    if (attacker == NPCType::SQUIRREL) {
        return defender == NPCType::ELF || defender == NPCType::BANDIT;
    }
    
    // Разбойник может убивать: Эльфа, Белку
    if (attacker == NPCType::BANDIT) {
        return defender == NPCType::ELF || defender == NPCType::SQUIRREL;
    }
    
    return false;
}

void BattleVisitor::processBattle(size_t attackerIdx, size_t defenderIdx) {
    if (attackerIdx >= npcsRef.size() || defenderIdx >= npcsRef.size()) return;
    if (attackerIdx == defenderIdx) return;
    
    auto& attacker = npcsRef[attackerIdx];
    auto& defender = npcsRef[defenderIdx];
    
    if (!attacker->isAlive() || !defender->isAlive()) return;
    
    double distance = distBetween(*attacker, *defender);
    
    // Проверяем, может ли атакующий убить защитника
    if (canKill(attacker->getType(), defender->getType()) && 
        distance <= attacker->getKillDistance()) {
        // Бросаем кубики
        int attackPower = rollDice();
        int defensePower = rollDice();
        
        if (attackPower > defensePower) {
            defender->kill();
        }
    }
    
    // Проверяем обратную ситуацию
    if (canKill(defender->getType(), attacker->getType()) && 
        distance <= defender->getKillDistance()) {
        int attackPower = rollDice();
        int defensePower = rollDice();
        
        if (attackPower > defensePower) {
            attacker->kill();
        }
    }
}

