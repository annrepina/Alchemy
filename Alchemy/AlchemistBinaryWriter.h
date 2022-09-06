#pragma once
#include "Alchemist.h"
#include <fstream>

class AlchemistBinaryWriter
{
public:

	AlchemistBinaryWriter(Alchemist& alchemist, string filePath);

	void write() const;

private:

	// объект целевого класса
	Alchemist& alchemist;

	// Путь к файлу
	string filePath;
};
