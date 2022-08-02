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

		this->ingredientsTable->notify(id);

		return true;
	}

	return false;
}

bool AlchemyLogic::checkPotion(Potion* potion)
{	
	// если зелье не пустое
	if (potion->getEffectId() != 0)
	{
		// 0 - если таких зелий нет
		int id = hasSuchPotion(potion);

		// если точно такое же зелье уже есть
		if (id > 0)
		{
			this->potionTable->getPotionById(id)->increaseNumber();

			this->potionTable->notify(id);

			// удаляем созданное зелье
			delete potion;
			potion = nullptr;
		}
		else
		{
			this->potionTable->add(potion);
		}

		return true;
	}

	return false;
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

	decreaseNumberOfIngredient(ingredientId, numberOfIngredient);

	int profit = ingredient->getPrice();

	this->alchemist->increaseCapital(profit);

	this->alchemist->increaseSalesmanLevel(numberOfIngredient);
}

void AlchemyLogic::decreaseNumberOfIngredient(int ingredientId, int numberOfIngredient)
{
	this->ingredientsTable->decreaseNumberOfIngredient(ingredientId, numberOfIngredient);
}

void AlchemyLogic::eatIngredient(int ingredientId)
{
	Ingredient* ingredient = this->ingredientsTable->getIngredientById(ingredientId);

	decreaseNumberOfIngredient(ingredientId, 1);

	ingredient->openEffectRandomly();

	ingredient->notify(ingredientId);
}

//void AlchemyProgram::printIngredientsTable()
//{
//	this->ingredientsTable->print();
//}

//void AlchemyProgram::printTitle()
//{
//	this->setXCoord();
//
//	printFramedText(title, TITLE_Y_COORD, titleXCoord);
//}
//
//void AlchemyProgram::printMenu()
//{
//	cout << "\nВыберите действие: " << endl
//		<< "1 - Заняться алхимией" << endl
//		<< "2 - Ознакомиться с инструкцией к программе" << endl
//		<< "ESC - выход" << endl;
//}
//
//void AlchemyProgram::printInstructions()
//{
//	eraseScreenAfterTitle();
//
//	cout << "Инструкции к программе \"Зельеварение\"" << endl
//		<< "0 - назад"
//		<< "ESC - выход";
//}
//
//void AlchemyProgram::eraseScreenAfterTitle()
//{
//	cout << goToXY(Y_COORD_AFTER_TITLE, 0);
//
//	cout << eraseOnScreen(FROM_CURSOR_TO_SCREEN_END);
//}
//
//bool AlchemyProgram::isMenuChoiceFalse(int key)
//{
//	return key != VK_1 && key != VK_2 && key != VK_NUMPAD1 && key != VK_NUMPAD2 && key != VK_ESCAPE;
//}
//
//bool AlchemyProgram::isContinueGameFalse(int key)
//{
//	return VK_1 != key && VK_2 != key && VK_NUMPAD1 != key && VK_NUMPAD2 != key;
//}
//
//bool AlchemyProgram::isContinue(int key)
//{
//	return VK_RETURN != key && VK_ESCAPE != key;
//}
//
//void AlchemyProgram::launchMainLoop()
//{
//	/*setXCoord();*/
//
//	/*printTitle();*/
//
//	printMenu();
//
//	//using std::placeholders::_1;
//
//	//function<bool(int)> func = std::bind(&AlchemyProgram::isMenuChoiceFalse, this, _1);
//
//	this->func = std::bind(&AlchemyProgram::isMenuChoiceFalse, this, _1);
//
//	//checkMenuChoice(/*0, */func);
//	checkMenuChoice();
//
//	eraseScreenAfterTitle();
//
//	switch (this->keyBoard->getPressedKey())
//	{
//		case VK_1: case VK_NUMPAD1:
//		{
//			doAlchemy();
//
//			//cout << "\nАлхимия" << endl;
//			//
//			//cout << "Хотите продолжить последнюю игру или создать новую?" << endl
//			//	<< "1 - Продолжить игру" << endl
//			//	<< "2 - Создать новую игру" << endl;
//
//			//func = std::bind(&AlchemyProgram::isContinuePlayFalse, this, _1);
//
//			////checkMenuChoice(/*0, */func);
//
//			//checkMenuChoice();
//
//
//		}
//		break;
//
//		case VK_2: case VK_NUMPAD2:
//		{
//			cout << "\nИнструкция" << endl;
//		}
//		break;
//
//		case VK_ESCAPE:
//		{
//			cout << "\nДо скорой встречи!" << endl;
//		}
//		break;
//	}
//	//
//	//cout << "Вы нажали верную клавишу";
//
//	//system("pause");
//
//
//
//	//cout << "А теперь стерли все";
//}
//
//void AlchemyProgram::setXCoord()
//{
//	titleXCoord = (defineConsoleWidth() / 2) - (title.length() / 2);
//}
//
////void AlchemyProgram::getKey()
////{
////	// ждем нажатия клавиши
////	while (!_kbhit());
////
////	// записываем нажатую клавишу
////	auto key = getch();
////
////	// Присваиваем нажатую кнопку
////	this->key = key;
////}
//
////void AlchemyProgram::checkMenuChoice(/*int key,*/ function<bool(int)> condition/*bool (*condition) (int key)*/)
////{
////	// нажатая клавиша
////	int key;
////
////	do {
////
////		this->keyBoard->waitForKey();
////
////		key = this->keyBoard->getPressedKey();
////
////	}	// Если нажатая клавиша не соответсвует кнопкам меню
////	while (condition(key));
////}
//
//void AlchemyProgram::checkMenuChoice()
//{
//	// нажатая клавиша
//	int key;
//
//	do {
//
//		this->keyBoard->waitForKey();
//
//		key = this->keyBoard->getPressedKey();
//
//	}	// Если нажатая клавиша не соответсвует кнопкам меню
//	while (this->func(key));
//}
//
//void AlchemyProgram::doAlchemy()
//{
//	cout << "\nАлхимия" << endl;
//
//	cout << "Хотите продолжить последнюю игру или создать новую?" << endl
//		 << "1 - Продолжить игру" << endl
//		 << "2 - Создать новую игру" << endl;
//
//	func = std::bind(&AlchemyProgram::isContinueGameFalse, this, _1);
//
//	//checkMenuChoice(/*0, */func);
//
//	checkMenuChoice();
//
//
//
//	// Имя алхимика
//	string name;
//
//	eraseScreenAfterTitle();
//
//	switch (this->keyBoard->getPressedKey())
//	{
//		case VK_1: case VK_NUMPAD1:
//		{
//			// продумать проверку была ли игра до этого или нет
//		}
//		break;
//
//		case VK_2: case VK_NUMPAD2:
//		{
//			cout << "Введите ваше имя: ";
//
//			cin >> name;
//
//			this->alchemist->setName(name);
//
//			cout << "\nEnter - продолжить" << endl
//				<< "Esc - выход";
//
//			func = std::bind(&AlchemyProgram::isContinue, this, _1);
//
//			checkMenuChoice();
//
//			printUserInterface();
//		}
//		break;
//
//
//		default:
//			break;
//	}
//
//
//
//
//
//}
