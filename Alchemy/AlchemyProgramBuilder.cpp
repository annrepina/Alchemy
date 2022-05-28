#include "AlchemyProgramBuilder.h"

AlchemyProgramBuilder::AlchemyProgramBuilder() : Builder()
{
	/*reset();*/

	this->effectsTableBuilder = new EffectsTableBuilder();

	this->ingredientsTableBuilder = new IngredientsTableBuilder();

	this->ingredientBuilder = new IngredientBuilder();
}

AlchemyProgramBuilder::~AlchemyProgramBuilder()
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

void AlchemyProgramBuilder::buildAlchemyProgram(AlchemyProgramParser* alchemyProgramParse)
{
	/// ������

	// ���� ��� ������

	// ������ ������� ��������
	this->effectsTableBuilder->buildTable(alchemyProgramParse);

	// ����������� ��������� ������� ��������
	this->element->setEffectsTable(this->effectsTableBuilder->getResult());

	// ��������� ��������� ������������ ������� ��������
	this->ingredientBuilder->setEffectsTable(this->element->getEffectsTable());

	// ��������� ������ ���� ��������
	this->ingredientBuilder->fillEffectId();

	// ������ ��������� ������������
	this->ingredientsTableBuilder->setIngredientBuilder(ingredientBuilder);

	// ������ ������� ������������
	this->ingredientsTableBuilder->buildTable(alchemyProgramParse);

	// ����������� ������� ������������
	this->element->setIngredientsTable(ingredientsTableBuilder->getResult());

}

void AlchemyProgramBuilder::setEffectsTable(AlchemyProgramParser* alchemyProgramParse)
{
	// ��������� ������� �������
	this->effectsTableBuilder->buildTable(alchemyProgramParse);

	// ��������� ������� � ���������
	this->element->setEffectsTable(this->effectsTableBuilder->getResult());
}

//void AlchemyProgramBuilder::reset()
//{
//	this->alchemyProgram = new AlchemyProgram();
//}

void AlchemyProgramBuilder::clear()
{
	// �������� �-wb. � �������� ������
	Builder::clear();

	if (nullptr != this->effectsTableBuilder)
	{
		delete this->effectsTableBuilder;
		this->effectsTableBuilder = nullptr;
	}
}
