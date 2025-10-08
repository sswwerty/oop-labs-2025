#ifndef MONEY_H
#define MONEY_H

#include <string>
#include <stdexcept>

class Money {
private:
    unsigned char* digits;  // digits[0] — единицы копеек, digits[1] — десятки копеек, и т.д.
    size_t size;

    void normalize(); // удалить ведущие нули
    static int compareAbsolute(const Money& a, const Money& b);

public:
    // Исключения
    class InvalidMoneyException : public std::invalid_argument {
    public:
        InvalidMoneyException(const std::string& msg) : std::invalid_argument(msg) {}
    };

    class NegativeResultException : public std::domain_error {
    public:
        NegativeResultException() : std::domain_error("Result of subtraction is negative") {}
    };

    // Конструкторы
    Money();
    explicit Money(const std::string& str);
    Money(const Money& other);
    Money& operator=(const Money& other);
    ~Money();

    // Арифметика
    Money operator+(const Money& other) const;
    Money operator-(const Money& other) const;

    // Сравнения
    bool operator==(const Money& other) const;
    bool operator!=(const Money& other) const;
    bool operator<(const Money& other) const;
    bool operator<=(const Money& other) const;
    bool operator>(const Money& other) const;
    bool operator>=(const Money& other) const;

    // Вспомогательные методы
    std::string toString() const;
};

#endif // MONEY_H