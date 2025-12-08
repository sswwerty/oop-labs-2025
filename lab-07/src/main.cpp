#include "Dungeon.hpp"
#include "NPC.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <vector>
#include <iomanip>

// Список всех типов NPC
const std::vector<std::string> NPC_TYPES = {
    "ORC", "SQUIRREL", "DRUID", "ELF", "DRAGON", "BEAR", "BANDIT",
    "WEREWOLF", "PRINCESS", "TOAD", "SLAVER", "PEGASUS",
    "BITTERN", "DESMAN", "BULL", "KNIGHT"
};

void createRandomNPCs(Dungeon& dungeon, int count) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> xDis(0.0, 100.0);
    std::uniform_real_distribution<> yDis(0.0, 100.0);
    std::uniform_int_distribution<> typeDis(0, NPC_TYPES.size() - 1);
    
    for (int i = 0; i < count; ++i) {
        std::string type = NPC_TYPES[typeDis(gen)];
        double x = xDis(gen);
        double y = yDis(gen);
        std::string name = type + "_" + std::to_string(i);
        dungeon.addNPC(type, x, y, name);
    }
}

int main() {
    std::cout << "=== LAB-07: Asynchronous Programming ===\n";
    std::cout << "Creating 50 NPCs in random locations...\n";
    
    Dungeon dungeon;
    createRandomNPCs(dungeon, 50);
    
    std::cout << "Starting game for 30 seconds...\n\n";
    
    // Запускаем потоки с использованием лямбда-функций
    std::thread movement([&dungeon]() {
        dungeon.movementThread();
    });
    std::thread battle([&dungeon]() {
        dungeon.battleThread();
    });
    std::thread printer([&dungeon]() {
        dungeon.printThread();
    });
    
    // Ждем 30 секунд
    std::this_thread::sleep_for(std::chrono::seconds(30));
    
    // Останавливаем игру
    dungeon.stopGame();
    
    // Ждем завершения потоков
    movement.join();
    battle.join();
    printer.join();
    
    // Выводим список выживших
    std::cout << "\n=== GAME OVER ===\n";
    std::cout << "Survivors:\n";
    
    auto survivors = dungeon.getSurvivors();
    if (survivors.empty()) {
        std::cout << "No survivors!\n";
    } else {
        std::cout << "Total survivors: " << survivors.size() << "\n\n";
        for (const auto& npc : survivors) {
            std::string typeStr;
            switch (npc->getType()) {
                case NPCType::ORC: typeStr = "ORC"; break;
                case NPCType::SQUIRREL: typeStr = "SQUIRREL"; break;
                case NPCType::DRUID: typeStr = "DRUID"; break;
                case NPCType::ELF: typeStr = "ELF"; break;
                case NPCType::DRAGON: typeStr = "DRAGON"; break;
                case NPCType::BEAR: typeStr = "BEAR"; break;
                case NPCType::BANDIT: typeStr = "BANDIT"; break;
                case NPCType::WEREWOLF: typeStr = "WEREWOLF"; break;
                case NPCType::PRINCESS: typeStr = "PRINCESS"; break;
                case NPCType::TOAD: typeStr = "TOAD"; break;
                case NPCType::SLAVER: typeStr = "SLAVER"; break;
                case NPCType::PEGASUS: typeStr = "PEGASUS"; break;
                case NPCType::BITTERN: typeStr = "BITTERN"; break;
                case NPCType::DESMAN: typeStr = "DESMAN"; break;
                case NPCType::BULL: typeStr = "BULL"; break;
                case NPCType::KNIGHT: typeStr = "KNIGHT"; break;
            }
            std::cout << std::setw(12) << typeStr << " " << npc->getName()
                      << " at (" << std::fixed << std::setprecision(2)
                      << npc->getX() << ", " << npc->getY() << ")\n";
        }
    }
    
    return 0;
}

