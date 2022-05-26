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

EffectBuilder::EffectBuilder()
{
	reset();
}

EffectBuilder::~EffectBuilder()
{
	clear();
}

void EffectBuilder::setName(string name)
{
	this->effect->setName(name);
}

void EffectBuilder::setIsPositive(bool isPositive)
{
	this->effect->setIsPositive(isPositive);
}

void EffectBuilder::buildEffect(int lastIndex, string listOfEffectsNames[], bool isPositive)
{
	// �������� �������� ���
	string name = chooseEffectName(lastIndex, listOfEffectsNames);

	// ������������� ���
	setName(name);

	// �������, ��� ������ ����������
	setIsPositive(isPositive);
}

void EffectBuilder::buildPositiveEffect(int lastIndex)
{
	// �������� �������� ���
	string name = chooseEffectName(lastIndex, listOfPositiveEffectsNames);

	// ������������� ���
	setName(name);

	// �������, ��� ������ ����������
	setIsPositive(true);
}

void EffectBuilder::buildNegativeEffect(int lastIndex)
{
	// �������� �������� ���
	string name = chooseEffectName(lastIndex, listOfNegativeEffectsNames);

	// ������������� ���
	setName(name);

	// �������, ��� ������ ����������
	setIsPositive(false);
}

Effect* EffectBuilder::getResult()
{
	Effect* res = this->effect;

	reset();

	return res;
}

void EffectBuilder::reset()
{
	effect = new Effect;
}

void EffectBuilder::clear()
{
	if (nullptr != this->effect)
	{
		delete this->effect;
		this->effect = nullptr;
	}
}

string EffectBuilder::chooseEffectName(int lastIndex, string listOfEffectsNames[])
{
	// �������� �������� ��� �� ������
	int NumberOfName = randInRange(0, lastIndex);

	// ����������� ������ ��������� ���
	string name = listOfEffectsNames[NumberOfName];

	// ������� ��������� � ��������� �������
	swap(listOfEffectsNames[NumberOfName], listOfEffectsNames[lastIndex]);

	// ���������� ���
	return name;
}


