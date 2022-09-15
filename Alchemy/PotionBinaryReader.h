#pragma once
#include "BinaryReader.h"
#include "Potion.h"

// Класс, который читает класс Potion из бинарного файла
class PotionBinaryReader : public BinaryReader<Potion>
{
public:

	// Конструктор по умолчанию
	PotionBinaryReader();

	// Деструктор
	~PotionBinaryReader() override;

	// Читать из бинарного файла
	Potion* readFromFile(string path, ifstream& stream) override;

private:

	// очистить память
	void clear() override;
};

