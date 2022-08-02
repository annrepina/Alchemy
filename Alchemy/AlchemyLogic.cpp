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

		this->ingredientsTable->notify(id);

		return true;
	}

	return false;
}

bool AlchemyLogic::checkPotion(Potion* potion)
{	
	// ���� ����� �� ������
	if (potion->getEffectId() != 0)
	{
		// 0 - ���� ����� ����� ���
		int id = hasSuchPotion(potion);

		// ���� ����� ����� �� ����� ��� ����
		if (id > 0)
		{
			this->potionTable->getPotionById(id)->increaseNumber();

			this->potionTable->notify(id);

			// ������� ��������� �����
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
//	cout << "\n�������� ��������: " << endl
//		<< "1 - �������� ��������" << endl
//		<< "2 - ������������ � ����������� � ���������" << endl
//		<< "ESC - �����" << endl;
//}
//
//void AlchemyProgram::printInstructions()
//{
//	eraseScreenAfterTitle();
//
//	cout << "���������� � ��������� \"������������\"" << endl
//		<< "0 - �����"
//		<< "ESC - �����";
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
//			//cout << "\n�������" << endl;
//			//
//			//cout << "������ ���������� ��������� ���� ��� ������� �����?" << endl
//			//	<< "1 - ���������� ����" << endl
//			//	<< "2 - ������� ����� ����" << endl;
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
//			cout << "\n����������" << endl;
//		}
//		break;
//
//		case VK_ESCAPE:
//		{
//			cout << "\n�� ������ �������!" << endl;
//		}
//		break;
//	}
//	//
//	//cout << "�� ������ ������ �������";
//
//	//system("pause");
//
//
//
//	//cout << "� ������ ������ ���";
//}
//
//void AlchemyProgram::setXCoord()
//{
//	titleXCoord = (defineConsoleWidth() / 2) - (title.length() / 2);
//}
//
////void AlchemyProgram::getKey()
////{
////	// ���� ������� �������
////	while (!_kbhit());
////
////	// ���������� ������� �������
////	auto key = getch();
////
////	// ����������� ������� ������
////	this->key = key;
////}
//
////void AlchemyProgram::checkMenuChoice(/*int key,*/ function<bool(int)> condition/*bool (*condition) (int key)*/)
////{
////	// ������� �������
////	int key;
////
////	do {
////
////		this->keyBoard->waitForKey();
////
////		key = this->keyBoard->getPressedKey();
////
////	}	// ���� ������� ������� �� ������������ ������� ����
////	while (condition(key));
////}
//
//void AlchemyProgram::checkMenuChoice()
//{
//	// ������� �������
//	int key;
//
//	do {
//
//		this->keyBoard->waitForKey();
//
//		key = this->keyBoard->getPressedKey();
//
//	}	// ���� ������� ������� �� ������������ ������� ����
//	while (this->func(key));
//}
//
//void AlchemyProgram::doAlchemy()
//{
//	cout << "\n�������" << endl;
//
//	cout << "������ ���������� ��������� ���� ��� ������� �����?" << endl
//		 << "1 - ���������� ����" << endl
//		 << "2 - ������� ����� ����" << endl;
//
//	func = std::bind(&AlchemyProgram::isContinueGameFalse, this, _1);
//
//	//checkMenuChoice(/*0, */func);
//
//	checkMenuChoice();
//
//
//
//	// ��� ��������
//	string name;
//
//	eraseScreenAfterTitle();
//
//	switch (this->keyBoard->getPressedKey())
//	{
//		case VK_1: case VK_NUMPAD1:
//		{
//			// ��������� �������� ���� �� ���� �� ����� ��� ���
//		}
//		break;
//
//		case VK_2: case VK_NUMPAD2:
//		{
//			cout << "������� ���� ���: ";
//
//			cin >> name;
//
//			this->alchemist->setName(name);
//
//			cout << "\nEnter - ����������" << endl
//				<< "Esc - �����";
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
