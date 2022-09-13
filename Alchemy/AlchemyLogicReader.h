#pragma once
#include "BinaryReader.h"
#include "AlchemyLogic.h"
#include "AlchemistBinaryReader.h"
#include "EffectsTableBinaryReader.h"
#include "IngredientsTableBinaryReader.h"
#include "PotionTableBinaryReader.h"

// Класс, который читает класс AlchemyLogic из бинарного файла
class AlchemyLogicReader : public BinaryReader< AlchemyLogic>
{
public:

	// Конструктор по умолчанию
	AlchemyLogicReader();

	// Деструктор
	~AlchemyLogicReader();

	// Читать из бинарного файла
	AlchemyLogic* readFromFile(string path, ifstream& stream);

private:

	// Класс, который читает класс Alchemist из бинарного файла
	AlchemistBinaryReader* alchemistBinaryReader;

	// Класс, который читает класс EffectsTable из бинарного файла
	EffectsTableBinaryReader* effectsTableBinaryReader;

	// Класс, который читает класс IngredientsTable из бинарного файла
	IngredientsTableBinaryReader* ingredientsTableBinaryReader;

	// Класс, который читает класс PotionTable из бинарного файла
	PotionTableBinaryReader* potionTableBinaryReader;

	// Очистить память
	void clear() override;
};

