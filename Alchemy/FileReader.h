#pragma once
#include <string>
#include <fstream>

using namespace std;

class FileReader
{
public:

	FileReader(string filePath);

	// ������ �����
	string read();

private:

	// ���� � �����
	string filePath;

};

