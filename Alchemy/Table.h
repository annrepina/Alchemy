#pragma once
#include <string>
#include "Formatting.h"

using namespace std;

#define Y_COORD_FOR_PRINTING	10		// ���������� Y ��� ������

// �����- �������
template<typename T>
class Table
{
public:

	// ����������� �� ���������
	Table()
	{
		title = "";
	}

	// ����������� ����������
	virtual ~Table()
	{
	}

	//virtual void calculateXCoordForPrinting();

	virtual void add(T* element) = 0;

protected:

	// �������� �������
	string title;

	//map<int, T*> elementWithId;


	//// ���-�� ��������
	//int numberOfColumns;

	//// ���-�� �����
	//int numberOfLines;

	//// �����
	//int length;

	//// ��������� y ��� ������
	//int yCoordForPrinting;

	//// ���������� � ��� ������
	//int xCoordForPrinting;

	//// ������
	//virtual void print() = 0;




private:

};

