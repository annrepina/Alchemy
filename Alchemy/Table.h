#pragma once
#include <string>
#include "Formatting.h"
#include "ServiceFunctions.h"

using namespace std;

#define Y_COORD_FOR_FRAME_PRINTING	10		// Координата Y для печати

// Шаблонный класс - таблица
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

	// Добавить элемент в таблицу
	virtual void add(T* element) = 0;

	// Добавить элемент в таблицу с id 
	virtual void add(T* element, int id) = 0;

	// Геттер для названия
	string getTitle() 
	{
		return this->title;
	}

	// Геттер для получения доступных элементов (тех, у которых кол-во больше 0)
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

	// Название таблицы
	string title;

	// Доступные пользователю элементы, те, у которых кол-во больше нуля
	vector<int> availableElements;

};