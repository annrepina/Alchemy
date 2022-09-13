#pragma once
#include "Alchemist.h"
#include "BinaryReader.h"
#include <fstream>

// Класс, который читает класс Alchemist из бинарного файла
class AlchemistBinaryReader : public BinaryReader<Alchemist>
{
public: 

	// Конструктор
	AlchemistBinaryReader();

	// Деструктор
	~AlchemistBinaryReader();

	// Читать из бинарного файла
	Alchemist* readFromFile(string path, ifstream& stream) override;

private:

	// Очистить память
	void clear() override;
};

