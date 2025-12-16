#include "Factories.hpp"
#include <stdexcept>

std::shared_ptr<NPC> NPCFactory::create(const std::string& type,
                                        double x, double y,
                                        const std::string& name) {
    if (type == "ELF") return std::make_shared<Elf>(x, y, name);
    if (type == "SQUIRREL") return std::make_shared<Squirrel>(x, y, name);
    if (type == "BANDIT") return std::make_shared<Bandit>(x, y, name);
    throw std::runtime_error("Unknown NPC type: " + type);
}


