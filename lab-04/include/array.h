#ifndef ARRAY_H
#define ARRAY_H

#include <memory>
#include <utility>
#include <stdexcept>
#include <iostream>

// Динамический массив, использующий std::shared_ptr<T[]> как внутренний буфер
template<typename T>
class Array {
std::shared_ptr<T[]> data;
size_t sz = 0;
size_t cap = 0;

public:
Array() = default;
explicit Array(size_t capacity) { reserve(capacity); }

size_t size() const noexcept { return sz; }
size_t capacity() const noexcept { return cap; }

void reserve(size_t new_cap) {
if (new_cap <= cap) return;
std::shared_ptr<T[]> new_buf(new T[new_cap]);
// перемещаем существующие элементы
for (size_t i = 0; i < sz; ++i) {
new_buf[i] = std::move(data[i]);
}
data = std::move(new_buf);
cap = new_cap;
}

void push_back(const T& v) {
if (sz >= cap) reserve(cap == 0 ? 4 : cap * 2);
data[sz++] = v; // копирование
}
void push_back(T&& v) {
if (sz >= cap) reserve(cap == 0 ? 4 : cap * 2);
data[sz++] = std::move(v);
}

void remove_at(size_t idx) {
if (idx >= sz) throw std::out_of_range("Index out of range");
for (size_t i = idx; i + 1 < sz; ++i) data[i] = std::move(data[i+1]);
data[--sz] = T{}; // опционально: сбросить последний элемент
}

T& operator[](size_t i) {
if (i >= sz) throw std::out_of_range("Index out of range");
return data[i];
}
const T& operator[](size_t i) const {
if (i >= sz) throw std::out_of_range("Index out of range");
return data[i];
}

void clear() { sz = 0; }
};

#endif