#include "Dungeon.hpp"
#include "Observer.hpp"

int main() {
    Dungeon d;

    ConsoleObserver consoleLog;
    FileObserver fileLog;

    d.addObserver(&consoleLog);
    d.addObserver(&fileLog);

    d.addNPC("ELF", 10, 10, "legolas");
    d.addNPC("BANDIT", 11, 10, "harry");
    d.addNPC("SQUIRREL", 12, 10, "scrat");

    d.print();
    d.battle(5.0);

    d.save("dungeon.txt");

    return 0;
}