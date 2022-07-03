#pragma once
#include "Table.h"

class IObserver
{
public:

	IObserver();

	virtual ~IObserver();

	virtual void update(int id) = 0;

	//virtual void update(float course) = 0;


private:

};

