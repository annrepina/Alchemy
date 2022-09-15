#pragma once
#include "BinaryWriter.h"
#include "EffectsTable.h"
#include "EffectBinaryWriter.h"

// Класс,который пишет класс EffectsTable в файл в бинарном виде
class EffectsTableBinaryWriter : public BinaryWriter<EffectsTable>
{
public:

	// Конструктор по умолчанию
	EffectsTableBinaryWriter();

	// Деструктор
	~EffectsTableBinaryWriter() override;

	// Пишет в файл в бинарном виде
	void write(ofstream& stream, string filePath, EffectsTable* effectsTable) const override;

protected:

	// Чистит память
	void clear() override;

	// Класс,который пишет класс Effect в файл в бинарном виде
	EffectBinaryWriter* effectBinaryWriter;
};

