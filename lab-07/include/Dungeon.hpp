#pragma once
#include "NPC.hpp"
#include "Factories.hpp"
#include <vector>
#include <memory>
#include <shared_mutex>
#include <queue>
#include <mutex>
#include <atomic>
#include <string>

class Dungeon {
    std::vector<std::shared_ptr<NPC>> npcs;
    mutable std::shared_mutex npcsMutex; // для shared_lock при чтении
    
    std::queue<std::pair<std::weak_ptr<NPC>, std::weak_ptr<NPC>>> battleQueue; // пары указателей NPC для боя
    std::mutex battleQueueMutex;
    
    std::atomic<bool> gameRunning{true};
    mutable std::mutex coutMutex; // для синхронизации вывода в std::cout
    
    static constexpr double MAP_WIDTH = 100.0;
    static constexpr double MAP_HEIGHT = 100.0;

public:
    Dungeon();
    ~Dungeon();
    
    void addNPC(const std::string& type, double x, double y, const std::string& name);
    void print() const;
    
    // Поток передвижения и определения боев
    void movementThread();
    
    // Поток боев
    void battleThread();
    
    // Основной поток для вывода карты
    void printThread();
    
    // Запустить игру
    void runGame();
    
    // Остановить игру
    void stopGame() { gameRunning.store(false); }
    
    // Получить список выживших
    std::vector<std::shared_ptr<NPC>> getSurvivors() const;

private:
    bool inBounds(double x, double y) const;
    void moveNPC(size_t index);
    double distanceBetween(size_t i, size_t j) const;
    void checkForBattles();
    void removeDeadNPCs();
    std::string getTypeString(NPCType type) const;
};

