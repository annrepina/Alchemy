#pragma once
#include "IObserver.h"
#include <vector>

using namespace std;

#define NEW_ELEMENT		true
#define NOT_NEW_ELEMENT	false

// Класс - индерфейс, обозреваемого объекта
class IObservable
{
public:

	// Конструктор по умолчанию
	IObservable();

	// Деструктор
	virtual ~IObservable();

	// Подписать обозреватель на наблюдение
	virtual void subscribe(IObserver* observer);

	// Отписать обозревателя из наблюдения
	virtual void unsubscribe(IObserver* observer);

	// Уведомить подписчиков об измениях
	virtual void notify(int id, bool isNewElement);

	// уведомить об изменениях с id элемента и предыдущим кол-вом 
	virtual void notify(int id, int previousNumber);

	// уведомление без параметрв
	virtual void notify();

protected:

	// Список подписчиков
	vector<IObserver*> observerList;

};