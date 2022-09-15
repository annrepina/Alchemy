#pragma once
#include "Ingredient.h"

// ����� - �����
class Potion
{
public:

	// ����������� �� ���������
	Potion();

	// ����������
	~Potion();

#pragma region �������

	// ������ ��� id �������
	void setEffectId(int id);

	// ������ ��� ����
	void setPrice(int price);

	// ������ ��� ���-�� ����� � ������������
	void setNumber(int number);

	// ������ ��� ��������
	void setPower(int power);

#pragma endregion �������

#pragma region �������

	// ������ ��� ���-�� ����� � ������������
	int getNumber();

	// ������ ��� id ������� 
	int getEffectId();

	// ������ ��� ��������
	int getPower();

	// ������ ��� ����
	int getPrice();

#pragma endregion �������

	// ��������� ���-�� �����
	void increaseNumber();

	// ��������� ���-�� ����� �� ������������ �����
	void decreaseNumber(int number);

private:

	// id �������
	int effectId;

	// ����
	int price;

	// ���-��
	int number;

	// �������� �����, ������� ������� �� ������ ��������
	int power;
};