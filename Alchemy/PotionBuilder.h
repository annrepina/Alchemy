#pragma once
#include "Builder.h"
#include "Potion.h"
#include "Ingredient.h"

class PotionBuilder : public Builder<Potion>
{
public:

	PotionBuilder();

	void buildPotion(Ingredient* ingredient1, Ingredient* ingredient2);

private:


};

