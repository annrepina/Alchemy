#pragma once
#include <string>
#include "Formatting.h"

using namespace std;

#define Y_COORD_FOR_FRAME_PRINTING	10		// ���������� Y ��� ������

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

	virtual void add(T* element) = 0;

	string getTitle() 
	{
		return this->title;
	}

protected:

	// �������� �������
	string title;

private:

};

