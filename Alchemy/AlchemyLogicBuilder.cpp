#include "AlchemyLogicBuilder.h"

AlchemyLogicBuilder::AlchemyLogicBuilder() : Builder()
{
	this->effectsTableBuilder = new EffectsTableBuilder();
	this->ingredientsTableBuilder = new IngredientsTableBuilder();
	this->ingredientBuilder = new IngredientBuilder();
}

AlchemyLogicBuilder::~AlchemyLogicBuilder()
{
	clear();
}

void AlchemyLogicBuilder::buildAlchemyProgram()
{
	// ������� ������� ��������
	this->element->setAlchemist(new Alchemist);

	// ������ ������� ��������
	this->effectsTableBuilder->buildTable();

	// ����������� ��������� ������� ��������
	this->element->setEffectsTable(this->effectsTableBuilder->getResult());

	// ��������� ��������� ������������ ������� ��������
	this->ingredientBuilder->setEffectsTable(this->element->getEffectsTable());

	// ��������� ������ ���� ��������
	this->ingredientBuilder->fillEffectId();

	// ������ ��������� ������������
	this->ingredientsTableBuilder->setIngredientBuilder(ingredientBuilder);

	// ������ ������� ������������
	this->ingredientsTableBuilder->buildTable();

	// ����������� ������� ������������
	this->element->setIngredientsTable(ingredientsTableBuilder->getResult());

	// ��������� ����� ������ ������� �����
	this->element->setPotionTable(new PotionTable);

	// ������ ������� �������� ������� �����
	this->element->getPotionTable()->setEffectsTable(this->element->getEffectsTable());
}

void AlchemyLogicBuilder::setEffectsTable(AlchemyLogicWriter* alchemyLogicWriter)
{
	// ��������� ������� �������
	this->effectsTableBuilder->buildTable();

	// ��������� ������� � ���������
	this->element->setEffectsTable(this->effectsTableBuilder->getResult());
}

void AlchemyLogicBuilder::clear()
{
	// �������� �-wb. � �������� ������
	Builder::clear();

	if (nullptr != this->effectsTableBuilder)
	{
		delete this->effectsTableBuilder;
		this->effectsTableBuilder = nullptr;
	}
}