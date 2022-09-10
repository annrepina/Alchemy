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

	virtual void add(T* element, int id) = 0;

	string getTitle() 
	{
		return this->title;
	}

	int getNumberOfAvailableElements()
	{
		return this->availableElements.size();
	}
	
	// �������� �������� �� ������ ������� ��������� ���������
	vector<int>::iterator getBeginIteratorOfAvailableElements()
	{
		return this->availableElements.begin();
	}

	// �������� �������� �� ����� ������� ��������� ���������
	vector<int>::iterator getEndIteratorOfAvailableElements()
	{
		return this->availableElements.end();
	}

	// �������� ��������� �������
	void addAvailableElement(int id)
	{
		// ����� �� ������� ����� ������� ���
		bool hasSuchElement = false;

		// ��������� � �����
		for (auto element : availableElements)
		{
			// ���� ���� ����������
			if (element == id)
			{
				hasSuchElement = true;
				break;
			}
		}

		// ���� ������ �������� �� ����
		if(!hasSuchElement)
			this->availableElements.push_back(id);
	}

protected:

	// �������� �������
	string title;

	// ��������� ������������ ��������, ��, � ������� ���-�� ������ ����
	vector<int> availableElements;

private:

};
