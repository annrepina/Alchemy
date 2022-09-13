#pragma once
#include "BinaryWriter.h"
#include "AlchemyLogic.h"
#include "AlchemistBinaryWriter.h"
#include "EffectsTableBinaryWriter.h"
#include "IngredientsTableBinaryWriter.h"
#include "PotionTableBinaryWriter.h"

// Класс,который пишет класс AlchemyLogic в файл в бинарном виде
class AlchemyLogicWriter : public BinaryWriter<AlchemyLogic>
{
public:

	// Конструктор по умолчанию
	AlchemyLogicWriter();

	// Деструктор
	~AlchemyLogicWriter();

	// Пишет в файл в бинарном виде
	void write(ofstream& stream, string filePath, AlchemyLogic* alchemyLogic) const override;

protected:

	// Класс,который пишет класс Alchemist в файл в бинарном виде
	AlchemistBinaryWriter* alchemistBinaryWriter;

	// Класс,который пишет класс EffectsTable в файл в бинарном виде
	EffectsTableBinaryWriter* effectsTableBinaryWriter;

	// Класс,который пишет класс IngredientsTable в файл в бинарном виде
	IngredientsTableBinaryWriter* ingredientsTableBinaryWriter;

	// Класс,который пишет класс PotionTable в файл в бинарном виде
	PotionTableBinaryWriter* potionTableBinaryWriter;

	// Очистить память
	void clear() override;

};