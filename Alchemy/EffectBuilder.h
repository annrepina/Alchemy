#pragma once
#include "Effect.h"
#include "Builder.h"

#define TOTAL_NUMBER_OF_EFFECTS		55		// Общее кол-во эффектов
#define NUMBER_OF_POSITIVE_EFFECTS	35		// Кол-во позитивных эффектов
#define NUMBER_OF_NEGATIVE_EFFECTS	20		// Кол-во негативных эффектов

#define POSITIVE					true	// Позитивный эффект
#define NEGATIVE					false	// Негативный эффект

// Строитель эффектов
class EffectBuilder : public Builder<Effect>
{
public:

	// Конструктор по умолчанию
	EffectBuilder();

	// Сеттер для имени
	void setName(string name);

	// Сеттер для пременной означающей положительный ли эффект
	void setIsPositive(bool isPositive);

	// Создать эффект
	void buildEffect(int lastIndex, bool IsPositive);

	// Создать эффект - перегрузка
	void buildEffect(int lastIndex, string listOfEffects[], bool isPositive);

private:

	// Выбрать имя эффекту
	string chooseEffectName(int lastIndex, string listOfEffectsNames[]);

	// Список имен положительных эффектов
	static string listOfPositiveEffectsNames[NUMBER_OF_POSITIVE_EFFECTS];

	// Список имен отрицательных эффектов
	static string listOfNegativeEffectsNames[NUMBER_OF_NEGATIVE_EFFECTS];
};