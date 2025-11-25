#include "NPC.hpp"
#include "Visitor.hpp"

void Squirrel::accept(Visitor& v) { v.visit(*this); }
void Elf::accept(Visitor& v) { v.visit(*this); }
void Bandit::accept(Visitor& v) { v.visit(*this); }