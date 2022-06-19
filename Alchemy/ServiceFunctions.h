#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define NO_DELIM	-1

// Генерирует случайные числа в диапазоне заданном пользователем min - max
int randInRange(const int min, const int max);

// Разделяет строку на подстроки по символу разделителю
vector <string> splitForOneDelim(string str, char delim);

// Находит индексы делиметров и заносит их в вектор
int findDelimetrIndexes(const char delimetr, const size_t length, const string str);

// Попытаться привести к инту
bool tryParseToInt(string& value);

template<typename T>
void fillMap(map<int, T> map, vector <T> vector, int startKey, int border)
{
	// Заполняем ассоциативный массив
	for (int i = 0; i < border; ++i, ++startKey)
	{
		map.emplace(startKey, vector[i]);
	}
}