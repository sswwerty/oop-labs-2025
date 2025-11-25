#include "Factories.hpp"
#include <sstream>
#include <stdexcept>

std::shared_ptr<NPC> NPCFactory::create(const std::string& type,
                                        double x, double y,
                                        const std::string& name) {
    if (type == "SQUIRREL") return std::make_shared<Squirrel>(x, y, name);
    if (type == "ELF")      return std::make_shared<Elf>(x, y, name);
    if (type == "BANDIT")   return std::make_shared<Bandit>(x, y, name);
    throw std::runtime_error("Unknown NPC type");
}

std::shared_ptr<NPC> FileNPCFactory::createFromLine(const std::string& line) {
    std::stringstream ss(line);
    std::string type, name;
    double x, y;
    if (!(ss >> type >> name >> x >> y)) {
        throw std::runtime_error("Malformed NPC entry: " + line);
    }
    std::string leftover;
    if (ss >> leftover) {
        throw std::runtime_error("Too many tokens in NPC entry: " + line);
    }
    return NPCFactory::create(type, x, y, name);
}
