#ifndef MONEY_H
#define MONEY_H

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

class InvalidMoneyException : public std::runtime_error {
public:
    explicit InvalidMoneyException(const std::string &msg)
        : std::runtime_error(msg) {}
};

class NegativeResultException : public std::runtime_error {
public:
    explicit NegativeResultException(const std::string &msg)
        : std::runtime_error(msg) {}
};

class Money {
private:
    std::vector<unsigned char> digits_;
    void removeLeadingZeros(); // удаляет ведущие нули старших разрядов, оставляя хотя бы один ноль
    static int compare(const Money &a, const Money &b);

public:
    // Конструкторы
    Money(); 
    explicit Money(const std::string &value);

    // Методы арифметики
    Money add(const Money &other) const;
    Money subtract(const Money &other) const;
    Money addAssign(const Money &other) const;
    Money subtractAssign(const Money &other) const;
    Money copy() const;

    // Методы сравнения
    bool isEqual(const Money &other) const;
    bool isGreater(const Money &other) const;
    bool isLess(const Money &other) const;

    // Преобразование в строку (RRR.KK)
    std::string toString() const;
};

#endif