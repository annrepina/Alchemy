#pragma once
#include "IngredientsTable.h"
#include "IngredientBuilder.h"
#include "AlchemyLogicWriter.h"
#include "AlchemyTableBuilder.h"

// Строитель таблицы ингредиентов
class IngredientsTableBuilder : public AlchemyTableBuilder<IngredientsTable>
{
public:

	// Конструктор по умолчанию
	IngredientsTableBuilder();

	// Деструктор
	~IngredientsTableBuilder() override;

	// Сеттер строителя ингредиентов
	void setIngredientBuilder(IngredientBuilder* ingredientBuilder);

	// Построить ингредиент
	void buildTable() override;

private:

	// Строитель ингредиентов
	IngredientBuilder* ingredientBuilder;

	// Чистит память
	void clear() override;

	// Добавить ингредиенты в таблицу
	void addIngredients(int numberOfIngredients);
};
