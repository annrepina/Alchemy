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

	BinaryWriter(T& object, string filePath)
		: object(object), filePath(filePath)
	{
	}

	virtual void write(ofstream& stream) const = 0;
		
protected:

	// объект целевого класса
	T& object;

	// Путь к файлу
	string filePath;

	//ofstream stream;

};

