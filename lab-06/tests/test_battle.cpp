#include <gtest/gtest.h>
#include "Dungeon.hpp"
#include "Observer.hpp"
#include <stdexcept>

class TestObserver : public Observer {
public:
    std::vector<std::pair<std::string, std::string>> events;

    void onKill(const std::string& killer, const std::string& victim) override {
        events.emplace_back(killer, victim);
    }
};

TEST(BattleTest, ElfKillsBandit) {
    Dungeon d;
    TestObserver obs;
    d.addObserver(&obs);

    d.addNPC("ELF", 0, 0, "legolas");
    d.addNPC("BANDIT", 0, 1, "harry");

    d.battle(5.0);

    ASSERT_EQ(obs.events.size(), 1);
    EXPECT_EQ(obs.events[0].first, "legolas");
    EXPECT_EQ(obs.events[0].second, "harry");
}

TEST(BattleTest, BanditKillsSquirrel) {
    Dungeon d;
    TestObserver obs;
    d.addObserver(&obs);

    d.addNPC("BANDIT", 0, 0, "razor");
    d.addNPC("SQUIRREL", 0, 1, "scrat");

    d.battle(5.0);

    ASSERT_EQ(obs.events.size(), 1);
    EXPECT_EQ(obs.events[0].first, "razor");
    EXPECT_EQ(obs.events[0].second, "scrat");
}

TEST(BattleTest, SquirrelKillsElf) {
    Dungeon d;
    TestObserver obs;
    d.addObserver(&obs);

    d.addNPC("SQUIRREL", 0, 0, "scrat");
    d.addNPC("ELF", 0, 1, "legolas");

    d.battle(5.0);

    ASSERT_EQ(obs.events.size(), 1);
    EXPECT_EQ(obs.events[0].first, "scrat");
    EXPECT_EQ(obs.events[0].second, "legolas");
}

TEST(BattleTest, SameTypeMutualKill) {
    Dungeon d;
    TestObserver obs;
    d.addObserver(&obs);

    d.addNPC("ELF", 0, 0, "elf1");
    d.addNPC("ELF", 0, 1, "elf2");

    d.battle(5.0);

    ASSERT_EQ(obs.events.size(), 2);
    EXPECT_EQ(obs.events[0].first, "elf1");
    EXPECT_EQ(obs.events[0].second, "elf2");
    EXPECT_EQ(obs.events[1].first, "elf2");
    EXPECT_EQ(obs.events[1].second, "elf1");

    EXPECT_NO_THROW(d.addNPC("ELF", 2, 2, "elf1"));
}

TEST(DungeonValidation, RejectsOutOfBoundsNPC) {
    Dungeon d;
    EXPECT_THROW(d.addNPC("ELF", 600, 0, "longshot"), std::runtime_error);
}

TEST(DungeonValidation, RejectsDuplicateNamesPerType) {
    Dungeon d;
    d.addNPC("BANDIT", 10, 10, "bandos");
    EXPECT_THROW(d.addNPC("BANDIT", 11, 10, "bandos"), std::runtime_error);
}
