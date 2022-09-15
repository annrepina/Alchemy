#pragma once
#include "Table.h"

// Класс - обозреватель, который следит за измениями объектов, на которые подписан
class IObserver
{
public:

	// Конструктор по умолчанию
	IObserver();

	// Деструктор
	virtual ~IObserver();

	// Сделать обновления в зависимостти от изменений
	virtual void update(int id, bool isNewElement) = 0;

	// Сделать обновления в зависимостти от изменений
	virtual void update(int id, int previousNumber) = 0;

	// уведомление без параметров
	virtual void update() = 0;

};