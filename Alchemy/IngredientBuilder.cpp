#include "IngredientBuilder.h"
#include "ServiceFunctions.h"

string IngredientBuilder::listOfIngredientsNames[NUMBER_OF_INGREDIENTS] = {
	"���������� �����",
	"���� ������ �����",
	"�������",
	"��������� ����",
	"�������� �����",
	"�������� �������",
	"������� ����",
	"��������� ���",
	"���������� ������",
	"����� �����������",
	"�������� ������",
	"���������� ��������",
	"���� ���������",
	"����� ������",
	"������� ���������",
	"���������� �����",
	"������� ��������� ����",
	"���������",
	"������ ���������",
	"��� ������",
	"���� �������� ����������",
	"���� ����-������",
	"������ �����",
	"������� ���������",
	"������ ��������� �����",
	"���� ���������",
	"���� �������",
	"������ �������",
	"������� ����",
	"�������� �����",
	"����� ������� ��������",
	"����� �������",
	"����� ����� �������",
	"������� ����",
	"�������",
	"������� ���������",
	"������ �����",
	"����� ����",
	"��������� ���������",
	"��������� ����",
	"�������� �����",
	"������� ����",
	"���� ���������",
	"�������� ������",
	"�������� ����",
	"������� �����",
	"�������",
	"�������� ����",
	"��������� ��������",
	"����� ��������",
	"�����",
	"������ ����",
	"������ �����",
	"����� �������",
	"����� �������",
	"�������� ����",
	"���� �������",
	"������",
	"�����",
	"�������� ������",
	"�������",
	"���������� ����",
	"���������� ����",
	"������ ������",
	"����������� �����",
	"����� ��������",
	"������������ �����������",
	"������� �����",
	"������� ������",
	"����",
	"���� �������",
	"���������� ������",
	"�������� ������ �������",
	"������ ���������",
	"�������� �������",
	"��� �������",
	"����� ��������",
	"��������",
	"������������ ������",
	"��������� ����",
	"������",
	"����������",
	"����� ����-������",
	"����������",
	"���������� ���",
	"����� �������������",
	"�������� �����������",
	"���� �������",
	"���� ������",
	"���� ������",
	"���� ��������� ������",
	"Ƹ���� ���������",
	"����� �������� ������",
	"���������� ������",
	"�������� ������",
	"�������� ����",
	"���� �������",
	"�����������",
	"���� �����",
	"����� ����������",
};

IngredientBuilder::IngredientBuilder() : Builder()
{
	this->effectsTable = nullptr;
}

void IngredientBuilder::setEffectsTable(EffectsTable* effectsTable)
{
	this->effectsTable = effectsTable;
}

int IngredientBuilder::getEffectsTableSize()
{
	return this->effectsTable->getSize();
}

EffectsTable* IngredientBuilder::getEffectsTable()
{
	return this->effectsTable;
}

void IngredientBuilder::buildIngredient(int lastIngredientNameIndex, int& lastEffectIndex)
{
	setNameFromListRandomly(lastIngredientNameIndex);

	setPriceRandomly();

	setEffects(lastEffectIndex);
}

void IngredientBuilder::buildIngredient(string ingredientName, EffectsTable* effectsTable)
{
	this->effectsTable = effectsTable;

	setName(ingredientName);

	setPriceRandomly();

	setEffectsRandomly();
}

void IngredientBuilder::setName(string name)
{
	this->element->setName(name);
}

void IngredientBuilder::setNameFromListRandomly(int lastIngredientNameIndex)
{
	string name = chooseIngredientName(lastIngredientNameIndex);

	setName(name);
}

void IngredientBuilder::setPrice(int price)
{
	this->element->setPrice(price);
}

void IngredientBuilder::setPriceRandomly()
{
	int price = randInRange(MIN_PRICE, MAX_PRICE);

	setPrice(price);
}

void IngredientBuilder::setEffects(int& lastEffectIndex)
{
	// ������� ������ id ��������
	vector<int> tempEffectsId;

	// ���������� ��������
	for (int i = 0; i < NUMBER_OF_EFFECTS; ++i, --lastEffectIndex)
	{
		// ���� ����������� �������, �� �������� �������
		if (0 == lastEffectIndex)
			lastEffectIndex = this->getEffectsTableSize() - 1;

		int idIndex = randInRange(0, lastEffectIndex);

		// ���� ��� ��� �� ������ ������
		if (0 < i)
		{
			// ��������� �� ���������� �� ����� �� �� �����, � ���� ����������
			if (find(tempEffectsId.begin(), tempEffectsId.end(), this->effectsId[idIndex]) != tempEffectsId.end())
			{
				--i;
				++lastEffectIndex;
				continue;
			}
		}

		// ��������� �� ��������� ������ id
		tempEffectsId.push_back(effectsId[idIndex]);

		// ��������� id � ������� ���������
		addEffect(effectsId[idIndex]);

		// ������� �������� � �������
		swap(this->effectsId[idIndex], this->effectsId[lastEffectIndex]);
	}
}

void IngredientBuilder::setEffectsRandomly()
{
	// ������� ��������� ������ id ��������
	vector<int> tempEffectsId;

	// ������������ id ������� 
	int maxEffectId = this->effectsTable->getSize();

	// ���������� ��������
	for (int i = 0; i < NUMBER_OF_EFFECTS; ++i)
	{
		int idIndex = randInRange(1, maxEffectId);

		// ���� ��� ��� �� ������ ������ � ���������� ��������� � ����� ���������
		if (0 < i && tempEffectsId[0] == idIndex)
		{
			--i;
			continue;
		}

		// ��������� �� ��������� ������ id
		tempEffectsId.push_back(idIndex);

		addEffect(idIndex);
	}
}

void IngredientBuilder::addEffect(int effectId)
{
	this->element->addEffect(effectId);
}

string IngredientBuilder::chooseIngredientName(int lastIndex)
{
	// �������� �������� ��� �� ������
	int numberOfName = randInRange(0, lastIndex);

	// ����������� ������ ��������� ���
	string name = listOfIngredientsNames[numberOfName];

	// ������� ��������� � ��������� �������
	swap(listOfIngredientsNames[numberOfName], listOfIngredientsNames[lastIndex]);

	// ���������� ���
	return name;
}

void IngredientBuilder::fillEffectId()
{
	int size = this->effectsTable->getSize();

	for (int i = 1; i <= size; ++i)
	{
		this->effectsId.push_back(i);
	}
}