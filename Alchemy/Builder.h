#pragma once

// Шаблонный класс - по паттерну строитель
// Конструируют другие классы
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

	// Получить результат
	virtual T* getResult()
	{
		T* result = this->element;

		reset();

		return result;
	}

protected:

	// Сбросить параметры строителя
	// Создают новый объект строительства
	virtual void reset()
	{
		this->element = new T();
	}

	// Очистить память
	virtual void clear() 
	{
		if (nullptr != this->element)
		{
			delete this->element;
			this->element = nullptr;
		}
	}

	// Объект строительства
	T* element;
};