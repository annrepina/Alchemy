#include "PotionTable.h"

int PotionTable::id = 0;

PotionTable::PotionTable()
{
	this->title = "�����";
	this->effectsTable = nullptr;
}

PotionTable::~PotionTable()
{
	clear();
}

void PotionTable::add(Potion* potion)
{
	this->potiontsWithId.emplace(++id, potion);

	notify(id, NEW_ELEMENT);
}

void PotionTable::setEffectsTable(EffectsTable* effectsTable)
{
	this->effectsTable = effectsTable;
}

int PotionTable::hasSuchPotion(Potion* potion)
{
	// ��������� ������
	int key = -1;

	auto mapp = this->potiontsWithId;

	auto beginIter = getStartIterator();
	auto endIter = getEndIterator();



	//Potion* potion1 = beginIter->second;

	int effectId = potion->getEffectId();
	int price = potion->getPrice();
	int power = potion->getPower();

	for (auto i = beginIter; i != endIter; ++i)
	{
		// ���� ��������� �������� ����������
		if (effectId == i->second->getEffectId() && price == i->second->getPrice() && power == i->second->getPower())
		{
			key = i->first;

			break;
		}
	}

	return key;
}

void PotionTable::update(int id, bool isNewElement)
{
}

void PotionTable::update(int id, int previousNumber)
{
}

void PotionTable::update()
{
}

void PotionTable::decreaseNumberOfPotion(int potionId, int number)
{
	Potion* potion = getPotionById(potionId);

	// �������� ����� � ��������� ��� ���-��
	potion->decreaseNumber(number);

	// ���� ���-�� ����� ����� 0, �� ������� ��� �� �������
	if (potion->getNumber() == 0)
	{
		// ������� ���������� ������� �� ����
		notify(potionId, NOT_NEW_ELEMENT);

		// ������� �� map ������ �������
		this->potiontsWithId.erase(potionId);

		// ������� ���� �����
		delete potion;
		potion = nullptr;

		// ��� ��� ���������� ������� ����� �������������� �������� ��������
		notify();
	}
}

map<int, Potion*>::iterator PotionTable::getEndIterator()
{
	// ���������� �������� �� ��������� �������
	return this->potiontsWithId.end();
}

map<int, Potion*>::iterator PotionTable::getStartIterator()
{
	// �������� �� ������ �������
	return this->potiontsWithId.begin();
}

EffectsTable* PotionTable::getEffectsTable()
{
	return this->effectsTable;
}

Potion* PotionTable::getPotionById(int id)
{
	return this->potiontsWithId[id];
}

int PotionTable::getSize()
{
	return this->potiontsWithId.size();
}

//Potion* PotionTable::getSuchPotion(Potion* potion)
//{
//	Potion* potion = nullptr;
//
//	auto beginIter = getStartIterator();
//	auto endIter = getEndIterator();
//
//	int effectId = potion->getEffectId();
//	int price = potion->getPrice();
//	int power = potion->getPower();
//
//	for (auto i = beginIter; i != endIter; ++i)
//	{
//		// ���� ��������� �������� ����������
//		if (effectId == i->second->getEffectId() && price == i->second->getPrice() && power == i->second->getPower())
//		{
//			potion = i->second;
//
//			break;
//		}
//	}
//
//	return potion;
//}

void PotionTable::clear()
{
	for (auto potion : potiontsWithId)
	{
		if (nullptr != potion.second)
		{
			delete potion.second;
			potion.second = nullptr;
		}
	}
}
