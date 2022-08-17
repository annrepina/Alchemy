#pragma once
#include <string>
#include <iostream>

using namespace std;

// ��������� ���������� ��������
#define START_LEVEL			10
#define START_UP_CAPITAL	5000

// ������������ ���������� ��������
#define MAX_LEVEL			1000
#define LEVEL_DIVISOR		10		// �������� ��� ���������� ������ ��������

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

	// ������ ��� ��������
	int getCapital();

	int getAlchemistLevel();

	int getSalesmanLevel();

#pragma endregion ������� 

	// ��������� ������� �������� �� 1 
	void increaseAlchemistLevel();

	// ��������� ������� ���������� �� 1 
	void increaseSalesmanLevel();

	// ��������� ������� ���������� �� ������������ ����� 
	void increaseSalesmanLevel(int number);

	// ��������� ������� ������������ �� ��������� �����
	void increaseCapital(int value);

	// ��������� ������� ������������ �� ��������� �����
	void decreaseCapital(int value);

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

	//int alchemistLevelIndicator;

	//int salesmanLevelIndicator;
};

