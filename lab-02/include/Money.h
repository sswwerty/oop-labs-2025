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
    std::vector<unsigned char> digits_; // цифры, младшие сначала
    void removeLeadingZeros() const;    // вспомогательный (иммутабельный)
    static int compare(const Money &a, const Money &b);

public:
    // Конструкторы
    Money(); 
    explicit Money(const std::string &value);

    // Методы арифметики (иммутабельные)
    Money add(const Money &other) const;
    Money subtract(const Money &other) const;
    Money addAssign(const Money &other) const;       // возвращает новый объект
    Money subtractAssign(const Money &other) const;  // возвращает новый объект
    Money copy() const;

    // Методы сравнения
    bool isEqual(const Money &other) const;
    bool isGreater(const Money &other) const;
    bool isLess(const Money &other) const;

    // Преобразование в строку
    std::string toString() const;
};

#endif // MONEY_H