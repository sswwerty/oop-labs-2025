#include "Money.h"
#include <cctype>
#include <algorithm>

Money::Money() : digits_({0}) {}

Money::Money(const std::string &value) {
    if (value.empty()) {
        throw InvalidMoneyException("Пустая строка недопустима");
    }

    // Разделяем на рубли и копейки по точке (если есть)
    std::string rubles;
    std::string kopecks;

    size_t dotPos = value.find('.');
    if (dotPos == std::string::npos) {
        // Нет точки: вся строка — цифры, последние 2 — копейки (при необходимости дополним нулями)
        for (char c : value) {
            if (!std::isdigit(static_cast<unsigned char>(c))) {
                throw InvalidMoneyException("Неверный символ в числе");
            }
        }
        if (value.size() <= 2) {
            rubles = "0";
            kopecks = std::string(2 - value.size(), '0') + value;
        } else {
            rubles = value.substr(0, value.size() - 2);
            kopecks = value.substr(value.size() - 2);
        }
    } else {
        // Есть точка: левая часть — рубли, правая — копейки (0..2 цифры)
        rubles = value.substr(0, dotPos);
        kopecks = value.substr(dotPos + 1);

        if (rubles.empty()) rubles = "0";
        for (char c : rubles) {
            if (!std::isdigit(static_cast<unsigned char>(c))) {
                throw InvalidMoneyException("Неверный символ в части рублей");
            }
        }

        if (kopecks.size() > 2) {
            throw InvalidMoneyException("Слишком много знаков копеек");
        }
        for (char c : kopecks) {
            if (!std::isdigit(static_cast<unsigned char>(c))) {
                throw InvalidMoneyException("Неверный символ в части копеек");
            }
        }
        // Дополняем копейки до 2 знаков
        while (kopecks.size() < 2) kopecks.push_back('0');
    }

    // Убираем ведущие нули у рублей (оставляя хотя бы один)
    size_t start = 0;
    while (start + 1 < rubles.size() && rubles[start] == '0') ++start;
    rubles = rubles.substr(start);
    if (rubles.empty()) rubles = "0";

    // Собираем полную строку цифр без точки: rubles + kopecks
    std::string full = rubles + kopecks;

    // Переносим в digits_ в обратном порядке (LSB first)
    digits_.clear();
    digits_.reserve(full.size());
    for (auto it = full.rbegin(); it != full.rend(); ++it) {
        digits_.push_back(static_cast<unsigned char>(*it - '0'));
    }

    removeLeadingZeros();
}

// Правило пяти
Money::Money(const Money &other) : digits_(other.digits_) {}

Money::Money(Money &&other) noexcept : digits_(std::move(other.digits_)) {}

Money &Money::operator=(const Money &other) {
    if (this != &other) {
        digits_ = other.digits_;
    }
    return *this;
}

Money &Money::operator=(Money &&other) noexcept {
    if (this != &other) {
        digits_ = std::move(other.digits_);
    }
    return *this;
}

Money::~Money() = default;

void Money::removeLeadingZeros() {
    while (digits_.size() > 1 && digits_.back() == 0) {
        digits_.pop_back();
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
        result.digits_.push_back(static_cast<unsigned char>(diff));
    }

    result.removeLeadingZeros();
    return result;
}

Money Money::addAssign(const Money &other) const {
    return add(other);
}

Money Money::subtractAssign(const Money &other) const {
    return subtract(other);
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
    // Сформировать строку цифр в прямом порядке
    std::string full;
    full.reserve(digits_.size());
    for (auto it = digits_.rbegin(); it != digits_.rend(); ++it) {
        full += static_cast<char>(*it + '0');
    }

    // Обеспечить минимум 2 цифры (для копеек)
    if (full.size() < 2) {
        full = std::string(2 - full.size(), '0') + full;
    }

    // Разделить на рубли и копейки и поставить точку
    std::string rubles = full.substr(0, full.size() - 2);
    std::string kopecks = full.substr(full.size() - 2);
    if (rubles.empty()) rubles = "0";

    return rubles + "." + kopecks;
}