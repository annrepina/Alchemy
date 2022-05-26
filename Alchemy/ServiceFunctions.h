#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#define NO_DELIM	-1

// √енерирует случайные числа в диапазоне заданном пользователем min - max
int randInRange(const int MIN, const int MAX);

// –аздел€ет строку на подстроки по символу разделителю
vector <string> splitForOneDelim(string str, char delim);

// Ќаходит индексы делиметров и заносит их в вектор
int findDelimetrIndexes(const char delimetr, const size_t length, const string str);
