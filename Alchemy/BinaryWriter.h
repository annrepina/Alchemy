#pragma once
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

template <typename T>
class BinaryWriter
{
public:

	BinaryWriter()
	{

	}

	virtual ~BinaryWriter()
	{
		//clear();
	}

	BinaryWriter(T* object, string filePath)/*
		: object(object), filePath(filePath)*/
	{
		this->object = object;
		this->filePath = filePath;
	}

	virtual void write(ofstream& stream) const
	{
		if ("" == this->filePath)
			throw "Invalid file path";

		// ЕСЛИ СТРИМ НЕ ОТКРЫТ, открываем для записи
		if (!stream.is_open())
			stream.open(filePath, ios::out | ios::binary | ios::trunc);
	}

	void setObject(T* obj)
	{
		this->object = obj;
	}

protected:

	// объект целевого класса
	T* object;

	// Путь к файлу
	string filePath;

	virtual void writeString(ofstream& stream, string text) const
	{
		// размер текста
		auto textSize = text.size();

		// пишем размер текста
		stream.write((char*)(&textSize), sizeof(textSize));

		// пишем сам текст
		stream << text;
	}

	virtual void writeInt(ofstream& stream, int value) const
	{
		// пишем значение
		stream.write((char*)(&value), sizeof(value));
	}

	virtual void writeBool(ofstream& stream, bool value) const
	{
		// пишем значение 
		stream.write((char*)&value, sizeof(value));
	}

	virtual void clear() = 0;
};

