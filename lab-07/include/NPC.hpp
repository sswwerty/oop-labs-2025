#pragma once
#include <string>
#include <memory>
#include <mutex>
#include <shared_mutex>
#include <atomic>

class Visitor; // forward declaration

enum class NPCType {
    ORC = 0,
    SQUIRREL = 1,
    DRUID = 2,
    ELF = 3,
    DRAGON = 4,
    BEAR = 5,
    BANDIT = 6,
    WEREWOLF = 7,
    PRINCESS = 8,
    TOAD = 9,
    SLAVER = 10,
    PEGASUS = 11,
    BITTERN = 12,
    DESMAN = 13,
    BULL = 14,
    KNIGHT = 15
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

// Все типы NPC
class Orc : public NPC {
public:
    Orc(double x, double y, const std::string& name)
        : NPC(x, y, name, NPCType::ORC) {}
    void accept(Visitor& v) override;
};

class Squirrel : public NPC {
public:
    Squirrel(double x, double y, const std::string& name)
        : NPC(x, y, name, NPCType::SQUIRREL) {}
    void accept(Visitor& v) override;
};

class Druid : public NPC {
public:
    Druid(double x, double y, const std::string& name)
        : NPC(x, y, name, NPCType::DRUID) {}
    void accept(Visitor& v) override;
};

class Elf : public NPC {
public:
    Elf(double x, double y, const std::string& name)
        : NPC(x, y, name, NPCType::ELF) {}
    void accept(Visitor& v) override;
};

class Dragon : public NPC {
public:
    Dragon(double x, double y, const std::string& name)
        : NPC(x, y, name, NPCType::DRAGON) {}
    void accept(Visitor& v) override;
};

class Bear : public NPC {
public:
    Bear(double x, double y, const std::string& name)
        : NPC(x, y, name, NPCType::BEAR) {}
    void accept(Visitor& v) override;
};

class Bandit : public NPC {
public:
    Bandit(double x, double y, const std::string& name)
        : NPC(x, y, name, NPCType::BANDIT) {}
    void accept(Visitor& v) override;
};

class Werewolf : public NPC {
public:
    Werewolf(double x, double y, const std::string& name)
        : NPC(x, y, name, NPCType::WEREWOLF) {}
    void accept(Visitor& v) override;
};

class Princess : public NPC {
public:
    Princess(double x, double y, const std::string& name)
        : NPC(x, y, name, NPCType::PRINCESS) {}
    void accept(Visitor& v) override;
};

class Toad : public NPC {
public:
    Toad(double x, double y, const std::string& name)
        : NPC(x, y, name, NPCType::TOAD) {}
    void accept(Visitor& v) override;
};

class Slaver : public NPC {
public:
    Slaver(double x, double y, const std::string& name)
        : NPC(x, y, name, NPCType::SLAVER) {}
    void accept(Visitor& v) override;
};

class Pegasus : public NPC {
public:
    Pegasus(double x, double y, const std::string& name)
        : NPC(x, y, name, NPCType::PEGASUS) {}
    void accept(Visitor& v) override;
};

class Bittern : public NPC {
public:
    Bittern(double x, double y, const std::string& name)
        : NPC(x, y, name, NPCType::BITTERN) {}
    void accept(Visitor& v) override;
};

class Desman : public NPC {
public:
    Desman(double x, double y, const std::string& name)
        : NPC(x, y, name, NPCType::DESMAN) {}
    void accept(Visitor& v) override;
};

class Bull : public NPC {
public:
    Bull(double x, double y, const std::string& name)
        : NPC(x, y, name, NPCType::BULL) {}
    void accept(Visitor& v) override;
};

class Knight : public NPC {
public:
    Knight(double x, double y, const std::string& name)
        : NPC(x, y, name, NPCType::KNIGHT) {}
    void accept(Visitor& v) override;
};

