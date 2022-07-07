#pragma once
#include "Builder.h"
#include "Potion.h"
#include "Ingredient.h"
#include "Alchemist.h"

#define COEFFICIENT_OF_POWER			3		// Коэффициент мощности зелья
#define COEFFICIENT_OF_PRICE			2		// Коэффициент цены зелья

class PotionBuilder : public Builder<Potion>
{
public:

	PotionBuilder();

	void buildPotion(Ingredient* ingredient1, Ingredient* ingredient2, Alchemist* alchemist);

private:

	// коэффициент мощности зелья
	static int coefficientOfPower;

	// коэффициент цены зелья
	static int coefficientOfPrice;
};

