#pragma once
#include <string>
#include <memory>

class Visitor;

enum class NPCType { SQUIRREL = 0, ELF = 1, BANDIT = 2 };

class NPC {
protected:
    double x, y;
    std::string name;
    NPCType type;

public:
    NPC(double x, double y, const std::string& name, NPCType t)
        : x(x), y(y), name(name), type(t) {}
    virtual ~NPC() = default;

    double getX() const { return x; }
    double getY() const { return y; }
    std::string getName() const { return name; }
    NPCType getType() const { return type; }

    virtual void accept(Visitor& v) = 0;
};

class Squirrel : public NPC {
public:
    Squirrel(double x, double y, const std::string& name)
        : NPC(x, y, name, NPCType::SQUIRREL) {}
    void accept(Visitor& v) override;
};

class Elf : public NPC {
public:
    Elf(double x, double y, const std::string& name)
        : NPC(x, y, name, NPCType::ELF) {}
    void accept(Visitor& v) override;
};

class Bandit : public NPC {
public:
    Bandit(double x, double y, const std::string& name)
        : NPC(x, y, name, NPCType::BANDIT) {}
    void accept(Visitor& v) override;
};
