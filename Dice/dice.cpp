#include "dice.h"
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

// Определения
// Структура игральной кости
Dice::Dice(int c, int s, int m) : count(c), sides(s), modifier(m) {}

// Броскок игральной кости
int PlayDice(int sides) {
  return rand() % sides + 1;
}

// Бросок нескольких игральных костей
int PlayDices(const std::vector<Dice>& dice) {
  int total = 0;
  for (const auto& diсe : dice) {
    for (int i = 0; i < diсe.count; ++i) {
      total += PlayDice(diсe.sides);
    }
    total += diсe.modifier;  // применение модификатора, если он имеется
  }
  return total;
}

// Парсинг строки
std::vector<Dice> ParseString(const std::string& specification) {
  std::vector<Dice> dice;               // вектор, в котором хранятся кости
  std::stringstream ss(specification);  // парсинг строки непосредственно
  std::string part;                     // часть спецификации
  //int count = 0, sides = 0, modifier = 0;
  int count, sides, modifier;

  while (std::getline(ss, part, ',')) {

    count = 0, sides = 0, modifier = 0;

    // Поиск разделителя 'd' между количеством костей и граней
    size_t d_pos = part.find('d');

    if (d_pos == std::string::npos)
      return dice;

    // Извлечение количества костей
    count = std::stoi(part.substr(0, d_pos));

    // Извлечение количества граней
    size_t modifier_pos = part.find_first_of("+-", d_pos);
    
    // Если модификатор отсутствует, то приписываем значение 0
    // Иначе его тоже парсим и записываем
    if (modifier_pos == std::string::npos) {
      sides = std::stoi(part.substr(d_pos + 1));
      modifier = 0;
    } else {
      sides = std::stoi(part.substr(d_pos + 1, modifier_pos - d_pos - 1));
      modifier = std::stoi(part.substr(modifier_pos));
    }

    // Добавление данных в вектор
    dice.push_back(Dice(count, sides, modifier));
  }

  return dice;
}

// Обработка спецификации и вызов функции
int GetDice(const std::string& specification) {
  // Сначала парсинг
  std::vector<Dice> dices = ParseString(specification);
  
  // А потом уже и сама игра в кости!
  return PlayDices(dices);
}