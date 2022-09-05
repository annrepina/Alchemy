#include "ServiceFunctions.h"

int randInRange(const int min, const int max)
{
	int randomNumber;

	// ����������� randomNumber ��������� ����� � ��������� min - max
	randomNumber = min + rand() % (max + 1 - min);

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

bool tryParseToInt(string value)
{
	bool res = true;

	//cin >> value;

	// �������� � ���� ������ ������� ������� �� ����������� ������
	size_t nonDigitIndex;

	// ���� ������ ������������ � 0123456789, �� ��� ������, ���� ������������ ���� ������ �� �����
	nonDigitIndex = value.find_first_not_of("0123456789");

	// ���� ����� ���� ���� �� ����� � ������ (string::npos = -1)
	if (nonDigitIndex != string::npos)
	{
		res = false;
	}

	return res;
}

bool firstStringIsBiggerOrEqualSecond(string str1, string str2)
{
	std::transform(str1.begin(), str1.end(), str1.begin(), ::tolower);
	std::transform(str2.begin(), str2.end(), str2.begin(), ::tolower);

	auto a = str1;
	auto v = str2; 

	if (str1 < str2)
		return false;

	else
		return true;
}

bool firstStringIsSmallerOrEqualSecond(string str1, string str2)
{
	std::transform(str1.begin(), str1.end(), str1.begin(), ::tolower);
	std::transform(str2.begin(), str2.end(), str2.begin(), ::tolower);

	if (str1 > str2)
		return false;

	else
		return true;
}

bool hasSubstring(string mainString, string subString)
{
	std::transform(mainString.begin(), mainString.end(), mainString.begin(), ::tolower);
	std::transform(subString.begin(), subString.end(), subString.begin(), ::tolower);

	int substringSize = subString.size();
	int mainStringSize = mainString.size();

	int success = 0;

	for (int i = 0, j = 0; i < mainStringSize; ++i)
	{
		if (mainString[i] == subString[j])
		{
			++success;
			++j;
		}
		else
		{
			success = 0;
			j = 0;
		}

		if (j == substringSize)
			return true;
	}

	return false;
}


