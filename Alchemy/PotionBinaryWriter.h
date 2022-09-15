#pragma once
#include "BinaryWriter.h"
#include "Potion.h"

// Класс,который пишет класс Potion в файл в бинарном виде
class PotionBinaryWriter : public BinaryWriter<Potion>
{
public:

	// Конструктор по умолчанию
	PotionBinaryWriter();

	// Деструктор
	~PotionBinaryWriter() override;

	// Пишет в файл в бинарном виде
	void write(ofstream& stream, string path, Potion* potion) const override;

private:

	// Чистит память
	void clear() override;

};