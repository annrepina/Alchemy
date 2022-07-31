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

protected:

	vector<IObserver*> observerList;

};

