#pragma once
#include "BinaryWriter.h"
#include "Effect.h"

// Класс,который пишет класс Effect в файл в бинарном виде
class EffectBinaryWriter : public BinaryWriter<Effect>
{
public:

	// Конструктор по умолчанию
	EffectBinaryWriter();

	// Деструктор
	~EffectBinaryWriter() override;

	// Пишет в файл в бинарном виде
	void write(ofstream& stream, string filePath, Effect* effect) const override;

private:

	// Чистит память
	void clear() override;
};

