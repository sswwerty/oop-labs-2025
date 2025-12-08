#include "NPC.hpp"
#include "Visitor.hpp"
#include <shared_mutex>
#include <cmath>
#include <limits>

// Реализация accept для всех типов
void Orc::accept(Visitor& v) { v.visit(*this); }
void Squirrel::accept(Visitor& v) { v.visit(*this); }
void Druid::accept(Visitor& v) { v.visit(*this); }
void Elf::accept(Visitor& v) { v.visit(*this); }
void Dragon::accept(Visitor& v) { v.visit(*this); }
void Bear::accept(Visitor& v) { v.visit(*this); }
void Bandit::accept(Visitor& v) { v.visit(*this); }
void Werewolf::accept(Visitor& v) { v.visit(*this); }
void Princess::accept(Visitor& v) { v.visit(*this); }
void Toad::accept(Visitor& v) { v.visit(*this); }
void Slaver::accept(Visitor& v) { v.visit(*this); }
void Pegasus::accept(Visitor& v) { v.visit(*this); }
void Bittern::accept(Visitor& v) { v.visit(*this); }
void Desman::accept(Visitor& v) { v.visit(*this); }
void Bull::accept(Visitor& v) { v.visit(*this); }
void Knight::accept(Visitor& v) { v.visit(*this); }

double NPC::getX() const {
    std::shared_lock<std::shared_mutex> lock(positionMutex);
    return x;
}

double NPC::getY() const {
    std::shared_lock<std::shared_mutex> lock(positionMutex);
    return y;
}

void NPC::setX(double newX) {
    std::lock_guard<std::shared_mutex> lock(positionMutex);
    x = newX;
}

void NPC::setY(double newY) {
    std::lock_guard<std::shared_mutex> lock(positionMutex);
    y = newY;
}

double NPC::getMoveDistance() const {
    switch (type) {
        case NPCType::ORC: return 20.0;
        case NPCType::SQUIRREL: return 5.0;
        case NPCType::DRUID: return 10.0;
        case NPCType::ELF: return 10.0;
        case NPCType::DRAGON: return 50.0;
        case NPCType::BEAR: return 5.0;
        case NPCType::BANDIT: return 10.0;
        case NPCType::WEREWOLF: return 40.0;
        case NPCType::PRINCESS: return 1.0;
        case NPCType::TOAD: return 1.0;
        case NPCType::SLAVER: return 10.0;
        case NPCType::PEGASUS: return 30.0;
        case NPCType::BITTERN: return 50.0;
        case NPCType::DESMAN: return 5.0;
        case NPCType::BULL: return 30.0;
        case NPCType::KNIGHT: return 30.0;
        default: return 10.0;
    }
}

double NPC::getKillDistance() const {
    switch (type) {
        case NPCType::ORC: return 10.0;
        case NPCType::SQUIRREL: return 5.0;
        case NPCType::DRUID: return 10.0;
        case NPCType::ELF: return 50.0;
        case NPCType::DRAGON: return 30.0;
        case NPCType::BEAR: return 10.0;
        case NPCType::BANDIT: return 10.0;
        case NPCType::WEREWOLF: return 5.0;
        case NPCType::PRINCESS: return 1.0;
        case NPCType::TOAD: return 10.0;
        case NPCType::SLAVER: return 10.0;
        case NPCType::PEGASUS: return 10.0;
        case NPCType::BITTERN: return 10.0;
        case NPCType::DESMAN: return 20.0;
        case NPCType::BULL: return 10.0;
        case NPCType::KNIGHT: return 10.0;
        default: return 10.0;
    }
}

