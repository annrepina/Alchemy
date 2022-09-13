#pragma once
#include "BinaryWriter.h"
#include "PotionTable.h"
#include "PotionBinaryWriter.h"
#include "EffectsTableBinaryWriter.h"

// Класс,который пишет класс PotionTable в файл в бинарном виде
class PotionTableBinaryWriter : public BinaryWriter<PotionTable>
{
public:

	// Конструктор по умолчанию
	PotionTableBinaryWriter();

	// Деструктор
	~PotionTableBinaryWriter();

	// Пишет в файл в бинарном виде
	void write(ofstream& stream, string path, PotionTable* potionTable) const override;

private:

	// Чистит память
	void clear() override;

	// Класс,который пишет класс Potion в файл в бинарном виде
	PotionBinaryWriter* potionBinaryWriter;

	// Класс,который пишет класс EffectsTable в файл в бинарном виде
	EffectsTableBinaryWriter* effectsTableBinaryWriter;
};