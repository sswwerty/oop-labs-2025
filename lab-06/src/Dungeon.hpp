#pragma once
#include "NPC.hpp"
#include "Factories.hpp"
#include "Observer.hpp"
#include <vector>
#include <memory>

class Dungeon {
    std::vector<std::shared_ptr<NPC>> npcs;
    std::vector<Observer*> observers;

public:
    void addNPC(const std::string& type, double x, double y, const std::string& name);
    void print();
    void save(const std::string& filename);
    void load(const std::string& filename);
    void battle(double distance);

    void addObserver(Observer* obs) { observers.push_back(obs); }

private:
    bool inBounds(double x, double y) const;
    bool nameFree(const std::vector<std::shared_ptr<NPC>>& list,
                  NPCType type, const std::string& name) const;
    void validateAndInsert(std::vector<std::shared_ptr<NPC>>& list,
                           std::shared_ptr<NPC> npc);
};
