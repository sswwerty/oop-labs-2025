#pragma once
#include <string>

class Observer {
public:
    virtual void onKill(const std::string& killer, const std::string& victim) = 0;
    virtual ~Observer() = default;
};

class ConsoleObserver : public Observer {
public:
    void onKill(const std::string& killer, const std::string& victim) override;
};

class FileObserver : public Observer {
public:
    void onKill(const std::string& killer, const std::string& victim) override;
};
