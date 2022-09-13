#pragma once
#include <string>
#include "Formatting.h"
#include "ServiceFunctions.h"

using namespace std;

#define Y_COORD_FOR_FRAME_PRINTING	10		// ���������� Y ��� ������

// ��������� ����� - �������
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

	// �������� ������� � �������
	virtual void add(T* element) = 0;

	// �������� ������� � ������� � id 
	virtual void add(T* element, int id) = 0;

	// ������ ��� ��������
	string getTitle() 
	{
		return this->title;
	}

	// ������ ��� ��������� ��������� ��������� (���, � ������� ���-�� ������ 0)
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
		if (!hasSuchElement)
		{
			this->availableElements.push_back(id);
			quickSort(&availableElements[0], availableElements.size());
		}
	}

	virtual int findElementInAvailableElements(int key)
	{
		int res = binarySearch(this->availableElements, key);

		return res;
	}

protected:

	// �������� �������
	string title;

	// ��������� ������������ ��������, ��, � ������� ���-�� ������ ����
	vector<int> availableElements;

};