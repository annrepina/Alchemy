#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

#define NO_DELIM		-1
#define PIVOT_INDEX		0	// ������ ������
#define MIN_SIZE		2	// ����������� ��������� ������ ������� ��� ����������
#define NO_POSITION		-1	// ��� ����� ������� � ����������

// ���������� ��������� ����� � ��������� �������� ������������� min - max
int randInRange(const int min, const int max);

// ��������� ������ �� ��������� �� ������� �����������
vector <string> splitForOneDelim(string str, char delim);

// ������� ������� ���������� � ������� �� � ������
int findDelimetrIndexes(const char delimetr, const size_t length, const string str);

// ���������� �������� � ����
bool tryParseToInt(string value);

// ��������� ������������� ������ ������� �� �������
template<typename T>
void fillMap(map<int, T>& map, vector <T> vector, int startKey, int border)
{
	// ���� ������������� ������ ������
	if (map.empty())
	{
		// ��������� ������������� ������
		for (int i = 0; i < border; ++i, ++startKey)
		{
			map.emplace(startKey, vector[i]);
		}
	}

}

// ������� ����������
template<typename T>
void quickSort(T* vec, int size)
{
	// ����������� �������, � ������� ����� ����������� ��������� ������ ��������� - ������ ��������� ������� �������
	T pivot = vec[PIVOT_INDEX];

	// ������ ���������� ������ �������� - ��������� ������ �������
	auto left = 0;

	// ������ ���������� ������� �������� - ��������� ������ �������
	auto right = size - 1;

	// ���� ������������, ���� �� ���������� break
	while (true)
	{
		// ���� ������ ������� ������ ������
		// ��������� ������ ������ �� ��� ���, ���� �������� ������ ���� ����� ������ � ���� ������ ������ ������ ������
		while (right > left && vec[right] >= pivot)
		{
			--right;
		}

		// ���� ����� ������� ������ ������
		// ����������� ����� ������ �� ��� ���, ���� �������� ������ ���� ����� ������ � ���� ����� ������� ������ �������
		while (left < right && vec[left] <= pivot)
		{
			++left;
		}

		// ���� ������� ���������� �� ����� ������
		if (right == left)
		{
			// ������ ������� ����� � �������, �� ������� ������� ����������, 
			//����� ����� ����� ����� ���� ������� � �������� ����� �� 2 �����
			swap(vec[PIVOT_INDEX], vec[right]);

			break;
		}

		// ���� left � right �� ����������� ������� ��������������� ��������, 
		// ����������� �������� ������ ������ - �����, � ������ - ������
		swap(vec[left], vec[right]);
	}

	// ���� ������ ������ ������ ��� ����� ������������ ������� �������, ������� ����� �������������, 
	// ������ ����� �������� ��������������� 2 ��� ������ �����������
	// �������� ������� �� �� ����������
	if (right >= MIN_SIZE)
	{
		// �������� ��������� �� ������ ��� ��������� - �������� � 0�� �������� ��������� �������
		// ������ ������� ����� ������� ������� ��������
		quickSort(vec, right);
	}

	// ���� ������ ������ ������ ������� ������� ����� 2, ������ ������ �������� ��������������� 2 ��� ������ �����������
	// �������� ������� �� �� ����������
	if (right < size - 2)
	{
		// �������� ��������� �� ������ + right + 1. �.�. ������ ����� �.�. �������� �������� ������������ ����� �������
		// ������ ������� ����� ��������� ������� �� ������� right � 1
		quickSort(vec + right + 1, size - right - 1);
	}
}

template<typename T>
int binarySearch(vector<T> vec, int key)
{
	// ������ �������� ����� (�������� -1, ���� ����� �� ������� � �������)
	int index = NO_POSITION;

	// ������ ���������� �������� ������ � ����������
	int min = 0;

	int size = vec.size();

	// ������ ��������� �������� ������ � ����������
	// ��������� ������������ ������ ��� ������ �������, �.�. �������� �� ��, ��� ����� ������� ��� � ����� �������
	// ������ ��� ���� ��������� max = ARRAY_SIZE - 1, �.�. ��������� ������ 19, �� �������� �� ������� ��������� �������. 
	// �.�. 18+19=37, 37/2 = 18, � 19�� ������� ������� �� ���������.
	int max = size;

	for (int i = 0; i <= size / 2; ++i)
	{
		if (key == vec[(min + max) / 2])
		{
			index = (min + max) / 2;
			break;
		}

		else if (key > vec[(min + max) / 2])
		{
			min = (min + max) / 2;
		}

		else
		{
			max = (min + max) / 2;
		}
	}

	return index;
}

// ������ ������ ������ ���� ����� ������ ��� ����� ��������
bool firstStringIsBiggerOrEqualSecond(string str1, string str2);

//  ������ ������ ���� ����� ������ ��� ����� ��������
bool firstStringIsSmallerOrEqualSecond(string str1, string str2);

// ����� �� ��������� ��� ����� ��������
bool hasSubstring(string mainString, string subString);