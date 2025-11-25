#include "Observer.hpp"
#include <iostream>
#include <fstream>

void ConsoleObserver::onKill(const std::string& killer, const std::string& victim) {
    std::cout << "[LOG] " << killer << " killed " << victim << std::endl;
}

void FileObserver::onKill(const std::string& killer, const std::string& victim) {
    std::ofstream log("log.txt", std::ios::app);
    log << killer << " killed " << victim << "\n";
}
