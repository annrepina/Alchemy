#include "AlchemyProgramBuilder.h"

AlchemyProgramBuilder::AlchemyProgramBuilder()
{
	reset();
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
}
