#include "AlchemyLogicBuilder.h"

AlchemyLogicBuilder::AlchemyLogicBuilder() : Builder()
{
	/*reset();*/

	this->effectsTableBuilder = new EffectsTableBuilder();

	this->ingredientsTableBuilder = new IngredientsTableBuilder();

	this->ingredientBuilder = new IngredientBuilder();
}

AlchemyLogicBuilder::~AlchemyLogicBuilder()
{
	clear();
}

//AlchemyProgram* AlchemyProgramBuilder::getResult()
//{
//	AlchemyProgram* res = this->alchemyProgram;
//
//	reset();
//
//	return res;
//}

void AlchemyLogicBuilder::buildAlchemyProgram(AlchemyLogicWriter* alchemyLogicWriter)
{
	/// ������

	// ���� ��� ������




	// ������� ������� ��������
	this->element->setAlchemist(new Alchemist);

	// ������ ������� ��������
	this->effectsTableBuilder->buildTable(alchemyLogicWriter);

	// ����������� ��������� ������� ��������
	this->element->setEffectsTable(this->effectsTableBuilder->getResult());

	// ��������� ��������� ������������ ������� ��������
	this->ingredientBuilder->setEffectsTable(this->element->getEffectsTable());

	// ��������� ������ ���� ��������
	this->ingredientBuilder->fillEffectId();

	// ������ ��������� ������������
	this->ingredientsTableBuilder->setIngredientBuilder(ingredientBuilder);

	// ������ ������� ������������
	this->ingredientsTableBuilder->buildTable(alchemyLogicWriter);

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
	this->effectsTableBuilder->buildTable(alchemyLogicWriter);

	// ��������� ������� � ���������
	this->element->setEffectsTable(this->effectsTableBuilder->getResult());
}

//void AlchemyProgramBuilder::reset()
//{
//	this->alchemyProgram = new AlchemyProgram();
//}

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
