#pragma once
#include "Ingredient.h"
//#include "EffectsTable.h"

// ����� - �����
class Potion
{
public:

	// ����������� �� ���������
	Potion();

	~Potion();

#pragma region �������

	void setEffectId(int id);

	void setPrice(int price);

	void setNumber(int number);

	void setPower(int power);

#pragma endregion �������

#pragma region �������

	int getNumber();

	int getEffectId();

	int getPower();

	int getPrice();

#pragma endregion �������

	// ��������� ���-�� �����
	void increaseNumber();

	// ��������� ���-�� ����� �� 1
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