#pragma once
#include <string>
#include "Formatting.h"

using namespace std;

// �����- �������
class Table
{
public:

	// ����������� �� ���������
	Table();

protected:

	// �������� �������
	string title;

	// ���-�� �������
	int numberOfColumns;

	// ���-�� �����
	int numberOfLines;

	int length;

	virtual void print() const;

	virtual void calculateLength() = 0;

private:

	


};

