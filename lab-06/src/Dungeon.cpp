#include "Dungeon.hpp"
#include "Visitor.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>

void Dungeon::addNPC(const std::string& type, double x, double y, const std::string& name) {
    auto npc = NPCFactory::create(type, x, y, name);
    validateAndInsert(npcs, std::move(npc));
}

void Dungeon::print() {
    for (auto& n : npcs) {
        std::string t;
        if (n->getType() == NPCType::SQUIRREL) t = "SQUIRREL";
        if (n->getType() == NPCType::ELF) t = "ELF";
        if (n->getType() == NPCType::BANDIT) t = "BANDIT";

        std::cout << t << " " << n->getName()
                  << " (" << n->getX() << ", " << n->getY() << ")"
                  << std::endl;
    }
}

void Dungeon::save(const std::string& filename) {
    std::ofstream f(filename);
    for (auto& n : npcs) {
        std::string type;
        if (n->getType() == NPCType::SQUIRREL) type = "SQUIRREL";
        if (n->getType() == NPCType::ELF) type = "ELF";
        if (n->getType() == NPCType::BANDIT) type = "BANDIT";
        f << type << " " << n->getName() << " " << n->getX() << " " << n->getY() << "\n";
    }
}

void Dungeon::load(const std::string& filename) {
    npcs.clear();
    std::ifstream f(filename);
    if (!f.is_open()) {
        throw std::runtime_error("Failed to open file: " + filename);
    }
    std::string line;
    size_t lineNo = 0;
    while (std::getline(f, line)) {
        ++lineNo;
        if (line.empty()) continue;
        try {
            auto npc = FileNPCFactory::createFromLine(line);
            validateAndInsert(npcs, std::move(npc));
        } catch (const std::exception& ex) {
            throw std::runtime_error("Line " + std::to_string(lineNo) + ": " + ex.what());
        }
    }
}

void Dungeon::battle(double dist) {
    BattleVisitor visitor(npcs, observers, dist);
    visitor.run();
}

bool Dungeon::inBounds(double x, double y) const {
    return x >= 0.0 && x <= 500.0 && y >= 0.0 && y <= 500.0;
}

bool Dungeon::nameFree(const std::vector<std::shared_ptr<NPC>>& list,
                       NPCType type, const std::string& name) const {
    for (const auto& npc : list) {
        if (npc->getType() == type && npc->getName() == name) {
            return false;
        }
    }
    return true;
}

void Dungeon::validateAndInsert(std::vector<std::shared_ptr<NPC>>& list,
                                std::shared_ptr<NPC> npc) {
    if (!npc) {
        throw std::runtime_error("Attempted to insert empty NPC");
    }
    if (!inBounds(npc->getX(), npc->getY())) {
        throw std::runtime_error("NPC coordinates out of bounds");
    }
    if (!nameFree(list, npc->getType(), npc->getName())) {
        throw std::runtime_error("NPC name for this type must be unique");
    }
    list.push_back(std::move(npc));
}
