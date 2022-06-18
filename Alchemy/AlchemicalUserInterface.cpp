#include "AlchemicalUserInterface.h"

string AlchemicalUserInterface::listOfMainMenuItems[NUMBER_OF_MAIN_MENU_ITEMS] = {
	"����������",
	"������ ���������� � ���������"
};

string AlchemicalUserInterface::listOfALchemicalMenuItems[NUMBER_OF_ALCHEMICAL_MENU_ITEMS] = {
	"�������� �����",
	"������� ������������",
	"������� ������������",
	"�������� ������������",
	"������� �����",
	"������ � ���������",
	"�����"
};

string AlchemicalUserInterface::listOfInstructionsMenuItems[NUMBER_OF_MAIN_MENU_ITEMS] = {
	"�����",
	"����� �� ���������"
};

string AlchemicalUserInterface::listOfBuyingIngredientsMenuItems[NUMBER_OF_BUYING_MENU_ITEMS] = {
	"������� ������������ �� ���������� ������",
	"������� ����� ������������, ������� ��� � ������",
	"�����"
};

string AlchemicalUserInterface::listOfBuyingFaultMenuItems[NUMBER_OF_MAIN_MENU_ITEMS] =
{
	"������� ������ ����������.",
	"������� ������ ���-�� �����������"
};

AlchemicalUserInterface::AlchemicalUserInterface() : UserInterface()
{
	//this->alchemist = new Alchemist();
	//this->ingredientBuilder = new IngredientBuilder();
	this->exitFlag = false;
	this->currentYCursorCoord = MAIN_MENU_Y_COORD;
	this->boundaryYCoord = MAIN_MENU_Y_COORD;
	//this->instructionsXCoord = 0;
	this->instructionsMenuTitle = "���������� � ��������� \"������������\"";
	this->mainMenuTitle = "������� ����";
	this->alchemicalMenuTitle = "���� �������";
	this->buyingIngredientsMenuTitle = "������� ������������";
	this->buingFaultMenuTitle = "������������ ������� ��� ������� ����������� �";

	// ��������� - �������
	this->alchemyProgram = nullptr;

	// ��������� ��� ������������ ���������
	this->alchemyProgramBuilder = new AlchemyProgramBuilder();

	// ������� ����� ���������
	this->alchemyProgramParser = new AlchemyProgramParser();

	this->ingredientsTableprinter = new IngredientsTablePrinter();

	this->state = new MainMenu();
}

void AlchemicalUserInterface::launchMainLoop()
{
	setAlchemyProgram();

	fillAllMenu();

	printTitle();

	printExitButton();

	//do
	//{
	//	printAlchemist();

	//	menuCode = MenuCode::MainMenu;

	//	// ���������� �� ��������� ����������
	//	this->currentYCursorCoord = MAIN_MENU_Y_COORD;

	//	// �������� �� ��������������
	//	eraseScreenAfterAlchemist();

	//	printMenuInLoop(mainMenu, mainMenuTitle);

	//} while (exitFlag == false);	

	do
	{
		printAlchemist();

		//menuCode = MenuCode::MainMenu;

		//// ���������� �� ��������� ����������
		//this->currentYCursorCoord = MAIN_MENU_Y_COORD;

		// �������� �� ��������������
		eraseScreenAfterAlchemist();

		

		printMenuInLoop(mainMenu, mainMenuTitle);

	} while (exitFlag == false);


	printBye();
}

int AlchemicalUserInterface::getBoundaryYCoord()
{
	return this->boundaryYCoord;
}

void AlchemicalUserInterface::setState(MenuState* state)
{
	this->state = state;
}

void AlchemicalUserInterface::setAlchemyProgram()
{
	// ������� ��������� �������
	this->alchemyProgramBuilder->buildAlchemyProgram(this->alchemyProgramParser);

	// ��������� ��������� ��������� �������
	this->alchemyProgram = this->alchemyProgramBuilder->getResult();
}

void AlchemicalUserInterface::chooseMenuItem(map <int, string> menu)
{
	this->func = std::bind(&AlchemicalUserInterface::isArrowKeyFalse, this, _1);

	// ���� ��� ����������� � ���������� ����, �� �� ����� �� ���������
	bool innerExitFlag = false;

	do {
		// ��������� ������� ������
		checkMenuChoice();

		switch (this->keyBoard->getPressedKey())
		{
			case VK_UP:
			{
				// ��������� ���������
				checkVerticalArrowsChoice(boundaryYCoord, VK_UP, menu);
			}
			break;

			case VK_DOWN:
			{
				// ��������� ���������
				checkVerticalArrowsChoice(boundaryYCoord + menu.size() - 1, VK_DOWN, menu);
			}
			break;

			case VK_RETURN:
			{
				// ������� ����� ������ ����
				makeChoice(innerExitFlag);// !! ������������� ��������
			}
			break;

			case VK_ESCAPE:
			{
				exitFlag = true;
			}
			break;
		}
	} while (false == exitFlag && false == innerExitFlag);
}

void AlchemicalUserInterface::choosePage(int page, TableCode code)
{
	this->func = std::bind(&AlchemicalUserInterface::isPageChoiceFalse, this, _1);

	// ���� ���� ������ �� �����
	bool exit = false;

	do
	{
		// ��������� ������� ������
		checkMenuChoice();

		switch (this->keyBoard->getPressedKey())
		{
			case VK_LEFT:
			{
				// ��������� ���������
				//checkVerticalArrowsChoice(boundaryYCoord, VK_UP, menu);
				//checkHorizontalArrowChoice(page, code, VK_LEFT);

				if (checkHorizontalArrowChoice(page, code, VK_LEFT))
				{
					printTablePagesInLoop(code, page);
					exit = true;
				}		
			}
			break;

			case VK_RIGHT:
			{
				// ��������� ���������
				//checkVerticalArrowsChoice(boundaryYCoord + menu.size() - 1, VK_DOWN, menu);
				if (checkHorizontalArrowChoice(page, code, VK_RIGHT))
				{
					printTablePagesInLoop(code, page);
					exit = true;
				}
			}
			break;

			case VK_RETURN:
			{
				exit = true;
			}
			break;

			case VK_ESCAPE:
			{
				exitFlag = true;
			}
			break;
		}
	} while (false == exitFlag && false == exit);
}

int AlchemicalUserInterface::chooseId(string strChoice, TableCode code)
{
	int id = 0;

	string value = "";

	// ������� �� ���������� ��� ������
	cout << goToXY(Y_COORD_AFTER_MENU_TITLE_1, strChoice.size() + 1);

	map<int, Ingredient*>::iterator iter = this->alchemyProgram->getIngredientsTable()->getEndIterator();

	//checkInput(id, 1, iter->first, strChoice);

	if (code == TableCode::IngredientTable)
	{
		map<int, Ingredient*>::iterator iter = this->alchemyProgram->getIngredientsTable()->getEndIterator();

		string errorText = "������� �������� �� ���������� � �������, ���������� �����: ";

		id = checkInput(value, 1, iter->first, errorText, Y_COORD_AFTER_MENU_TITLE_1);
	}
	else
	{

	}

	return id;
}

int AlchemicalUserInterface::chooseNumber(string strChoice, TableCode code)
{
	int number = 0;

	string value = "";

	if (code == TableCode::IngredientTable)
	{
		// ������� �� ���������� ��� ������
		cout << goToXY(Y_COORD_AFTER_MENU_TITLE_2, strChoice.size() + 1);

		map<int, Ingredient*>::iterator iter = this->alchemyProgram->getIngredientsTable()->getEndIterator();

		string errorText = "������ �������� �� ��������, ���������� �����: ";

		number = checkInput(value, 1, MAX_INT, errorText, Y_COORD_AFTER_MENU_TITLE_2);
	}
	else
	{
		//cout << goToXY(Y_COORD_AFTER_MENU_TITLE_3, STANDARD_CURSOR_X_COORD);

		string error = "������������ ������� ��� �������.";

		printColoredTextByCoords(error, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE, Y_COORD_AFTER_MENU_TITLE_3, STANDARD_CURSOR_X_COORD);

	
	}

	return number;
}

void AlchemicalUserInterface::makeChoice(bool& innerExitFlag)
{
	switch (menuCode)
	{
		case MenuCode::MainMenu:
		{
			checkMainMenu(innerExitFlag);
		}
		break;

		case MenuCode::AlchemicalMenu:
		{
			checkAlchemicalMenu(innerExitFlag);
		}
		break;

		case MenuCode::InstructionsMenu:
		{
			checkInstructionsMenu(innerExitFlag);
		}
		break;

		case MenuCode::BuyingIngredientsMenu:
		{
			checkBuyingIngredientsMenu(innerExitFlag);
		}
		break;

		case MenuCode::BuyingFaultMenu:
		{
			checkBuyingFaultMenu();
		}
	}
}

void AlchemicalUserInterface::makeChoice()
{

}

void AlchemicalUserInterface::checkMainMenu(bool& innerExitFlag)
{
	switch (this->currentYCursorCoord)
	{
		case MainMenuCode::DoAlchemy:
		{
			doAlchemy();
		}
		break;

		case MainMenuCode::ReadInstructions:
		{
			printInstructions();
		}
		break;
	}

	innerExitFlag = true;
}

void AlchemicalUserInterface::checkInstructionsMenu(bool& innerExitFlag)
{
	switch (this->currentYCursorCoord)
	{
		case InstructionsMenuCode::InstrReturn:
		{
			//this->menuCode = MenuCode::MainMenu;
			//this->currentYCursorCoord = MAIN_MENU_Y_COORD;

			//eraseScreenAfterAlchemist();

			//printMenuInLoop(mainMenu, mainMenuTitle);

			innerExitFlag = true;
		}
		break;

		case InstructionsMenuCode::Exit:
		{
			this->exitFlag = true;
		}
		break;
	}
}

void AlchemicalUserInterface::checkAlchemicalMenu(bool& innerExitFlag)
{
	switch (this->currentYCursorCoord)
	{
		case AlchemicalMenuCode::MakingPotions:
		{

		}
		break;

		case AlchemicalMenuCode::BuyingIngredients:
		{
			buyIngredients();
		}
		break;



		case AlchemicalMenuCode::AlcReturn:
		{
			innerExitFlag = true;
		}
		break;
	}
}

void AlchemicalUserInterface::checkBuyingIngredientsMenu(bool& innerExitFlag)
{
	switch (this->currentYCursorCoord)
	{
		case BuyingIngredientsMenuCode::ChooseFromList:
		{
			buyIngredientsFromList();
		}
		break;

		case BuyingIngredientsMenuCode::CreateNewIngredient:
		{

		}
		break;
	}

	innerExitFlag = true;
}

void AlchemicalUserInterface::checkBuyingFaultMenu()
{
	switch (this->currentYCursorCoord)
	{
		case BuyingFaultMenuCode::�hooseAnotherIngredient:
		{
			//chooseAnotherIngredient();
		}
		break;

		case BuyingFaultMenuCode::ChangeNumberOfIngredient:
		{
			//changeNumberOfIngredient();
		}
		break;
	}
}

bool AlchemicalUserInterface::checkHorizontalArrowChoice(int& page, TableCode code, int keyCode)
{
	if (VK_LEFT == keyCode)
	{
		// ���� ��� �� ������ ��������
		if (FIRST_PAGE < page)
		{
			--page;
			return true;
		}
			
		else
			return false;
	}

	else
	{
		// ���� ������������� ������� ������������
		if (code == TableCode::IngredientTable)
		{
			int numberOfLines = ingredientsTableprinter->getNumberOfLines();

			if (numberOfLines > page * NUMBER_OF_CONTENT_LINES)
			{
				++page;
				return true;
			}
			else
				return false;
		}

		// ���� ������������� ������� �����
		else 
		{

		}
	}
}

void AlchemicalUserInterface::doAlchemy()
{
	// ���� ��� ������ �� �����
	bool innerExitFlag = false;

	do
	{
		this->currentYCursorCoord = MAIN_MENU_Y_COORD;

		this->menuCode = MenuCode::AlchemicalMenu;

		printMenuInLoop(alchemicalMenu, alchemicalMenuTitle);

	} while (exitFlag == false && innerExitFlag == false);
}

void AlchemicalUserInterface::buyIngredients()
{
	this->currentYCursorCoord = MAIN_MENU_Y_COORD;
	//this->boundaryYCoord = MAIN_MENU_Y_COORD;

	this->menuCode = MenuCode::BuyingIngredientsMenu;

	printMenuInLoop(buyingIngredientsMenu, alchemicalMenuTitle);
}

void AlchemicalUserInterface::buyIngredientsFromList()
{
	// ��������� �������� �������
	int page = FIRST_PAGE;

	string choiceIngredient = "������� � �����������: ";

	string choiceNumber = "������� ���-�� ������������: ";

	// ���� ���� ������ �� �����
	bool exit = false;

	printColoredTextByCoords(choiceIngredient, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE, Y_COORD_AFTER_MENU_TITLE_1, STANDARD_CURSOR_X_COORD);

	//cout << goToXY(Y_COORD_AFTER_MENU_TITLE, STANDARD_CURSOR_X_COORD);

	//cout << eraseOnScreen(FROM_CURSOR_TO_SCREEN_END);

	//printColoredText(choiceIngredient, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE);

	printColoredTextByCoords(choiceNumber, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE, Y_COORD_AFTER_MENU_TITLE_2, STANDARD_CURSOR_X_COORD);

	//cout << goToXY(Y_COORD_AFTER_MENU_TITLE + 1, STANDARD_CURSOR_X_COORD);

	//cout << eraseOnScreen(FROM_CURSOR_TO_SCREEN_END);

	//printColoredText(choiceNumber, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE);

	printTablePagesInLoop(TableCode::IngredientTable, page);

	// ���� ��� ����� esc
	if (true == exitFlag)
		return;

	int id = chooseId(choiceIngredient, TableCode::IngredientTable);

	int number = chooseNumber(choiceNumber, TableCode::IngredientTable);

	tryAddIngredientFromList(id, number);


	
}

bool AlchemicalUserInterface::tryAddIngredientFromList(int id, int number)
{
	// ���������
	bool res = false;

	// ������� ������������
	IngredientsTable* ingredientsTable = this->alchemyProgram->getIngredientsTable();

	// ���� ����������, ���������� �� id 
	Ingredient* ingredient = ingredientsTable->getIngredientById(id);

	// �������� ��������
	Alchemist* alchemist = this->alchemyProgram->getAlchemist();

	// ������ ��������
	int capital = alchemist->getCapital();

	// �������
	int cost = ingredient->getPrice() * number;

	// ���� ����� � �������� ������ ��� ����� ���� �����������
	if (capital >= cost)
	{
		ingredient->increaseNumber(number);

		alchemist->decreaseCapital(number);
	}
	// ���� ����� ������������
	else
	{
		this->currentYCursorCoord = MAIN_MENU_Y_COORD;

		// ������� �������� ����
		string menuTitle = this->buingFaultMenuTitle + to_string(id);

		MenuCode menuCode = MenuCode::BuyingFaultMenu;

		printMenuInLoop(buyingFaultMenu, menuTitle);
	}

	return res;
}

void AlchemicalUserInterface::eraseScreenAfterAlchemist()
{
	cout << goToXY(Y_COORD_AFTER_ALCHEMIST, STANDARD_CURSOR_X_COORD);
	cout << eraseOnScreen(FROM_CURSOR_TO_SCREEN_END);
}

void AlchemicalUserInterface::fillAllMenu()
{
	mainMenu = fillMenuMap(NUMBER_OF_MAIN_MENU_ITEMS, listOfMainMenuItems);
	alchemicalMenu = fillMenuMap(NUMBER_OF_ALCHEMICAL_MENU_ITEMS, listOfALchemicalMenuItems);
	instructionsMenu = fillMenuMap(NUMBER_OF_MAIN_MENU_ITEMS, listOfInstructionsMenuItems);
	buyingIngredientsMenu = fillMenuMap(NUMBER_OF_MAIN_MENU_ITEMS, listOfBuyingIngredientsMenuItems);
	this->buyingFaultMenu = fillMenuMap(NUMBER_OF_MAIN_MENU_ITEMS, listOfBuyingFaultMenuItems/* Y_COORD_AFTER_MENU_TITLE_4*/);
}

void AlchemicalUserInterface::printTitle()
{
	// ��������� �� 1 �� ���� �����
	titleXCoord = calculateXCoordInMiddle(title) - 1;

	printFramedText(title, TITLE_Y_COORD, titleXCoord);
}

void AlchemicalUserInterface::printExitButton()
{
	// ����� ������
	string exit = "ESC - �����";

	// ���������� ������ ������
	int xCoord = calculateConsoleWidth() - exit.length();

	// ������ ������
	cout << goToXY(EXIT_Y_COORD, xCoord) << exit << endl << endl;
}

void AlchemicalUserInterface::printMenuInLoop(map<int, string> menu, string menuTitle)
{
	printMenuTitle(menuTitle);

	printColoredText("�������� ��������:", R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE);
	cout << endl;

	printMenu(menu);

	cout << goToXY(currentYCursorCoord, STANDARD_CURSOR_X_COORD);
	
	chooseMenuItem(menu);
}

void AlchemicalUserInterface::printInstructions()
{
	menuCode = MenuCode::InstructionsMenu;

	this->currentYCursorCoord = MAIN_MENU_Y_COORD;

	printMenuInLoop(instructionsMenu, instructionsMenuTitle);
}

void AlchemicalUserInterface::printBye()
{
	eraseScreenAfterAlchemist();

	printColoredText("�� ������ �������!", R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED);
}

void AlchemicalUserInterface::printAlchemist()
{
	// ���� ���� ������ � ��� ������
	if ("" == this->alchemyProgram->getAlchemist()->getName())
	{
		string name;

		cout << "������� ���� ���: ";
		cin >> name;

		this->alchemyProgram->getAlchemist()->setName(name);
	}

	eraseScreenAfterTitle();

	this->alchemyProgram->getAlchemist()->print();
}

void AlchemicalUserInterface::printMenuTitle(string title)
{
	//eraseScreenAfterAlchemist();

	this->currentXCursorCoord = calculateXCoordInMiddle(title);

	cout << goToXY(this->currentYCursorCoord - TWO_LINES, currentXCursorCoord);

	printColoredText(title, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED);

	cout << endl;
}

void AlchemicalUserInterface::printPageMenu(int page)
{
	string strPage = "�������� " + to_string(page + 1);

	int numberOfSymbols = strPage.size();

	cout << eraseSymbolsOnScreen(to_string(numberOfSymbols));

	printColoredText("�������� " + to_string(page), R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE);

	cout << "\t<-- ������� �� ���������� ��������\t ������� �� ��������� �������� -->\tENTER ����������� ����� ��������";
}

void AlchemicalUserInterface::printTablePagesInLoop(TableCode code, int& page)
{
	if (code == TableCode::IngredientTable)
	{
		this->ingredientsTableprinter->print(this->alchemyProgram->getIngredientsTable(), page);

		printPageMenu(page);

		choosePage(page, TableCode::IngredientTable);
	}
	else
	{

	}
}

bool AlchemicalUserInterface::isPageChoiceFalse(int key)
{
	bool res = VK_LEFT != key && VK_RIGHT != key && VK_ESCAPE != key && VK_RETURN != key;

	return res;
}
