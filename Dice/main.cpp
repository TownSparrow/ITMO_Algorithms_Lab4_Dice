#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "dice.h"

// Функция для расчета распределений и сохранения в .csv файл
void CalculateAndSaveDistributions() {
  // Параметры для расчета
  const std::vector<std::string> dicesStringed = { "1d6", "2d6", "3d6", "1d10", "2d10", "3d10" };
  const int num_rolls = 10000;  // количество бросков для каждого распределения

  for (const auto& specification : dicesStringed) {
    // Определение диапазона значений для данной спецификации
    int max_result = 0;
    std::vector<Dice> dice = ParseString(specification);
    for (const auto& dice : dice) {
      max_result += dice.count * dice.sides + dice.modifier;
    }

    // Расчет частоты выпадений
    std::vector<int> frequencies(max_result + 1, 0);
    for (int i = 0; i < num_rolls; ++i) {
      int result = GetDice(specification);
      frequencies[result]++;
    }

    // Формирование имени файла
    std::string filename = specification + ".csv";

    // Сохранение результатов
    std::ofstream file(filename);
    if (file.is_open()) {
      file << "Result,Frequency,Probability\n";
      for (int i = 0; i < frequencies.size(); ++i) {
        if (frequencies[i] > 0) {
          double probability = static_cast<double>(frequencies[i]) / num_rolls;
          file << i << "," << frequencies[i] << "," << probability << "\n";
        }
      }
      //file.close(); // люблю избыточность, а вы?
      std::cout << "Saved distribution for " << specification << " to " << filename << std::endl;
    }
    else {
      std::cerr << "Failed to open file: " << filename << std::endl;
    }
  }
}

int main() {
  // Инициализация генератора случайных чисел
  srand(time(NULL));
  
  // Расчет распределений для выборки и сохранение в виде .csv-файлов
  CalculateAndSaveDistributions();

  // Пример использования
  // std::cout << GetDice("2d6+2,3d10") << std::endl;
  std::cout << GetDice("2d6+2,3d10") << std::endl;

  // Распределение вероятностей (для 40 значений)
  std::vector<int> result(40, 0);

  for (int i = 0; i < 1000; ++i) {
    result[GetDice("3d10")]++;
  }

  // Вывод нормализованных данных
  std::cout << "___________" << std::endl;
  double total = 0;
  for (auto i : result) {
    total += i;
  }
  for (auto i : result) {
    std::cout << i / total << " " << std::endl;
  }

  return 0;
}