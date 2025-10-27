#include "Money.h"
#include <cctype>
#include <algorithm>

Money::Money() : digits_({0}) {}

Money::Money(const std::string &value) {
    if (value.empty()) {
        throw InvalidMoneyException("Пустая строка недопустима");
    }

    // Проверка корректности и запись в обратном порядке
    for (auto it = value.rbegin(); it != value.rend(); ++it) {
        if (!std::isdigit(*it)) {
            throw InvalidMoneyException("Неверный символ в числе");
        }
        digits_.push_back(*it - '0');
    }

    // Удаляем ведущие нули
    removeLeadingZeros();
}

void Money::removeLeadingZeros() const {
    // const метод, но модифицирует внутренние данные через const_cast
    auto *self = const_cast<Money *>(this);
    while (self->digits_.size() > 1 && self->digits_.back() == 0) {
        self->digits_.pop_back();
    }
}

int Money::compare(const Money &a, const Money &b) {
    if (a.digits_.size() != b.digits_.size()) {
        return (a.digits_.size() < b.digits_.size()) ? -1 : 1;
    }

    for (size_t i = a.digits_.size(); i-- > 0;) {
        if (a.digits_[i] != b.digits_[i]) {
            return (a.digits_[i] < b.digits_[i]) ? -1 : 1;
        }
    }
    return 0;
}

Money Money::add(const Money &other) const {
    Money result;
    result.digits_.clear();

    size_t maxSize = std::max(digits_.size(), other.digits_.size());
    unsigned char carry = 0;

    for (size_t i = 0; i < maxSize; ++i) {
        unsigned char sum = carry;
        if (i < digits_.size()) sum += digits_[i];
        if (i < other.digits_.size()) sum += other.digits_[i];
        carry = sum / 10;
        result.digits_.push_back(sum % 10);
    }

    if (carry) result.digits_.push_back(carry);
    result.removeLeadingZeros();
    return result;
}

Money Money::subtract(const Money &other) const {
    if (compare(*this, other) < 0) {
        throw NegativeResultException("Результат отрицательный");
    }

    Money result;
    result.digits_.clear();

    unsigned char borrow = 0;
    for (size_t i = 0; i < digits_.size(); ++i) {
        int diff = digits_[i] - borrow - (i < other.digits_.size() ? other.digits_[i] : 0);
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result.digits_.push_back(diff);
    }

    result.removeLeadingZeros();
    return result;
}

Money Money::addAssign(const Money &other) const {
    return add(other); // возвращает новый объект
}

Money Money::subtractAssign(const Money &other) const {
    return subtract(other); // возвращает новый объект
}

Money Money::copy() const {
    return Money(this->toString());
}

bool Money::isEqual(const Money &other) const {
    return compare(*this, other) == 0;
}

bool Money::isGreater(const Money &other) const {
    return compare(*this, other) > 0;
}

bool Money::isLess(const Money &other) const {
    return compare(*this, other) < 0;
}

std::string Money::toString() const {
    std::string result;
    for (auto it = digits_.rbegin(); it != digits_.rend(); ++it) {
        result += static_cast<char>(*it + '0');
    }
    return result;
}