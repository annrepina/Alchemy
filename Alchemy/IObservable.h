#pragma once
#include "IObserver.h"
#include <vector>

using namespace std;

#define NEW_ELEMENT		true
#define NOT_NEW_ELEMENT	false

class IObservable
{
public:

	IObservable();

	virtual ~IObservable() {};

	virtual void subscribe(IObserver* observer);

	virtual void unsubscribe(IObserver* observer);

	virtual void notify(int id, bool isNewElement);

	// уведомить об изменениях с id элемента и предыдущим кол-вом 
	virtual void notify(int id, int previousNumber);

	// уведомление без параметрв
	virtual void notify();

protected:

	vector<IObserver*> observerList;

};

