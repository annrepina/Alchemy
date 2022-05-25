#include "FileReader.h"

FileReader::FileReader(string filePath)
{
	this->filePath = filePath;
}

string FileReader::read()
{
	// Сделать проверку имени файла
	if ("" == this->filePath)
	{
		throw "Invalid file path";
	}

	ifstream stream(filePath, ios::in);

	string res;

	char ch;

	// Если файл открыт
	if (stream.is_open())
	{
		while ((ch = stream.get()) != EOF)
		{
			res += ch;
		}
	}

	// Закрываем стрим
	stream.close();

	return res;
}
