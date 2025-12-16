#include "NPC.hpp"
#include "Visitor.hpp"
#include <shared_mutex>
#include <cmath>
#include <limits>

// Реализация accept для трех типов
void Elf::accept(Visitor& v) { v.visit(*this); }
void Squirrel::accept(Visitor& v) { v.visit(*this); }
void Bandit::accept(Visitor& v) { v.visit(*this); }

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
        case NPCType::ELF: return 10.0;
        case NPCType::SQUIRREL: return 5.0;
        case NPCType::BANDIT: return 10.0;
        default: return 10.0;
    }
}

double NPC::getKillDistance() const {
    switch (type) {
        case NPCType::ELF: return 50.0;
        case NPCType::SQUIRREL: return 5.0;
        case NPCType::BANDIT: return 10.0;
        default: return 10.0;
    }
}

