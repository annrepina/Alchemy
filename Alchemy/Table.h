#pragma once
#include <string>
#include "Formatting.h"

using namespace std;

#define Y_COORD_FOR_FRAME_PRINTING	10		// Координата Y для печати

// Класс- таблица
template<typename T>
class Table
{
public:

	// Конструктор по умолчанию
	Table()
	{
		title = "";
	}

	// Виртуальный деструктор
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
	
	// Получить итератор на начало вектора доступных элементов
	vector<int>::iterator getBeginIteratorOfAvailableElements()
	{
		return this->availableElements.begin();
	}

	// Получить итератор на конец вектора доступных элементов
	vector<int>::iterator getEndIteratorOfAvailableElements()
	{
		return this->availableElements.end();
	}

	// Добавить доступный элемент
	void addAvailableElement(int id)
	{
		// Имеет ли таблица такой элемент уже
		bool hasSuchElement = false;

		// проверяем в цикле
		for (auto element : availableElements)
		{
			// если есть совпадение
			if (element == id)
			{
				hasSuchElement = true;
				break;
			}
		}

		// если такого элемента не было
		if(!hasSuchElement)
			this->availableElements.push_back(id);
	}

protected:

	// Название таблицы
	string title;

	// Доступные пользователю элементы, те, у которых кол-во больше нуля
	vector<int> availableElements;

private:

};
