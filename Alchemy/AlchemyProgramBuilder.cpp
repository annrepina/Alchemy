#include "AlchemyProgramBuilder.h"

AlchemyProgramBuilder::AlchemyProgramBuilder()
{
	reset();

	this->effectsTableBuilder = new EffectsTableBuilder();

	this->ingredientsTableBuilder = new IngredientsTableBuilder();

	this->ingredientBuilder = new IngredientBuilder();
}

AlchemyProgramBuilder::~AlchemyProgramBuilder()
{
	clear();
}

AlchemyProgram* AlchemyProgramBuilder::getResult()
{
	AlchemyProgram* res = this->alchemyProgram;

	reset();

	return res;
}

void AlchemyProgramBuilder::buildAlchemyProgram(AlchemyProgramParser* alchemyProgramParse)
{
	/// ������

	// ���� ��� ������

	// ������ ������� ��������
	this->effectsTableBuilder->buildEffectsTable(alchemyProgramParse);

	// ����������� ��������� ������� ��������
	this->alchemyProgram->setEffectsTable(this->effectsTableBuilder->getResult());

	// ��������� ��������� ������������ ������� ��������
	this->ingredientBuilder->setEffectsTable(this->alchemyProgram->getEffectsTable());

	// ��������� ������ ���� ��������
	this->ingredientBuilder->fillEffectId();

	// ������ ��������� ������������
	this->ingredientsTableBuilder->setIngredientBuilder(ingredientBuilder);

	// ������ ������� ������������
	this->ingredientsTableBuilder->buildIngredientsTable(alchemyProgramParse);

	// ����������� ������� ������������
	this->alchemyProgram->setIngredientsTable(ingredientsTableBuilder->getResult());

}

void AlchemyProgramBuilder::setEffectsTable(AlchemyProgramParser* alchemyProgramParse)
{
	// ��������� ������� �������
	this->effectsTableBuilder->buildEffectsTable(alchemyProgramParse);

	// ��������� ������� � ���������
	this->alchemyProgram->setEffectsTable(this->effectsTableBuilder->getResult());
}

void AlchemyProgramBuilder::reset()
{
	this->alchemyProgram = new AlchemyProgram();
}

void AlchemyProgramBuilder::clear()
{
	if (nullptr != this->alchemyProgram)
	{
		delete this->alchemyProgram;
		this->alchemyProgram = nullptr;
	}

	if (nullptr != this->effectsTableBuilder)
	{
		delete this->effectsTableBuilder;
		this->effectsTableBuilder = nullptr;
	}
}
