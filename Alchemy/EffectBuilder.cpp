#include "EffectBuilder.h"

EffectBuilder::EffectBuilder()
{
	reset();
}

EffectBuilder::~EffectBuilder()
{
	clear();
}

void EffectBuilder::setName(string name)
{
	this->effect->setName(name);
}

void EffectBuilder::setIsPositive(bool isPositive)
{
	this->effect->setIsPositive(isPositive);
}

Effect* EffectBuilder::getResult()
{
	Effect* res = this->effect;

	reset();

	return res;
}

void EffectBuilder::reset()
{
	effect = new Effect;
}

void EffectBuilder::clear()
{
	if (nullptr != this->effect)
	{
		delete this->effect;
		this->effect = nullptr;
	}
}


