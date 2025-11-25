#include <gtest/gtest.h>
#include "Factories.hpp"

TEST(FactoryTest, CreateElf) {
    auto npc = NPCFactory::create("ELF", 10, 20, "legolas");

    EXPECT_EQ(npc->getType(), NPCType::ELF);
    EXPECT_EQ(npc->getName(), "legolas");
    EXPECT_DOUBLE_EQ(npc->getX(), 10);
    EXPECT_DOUBLE_EQ(npc->getY(), 20);
}

TEST(FactoryTest, CreateBandit) {
    auto npc = NPCFactory::create("BANDIT", 5, 7, "bandos");
    EXPECT_EQ(npc->getType(), NPCType::BANDIT);
}

TEST(FactoryTest, CreateSquirrelFromFile) {
    auto npc = FileNPCFactory::createFromLine("SQUIRREL scrat 1 2");
    EXPECT_EQ(npc->getType(), NPCType::SQUIRREL);
    EXPECT_EQ(npc->getName(), "scrat");
}

TEST(FactoryTest, MalformedLineThrows) {
    EXPECT_THROW(FileNPCFactory::createFromLine("ELF legolas 1"), std::runtime_error);
}