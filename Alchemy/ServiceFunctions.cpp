#include "ServiceFunctions.h"

int randInRange(const int MIN, const int MAX)
{
	int randomNumber;

	// ����������� randomNumber ��������� ����� � ��������� min - max
	randomNumber = MIN + rand() % (MAX + 1 - MIN);

	// ���������� randomNumber
	return randomNumber;
}

vector<string> splitForOneDelim(string str, char delim)
{
	// ������ � �����������
	vector <string> subStrings;

	// ��������� ���������
	string temp = str;

	// ����� ������
	size_t length = str.size();

	// ���� ������ �� �������
	if (0ULL < length)
	{
		int delimetrIndex = findDelimetrIndexes(delim, length, str);

		// delimetrIndex ����� -1, �� ������� �� �������
		if (NO_DELIM == delimetrIndex)
		{
			return subStrings;
		}

		// ������ 1 � 2
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

	// ���� ������ ������ ���������� ������ ������
	return subStrings;
}

int findDelimetrIndexes(const char delimetr, const size_t length, const string str)
{
	// ������ ���������
	size_t delimetrIndex = -1;

	for (size_t i = 0ULL; i < length; ++i)
	{
		// ���� ������� ������ �������, ���������� ��� ������
		if (delimetr == str[i])
		{
			delimetrIndex = i;

			break;
		}
	}

	return delimetrIndex;
}