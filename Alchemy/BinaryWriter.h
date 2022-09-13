#pragma once
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

// �����, ������� ����� ������ ����� � ���� � �������� ����
template <typename T>
class BinaryWriter
{
public:

	// ����������� �� ���������
	BinaryWriter()
	{

	}

	// ����������� ����������
	virtual ~BinaryWriter()
	{
	}

	// ������ � ����
	virtual void write(ofstream& stream, string filePath, T* object) const
	{
		if ("" == filePath)
			throw "Invalid file path";

		// ���� ����� �� ������, ��������� ��� ������
		if (!stream.is_open())
			stream.open(filePath, ios::out | ios::binary | ios::trunc);
	}

protected:

	// ������ ������ � ����
	virtual void writeString(ofstream& stream, string text) const
	{
		// ������ ������
		size_t textSize = text.size();

		// ����� ������ ������
		stream.write((char*)(&textSize), sizeof(textSize));

		// ����� ��� �����
		stream << text;
	}

	// ������ ��� � ����
	virtual void writeInt(ofstream& stream, int value) const
	{
		// ����� ��������
		stream.write((char*)(&value), sizeof(value));
	}

	// ������ bool � ����
	virtual void writeBool(ofstream& stream, bool value) const
	{
		// ����� �������� 
		stream.write((char*)(&value), sizeof(value));
	}

	// �������� ������
	virtual void clear() = 0;
};

