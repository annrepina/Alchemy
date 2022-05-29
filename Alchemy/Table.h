#pragma once
#include <string>
#include "Formatting.h"

using namespace std;

#define Y_COORD_FOR_PRINTING	10		// ���������� Y ��� ������

// �����- �������
class Table
{
public:

	// ����������� �� ���������
	Table();

	// ����������� ����������
	virtual ~Table();

	virtual void calculateXCoordForPrinting();

protected:

	// �������� �������
	string title;

	// ���-�� ��������
	int numberOfColumns;

	//// ���-�� �����
	//int numberOfLines;

	// �����
	int length;

	// ��������� y ��� ������
	int yCoordForPrinting;

	// ���������� � ��� ������
	int xCoordForPrinting;

	// ������
	virtual void print() = 0;




private:

};

