#pragma once

// Строитель - шаблон
template <typename T>
class Builder
{
public:

	// Конструктор по умолчанию
	Builder()
	{
		reset();
	}

	// Виртуальный деструктор
	virtual ~Builder()
	{
		clear();
	}

	T* getResult() 
	{
		T* result = this->element;

		reset();

		return result;
	}

protected:

	virtual void reset()
	{
		this->element = new T();
	}

	virtual void clear() 
	{
		if (nullptr != this->element)
		{
			delete this->element;
			this->element = nullptr;
		}
	}

	T* element;

private:

};

