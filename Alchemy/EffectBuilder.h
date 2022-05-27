#pragma once
#include "Effect.h"

#define TOTAL_NUMBER_OF_EFFECTS		55		// Общее кол-во эффектов
#define NUMBER_OF_POSITIVE_EFFECTS	35		// Кол-во позитивных эффектов
#define NUMBER_OF_NEGATIVE_EFFECTS	20		// Кол-во негативных эффектов

#define POSITIVE	true
#define NEGATIVE	false

// Строитель эффектов
class EffectBuilder
{
public:

	// Конструктор по умолчанию
	EffectBuilder();

	// Деструктор
	~EffectBuilder();

	// Сеттер для имени
	void setName(string name);

	// Сеттер для пременной означающей положительный ли эффект
	void setIsPositive(bool isPositive);

	// Создать эффект
	void buildEffect(int lastIndex, bool IsPositive);

	// Создать эффект - перегрузка
	void buildEffect(int lastIndex, string listOfEffects[], bool isPositive);

	//// Создать позитивный эффект
	//void buildPositiveEffect(int lastIndex);

	//// Создать негативныйэффект эффект
	//void buildNegativeEffect(int lastIndex);

	// Получить результат строительства
	Effect* getResult();

private:

	// Экземпляр эффекта
	Effect* effect;

	// Сбросить до начальных установок
	void reset();

	// Чистит память (неиспользованный эффект)
	void clear();

	// Выбрать имя эффекту
	string chooseEffectName(int lastIndex, string listOfEffectsNames[]);

	// Список имен положительных эффектов
	static string listOfPositiveEffectsNames[NUMBER_OF_POSITIVE_EFFECTS];

	// Список имен отрицательных эффектов
	static string listOfNegativeEffectsNames[NUMBER_OF_NEGATIVE_EFFECTS];
};

