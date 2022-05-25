#pragma once
#include <string>
#include <iostream>

using namespace std;

// ��������� ���������� ��������
#define START_LEVEL			0
#define START_UP_CAPITAL	100

// ������������ ���������� ��������
#define MAX_LEVEL			100

// ����� �������
class Alchemist
{
public:

	// ����������� �� ���������
	Alchemist();

#pragma region �������

	// ������ ��� �����
	void setName(string name);

	// ������ ��� ������ ��������
	void setAlchemistLevel(int alchemistLevel);

	// ������ ��� ������ ��������
	void setSalesmanLevel(int salesmanLevel);

#pragma endregion �������

#pragma region �������

	// ������ ��� �����
	string getName();

#pragma endregion ������� 

	// ��������� ������� �������� �� 1 
	void increaseAlchemistLevel();

	// ��������� ������� ���������� �� 1 
	void increaseSalesmanLevel();

	// ��������� ������� ������������ �� ��������� �����
	void increaseCapital(int value);

	// ������ ������ ��������
	void print();

private:

	// ��� ��������
	string name;

	// ������� ��������
	int alchemistLevel;

	// ������� ��������
	int salesmanLevel;

	// ������� ������������
	int �apital;
};

