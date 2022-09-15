#pragma once
#include "Effect.h"
#include "IObservable.h"
#include <map>

#define NUMBER_OF_EFFECTS			2		// ���-�� ��������

#define MIN_PRICE					4		// ����������� ���� �����������
#define MAX_PRICE					135		// ������������ ���� �����������

#define UNKNOWN						false	// ����������� ������������ ������	
#define KNOWN						true	// ��������� ������������ ������

// ����� ����������
class Ingredient : public IObservable
{
public:

	// ����������� �� ���������
	Ingredient();

	// ����������
	~Ingredient();

	// ������
	void print();

#pragma region �������

	// ������ �������� �� ������������ ������ � ������� ����������� �� ������ �������
	bool getEffectIsKnown(int number);

	// �������� �������� �� ������ �������������� ������� effectsId
	map<int, bool>::iterator getBeginIteratorOfEffectsId();

	// �������� �������� �� ����� �������������� ������� effectsId
	map<int, bool>::iterator getEndIteratorOfEffectsId();
	
	// �������� ���
	string getName();

	// �������� ���-��
	int getNumber();

	// ������ ��� ����
	int getPrice();

	// ������ ��� ���-�� ��������
	int getNumberOfEffects();

#pragma endregion �������

#pragma region �������

	// ������ ��� �����
	void setName(string name);

	// ������ ��� ����
	void setPrice(float price);

	// ������ ��� ���-��
	void setNumber(int number);

	// ������� ������ �� id
	void openEffect(int id);

	// ������� ������ ��������
	void openEffectRandomly();

#pragma endregion �������

	// �������� ������
	void addEffect(int effectId);

	// �������� ������ � ���������������
	void addEffectWithCharacteristic(int effectId, bool characteristic);

	// ��������� ���-�� ����������� �� ����� �����
	void increaseNumber(int number);

	// ��������� ���-�� ������������ �� ����� �����
	void decreaseNumber(int number);

private:

	// ���-�� ��������
	const static int numberOfEffects = NUMBER_OF_EFFECTS;
	
	// �������� �����������
	string name;

	// ���� �� ����������
	int price;

	// ���-�� ����������� � ��������
	int number;

	// ������ �������� �� 2� ������������ � �� �������� ����������� ������
	map<int, bool> effectsId;
};

