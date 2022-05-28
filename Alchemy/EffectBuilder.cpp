#include "EffectBuilder.h"
#include "ServiceFunctions.h"

string EffectBuilder::listOfPositiveEffectsNames[NUMBER_OF_POSITIVE_EFFECTS] = {
	"������ �������",
	"�������������� ������ ���",
	"�������������� ��������",
	"�������������� �����",
	"��������� ��������",
	"�����������",
	"��������� ������ ���",
	"��������� ��������",
	"��������� �����",
	"��������� ��������� ��������",
	"��������� ������: ������������",
	"��������� ������: �����",
	"��������� ������: ��������������",
	"��������� ������: ��������� ������",
	"��������� ������: �����������",
	"��������� ������: ���������",
	"��������� ������: �������",
	"��������� ������: ��������� �����",
	"��������� ������: ����������",
	"��������� ������: ��������� ����",
	"��������� ������: ����� �����",
	"��������� ������: ���������� ������",
	"��������� ������: ����������",
	"��������� ������: ����������",
	"��������� ������: ��������",
	"��������� ������: ������ �����",
	"��������� ������������ ����",
	"����������� ������ ���",
	"����������� ��������",
	"����������� �����",
	"������������� �����",
	"������������� ����",
	"������������� ������",
	"������������� �������������",
	"������������� ����",
};

string EffectBuilder::listOfNegativeEffectsNames[NUMBER_OF_NEGATIVE_EFFECTS] = {
	"���������",
	"����������",
	"�������� ���� ������ ���",
	"�������� ���� ��������",
	"�������� ���� �����",
	"����������� ������ ���",
	"����������� ��������",
	"����������� �����",
	"�������",
	"����������� ����������� ������ ���",
	"����������� ����������� �����",
	"�����",
	"���� ������ ���",
	"���� ��������",
	"���� �����",
	"���������� � �����",
	"���������� � ����",
	"���������� � ������",
	"���������� � �������������",
	"���������� � ���",
};

EffectBuilder::EffectBuilder() : Builder()
{
	//reset();
}

//EffectBuilder::~EffectBuilder()
//{
//	clear();
//}

void EffectBuilder::setName(string name)
{
	this->element->setName(name);
}

void EffectBuilder::setIsPositive(bool isPositive)
{
	this->element->setIsPositive(isPositive);
}

void EffectBuilder::buildEffect(int lastIndex, bool IsPositive)
{
	if (IsPositive)
		buildEffect(lastIndex, listOfPositiveEffectsNames, POSITIVE);

	else
		buildEffect(lastIndex, listOfNegativeEffectsNames, NEGATIVE);
}

void EffectBuilder::buildEffect(int lastIndex, string listOfEffects[], bool isPositive)
{
	// �������� �������� ���
	string name = chooseEffectName(lastIndex, listOfEffects);

	// ������������� ���
	setName(name);

	// �������, ��� ������ ����������
	setIsPositive(isPositive);
}

//Effect* EffectBuilder::getResult()
//{
//	Effect* res = this->effect;
//
//	reset();
//
//	return res;
//}

//void EffectBuilder::reset()
//{
//	effect = new Effect;
//}
//
//void EffectBuilder::clear()
//{
//	if (nullptr != this->effect)
//	{
//		delete this->effect;
//		this->effect = nullptr;
//	}
//}

string EffectBuilder::chooseEffectName(int lastIndex, string listOfEffectsNames[])
{
	// �������� �������� ��� �� ������
	int numberOfName = randInRange(0, lastIndex);

	// ����������� ������ ��������� ���
	string name = listOfEffectsNames[numberOfName];

	// ������� ��������� � ��������� �������
	swap(listOfEffectsNames[numberOfName], listOfEffectsNames[lastIndex]);

	// ���������� ���
	return name;
}


