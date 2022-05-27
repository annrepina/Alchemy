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

IngredientBuilder::IngredientBuilder()
{
	reset();

	this->effectsTable = nullptr;
}

IngredientBuilder::~IngredientBuilder()
{
	clear();
}

void IngredientBuilder::setEffectsTable(EffectsTable* effectsTable)
{
	this->effectsTable = effectsTable;
}

void IngredientBuilder::buildIngredient(int lastIngredientNameIndex, int& lastEffectIndex)
{
	string name = chooseIngredientName(lastIngredientNameIndex);

	setName(name);

	int price = randInRange(MIN_PRICE, MAX_PRICE);

	//int price = generatePrice();

	setPrice(price);

	for (int i = 0; i < NUMBER_OF_EFFECTS; ++i, --lastEffectIndex)
	{
		int id = randInRange(0, lastEffectIndex);

		addEffect(id);
	}
}

void IngredientBuilder::setName(string name)
{
	this->ingredient->setName(name);
}

void IngredientBuilder::setPrice(float price)
{
	this->ingredient->setPrice(price);
}

void IngredientBuilder::addEffect(int effectId)
{
	this->ingredient->addEffect(effectId);
}

Ingredient* IngredientBuilder::getResult()
{
	Ingredient* result = this->ingredient;

	reset();

	return result;
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

int IngredientBuilder::generatePrice()
{
	int price = randInRange(MIN_PRICE, MAX_PRICE);

	return price;
}

void IngredientBuilder::reset()
{
	this->ingredient = new Ingredient();
}

void IngredientBuilder::clear()
{
	if (this->ingredient != nullptr)
	{
		delete this->ingredient;
		this->ingredient = nullptr;
	}
}
