#include "Visitor.hpp"
#include <algorithm>
#include <random>
#include <chrono>

BattleVisitor::BattleVisitor(std::vector<std::shared_ptr<NPC>>& npcs)
    : npcsRef(npcs) {}

void BattleVisitor::visit(Orc& o) {
    processBattle(attackerIndex, defenderIndex);
}

void BattleVisitor::visit(Squirrel& s) {
    processBattle(attackerIndex, defenderIndex);
}

void BattleVisitor::visit(Druid& d) {
    processBattle(attackerIndex, defenderIndex);
}

void BattleVisitor::visit(Elf& e) {
    processBattle(attackerIndex, defenderIndex);
}

void BattleVisitor::visit(Dragon& dr) {
    processBattle(attackerIndex, defenderIndex);
}

void BattleVisitor::visit(Bear& b) {
    processBattle(attackerIndex, defenderIndex);
}

void BattleVisitor::visit(Bandit& ba) {
    processBattle(attackerIndex, defenderIndex);
}

void BattleVisitor::visit(Werewolf& w) {
    processBattle(attackerIndex, defenderIndex);
}

void BattleVisitor::visit(Princess& p) {
    processBattle(attackerIndex, defenderIndex);
}

void BattleVisitor::visit(Toad& t) {
    processBattle(attackerIndex, defenderIndex);
}

void BattleVisitor::visit(Slaver& sl) {
    processBattle(attackerIndex, defenderIndex);
}

void BattleVisitor::visit(Pegasus& pe) {
    processBattle(attackerIndex, defenderIndex);
}

void BattleVisitor::visit(Bittern& bi) {
    processBattle(attackerIndex, defenderIndex);
}

void BattleVisitor::visit(Desman& de) {
    processBattle(attackerIndex, defenderIndex);
}

void BattleVisitor::visit(Bull& bu) {
    processBattle(attackerIndex, defenderIndex);
}

void BattleVisitor::visit(Knight& k) {
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
    // Таблица убиваемости согласно заданию
    // Орк может убивать: Белку, Друида, Эльфа, Дракона, Медведя, Разбойника, Оборотня, Принцессу, Жабу, Работорговца, Пегаса, Выпь, Выхухоль, Быка, Странствующего рыцаря
    if (attacker == NPCType::ORC) {
        return defender == NPCType::SQUIRREL || defender == NPCType::DRUID ||
               defender == NPCType::ELF || defender == NPCType::DRAGON ||
               defender == NPCType::BEAR || defender == NPCType::BANDIT ||
               defender == NPCType::WEREWOLF || defender == NPCType::PRINCESS ||
               defender == NPCType::TOAD || defender == NPCType::SLAVER ||
               defender == NPCType::PEGASUS || defender == NPCType::BITTERN ||
               defender == NPCType::DESMAN || defender == NPCType::BULL ||
               defender == NPCType::KNIGHT;
    }
    
    // Белка может убивать: Орка, Друида, Эльфа, Дракона, Медведя, Разбойника, Оборотня, Принцессу, Жабу, Работорговца, Пегаса, Выпь, Выхухоль, Быка, Странствующего рыцаря
    if (attacker == NPCType::SQUIRREL) {
        return defender == NPCType::ORC || defender == NPCType::DRUID ||
               defender == NPCType::ELF || defender == NPCType::DRAGON ||
               defender == NPCType::BEAR || defender == NPCType::BANDIT ||
               defender == NPCType::WEREWOLF || defender == NPCType::PRINCESS ||
               defender == NPCType::TOAD || defender == NPCType::SLAVER ||
               defender == NPCType::PEGASUS || defender == NPCType::BITTERN ||
               defender == NPCType::DESMAN || defender == NPCType::BULL ||
               defender == NPCType::KNIGHT;
    }
    
    // Друид может убивать: Орка, Белку, Эльфа, Дракона, Медведя, Разбойника, Оборотня, Принцессу, Жабу, Работорговца, Пегаса, Выпь, Выхухоль, Быка, Странствующего рыцаря
    if (attacker == NPCType::DRUID) {
        return defender == NPCType::ORC || defender == NPCType::SQUIRREL ||
               defender == NPCType::ELF || defender == NPCType::DRAGON ||
               defender == NPCType::BEAR || defender == NPCType::BANDIT ||
               defender == NPCType::WEREWOLF || defender == NPCType::PRINCESS ||
               defender == NPCType::TOAD || defender == NPCType::SLAVER ||
               defender == NPCType::PEGASUS || defender == NPCType::BITTERN ||
               defender == NPCType::DESMAN || defender == NPCType::BULL ||
               defender == NPCType::KNIGHT;
    }
    
    // Эльф может убивать: Орка, Белку, Друида, Дракона, Медведя, Разбойника, Оборотня, Принцессу, Жабу, Работорговца, Пегаса, Выпь, Выхухоль, Быка, Странствующего рыцаря
    if (attacker == NPCType::ELF) {
        return defender == NPCType::ORC || defender == NPCType::SQUIRREL ||
               defender == NPCType::DRUID || defender == NPCType::DRAGON ||
               defender == NPCType::BEAR || defender == NPCType::BANDIT ||
               defender == NPCType::WEREWOLF || defender == NPCType::PRINCESS ||
               defender == NPCType::TOAD || defender == NPCType::SLAVER ||
               defender == NPCType::PEGASUS || defender == NPCType::BITTERN ||
               defender == NPCType::DESMAN || defender == NPCType::BULL ||
               defender == NPCType::KNIGHT;
    }
    
    // Дракон может убивать: Орка, Белку, Друида, Эльфа, Медведя, Разбойника, Оборотня, Принцессу, Жабу, Работорговца, Пегаса, Выпь, Выхухоль, Быка, Странствующего рыцаря
    if (attacker == NPCType::DRAGON) {
        return defender == NPCType::ORC || defender == NPCType::SQUIRREL ||
               defender == NPCType::DRUID || defender == NPCType::ELF ||
               defender == NPCType::BEAR || defender == NPCType::BANDIT ||
               defender == NPCType::WEREWOLF || defender == NPCType::PRINCESS ||
               defender == NPCType::TOAD || defender == NPCType::SLAVER ||
               defender == NPCType::PEGASUS || defender == NPCType::BITTERN ||
               defender == NPCType::DESMAN || defender == NPCType::BULL ||
               defender == NPCType::KNIGHT;
    }
    
    // Медведь может убивать: Орка, Белку, Друида, Эльфа, Дракона, Разбойника, Оборотня, Принцессу, Жабу, Работорговца, Пегаса, Выпь, Выхухоль, Быка, Странствующего рыцаря
    if (attacker == NPCType::BEAR) {
        return defender == NPCType::ORC || defender == NPCType::SQUIRREL ||
               defender == NPCType::DRUID || defender == NPCType::ELF ||
               defender == NPCType::DRAGON || defender == NPCType::BANDIT ||
               defender == NPCType::WEREWOLF || defender == NPCType::PRINCESS ||
               defender == NPCType::TOAD || defender == NPCType::SLAVER ||
               defender == NPCType::PEGASUS || defender == NPCType::BITTERN ||
               defender == NPCType::DESMAN || defender == NPCType::BULL ||
               defender == NPCType::KNIGHT;
    }
    
    // Разбойник может убивать: Орка, Белку, Друида, Эльфа, Дракона, Медведя, Оборотня, Принцессу, Жабу, Работорговца, Пегаса, Выпь, Выхухоль, Быка, Странствующего рыцаря
    if (attacker == NPCType::BANDIT) {
        return defender == NPCType::ORC || defender == NPCType::SQUIRREL ||
               defender == NPCType::DRUID || defender == NPCType::ELF ||
               defender == NPCType::DRAGON || defender == NPCType::BEAR ||
               defender == NPCType::WEREWOLF || defender == NPCType::PRINCESS ||
               defender == NPCType::TOAD || defender == NPCType::SLAVER ||
               defender == NPCType::PEGASUS || defender == NPCType::BITTERN ||
               defender == NPCType::DESMAN || defender == NPCType::BULL ||
               defender == NPCType::KNIGHT;
    }
    
    // Оборотень может убивать: Орка, Белку, Друида, Эльфа, Дракона, Медведя, Разбойника, Принцессу, Жабу, Работорговца, Пегаса, Выпь, Выхухоль, Быка, Странствующего рыцаря
    if (attacker == NPCType::WEREWOLF) {
        return defender == NPCType::ORC || defender == NPCType::SQUIRREL ||
               defender == NPCType::DRUID || defender == NPCType::ELF ||
               defender == NPCType::DRAGON || defender == NPCType::BEAR ||
               defender == NPCType::BANDIT || defender == NPCType::PRINCESS ||
               defender == NPCType::TOAD || defender == NPCType::SLAVER ||
               defender == NPCType::PEGASUS || defender == NPCType::BITTERN ||
               defender == NPCType::DESMAN || defender == NPCType::BULL ||
               defender == NPCType::KNIGHT;
    }
    
    // Принцесса может убивать: Орка, Белку, Друида, Эльфа, Дракона, Медведя, Разбойника, Оборотня, Жабу, Работорговца, Пегаса, Выпь, Выхухоль, Быка, Странствующего рыцаря
    if (attacker == NPCType::PRINCESS) {
        return defender == NPCType::ORC || defender == NPCType::SQUIRREL ||
               defender == NPCType::DRUID || defender == NPCType::ELF ||
               defender == NPCType::DRAGON || defender == NPCType::BEAR ||
               defender == NPCType::BANDIT || defender == NPCType::WEREWOLF ||
               defender == NPCType::TOAD || defender == NPCType::SLAVER ||
               defender == NPCType::PEGASUS || defender == NPCType::BITTERN ||
               defender == NPCType::DESMAN || defender == NPCType::BULL ||
               defender == NPCType::KNIGHT;
    }
    
    // Жаба может убивать: Орка, Белку, Друида, Эльфа, Дракона, Медведя, Разбойника, Оборотня, Принцессу, Работорговца, Пегаса, Выпь, Выхухоль, Быка, Странствующего рыцаря
    if (attacker == NPCType::TOAD) {
        return defender == NPCType::ORC || defender == NPCType::SQUIRREL ||
               defender == NPCType::DRUID || defender == NPCType::ELF ||
               defender == NPCType::DRAGON || defender == NPCType::BEAR ||
               defender == NPCType::BANDIT || defender == NPCType::WEREWOLF ||
               defender == NPCType::PRINCESS || defender == NPCType::SLAVER ||
               defender == NPCType::PEGASUS || defender == NPCType::BITTERN ||
               defender == NPCType::DESMAN || defender == NPCType::BULL ||
               defender == NPCType::KNIGHT;
    }
    
    // Работорговец может убивать: Орка, Белку, Друида, Эльфа, Дракона, Медведя, Разбойника, Оборотня, Принцессу, Жабу, Пегаса, Выпь, Выхухоль, Быка, Странствующего рыцаря
    if (attacker == NPCType::SLAVER) {
        return defender == NPCType::ORC || defender == NPCType::SQUIRREL ||
               defender == NPCType::DRUID || defender == NPCType::ELF ||
               defender == NPCType::DRAGON || defender == NPCType::BEAR ||
               defender == NPCType::BANDIT || defender == NPCType::WEREWOLF ||
               defender == NPCType::PRINCESS || defender == NPCType::TOAD ||
               defender == NPCType::PEGASUS || defender == NPCType::BITTERN ||
               defender == NPCType::DESMAN || defender == NPCType::BULL ||
               defender == NPCType::KNIGHT;
    }
    
    // Пегас может убивать: Орка, Белку, Друида, Эльфа, Дракона, Медведя, Разбойника, Оборотня, Принцессу, Жабу, Работорговца, Выпь, Выхухоль, Быка, Странствующего рыцаря
    if (attacker == NPCType::PEGASUS) {
        return defender == NPCType::ORC || defender == NPCType::SQUIRREL ||
               defender == NPCType::DRUID || defender == NPCType::ELF ||
               defender == NPCType::DRAGON || defender == NPCType::BEAR ||
               defender == NPCType::BANDIT || defender == NPCType::WEREWOLF ||
               defender == NPCType::PRINCESS || defender == NPCType::TOAD ||
               defender == NPCType::SLAVER || defender == NPCType::BITTERN ||
               defender == NPCType::DESMAN || defender == NPCType::BULL ||
               defender == NPCType::KNIGHT;
    }
    
    // Выпь может убивать: Орка, Белку, Друида, Эльфа, Дракона, Медведя, Разбойника, Оборотня, Принцессу, Жабу, Работорговца, Пегаса, Выхухоль, Быка, Странствующего рыцаря
    if (attacker == NPCType::BITTERN) {
        return defender == NPCType::ORC || defender == NPCType::SQUIRREL ||
               defender == NPCType::DRUID || defender == NPCType::ELF ||
               defender == NPCType::DRAGON || defender == NPCType::BEAR ||
               defender == NPCType::BANDIT || defender == NPCType::WEREWOLF ||
               defender == NPCType::PRINCESS || defender == NPCType::TOAD ||
               defender == NPCType::SLAVER || defender == NPCType::PEGASUS ||
               defender == NPCType::DESMAN || defender == NPCType::BULL ||
               defender == NPCType::KNIGHT;
    }
    
    // Выхухоль может убивать: Орка, Белку, Друида, Эльфа, Дракона, Медведя, Разбойника, Оборотня, Принцессу, Жабу, Работорговца, Пегаса, Выпь, Быка, Странствующего рыцаря
    if (attacker == NPCType::DESMAN) {
        return defender == NPCType::ORC || defender == NPCType::SQUIRREL ||
               defender == NPCType::DRUID || defender == NPCType::ELF ||
               defender == NPCType::DRAGON || defender == NPCType::BEAR ||
               defender == NPCType::BANDIT || defender == NPCType::WEREWOLF ||
               defender == NPCType::PRINCESS || defender == NPCType::TOAD ||
               defender == NPCType::SLAVER || defender == NPCType::PEGASUS ||
               defender == NPCType::BITTERN || defender == NPCType::BULL ||
               defender == NPCType::KNIGHT;
    }
    
    // Бык может убивать: Орка, Белку, Друида, Эльфа, Дракона, Медведя, Разбойника, Оборотня, Принцессу, Жабу, Работорговца, Пегаса, Выпь, Выхухоль, Странствующего рыцаря
    if (attacker == NPCType::BULL) {
        return defender == NPCType::ORC || defender == NPCType::SQUIRREL ||
               defender == NPCType::DRUID || defender == NPCType::ELF ||
               defender == NPCType::DRAGON || defender == NPCType::BEAR ||
               defender == NPCType::BANDIT || defender == NPCType::WEREWOLF ||
               defender == NPCType::PRINCESS || defender == NPCType::TOAD ||
               defender == NPCType::SLAVER || defender == NPCType::PEGASUS ||
               defender == NPCType::BITTERN || defender == NPCType::DESMAN ||
               defender == NPCType::KNIGHT;
    }
    
    // Странствующий рыцарь может убивать: Орка, Белку, Друида, Эльфа, Дракона, Медведя, Разбойника, Оборотня, Принцессу, Жабу, Работорговца, Пегаса, Выпь, Выхухоль, Быка
    if (attacker == NPCType::KNIGHT) {
        return defender == NPCType::ORC || defender == NPCType::SQUIRREL ||
               defender == NPCType::DRUID || defender == NPCType::ELF ||
               defender == NPCType::DRAGON || defender == NPCType::BEAR ||
               defender == NPCType::BANDIT || defender == NPCType::WEREWOLF ||
               defender == NPCType::PRINCESS || defender == NPCType::TOAD ||
               defender == NPCType::SLAVER || defender == NPCType::PEGASUS ||
               defender == NPCType::BITTERN || defender == NPCType::DESMAN ||
               defender == NPCType::BULL;
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

