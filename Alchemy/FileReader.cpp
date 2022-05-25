#include "FileReader.h"

FileReader::FileReader(string filePath)
{
	this->filePath = filePath;
}

string FileReader::read()
{
	// ������� �������� ����� �����
	if ("" == this->filePath)
	{
		throw "Invalid file path";
	}

	ifstream stream(filePath, ios::in);

	string res;

	char ch;

	// ���� ���� ������
	if (stream.is_open())
	{
		while ((ch = stream.get()) != EOF)
		{
			res += ch;
		}
	}

	// ��������� �����
	stream.close();

	return res;
}
