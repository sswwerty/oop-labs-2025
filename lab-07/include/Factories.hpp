#pragma once
#include "NPC.hpp"
#include <memory>
#include <string>

class NPCFactory {
public:
    static std::shared_ptr<NPC> create(const std::string& type,
                                       double x, double y,
                                       const std::string& name);
};

