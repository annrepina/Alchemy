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
	// ���������
	bool res = false;

	// ���� ����������, ���������� �� id 
	Ingredient* ingredient = ingredientsTable->getIngredientById(id);

	// ������ ��������
	int capital = alchemist->getCapital();

	// �������
	int cost = ingredient->getPrice() * number;

	// ���� ����� � �������� ������ ��� ����� ���� �����������
	if (capital >= cost)
	{
		// ���������� ���������� ���-�� �����������
		int previousNumber = ingredient->getNumber();

		ingredient->increaseNumber(number);

		// ���������� ����������� �� ����������
		ingredientsTable->notify(id, previousNumber);

		ingredientsTable->addAvailableElement(id);

		alchemist->decreaseCapital(cost);

		res = true;
	}
	// ���� ����� ������������
	else
	{
		res = false;
	}

	return res;
}

bool AlchemyLogic::tryAddNewIngredientToTable(string ingredientName)
{
	// ���� ����������� � �������� ��������� � ������� ���
	if (!hasSuchIngredientName(ingredientName))
	{
		IngredientBuilder ingredientBuilder;

		ingredientBuilder.buildIngredient(ingredientName, this->effectsTable);

		Ingredient* res = ingredientBuilder.getResult();

		// ��������� ���������� � �������
		this->ingredientsTable->add(res);

		res->subscribe(this->ingredientsTable);

		// id ����� �����������
		int id = (--this->ingredientsTable->getEndIterator())->first;

		// ��������� ������� � ������ ��������� ���������
		this->ingredientsTable->addAvailableElement(id);

		this->ingredientsTable->notify(id, NEW_ELEMENT);

		return true;
	}

	return false;
}

void AlchemyLogic::checkPotion(Potion* potion)
{	
	// 0 - ���� ����� ����� ���
	int id = hasSuchPotion(potion);

	// ���� ����� ����� �� ����� ��� ����
	if (id > 0)
	{
		this->potionTable->getPotionById(id)->increaseNumber();

		this->potionTable->notify(id, NOT_NEW_ELEMENT);

		// ������� ��������� �����
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
//	// ������ id ��������, ������� �������
//	vector<int> equalEffectsId;
//
//	// ������ ����������
//	Ingredient* firstIngredient = this->ingredientsTable->getIngredientById(firstIngredientId);
//
//	// ������ ����������
//	Ingredient* secondIngredient = this->ingredientsTable->getIngredientById(secondIngredientId);
//
//	// �������� �� ������ ���� � ��������� ������� �����������
//	auto firstIngredientBeginIter = firstIngredient->getBeginIteratorOfEffectsId();
//
//	// �������� �� ����� ���� � ��������� ������� ����������� 
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
//			// ���� id �������� �������
//			if (i->first == j->first)
//			{
//				// ��������� � ������ ��������
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
//	//// ������� ��������� �����
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
		// ���� ����� ���������, �� ���������� true
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

	// Id ������� �����
	int effectId = potion->getEffectId();

	// ���� �����
	int price = potion->getPrice();

	// �������� �����
	int power = potion->getPower();

	for (map<int, Potion*>::iterator i = startIter; i != endIter; ++i)
	{
		// ���� ��������� ������� ����, �� ���������� true
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
	// ������� ��������� �����
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
	// ����������� �������, � ������� ����� ����������� ��������� ������ ��������� - ������ ��������� ������� �������
	vector<string> pivot = tableData[PIVOT_INDEX];

	// �������� 1, �.�. ��������� ��������� � ������ � 0
	int analyzedIndex = numberOfColumn - 1;

	// ������ ���������� ������ �������� - ��������� ������ �������
	auto left = 0;

	// ������ ���������� ������� �������� - ��������� ������ �������
	auto right = size - 1;

	// ���� ������������, ���� �� ���������� break
	while (true)
	{
		// ���� ���������� �� �����������
		if (order == ASCENDING_ORDER_OF_SORTING)
		{
			// ���� ������ ������� ������ ������
			// ��������� ������ ������ �� ��� ���, ���� �������� ������ ���� ����� ������ � ���� ������ ������ ������ ������
			while (right > left && firstStringIsBiggerOrEqualSecond(tableData[right][analyzedIndex], pivot[analyzedIndex]))
			{
				--right;
			}

			// ���� ����� ������� ������ ������
			// ����������� ����� ������ �� ��� ���, ���� �������� ������ ���� ����� ������ � ���� ����� ������� ������ �������
			while (left < right && firstStringIsSmallerOrEqualSecond(tableData[left][analyzedIndex], pivot[analyzedIndex]))
			{
				++left;
			}

			// ���� ������� ���������� �� ����� ������
			if (right == left)
			{
				// ������ ������� ����� � �������, �� ������� ������� ����������, 
				//����� ����� ����� ����� ���� ������� � �������� ����� �� 2 �����
				swap(tableData[PIVOT_INDEX], tableData[right]);

				break;
			}

			// ���� left � right �� ����������� ������� ��������������� ��������, 
			// ����������� �������� ������ ������ - �����, � ������ - ������
			swap(tableData[left], tableData[right]);
		}

		// ���� �� ��������
		else
		{
			// ���� ������ ������� ������ ������
			// ��������� ������ ������ �� ��� ���, ���� �������� ������ ���� ����� ������ � ���� ������ ������ ������ ������
			while (right > left && firstStringIsSmallerOrEqualSecond(tableData[right][analyzedIndex], pivot[analyzedIndex]))
			{
				--right;
			}

			// ���� ����� ������� ������ ������
			// ����������� ����� ������ �� ��� ���, ���� �������� ������ ���� ����� ������ � ���� ����� ������� ������ �������
			while (left < right && firstStringIsBiggerOrEqualSecond(tableData[left][analyzedIndex], pivot[analyzedIndex]))
			{
				++left;
			}

			// ���� ������� ���������� �� ����� ������
			if (right == left)
			{
				// ������ ������� ����� � �������, �� ������� ������� ����������, 
				//����� ����� ����� ����� ���� ������� � �������� ����� �� 2 �����
				swap(tableData[PIVOT_INDEX], tableData[right]);

				break;
			}

			// ���� left � right �� ����������� ������� ��������������� ��������, 
			// ����������� �������� ������ ������ - �����, � ������ - ������
			swap(tableData[left], tableData[right]);
		}
	}

	// ���� ������ ������ ������ ��� ����� ������������ ������� �������, ������� ����� �������������, 
	// ������ ����� �������� ��������������� 2 ��� ������ �����������
	// �������� ������� �� �� ����������
	if (right >= MIN_SIZE)
	{
		// �������� ��������� �� ������ ��� ��������� - �������� � 0�� �������� ��������� �������
		// ������ ������� ����� ������� ������� ��������
		sortStringData(tableData, numberOfColumn, order, right);
	}

	// ���� ������ ������ ������ ������� ������� ����� 2, ������ ������ �������� ��������������� 2 ��� ������ �����������
	// �������� ������� �� �� ����������
	if (right < size - 2)
	{
		// �������� ��������� �� ������ + right + 1. �.�. ������ ����� �.�. �������� �������� ������������ ����� �������
		// ������ ������� ����� ��������� ������� �� ������� right � 1
		sortStringData(tableData + right + 1, numberOfColumn, order, size - right - 1);
	}
	
}

void AlchemyLogic::sortDigitData(vector<string>* tableData, int numberOfColumn, bool order, int size)
{
	// ����������� �������, � ������� ����� ����������� ��������� ������ ��������� - ������ ��������� ������� �������
	vector<string> pivot = tableData[PIVOT_INDEX];

	// �������� 1, �.�. ��������� ��������� � ������ � 0
	int analyzedIndex = numberOfColumn - 1;

	// ������ ���������� ������ �������� - ��������� ������ �������
	auto left = 0;

	// ������ ���������� ������� �������� - ��������� ������ �������
	auto right = size - 1;

	// ���� ������������, ���� �� ���������� break
	while (true)
	{
		// ���� ���������� �� �����������
		if (order == ASCENDING_ORDER_OF_SORTING)
		{
			// ���� ������ ������� ������ ������
			// ��������� ������ ������ �� ��� ���, ���� �������� ������ ���� ����� ������ � ���� ������ ������ ������ ������

			while (right > left && stoi(tableData[right][analyzedIndex]) >= stoi(pivot[analyzedIndex]))
			{
				--right;
			}

			// ���� ����� ������� ������ ������
			// ����������� ����� ������ �� ��� ���, ���� �������� ������ ���� ����� ������ � ���� ����� ������� ������ �������
			while (left < right && stoi(tableData[left][analyzedIndex]) <= stoi(pivot[analyzedIndex]))
			{
				++left;
			}

			// ���� ������� ���������� �� ����� ������
			if (right == left)
			{
				// ������ ������� ����� � �������, �� ������� ������� ����������, 
				//����� ����� ����� ����� ���� ������� � �������� ����� �� 2 �����
				swap(tableData[PIVOT_INDEX], tableData[right]);

				break;
			}

			// ���� left � right �� ����������� ������� ��������������� ��������, 
			// ����������� �������� ������ ������ - �����, � ������ - ������
			swap(tableData[left], tableData[right]);
		}

		// ���� �� ��������
		else
		{
			// ���� ������ ������� ������ ������
			// ��������� ������ ������ �� ��� ���, ���� �������� ������ ���� ����� ������ � ���� ������ ������ ������ ������
			while (right > left && stoi(tableData[right][analyzedIndex]) <= stoi(pivot[analyzedIndex]))
			{
				--right;
			}

			// ���� ����� ������� ������ ������
			// ����������� ����� ������ �� ��� ���, ���� �������� ������ ���� ����� ������ � ���� ����� ������� ������ �������
			while (left < right && stoi(tableData[left][analyzedIndex]) >= stoi(pivot[analyzedIndex]))
			{
				++left;
			}

			// ���� ������� ���������� �� ����� ������
			if (right == left)
			{
				// ������ ������� ����� � �������, �� ������� ������� ����������, 
				//����� ����� ����� ����� ���� ������� � �������� ����� �� 2 �����
				swap(tableData[PIVOT_INDEX], tableData[right]);

				break;
			}

			// ���� left � right �� ����������� ������� ��������������� ��������, 
			// ����������� �������� ������ ������ - �����, � ������ - ������
			swap(tableData[left], tableData[right]);
		}
	}

	// ���� ������ ������ ������ ��� ����� ������������ ������� �������, ������� ����� �������������, 
	// ������ ����� �������� ��������������� 2 ��� ������ �����������
	// �������� ������� �� �� ����������
	if (right >= MIN_SIZE)
	{
		// �������� ��������� �� ������ ��� ��������� - �������� � 0�� �������� ��������� �������
		// ������ ������� ����� ������� ������� ��������
		sortDigitData(tableData, numberOfColumn, order, right);
	}

	// ���� ������ ������ ������ ������� ������� ����� 2, ������ ������ �������� ��������������� 2 ��� ������ �����������
	// �������� ������� �� �� ����������
	if (right < size - 2)
	{
		// �������� ��������� �� ������ + right + 1. �.�. ������ ����� �.�. �������� �������� ������������ ����� �������
		// ������ ������� ����� ��������� ������� �� ������� right � 1
		sortDigitData(tableData + right + 1, numberOfColumn, order, size - right - 1);
	}
}

//void AlchemyLogic::filterData(vector<vector<string>> content, vector<string> queries)
//{
//
//}
