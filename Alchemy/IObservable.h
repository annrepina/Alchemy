#pragma once
#include "IObserver.h"
#include <vector>

using namespace std;

#define NEW_ELEMENT		true
#define NOT_NEW_ELMENT	false

class IObservable
{
public:

	IObservable();

	virtual ~IObservable() {};

	virtual void subscribe(IObserver* observer);

	virtual void unsubscribe(IObserver* observer);

	virtual void notify(int id, bool isNewElement);

	// ��������� �� ���������� � id �������� � ���������� ���-��� 
	virtual void notify(int id, int previousNumber);

protected:

	vector<IObserver*> observerList;

};

