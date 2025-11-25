#include "Visitor.hpp"
#include <algorithm>

BattleVisitor::BattleVisitor(std::vector<std::shared_ptr<NPC>>& npcs,
                             std::vector<Observer*>& observers,
                             double distance)
    : npcsRef(npcs), observersRef(observers), maxDistance(distance) {}

void BattleVisitor::visit(Squirrel& s) {
    latestFightDeaths = resolveFight(s, attackerIndex,
                                     *npcsRef[defenderIndex], defenderIndex);
}

void BattleVisitor::visit(Elf& e) {
    latestFightDeaths = resolveFight(e, attackerIndex,
                                     *npcsRef[defenderIndex], defenderIndex);
}

void BattleVisitor::visit(Bandit& b) {
    latestFightDeaths = resolveFight(b, attackerIndex,
                                     *npcsRef[defenderIndex], defenderIndex);
}

double BattleVisitor::distBetween(const NPC& a, const NPC& b) const {
    double dx = a.getX() - b.getX();
    double dy = a.getY() - b.getY();
    return std::sqrt(dx*dx + dy*dy);
}

std::vector<size_t> BattleVisitor::resolveFight(NPC& attacker, size_t attackerIdx,
                                                NPC& defender, size_t defenderIdx) {
    std::vector<size_t> dead;

    if (attackerIdx >= npcsRef.size() || defenderIdx >= npcsRef.size()) return dead;
    if (attackerIdx == defenderIdx) return dead;

    if (distBetween(attacker, defender) > maxDistance) return dead;

    if (attacker.getType() == defender.getType()) {
        notifyKill(attacker.getName(), defender.getName());
        notifyKill(defender.getName(), attacker.getName());
        dead.push_back(defenderIdx);
        dead.push_back(attackerIdx);
        return dead;
    }

    if (canKill(attacker.getType(), defender.getType())) {
        notifyKill(attacker.getName(), defender.getName());
        dead.push_back(defenderIdx);
    }
    if (canKill(defender.getType(), attacker.getType())) {
        notifyKill(defender.getName(), attacker.getName());
        dead.push_back(attackerIdx);
    }

    std::sort(dead.begin(), dead.end());
    dead.erase(std::unique(dead.begin(), dead.end()), dead.end());

    return dead;
}

bool BattleVisitor::canKill(NPCType attacker, NPCType defender) const {
    if (attacker == NPCType::ELF && defender == NPCType::BANDIT) return true;
    if (attacker == NPCType::BANDIT && defender == NPCType::SQUIRREL) return true;
    if (attacker == NPCType::SQUIRREL && defender == NPCType::ELF) return true;
    return false;
}

void BattleVisitor::notifyKill(const std::string& killer, const std::string& victim) {
    for (auto* obs : observersRef) {
        if (obs) {
            obs->onKill(killer, victim);
        }
    }
}

void BattleVisitor::run() {
    if (npcsRef.size() < 2) return;

    // Соберём индексы погибших в этом раунде (чтобы удалить после всех проверок).
    std::unordered_set<size_t> deadIndices;

    // Попарный перебор i<j
    size_t n = npcsRef.size();
    for (size_t i = 0; i < n; ++i) {
        // Если i уже помечен как мертвый — пропускаем.
        if (deadIndices.count(i)) continue;
        for (size_t j = i + 1; j < n; ++j) {
            if (deadIndices.count(j)) continue;
            attackerIndex = i;
            defenderIndex = j;
            latestFightDeaths.clear();
            npcsRef[i]->accept(*this);
            for (auto idx : latestFightDeaths) {
                deadIndices.insert(idx);
            }
        }
    }

    // Удалить по убывающим индексам, чтобы не ломать индексы
    if (!deadIndices.empty()) {
        std::vector<size_t> toRemove(deadIndices.begin(), deadIndices.end());
        std::sort(toRemove.begin(), toRemove.end(), std::greater<size_t>());

        for (auto idx : toRemove) {
            if (idx < npcsRef.size()) {
                npcsRef.erase(npcsRef.begin() + idx);
            }
        }
    }
}
