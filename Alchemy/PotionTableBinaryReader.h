#pragma once
#include "BinaryReader.h"
#include "PotionTable.h"
#include "PotionBinaryReader.h"
#include "EffectsTableBinaryReader.h"

// Класс, который читает класс PotionTable из бинарного файла
class PotionTableBinaryReader : public BinaryReader<PotionTable>
{
public:

	// КОнструктор по умолчанию
	PotionTableBinaryReader();

	// Деструктор
	~PotionTableBinaryReader() override;

	// Читать из бинарного файла
	PotionTable* readFromFile(string path, ifstream& stream) override;

private:

	// Очистить память
	void clear() override;

	// Класс, который читает класс Potion из бинарного файла
	PotionBinaryReader* potionBinaryReader;

	// Класс, который читает класс EffectsTable из бинарного файла
	EffectsTableBinaryReader* effectsTableBinaryReader;
};

