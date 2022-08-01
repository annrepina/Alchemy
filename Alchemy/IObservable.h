#pragma once
#include "IObserver.h"
#include <vector>

using namespace std;

class IObservable
{
public:

	IObservable();

	virtual ~IObservable() {};

	virtual void subscribe(IObserver* observer);

	virtual void unsubscribe(IObserver* observer);

	virtual void notify(int id);

	// уведомить об изменениях с id элемента и предыдущим кол-вом 
	virtual void notify(int id, int previousNumber);

protected:

	vector<IObserver*> observerList;

};

