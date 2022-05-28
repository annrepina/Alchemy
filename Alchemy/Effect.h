#pragma once
#include <string>

using namespace std;

// ������ �����������
class Effect
{
public:

#pragma region ������������

	// ����������� �� ���������
	Effect();

	// ����������� � �����������
	Effect(string name, bool isPositive);

	// ����������
	~Effect();

#pragma endregion ������������

#pragma region �������

	// ������ �����
	void setName(string name);

	// ������ ��� �������
	void setIsPositive(bool isPositive);

#pragma endregion �������

	// �������� ���
	string getName();

	// ������ �������
	void print();

private:

	//// ������� ��������
	//static int counter;

	//// id �������
	//int id;

	// �������� �������
	string name;

	// ������ ����������, ���������� ���������� ��� ���������� ������
	bool isPositive;


};

