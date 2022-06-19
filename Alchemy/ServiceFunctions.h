#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define NO_DELIM	-1

// ���������� ��������� ����� � ��������� �������� ������������� min - max
int randInRange(const int min, const int max);

// ��������� ������ �� ��������� �� ������� �����������
vector <string> splitForOneDelim(string str, char delim);

// ������� ������� ���������� � ������� �� � ������
int findDelimetrIndexes(const char delimetr, const size_t length, const string str);

// ���������� �������� � ����
bool tryParseToInt(string& value);

template<typename T>
void fillMap(map<int, T> map, vector <T> vector, int startKey, int border)
{
	// ��������� ������������� ������
	for (int i = 0; i < border; ++i, ++startKey)
	{
		map.emplace(startKey, vector[i]);
	}
}