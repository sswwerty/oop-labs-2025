#include "Money.h"
#include <vector>
#include <algorithm>
#include <cctype>
#include <sstream>

// Вспомогательная функция: парсинг строки в вектор цифр (в прямом порядке)
static std::vector<unsigned char> parseToDigitVector(const std::string& str) {
    if (str.empty()) {
        throw Money::InvalidMoneyException("Empty string");
    }

    size_t dotPos = str.find('.');
    std::string rublesPart, kopecksPart;

    if (dotPos == std::string::npos) {
        rublesPart = str;
        kopecksPart = "00";
    } else {
        rublesPart = str.substr(0, dotPos);
        kopecksPart = str.substr(dotPos + 1);

        if (kopecksPart.length() > 2) {
            throw Money::InvalidMoneyException("More than 2 digits after decimal point");
        }
        if (kopecksPart.length() == 1) {
        kopecksPart = kopecksPart + "0";
    }
    }

    // Проверка: только цифры
    for (char c : rublesPart) {
        if (!std::isdigit(static_cast<unsigned char>(c))) {
            throw Money::InvalidMoneyException("Invalid character in rubles part");
        }
    }
    for (char c : kopecksPart) {
        if (!std::isdigit(static_cast<unsigned char>(c))) {
            throw Money::InvalidMoneyException("Invalid character in kopecks part");
        }
    }

    // Убираем ведущие нули в рублях (но оставляем хотя бы один, если всё нули)
    if (rublesPart.empty()) rublesPart = "0";
    size_t start = 0;
    while (start < rublesPart.length() - 1 && rublesPart[start] == '0') {
        ++start;
    }
    rublesPart = rublesPart.substr(start);

    std::vector<unsigned char> digits;
    for (char c : rublesPart) {
        digits.push_back(static_cast<unsigned char>(c - '0'));
    }
    for (char c : kopecksPart) {
        digits.push_back(static_cast<unsigned char>(c - '0'));
    }

    return digits;
}

// Конструктор по умолчанию — 0.00
Money::Money() : size(2) {
    digits = new unsigned char[2]{0, 0};
}

// Конструктор из строки
Money::Money(const std::string& str) {
    auto vec = parseToDigitVector(str);
    size = vec.size();
    digits = new unsigned char[size];
    for (size_t i = 0; i < size; ++i) {
        digits[i] = vec[i];
    }
    // Переворачиваем: младший индекс → младшая цифра
    std::reverse(digits, digits + size);
}

// Копирующий конструктор
Money::Money(const Money& other) : size(other.size) {
    digits = new unsigned char[size];
    for (size_t i = 0; i < size; ++i) {
        digits[i] = other.digits[i];
    }
}

// Оператор присваивания
Money& Money::operator=(const Money& other) {
    if (this != &other) {
        delete[] digits;
        size = other.size;
        digits = new unsigned char[size];
        for (size_t i = 0; i < size; ++i) {
            digits[i] = other.digits[i];
        }
    }
    return *this;
}

// Деструктор
Money::~Money() {
    delete[] digits;
}

// Нормализация: удаление ведущих нулей (старших разрядов)
void Money::normalize() {
    if (size == 0) return;

    // Находим последний ненулевой разряд (с конца массива)
    size_t lastNonZero = size - 1;
    while (lastNonZero > 0 && digits[lastNonZero] == 0) {
        --lastNonZero;
    }

    // Если всё нули — оставляем один ноль
    if (lastNonZero == 0 && digits[0] == 0) {
        delete[] digits;
        digits = new unsigned char[1]{0};
        size = 1;
        return;
    }

    // Обрезаем массив
    size_t newSize = lastNonZero + 1;
    unsigned char* newDigits = new unsigned char[newSize];
    for (size_t i = 0; i < newSize; ++i) {
        newDigits[i] = digits[i];
    }
    delete[] digits;
    digits = newDigits;
    size = newSize;
}

// Сравнение по модулю (без знака, но у нас нет отрицательных)
int Money::compareAbsolute(const Money& a, const Money& b) {
    if (a.size != b.size) {
        return a.size > b.size ? 1 : -1;
    }
    for (int i = static_cast<int>(a.size) - 1; i >= 0; --i) {
        if (a.digits[i] != b.digits[i]) {
            return a.digits[i] > b.digits[i] ? 1 : -1;
        }
    }
    return 0;
}

// Сложение
Money Money::operator+(const Money& other) const {
    size_t maxSize = std::max(size, other.size);
    unsigned char* result = new unsigned char[maxSize + 1];
    size_t resultSize = 0;
    int carry = 0;

    for (size_t i = 0; i < maxSize || carry; ++i) {
        int d1 = (i < size) ? digits[i] : 0;
        int d2 = (i < other.size) ? other.digits[i] : 0;
        int sum = d1 + d2 + carry;
        result[resultSize++] = static_cast<unsigned char>(sum % 10);
        carry = sum / 10;
    }

    Money res;
    delete[] res.digits;
    res.digits = result;
    res.size = resultSize;
    res.normalize();
    return res;
}

// Вычитание (только если this >= other)
Money Money::operator-(const Money& other) const {
    if (compareAbsolute(*this, other) < 0) {
        throw NegativeResultException();
    }

    unsigned char* result = new unsigned char[size]; // this >= other → результат не длиннее this
    size_t resultSize = 0;
    int borrow = 0;

    for (size_t i = 0; i < size; ++i) {
        int d1 = digits[i];
        int d2 = (i < other.size) ? other.digits[i] : 0;
        int diff = d1 - d2 - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result[resultSize++] = static_cast<unsigned char>(diff);
    }

    Money res;
    delete[] res.digits;
    res.digits = result;
    res.size = resultSize;
    res.normalize();
    return res;
}

// Сравнения
bool Money::operator==(const Money& other) const {
    if (size != other.size) return false;
    for (size_t i = 0; i < size; ++i) {
        if (digits[i] != other.digits[i]) return false;
    }
    return true;
}

bool Money::operator!=(const Money& other) const {
    return !(*this == other);
}

bool Money::operator<(const Money& other) const {
    return compareAbsolute(*this, other) < 0;
}

bool Money::operator<=(const Money& other) const {
    return (*this < other) || (*this == other);
}

bool Money::operator>(const Money& other) const {
    return !(*this <= other);
}

bool Money::operator>=(const Money& other) const {
    return !(*this < other);
}

// Преобразование в строку
std::string Money::toString() const {
    if (size == 0) return "0.00";

    std::string full;
    // Восстанавливаем прямой порядок
    for (int i = static_cast<int>(size) - 1; i >= 0; --i) {
        full += ('0' + digits[i]);
    }

    // Добавляем точку перед двумя последними цифрами (копейки)
    if (full.length() < 2) {
        // Дополняем нулями спереди
        while (full.length() < 2) {
            full = "0" + full;
        }
    }

    std::string rubles = full.substr(0, full.length() - 2);
    std::string kopecks = full.substr(full.length() - 2);

    if (rubles.empty()) rubles = "0";

    return rubles + "." + kopecks;
}