#pragma once
#include "Builder.h"
#include "Potion.h"
#include "Ingredient.h"
#include "Alchemist.h"

#define COEFFICIENT_OF_POWER			3		// ����������� �������� �����
#define COEFFICIENT_OF_PRICE			2		// ����������� ���� �����

class PotionBuilder : public Builder<Potion>
{
public:

	PotionBuilder();

	void buildPotion(Ingredient* ingredient1, Ingredient* ingredient2, Alchemist* alchemist);

private:

	// ����������� �������� �����
	static int coefficientOfPower;

	// ����������� ���� �����
	static int coefficientOfPrice;
};

