#include "IObservable.h"

IObservable::IObservable()
{
}

IObservable::~IObservable()
{
}

void IObservable::subscribe(IObserver* observer)
{
	this->observerList.push_back(observer);
}

void IObservable::unsubscribe(IObserver* observer)
{
	// размер вектор
	int size = this->observerList.size();

	// итератор на первый элемент в векторе
	auto begin = this->observerList.cbegin();

	for (int i = 0; i < size; ++i)
	{
		if (this->observerList[i] == observer)
		{
			this->observerList.erase(begin + i);
			break;
		}
	}
}

void IObservable::notify(int id, bool isNewElement)
{
	for (auto observer : this->observerList)
	{
		observer->update(id, isNewElement);
	}
}

void IObservable::notify(int id, int previousNumber)
{
	for (auto observer : this->observerList)
	{
		observer->update(id, previousNumber);
	}
}

void IObservable::notify()
{
	for (auto observer : this->observerList)
	{
		observer->update();
	}
}