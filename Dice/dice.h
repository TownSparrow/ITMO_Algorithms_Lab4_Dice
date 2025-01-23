#pragma once

#include <string>
#include <vector>

// Структура игральной кости
struct Dice {
  int count;      // Количество костей
  int sides;      // Количество граней
  int modifier;   // Модификатор

  // Конструктор
  Dice(int c, int s, int m);
};

// Симуляция броска одной игральной кости
int PlayDice(int sides);

// Симуляция броска нескольких костей (с учётом модификатора)
int PlayDices(const std::vector<Dice>& dice);

// Парсинг строки
std::vector<Dice> ParseString(const std::string& specification);

// Обработка спецификации и вызов функции
int GetDice(const std::string& specification);