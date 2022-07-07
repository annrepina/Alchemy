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
