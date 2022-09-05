#include "AlchemyLogic.h"

AlchemyLogic::AlchemyLogic()
{
	//this->alchemist = new Alchemist();

	this->alchemist = nullptr;

	this->effectsTable = nullptr;

	this->ingredientsTable = nullptr;

	this->potionTable = nullptr;
}

void AlchemyLogic::setEffectsTable(EffectsTable* effectsTable)
{
	this->effectsTable = effectsTable;
}

void AlchemyLogic::setIngredientsTable(IngredientsTable* ingredientsTable)
{
	this->ingredientsTable = ingredientsTable;
}

void AlchemyLogic::setPotionTable(PotionTable* potionTable)
{
	this->potionTable = potionTable;
}

void AlchemyLogic::setAlchemist(Alchemist* alchemist)
{
	this->alchemist = alchemist;
}

Alchemist* AlchemyLogic::getAlchemist()
{
	return this->alchemist;
}

EffectsTable* AlchemyLogic::getEffectsTable()
{
	return this->effectsTable;
}

IngredientsTable* AlchemyLogic::getIngredientsTable()
{
	return this->ingredientsTable;
}

PotionTable* AlchemyLogic::getPotionTable()
{
	return this->potionTable;
}

bool AlchemyLogic::tryBuyIngredientFromList(int id, int number)
{
	// результат
	bool res = false;

	// Этот ингредиент, полученный по id 
	Ingredient* ingredient = ingredientsTable->getIngredientById(id);

	// деньги алхимика
	int capital = alchemist->getCapital();

	// расходы
	int cost = ingredient->getPrice() * number;

	// если денег у алхимика больше или равно цене ингредиента
	if (capital >= cost)
	{
		// закрепляем предыдущее кол-во ингредиента
		int previousNumber = ingredient->getNumber();

		ingredient->increaseNumber(number);

		// уведомляем подписчиков об изменениях
		ingredientsTable->notify(id, previousNumber);

		ingredientsTable->addAvailableElement(id);

		alchemist->decreaseCapital(cost);

		res = true;
	}
	// если денег недостаточно
	else
	{
		res = false;
	}

	return res;
}

bool AlchemyLogic::tryAddNewIngredientToTable(string ingredientName)
{
	// если ингредиента с подобным названием в таблице нет
	if (!hasSuchIngredientName(ingredientName))
	{
		IngredientBuilder ingredientBuilder;

		ingredientBuilder.buildIngredient(ingredientName, this->effectsTable);

		Ingredient* res = ingredientBuilder.getResult();

		// добавляем ингредиент в таблицу
		this->ingredientsTable->add(res);

		res->subscribe(this->ingredientsTable);

		// id Этого ингредиента
		int id = (--this->ingredientsTable->getEndIterator())->first;

		// добавляем элемент в вектор имеющихся элементов
		this->ingredientsTable->addAvailableElement(id);

		this->ingredientsTable->notify(id, NEW_ELEMENT);

		return true;
	}

	return false;
}

void AlchemyLogic::checkPotion(Potion* potion)
{	
	// 0 - если таких зелий нет
	int id = hasSuchPotion(potion);

	// если точно такое же зелье уже есть
	if (id > 0)
	{
		this->potionTable->getPotionById(id)->increaseNumber();

		this->potionTable->notify(id, NOT_NEW_ELEMENT);

		// удаляем созданное зелье
		delete potion;
		potion = nullptr;
	}
	else
	{
		this->potionTable->add(potion);
	}
}

//vector<int> AlchemyLogic::findEqualEffects(int firstIngredientId, int secondIngredientId)
//{
//	// Вектор id эффектов, которые совпали
//	vector<int> equalEffectsId;
//
//	// первый ингредиент
//	Ingredient* firstIngredient = this->ingredientsTable->getIngredientById(firstIngredientId);
//
//	// второй ингредиент
//	Ingredient* secondIngredient = this->ingredientsTable->getIngredientById(secondIngredientId);
//
//	// Итератор на начало мэпа с эффектами первого ингредиента
//	auto firstIngredientBeginIter = firstIngredient->getBeginIteratorOfEffectsId();
//
//	// итератор на конец мэпа с эффектами первого ингредиента 
//	auto firstIngredientEndInter = firstIngredient->getEndIteratorOfEffectsId();
//
//	auto secondIngredientBeginIter = secondIngredient->getBeginIteratorOfEffectsId();
//
//	auto secondIngredientEndInter = secondIngredient->getEndIteratorOfEffectsId();
//
//	for (auto i = firstIngredientBeginIter; i != firstIngredientEndInter; ++i)
//	{
//		for (auto j = secondIngredientBeginIter; j != secondIngredientEndInter; ++j)
//		{
//			// если id эффектов совпали
//			if (i->first == j->first)
//			{
//				// Добавляем в вектор эффектов
//				equalEffectsId.push_back(i->first);
//
//				break;
//			}
//		}
//	}
//
//	return equalEffectsId;
//}

//void AlchemyLogic::addPotion(int effectId)
//{
//	//// Создаем строителя зелий
//	//PotionBuilder potionBuilder;
//
//	//potionBuilder.buildPotion()
//}

bool AlchemyLogic::hasSuchIngredientName(string ingredientName)
{
	map<int, Ingredient*>::iterator startIter = ingredientsTable->getStartIterator();

	map<int, Ingredient*>::iterator endIter = ingredientsTable->getEndIterator();

	for (map<int, Ingredient*>::iterator i = startIter; i != endIter; ++i)
	{
		// если имена совпадают, то возвращаем true
		if (i->second->getName() == ingredientName)
		{
			return true;
		}
	}

	return false;
}

int AlchemyLogic::hasSuchPotion(Potion* potion)
{
	int id = 0;

	map<int, Potion*>::iterator startIter = potionTable->getStartIterator();

	map<int, Potion*>::iterator endIter = potionTable->getEndIterator();

	// Id эффекта зелья
	int effectId = potion->getEffectId();

	// цена зелья
	int price = potion->getPrice();

	// Мощность зелья
	int power = potion->getPower();

	for (map<int, Potion*>::iterator i = startIter; i != endIter; ++i)
	{
		// если совпадают главные поля, то возвращаем true
		if (i->second->getEffectId() == effectId && i->second->getPrice() == price && i->second->getPower() == power)
		{
			id = i->first;

			break;
		}
	}

	return id;
}

//Ingredient* AlchemyLogic::createNewIngredient(string ingredientName)
//{
//	return nullptr;
//}

Potion* AlchemyLogic::createPotion(Ingredient* firstIngredient, Ingredient* secondIngredient)
{
	// Создаем строителя зелий
	PotionBuilder potionBuilder;

	potionBuilder.buildPotion(firstIngredient, secondIngredient, this->alchemist);

	Potion* potion = potionBuilder.getResult();

	return potion;
}

void AlchemyLogic::sellIngredient(int ingredientId, int numberOfIngredient)
{
	Ingredient* ingredient = this->ingredientsTable->getIngredientById(ingredientId);

	int profit = ingredient->getPrice() * numberOfIngredient;

	decreaseNumberOfIngredient(ingredientId, numberOfIngredient);

	this->alchemist->increaseCapital(profit);

	this->alchemist->increaseSalesmanLevel(numberOfIngredient);
}

void AlchemyLogic::sellPotion(int potionId, int numberOfPotion)
{
	Potion* potion = this->potionTable->getPotionById(potionId);

	int profit = potion->getPrice() * numberOfPotion;

	decreaseNumberOfPotion(potionId, numberOfPotion);

	this->alchemist->increaseCapital(profit);

	this->alchemist->increaseSalesmanLevel(numberOfPotion);
}

void AlchemyLogic::decreaseNumberOfIngredient(int ingredientId, int numberOfIngredient)
{
	this->ingredientsTable->decreaseNumberOfIngredient(ingredientId, numberOfIngredient);
}

void AlchemyLogic::decreaseNumberOfPotion(int potionId, int numberOfPotion)
{
	this->potionTable->decreaseNumberOfPotion(potionId, numberOfPotion);
}

void AlchemyLogic::eatIngredient(int ingredientId)
{
	Ingredient* ingredient = this->ingredientsTable->getIngredientById(ingredientId);

	decreaseNumberOfIngredient(ingredientId, 1);

	ingredient->openEffectRandomly();

	ingredient->notify(ingredientId, NOT_NEW_ELEMENT);
}

//void AlchemyLogic::workWithTable(OperationCode code, vector<vector<string>> tableData, int numberOfColumn, bool order)
//{
//	switch (code)
//	{
//		case OperationCode::Search:
//		{
//
//		}
//		break;
//
//		case OperationCode::Sorting:
//		{
//			sortData(tableData, numberOfColumn, order);
//		}
//		break;
//	}
//}

void AlchemyLogic::sortStringData(vector<string>* tableData, int numberOfColumn, bool order, int size)
{
	// Разделяющий элемент, с которым будет происходить сравнение других элементов - всегда начальный элемент массива
	vector<string> pivot = tableData[PIVOT_INDEX];

	// Отнимаем 1, т.к. нумерация элементов в екторе с 0
	int analyzedIndex = numberOfColumn - 1;

	// Индекс начального левого элемента - начальный индекс массива
	auto left = 0;

	// Индекс начального правого элемента - последний индекс массива
	auto right = size - 1;

	// цикл продолжается, пока не встретится break
	while (true)
	{
		// если сортировка по возрастанию
		if (order == ASCENDING_ORDER_OF_SORTING)
		{
			// ищем справа элемент меньше пивота
			// уменьшаем правый индекс до тех пор, пока элементы больше либо равны пивоту и пока правый индекс больше левого
			while (right > left && firstStringIsBiggerOrEqualSecond(tableData[right][analyzedIndex], pivot[analyzedIndex]))
			{
				--right;
			}

			// ищем слева элемент больше пивота
			// увеличиваем левый индекс до тех пор, пока элементы меньше либо равны пивоту и пока левый элемент меньше правого
			while (left < right && firstStringIsSmallerOrEqualSecond(tableData[left][analyzedIndex], pivot[analyzedIndex]))
			{
				++left;
			}

			// если индексы сравнялись во время поиска
			if (right == left)
			{
				// меняем местами пивот и элемент, на котором индексы сравнялись, 
				//после этого пивот занял свою позицию и разделил масив на 2 части
				swap(tableData[PIVOT_INDEX], tableData[right]);

				break;
			}

			// если left и right не пересеклись свопаем соответствующие элементы, 
			// перекидывая элементы меньше пивота - влево, а больше - вправо
			swap(tableData[left], tableData[right]);
		}

		// если по убыванию
		else
		{
			// ищем справа элемент больше пивота
			// уменьшаем правый индекс до тех пор, пока элементы меньше либо равны пивоту и пока правый индекс больше левого
			while (right > left && firstStringIsSmallerOrEqualSecond(tableData[right][analyzedIndex], pivot[analyzedIndex]))
			{
				--right;
			}

			// ищем слева элемент меньше пивота
			// увеличиваем левый индекс до тех пор, пока элементы больше либо равны пивоту и пока левый элемент меньше правого
			while (left < right && firstStringIsBiggerOrEqualSecond(tableData[left][analyzedIndex], pivot[analyzedIndex]))
			{
				++left;
			}

			// если индексы сравнялись во время поиска
			if (right == left)
			{
				// меняем местами пивот и элемент, на котором индексы сравнялись, 
				//после этого пивот занял свою позицию и разделил масив на 2 части
				swap(tableData[PIVOT_INDEX], tableData[right]);

				break;
			}

			// если left и right не пересеклись свопаем соответствующие элементы, 
			// перекидывая элементы больше пивота - влево, а меньше - вправо
			swap(tableData[left], tableData[right]);
		}
	}

	// если правый индекс больше или равен минимального размера массива, который нужно отсортировать, 
	// значит слева осталось неотсортировано 2 или больше элелементов
	// вызываем функцию на их сортировку
	if (right >= MIN_SIZE)
	{
		// передаем указатель на массив без изменений - начинаем с 0го элемента исходного массива
		// размер массива равен индексу правого элемента
		sortStringData(tableData, numberOfColumn, order, right);
	}

	// если правый индекс меньше размера массива минус 2, значит справа осталось неотсортировано 2 или больше элелементов
	// вызываем функцию на их сортировку
	if (right < size - 2)
	{
		// передаем указатель на массив + right + 1. Т.е. задаем адрес т.н. нулевого элемента передаваемой части массива
		// размер массива равен исходному размеру за вычетом right и 1
		sortStringData(tableData + right + 1, numberOfColumn, order, size - right - 1);
	}
	
}

void AlchemyLogic::sortDigitData(vector<string>* tableData, int numberOfColumn, bool order, int size)
{
	// Разделяющий элемент, с которым будет происходить сравнение других элементов - всегда начальный элемент массива
	vector<string> pivot = tableData[PIVOT_INDEX];

	// Отнимаем 1, т.к. нумерация элементов в екторе с 0
	int analyzedIndex = numberOfColumn - 1;

	// Индекс начального левого элемента - начальный индекс массива
	auto left = 0;

	// Индекс начального правого элемента - последний индекс массива
	auto right = size - 1;

	// цикл продолжается, пока не встретится break
	while (true)
	{
		// если сортировка по возрастанию
		if (order == ASCENDING_ORDER_OF_SORTING)
		{
			// ищем справа элемент меньше пивота
			// уменьшаем правый индекс до тех пор, пока элементы больше либо равны пивоту и пока правый индекс больше левого

			while (right > left && stoi(tableData[right][analyzedIndex]) >= stoi(pivot[analyzedIndex]))
			{
				--right;
			}

			// ищем слева элемент больше пивота
			// увеличиваем левый индекс до тех пор, пока элементы меньше либо равны пивоту и пока левый элемент меньше правого
			while (left < right && stoi(tableData[left][analyzedIndex]) <= stoi(pivot[analyzedIndex]))
			{
				++left;
			}

			// если индексы сравнялись во время поиска
			if (right == left)
			{
				// меняем местами пивот и элемент, на котором индексы сравнялись, 
				//после этого пивот занял свою позицию и разделил масив на 2 части
				swap(tableData[PIVOT_INDEX], tableData[right]);

				break;
			}

			// если left и right не пересеклись свопаем соответствующие элементы, 
			// перекидывая элементы меньше пивота - влево, а больше - вправо
			swap(tableData[left], tableData[right]);
		}

		// если по убыванию
		else
		{
			// ищем справа элемент больше пивота
			// уменьшаем правый индекс до тех пор, пока элементы меньше либо равны пивоту и пока правый индекс больше левого
			while (right > left && stoi(tableData[right][analyzedIndex]) <= stoi(pivot[analyzedIndex]))
			{
				--right;
			}

			// ищем слева элемент меньше пивота
			// увеличиваем левый индекс до тех пор, пока элементы больше либо равны пивоту и пока левый элемент меньше правого
			while (left < right && stoi(tableData[left][analyzedIndex]) >= stoi(pivot[analyzedIndex]))
			{
				++left;
			}

			// если индексы сравнялись во время поиска
			if (right == left)
			{
				// меняем местами пивот и элемент, на котором индексы сравнялись, 
				//после этого пивот занял свою позицию и разделил масив на 2 части
				swap(tableData[PIVOT_INDEX], tableData[right]);

				break;
			}

			// если left и right не пересеклись свопаем соответствующие элементы, 
			// перекидывая элементы больше пивота - влево, а меньше - вправо
			swap(tableData[left], tableData[right]);
		}
	}

	// если правый индекс больше или равен минимального размера массива, который нужно отсортировать, 
	// значит слева осталось неотсортировано 2 или больше элелементов
	// вызываем функцию на их сортировку
	if (right >= MIN_SIZE)
	{
		// передаем указатель на массив без изменений - начинаем с 0го элемента исходного массива
		// размер массива равен индексу правого элемента
		sortDigitData(tableData, numberOfColumn, order, right);
	}

	// если правый индекс меньше размера массива минус 2, значит справа осталось неотсортировано 2 или больше элелементов
	// вызываем функцию на их сортировку
	if (right < size - 2)
	{
		// передаем указатель на массив + right + 1. Т.е. задаем адрес т.н. нулевого элемента передаваемой части массива
		// размер массива равен исходному размеру за вычетом right и 1
		sortDigitData(tableData + right + 1, numberOfColumn, order, size - right - 1);
	}
}

//void AlchemyLogic::filterData(vector<vector<string>> content, vector<string> queries)
//{
//
//}
