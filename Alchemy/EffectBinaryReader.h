#pragma once
#include "BinaryReader.h"
#include "Effect.h"

// Класс, который читает класс Effect из бинарного файла
class EffectBinaryReader : public BinaryReader<Effect>
{
public:

	// Конструктор по умолчанию
	EffectBinaryReader();

	// Деструктор
	~EffectBinaryReader();

	// Читать из бинарного файла
	Effect* readFromFile(string path, ifstream& stream) override;

private:

	// Очистить память
	void clear() override;
};

