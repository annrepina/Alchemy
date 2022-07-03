#pragma once
#include "IObserver.h"
#include <vector>

using namespace std;

class IObservable
{
public:

	IObservable();

	virtual ~IObservable() {};

	virtual void subscribe(IObserver* observer) = 0;

	virtual void unsubscribe(IObserver* observer) = 0;

	virtual void notify(int id) = 0;

	vector<IObserver*> observerList;

protected:



};

