#pragma once
#include "Table.h"

class IObserver
{
public:

	IObserver();

	virtual ~IObserver();

	virtual void update(int id, bool isNewElement) = 0;

	virtual void update(int id, int previousNumber) = 0;

	// уведомление без параметров
	virtual void update() = 0;

	//virtual void update(float course) = 0;


private:

};

