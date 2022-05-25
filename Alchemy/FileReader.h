#pragma once
#include <string>
#include <fstream>

using namespace std;

class FileReader
{
public:

	FileReader(string filePath);

	// Чтение файла
	string read();

private:

	// Путь к файлу
	string filePath;

};

