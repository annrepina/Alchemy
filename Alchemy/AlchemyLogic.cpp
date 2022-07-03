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
		ingredient->increaseNumber(number);

		// ���������� ����������� �� ����������
		ingredientsTable->notify(id);

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
		// ������� ��������� ������������
		IngredientBuilder builder;

		// ������ ������� ��������
		builder.setEffectsTable(this->effectsTable);

		builder.setName(ingredientName);

		int price = randInRange(MIN_PRICE, MAX_PRICE);

		builder.setPrice(price);

		// ������� ��������� ������ id ��������
		vector<int> tempEffectsId;

		// ������������ id ������� 
		int maxEffectId = builder.getEffectsTableSize();

		// ���������� ��������
		for (int i = 0; i < NUMBER_OF_EFFECTS; ++i)
		{
			int idIndex = randInRange(1, maxEffectId);

			// ���� ��� ��� �� ������ ������ � ���������� ��������� � ����� ���������
			if (0 < i && tempEffectsId[0] == idIndex)
			{
				--i;
				continue;
			}

			// ��������� �� ��������� ������ id
			tempEffectsId.push_back(idIndex);

			builder.addEffect(idIndex);
		}

		// ��������� ���������� � �������
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
		// ���� ����� ���������, �� ���������� false
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
