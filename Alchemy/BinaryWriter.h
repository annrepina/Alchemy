#pragma once
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

// Класс, который пишет другой класс в файл в бинарном виде
template <typename T>
class BinaryWriter
{
public:

	// Конструктор по умолчанию
	BinaryWriter()
	{

	}

	// Виртуальный деструктор
	virtual ~BinaryWriter()
	{
	}

	// Писать в файл
	virtual void write(ofstream& stream, string filePath, T* object) const
	{
		if ("" == filePath)
			throw "Invalid file path";

		// ЕСЛИ СТРИМ НЕ ОТКРЫТ, открываем для записи
		if (!stream.is_open())
			stream.open(filePath, ios::out | ios::binary | ios::trunc);
	}

protected:

	// Писать строку в файл
	virtual void writeString(ofstream& stream, string text) const
	{
		// размер текста
		size_t textSize = text.size();

		// пишем размер текста
		stream.write((char*)(&textSize), sizeof(textSize));

		// пишем сам текст
		stream << text;
	}

	// писать инт в файл
	virtual void writeInt(ofstream& stream, int value) const
	{
		// пишем значение
		stream.write((char*)(&value), sizeof(value));
	}

	// писать bool в файл
	virtual void writeBool(ofstream& stream, bool value) const
	{
		// пишем значение 
		stream.write((char*)(&value), sizeof(value));
	}

	// очистить память
	virtual void clear() = 0;
};

