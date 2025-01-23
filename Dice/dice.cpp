#include "dice.h"
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

// �����������
// ��������� ��������� �����
Dice::Dice(int c, int s, int m) : count(c), sides(s), modifier(m) {}

// ������� ��������� �����
int PlayDice(int sides) {
  return rand() % sides + 1;
}

// ������ ���������� ��������� ������
int PlayDices(const std::vector<Dice>& dice) {
  int total = 0;
  for (const auto& di�e : dice) {
    for (int i = 0; i < di�e.count; ++i) {
      total += PlayDice(di�e.sides);
    }
    total += di�e.modifier;  // ���������� ������������, ���� �� �������
  }
  return total;
}

// ������� ������
std::vector<Dice> ParseString(const std::string& specification) {
  std::vector<Dice> dice;               // ������, � ������� �������� �����
  std::stringstream ss(specification);  // ������� ������ ���������������
  std::string part;                     // ����� ������������
  //int count = 0, sides = 0, modifier = 0;
  int count, sides, modifier;

  while (std::getline(ss, part, ',')) {

    count = 0, sides = 0, modifier = 0;

    // ����� ����������� 'd' ����� ����������� ������ � ������
    size_t d_pos = part.find('d');

    if (d_pos == std::string::npos)
      return dice;

    // ���������� ���������� ������
    count = std::stoi(part.substr(0, d_pos));

    // ���������� ���������� ������
    size_t modifier_pos = part.find_first_of("+-", d_pos);
    
    // ���� ����������� �����������, �� ����������� �������� 0
    // ����� ��� ���� ������ � ����������
    if (modifier_pos == std::string::npos) {
      sides = std::stoi(part.substr(d_pos + 1));
      modifier = 0;
    } else {
      sides = std::stoi(part.substr(d_pos + 1, modifier_pos - d_pos - 1));
      modifier = std::stoi(part.substr(modifier_pos));
    }

    // ���������� ������ � ������
    dice.push_back(Dice(count, sides, modifier));
  }

  return dice;
}

// ��������� ������������ � ����� �������
int GetDice(const std::string& specification) {
  // ������� �������
  std::vector<Dice> dices = ParseString(specification);
  
  // � ����� ��� � ���� ���� � �����!
  return PlayDices(dices);
}