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
#include <coroutine>
#include <chrono>
#include <thread>

// Вспомогательный класс для awaitable (приостановка выполнения)
struct SleepAwaitable {
    std::chrono::milliseconds duration;
    
    bool await_ready() const noexcept { 
        return duration.count() <= 0;
    }
    
    void await_suspend(std::coroutine_handle<> h) const {
        // Делаем задержку и сразу возобновляем выполнение
        std::this_thread::sleep_for(duration);
        // Возобновляем выполнение coroutine
        h.resume();
    }
    
    void await_resume() const noexcept {}
};

// Coroutine генератор для объединения перемещения и сражения
class MovementBattleCoroutine {
public:
    struct promise_type {
        MovementBattleCoroutine get_return_object() {
            return MovementBattleCoroutine{
                std::coroutine_handle<promise_type>::from_promise(*this)
            };
        }
        std::suspend_never initial_suspend() { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
        void unhandled_exception() {}
        void return_void() {}
    };
    
    std::coroutine_handle<promise_type> coro;
    
    MovementBattleCoroutine(std::coroutine_handle<promise_type> h) : coro(h) {}
    
    ~MovementBattleCoroutine() {
        // При final_suspend = suspend_never coroutine завершается автоматически
        // Handle становится невалидным, поэтому ничего не делаем
    }
    
    MovementBattleCoroutine(const MovementBattleCoroutine&) = delete;
    MovementBattleCoroutine& operator=(const MovementBattleCoroutine&) = delete;
    
    MovementBattleCoroutine(MovementBattleCoroutine&& other) noexcept 
        : coro(other.coro) {
        other.coro = {};
    }
    
    // Явно не копируем и не перемещаем после создания
};

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
    
    // Coroutine для объединения перемещения и сражения в одном потоке
    MovementBattleCoroutine movementAndBattleCoroutine();
    
    // Поток для выполнения coroutine (перемещение + сражение)
    void movementAndBattleThread();
    
    // Основной поток для вывода карты
    void printThread();
    
    // Старые методы (оставлены для совместимости, но не используются)
    void movementThread();
    void battleThread();
    
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

