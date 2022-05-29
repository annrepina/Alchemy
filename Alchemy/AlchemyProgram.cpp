#include "AlchemyProgram.h"



AlchemyProgram::AlchemyProgram()
{
	this->alchemist = new Alchemist();

	this->effectsTable = nullptr;

	this->ingredientsTable = nullptr;

	
}

void AlchemyProgram::setEffectsTable(EffectsTable* effectsTable)
{
	this->effectsTable = effectsTable;
}

void AlchemyProgram::setIngredientsTable(IngredientsTable* ingredientsTable)
{
	this->ingredientsTable = ingredientsTable;
}

Alchemist* AlchemyProgram::getAlchemist()
{
	return this->alchemist;
}

EffectsTable* AlchemyProgram::getEffectsTable()
{
	return this->effectsTable;
}

IngredientsTable* AlchemyProgram::getIngredientsTable()
{
	return this->ingredientsTable;
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
