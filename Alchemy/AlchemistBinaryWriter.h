#pragma once
#include "BinaryWriter.h"
#include "Alchemist.h"
#include <fstream>

// Класс,который пишет класс AlchemistBinary в файл в бинарном виде
class AlchemistBinaryWriter : public BinaryWriter<Alchemist>
{
public:

	// КОнструктор по умолчанию
	AlchemistBinaryWriter();

	// деструктор
	~AlchemistBinaryWriter();

	// Писать в файл в бинарном виде
	void write(ofstream& stream, string filePath, Alchemist* alchemist) const override;

private:

	// очистить память
	void clear() override;

};