#pragma once
#include "Effect.h"

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

	// Получить результат строительства
	Effect* getResult();

private:

	// Экземпляр эффекта
	Effect* effect;

	// Сбросить до начальных установок
	void reset();

	// Чистит память (неиспользованный эффект)
	void clear();
};

