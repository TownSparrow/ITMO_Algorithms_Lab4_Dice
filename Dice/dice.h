#pragma once

#include <string>
#include <vector>

// ��������� ��������� �����
struct Dice {
  int count;      // ���������� ������
  int sides;      // ���������� ������
  int modifier;   // �����������

  // �����������
  Dice(int c, int s, int m);
};

// ��������� ������ ����� ��������� �����
int PlayDice(int sides);

// ��������� ������ ���������� ������ (� ������ ������������)
int PlayDices(const std::vector<Dice>& dice);

// ������� ������
std::vector<Dice> ParseString(const std::string& specification);

// ��������� ������������ � ����� �������
int GetDice(const std::string& specification);