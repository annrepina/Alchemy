#include "ServiceFunctions.h"

int randInRange(const int min, const int max)
{
	int randomNumber;

	// Присваивает randomNumber случайное число в диапазоне min - max
	randomNumber = min + rand() % (max + 1 - min);

	// Возвращает randomNumber
	return randomNumber;
}

vector<string> splitForOneDelim(string str, char delim)
{
	// Вектор с подстроками
	vector <string> subStrings;

	// Временный экземпляр
	string temp = str;

	// длина строки
	size_t length = str.size();

	// Если строка не нулевая
	if (0ULL < length)
	{
		int delimetrIndex = findDelimetrIndexes(delim, length, str);

		// delimetrIndex равен -1, то выходим из функции
		if (NO_DELIM == delimetrIndex)
		{
			return subStrings;
		}

		// Строка 1 и 2
		string str1 = "";
		string str2 = "";

		for (int i = 0; i < delimetrIndex; ++i)
		{
			str1 += str[i];
		}

		subStrings.push_back(str1);

		for (int i = delimetrIndex + 1; i < length; ++i)
		{
			str2 += str[i];
		}

		subStrings.push_back(str2);

		return subStrings;
	}

	// если строка пустая возвращаем пустой массив
	return subStrings;
}

int findDelimetrIndexes(const char delimetr, const size_t length, const string str)
{
	// Индекс делиметра
	size_t delimetrIndex = -1;

	for (size_t i = 0ULL; i < length; ++i)
	{
		// если находим нужный элемент, записываем его индекс
		if (delimetr == str[i])
		{
			delimetrIndex = i;

			break;
		}
	}

	return delimetrIndex;
}


bool tryParseToInt(string value)
{
	bool res = true;

	//cin >> value;

	// содержит в себе индекс первого символа не являющегося цифрой
	size_t nonDigitIndex;

	// ищет первое несовпадение с 0123456789, на тот случай, если пользователь ввел символ не цифру
	nonDigitIndex = value.find_first_not_of("0123456789");

	// если нашли хоть одну не цифру в строке (string::npos = -1)
	if (nonDigitIndex != string::npos)
	{
		res = false;
	}

	return res;
}