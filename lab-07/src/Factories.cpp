#include "Factories.hpp"
#include <stdexcept>

std::shared_ptr<NPC> NPCFactory::create(const std::string& type,
                                        double x, double y,
                                        const std::string& name) {
    if (type == "ORC") return std::make_shared<Orc>(x, y, name);
    if (type == "SQUIRREL") return std::make_shared<Squirrel>(x, y, name);
    if (type == "DRUID") return std::make_shared<Druid>(x, y, name);
    if (type == "ELF") return std::make_shared<Elf>(x, y, name);
    if (type == "DRAGON") return std::make_shared<Dragon>(x, y, name);
    if (type == "BEAR") return std::make_shared<Bear>(x, y, name);
    if (type == "BANDIT") return std::make_shared<Bandit>(x, y, name);
    if (type == "WEREWOLF") return std::make_shared<Werewolf>(x, y, name);
    if (type == "PRINCESS") return std::make_shared<Princess>(x, y, name);
    if (type == "TOAD") return std::make_shared<Toad>(x, y, name);
    if (type == "SLAVER") return std::make_shared<Slaver>(x, y, name);
    if (type == "PEGASUS") return std::make_shared<Pegasus>(x, y, name);
    if (type == "BITTERN") return std::make_shared<Bittern>(x, y, name);
    if (type == "DESMAN") return std::make_shared<Desman>(x, y, name);
    if (type == "BULL") return std::make_shared<Bull>(x, y, name);
    if (type == "KNIGHT") return std::make_shared<Knight>(x, y, name);
    throw std::runtime_error("Unknown NPC type: " + type);
}


