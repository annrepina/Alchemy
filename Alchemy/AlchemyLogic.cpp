#include "AlchemyLogic.h"



AlchemyLogic::AlchemyLogic()
{
	this->alchemist = new Alchemist();

	this->effectsTable = nullptr;

	this->ingredientsTable = nullptr;

	
}

void AlchemyLogic::setEffectsTable(EffectsTable* effectsTable)
{
	this->effectsTable = effectsTable;
}

void AlchemyLogic::setIngredientsTable(IngredientsTable* ingredientsTable)
{
	this->ingredientsTable = ingredientsTable;
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

bool AlchemyLogic::tryAddIngredientFromList(int id, int number)
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
		ingredient->increaseNumber(number);

		// уведомляем подписчиков об изменениях
		ingredientsTable->notify(id);

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
		// Создаем строителя ингредиентов
		IngredientBuilder builder;

		// Задаем таблицу эффектов
		builder.setEffectsTable(this->effectsTable);

		builder.setName(ingredientName);

		int price = randInRange(MIN_PRICE, MAX_PRICE);

		builder.setPrice(price);

		// Создаем временный вектор id эффектов
		vector<int> tempEffectsId;

		// Максимальное id эффекта 
		int maxEffectId = builder.getEffectsTableSize();

		// Добавление эффектов
		for (int i = 0; i < NUMBER_OF_EFFECTS; ++i)
		{
			int idIndex = randInRange(1, maxEffectId);

			// если это уже не первый эффект и предыдущий совпадает с вновь выбранным
			if (0 < i && tempEffectsId[0] == idIndex)
			{
				--i;
				continue;
			}

			// Добавляем во временный вектор id
			tempEffectsId.push_back(idIndex);

			builder.addEffect(idIndex);
		}

		// добавляем ингредиент в таблицу
		this->ingredientsTable->add(builder.getResult());

		return true;
	}

	return false;
}

bool AlchemyLogic::hasSuchIngredientName(string ingredientName)
{
	map<int, Ingredient*>::iterator startIter = ingredientsTable->getStartIterator();

	map<int, Ingredient*>::iterator endIter = ++ingredientsTable->getEndIterator();

	for (map<int, Ingredient*>::iterator i = startIter; i != endIter; ++i)
	{
		// если имена совпадают, то возвращаем false
		if (i->second->getName() == ingredientName)
		{
			return true;
		}
	}

	return false;
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
