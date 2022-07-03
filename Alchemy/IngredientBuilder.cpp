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
	//reset();

	this->effectsTable = nullptr;
}

//IngredientBuilder::~IngredientBuilder()
//{
//	clear();
//}

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
	string name = chooseIngredientName(lastIngredientNameIndex);

	setName(name);

	int price = randInRange(MIN_PRICE, MAX_PRICE);

	setPrice(price);

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
			// ��������� �� ���������� �� ����� �� �� �����
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

void IngredientBuilder::setName(string name)
{
	this->element->setName(name);
}

void IngredientBuilder::setPrice(int price)
{
	this->element->setPrice(price);
}

void IngredientBuilder::addEffect(int effectId)
{
	this->element->addEffect(effectId);
}

//Ingredient* IngredientBuilder::getResult()
//{
//	Ingredient* result = this->ingredient;
//
//	reset();
//
//	return result;
//}

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

//void IngredientBuilder::reset()
//{
//	this->ingredient = new Ingredient();
//}
//
//void IngredientBuilder::clear()
//{
//	if (this->ingredient != nullptr)
//	{
//		delete this->ingredient;
//		this->ingredient = nullptr;
//	}
//}

void IngredientBuilder::fillEffectId()
{
	int size = this->effectsTable->getSize();

	for (int i = 1; i <= size; ++i)
	{
		this->effectsId.push_back(i);
	}
}
