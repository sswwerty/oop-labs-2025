#pragma once
#include <string>
#include <memory>
#include <mutex>
#include <shared_mutex>
#include <atomic>

class Visitor; // forward declaration

enum class NPCType {
    ELF = 0,
    SQUIRREL = 1,
    BANDIT = 2
};

class NPC {
protected:
    double x, y;
    std::string name;
    NPCType type;
    std::atomic<bool> alive{true};
    mutable std::shared_mutex positionMutex; // для shared_lock при чтении позиции

public:
    NPC(double x, double y, const std::string& name, NPCType t)
        : x(x), y(y), name(name), type(t) {}
    virtual ~NPC() = default;

    double getX() const;
    double getY() const;
    void setX(double newX);
    void setY(double newY);
    std::string getName() const { return name; }
    NPCType getType() const { return type; }
    bool isAlive() const { return alive.load(); }
    void kill() { alive.store(false); }
    
    // Расстояние хода для данного типа NPC
    double getMoveDistance() const;
    // Расстояние убийства для данного типа NPC
    double getKillDistance() const;

    virtual void accept(Visitor& v) = 0;
};

// Типы NPC (только Эльфы, Белки и Разбойники)
class Elf : public NPC {
public:
    Elf(double x, double y, const std::string& name)
        : NPC(x, y, name, NPCType::ELF) {}
    void accept(Visitor& v) override;
};

class Squirrel : public NPC {
public:
    Squirrel(double x, double y, const std::string& name)
        : NPC(x, y, name, NPCType::SQUIRREL) {}
    void accept(Visitor& v) override;
};

class Bandit : public NPC {
public:
    Bandit(double x, double y, const std::string& name)
        : NPC(x, y, name, NPCType::BANDIT) {}
    void accept(Visitor& v) override;
};

