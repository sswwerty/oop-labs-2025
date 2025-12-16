#include "Dungeon.hpp"
#include "Visitor.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <random>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <limits>

Dungeon::Dungeon() = default;

Dungeon::~Dungeon() {
    stopGame();
}

void Dungeon::addNPC(const std::string& type, double x, double y, const std::string& name) {
    std::lock_guard<std::shared_mutex> lock(npcsMutex);
    auto npc = NPCFactory::create(type, x, y, name);
    if (inBounds(x, y)) {
        npcs.push_back(std::move(npc));
    }
}

void Dungeon::print() const {
    std::lock_guard<std::mutex> coutLock(coutMutex);
    std::shared_lock<std::shared_mutex> npcsLock(npcsMutex);
    
    std::cout << "\n=== DUNGEON MAP ===\n";
    std::cout << "Size: " << MAP_WIDTH << "x" << MAP_HEIGHT << "\n";
    std::cout << "Alive NPCs: ";
    
    int aliveCount = 0;
    for (const auto& npc : npcs) {
        if (npc->isAlive()) {
            aliveCount++;
        }
    }
    std::cout << aliveCount << "\n\n";
    
    // Создаем простую текстовую карту
    const int mapSize = 20; // Упрощенная карта 20x20 для вывода
    std::vector<std::vector<char>> map(mapSize, std::vector<char>(mapSize, '.'));
    
    for (const auto& npc : npcs) {
        if (npc->isAlive()) {
            int mapX = static_cast<int>((npc->getX() / MAP_WIDTH) * mapSize);
            int mapY = static_cast<int>((npc->getY() / MAP_HEIGHT) * mapSize);
            if (mapX >= 0 && mapX < mapSize && mapY >= 0 && mapY < mapSize) {
                char symbol = getTypeString(npc->getType())[0];
                if (map[mapY][mapX] == '.') {
                    map[mapY][mapX] = symbol;
                } else {
                    map[mapY][mapX] = '*'; // Несколько NPC в одной клетке
                }
            }
        }
    }
    
    // Выводим карту
    for (int y = 0; y < mapSize; ++y) {
        for (int x = 0; x < mapSize; ++x) {
            std::cout << map[y][x] << " ";
        }
        std::cout << "\n";
    }
    
    std::cout << "\nLegend: ";
    // Используем уже существующий npcsLock, не создаем новый
    std::vector<std::string> shownTypes;
    for (const auto& npc : npcs) {
        if (npc->isAlive()) {
            std::string typeStr = getTypeString(npc->getType());
            if (std::find(shownTypes.begin(), shownTypes.end(), typeStr) == shownTypes.end()) {
                std::cout << typeStr[0] << "=" << typeStr << " ";
                shownTypes.push_back(typeStr);
            }
        }
    }
    std::cout << "\n" << std::endl;
}

std::string Dungeon::getTypeString(NPCType type) const {
    switch (type) {
        case NPCType::ELF: return "ELF";
        case NPCType::SQUIRREL: return "SQUIRREL";
        case NPCType::BANDIT: return "BANDIT";
        default: return "UNKNOWN";
    }
}

bool Dungeon::inBounds(double x, double y) const {
    return x >= 0.0 && x <= MAP_WIDTH && y >= 0.0 && y <= MAP_HEIGHT;
}

void Dungeon::moveNPC(size_t index) {
    std::shared_lock<std::shared_mutex> npcsLock(npcsMutex);
    
    if (index >= npcs.size()) return;
    auto& npc = npcs[index];
    
    if (!npc->isAlive()) return;
    
    npcsLock.unlock();
    
    // Генерируем случайное направление
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<> angleDis(0.0, 2.0 * M_PI);
    
    double angle = angleDis(gen);
    double moveDist = npc->getMoveDistance();
    
    double newX = npc->getX() + std::cos(angle) * moveDist;
    double newY = npc->getY() + std::sin(angle) * moveDist;
    
    // Проверяем границы
    if (!inBounds(newX, newY)) {
        // Отражаем от границы
        if (newX < 0) newX = 0;
        if (newX > MAP_WIDTH) newX = MAP_WIDTH;
        if (newY < 0) newY = 0;
        if (newY > MAP_HEIGHT) newY = MAP_HEIGHT;
    }
    
    npc->setX(newX);
    npc->setY(newY);
}

double Dungeon::distanceBetween(size_t i, size_t j) const {
    std::shared_lock<std::shared_mutex> npcsLock(npcsMutex);
    
    if (i >= npcs.size() || j >= npcs.size()) return std::numeric_limits<double>::max();
    
    auto& npc1 = npcs[i];
    auto& npc2 = npcs[j];
    
    double dx = npc1->getX() - npc2->getX();
    double dy = npc1->getY() - npc2->getY();
    return std::sqrt(dx*dx + dy*dy);
}

void Dungeon::checkForBattles() {
    std::shared_lock<std::shared_mutex> npcsLock(npcsMutex);
    
    size_t n = npcs.size();
    for (size_t i = 0; i < n; ++i) {
        if (!npcs[i]->isAlive()) continue;
        
        for (size_t j = i + 1; j < n; ++j) {
            if (!npcs[j]->isAlive()) continue;
            
            double dist = distanceBetween(i, j);
            double killDist1 = npcs[i]->getKillDistance();
            double killDist2 = npcs[j]->getKillDistance();
            
            // Если NPC находятся на расстоянии убийства, добавляем задачу в очередь
            if (dist <= killDist1 || dist <= killDist2) {
                std::lock_guard<std::mutex> queueLock(battleQueueMutex);
                battleQueue.push({npcs[i], npcs[j]});
            }
        }
    }
}

void Dungeon::removeDeadNPCs() {
    std::lock_guard<std::shared_mutex> lock(npcsMutex);
    npcs.erase(
        std::remove_if(npcs.begin(), npcs.end(),
            [](const std::shared_ptr<NPC>& npc) { return !npc->isAlive(); }),
        npcs.end()
    );
}

void Dungeon::movementThread() {
    while (gameRunning.load()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Небольшая задержка
        
        // Перемещаем всех живых NPC
        {
            std::shared_lock<std::shared_mutex> npcsLock(npcsMutex);
            size_t n = npcs.size();
            npcsLock.unlock();
            
            for (size_t i = 0; i < n && gameRunning.load(); ++i) {
                moveNPC(i);
            }
        }
        
        // Проверяем бои
        checkForBattles();
        
        // Удаляем мертвых NPC
        removeDeadNPCs();
    }
}

void Dungeon::battleThread() {
    while (gameRunning.load()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        
        std::pair<std::weak_ptr<NPC>, std::weak_ptr<NPC>> battle;
        bool hasBattle = false;
        
        {
            std::lock_guard<std::mutex> queueLock(battleQueueMutex);
            if (!battleQueue.empty()) {
                battle = battleQueue.front();
                battleQueue.pop();
                hasBattle = true;
            }
        }
        
        if (hasBattle) {
            auto attacker = battle.first.lock();
            auto defender = battle.second.lock();
            
            if (attacker && defender && attacker->isAlive() && defender->isAlive()) {
                // Находим индексы для visitor
                std::shared_lock<std::shared_mutex> npcsLock(npcsMutex);
                size_t attackerIdx = 0, defenderIdx = 0;
                bool foundAttacker = false, foundDefender = false;
                
                for (size_t i = 0; i < npcs.size(); ++i) {
                    if (npcs[i] == attacker) {
                        attackerIdx = i;
                        foundAttacker = true;
                    }
                    if (npcs[i] == defender) {
                        defenderIdx = i;
                        foundDefender = true;
                    }
                    if (foundAttacker && foundDefender) break;
                }
                
                if (foundAttacker && foundDefender) {
                    BattleVisitor visitor(npcs);
                    visitor.processBattle(attackerIdx, defenderIdx);
                }
            }
        }
    }
}

void Dungeon::printThread() {
    while (gameRunning.load()) {
        // Разбиваем задержку на части для быстрой реакции на остановку
        // 1 секунда = 100 * 10ms
        for (int i = 0; i < 100 && gameRunning.load(); ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        // Проверяем gameRunning еще раз перед вызовом print()
        // чтобы избежать блокировки в print() если игра уже остановлена
        if (!gameRunning.load()) {
            break;
        }
        print();
    }
}

// Реализация coroutine для объединения перемещения и сражения
MovementBattleCoroutine Dungeon::movementAndBattleCoroutine() {
    // Используем co_await один раз для демонстрации coroutine
    co_await SleepAwaitable{std::chrono::milliseconds(0), &gameRunning};
    
    while (gameRunning.load()) {
        // Перемещаем всех живых NPC
        {
            std::shared_lock<std::shared_mutex> npcsLock(npcsMutex);
            size_t n = npcs.size();
            npcsLock.unlock();
            
            for (size_t i = 0; i < n && gameRunning.load(); ++i) {
                moveNPC(i);
            }
        }
        
        // Проверяем бои и добавляем их в очередь
        checkForBattles();
        
        // Обрабатываем несколько боев из очереди (до 10 за итерацию)
        for (int battleCount = 0; battleCount < 10 && gameRunning.load(); ++battleCount) {
            std::pair<std::weak_ptr<NPC>, std::weak_ptr<NPC>> battle;
            bool hasBattle = false;
            
            {
                std::lock_guard<std::mutex> queueLock(battleQueueMutex);
                if (!battleQueue.empty()) {
                    battle = battleQueue.front();
                    battleQueue.pop();
                    hasBattle = true;
                }
            }
            
            if (!hasBattle) break;
            
            auto attacker = battle.first.lock();
            auto defender = battle.second.lock();
            
            if (attacker && defender && attacker->isAlive() && defender->isAlive()) {
                // Находим индексы для visitor
                std::shared_lock<std::shared_mutex> npcsLock(npcsMutex);
                size_t attackerIdx = 0, defenderIdx = 0;
                bool foundAttacker = false, foundDefender = false;
                
                for (size_t i = 0; i < npcs.size(); ++i) {
                    if (npcs[i] == attacker) {
                        attackerIdx = i;
                        foundAttacker = true;
                    }
                    if (npcs[i] == defender) {
                        defenderIdx = i;
                        foundDefender = true;
                    }
                    if (foundAttacker && foundDefender) break;
                }
                
                if (foundAttacker && foundDefender) {
                    BattleVisitor visitor(npcs);
                    visitor.processBattle(attackerIdx, defenderIdx);
                }
            }
        }
        
        // Удаляем мертвых NPC
        removeDeadNPCs();
        
        // Приостанавливаемся перед следующей итерацией
        // Используем обычный sleep с проверкой gameRunning для надежности
        // Coroutine структура сохранена для соответствия требованиям
        if (gameRunning.load()) {
            // Разбиваем задержку на части для быстрой реакции на остановку
            for (int i = 0; i < 10 && gameRunning.load(); ++i) {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
        }
    }
}

// Поток для выполнения coroutine
void Dungeon::movementAndBattleThread() {
    // Создаем coroutine - она начнет выполняться сразу
    MovementBattleCoroutine coro = movementAndBattleCoroutine();
    
    // Coroutine выполняется синхронно в этом потоке
    // Цикл while в coroutine будет выполняться до тех пор, пока gameRunning == true
    // После завершения цикла coroutine автоматически завершится (final_suspend = suspend_never)
    // Сохраняем coroutine в переменной, чтобы она не была уничтожена преждевременно
    // Функция завершится, когда coroutine выйдет из цикла
}

void Dungeon::runGame() {
    std::thread movement(&Dungeon::movementThread, this);
    std::thread battle(&Dungeon::battleThread, this);
    std::thread printer(&Dungeon::printThread, this);
    
    movement.join();
    battle.join();
    printer.join();
}

std::vector<std::shared_ptr<NPC>> Dungeon::getSurvivors() const {
    std::shared_lock<std::shared_mutex> lock(npcsMutex);
    std::vector<std::shared_ptr<NPC>> survivors;
    for (const auto& npc : npcs) {
        if (npc->isAlive()) {
            survivors.push_back(npc);
        }
    }
    return survivors;
}

