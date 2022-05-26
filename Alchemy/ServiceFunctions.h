#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define NO_DELIM	-1

// ���������� ��������� ����� � ��������� �������� ������������� min - max
int randInRange(const int MIN, const int MAX);

// ��������� ������ �� ��������� �� ������� �����������
vector <string> splitForOneDelim(string str, char delim);

// ������� ������� ���������� � ������� �� � ������
int findDelimetrIndexes(const char delimetr, const size_t length, const string str);
