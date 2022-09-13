#pragma once
#include "BinaryReader.h"
#include "EffectsTable.h"
#include "EffectBinaryReader.h"

// Класс, который читает класс EffectsTable из бинарного файла
class EffectsTableBinaryReader : public BinaryReader<EffectsTable>
{
public:

	// Конструктор по умолчанию
	EffectsTableBinaryReader();

	// Деструктор
	~EffectsTableBinaryReader();

	// Читать из бинарного файла
	EffectsTable* readFromFile(string path, ifstream& stream) override;

private:

	// Очистить память
	void clear() override;
};

