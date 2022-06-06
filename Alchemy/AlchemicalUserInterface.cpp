#include "AlchemicalUserInterface.h"

string AlchemicalUserInterface::listOfMainMenuItems[NUMBER_OF_MAIN_MENU_ITEMS] = {
	"����������",
	"������ ���������� � ���������"
};

// �������� �������� ���� "������� � ����������"
string AlchemicalUserInterface::listOfALchemicalMenuItems[NUMBER_OF_ALCHEMICAL_MENU_ITEMS] = {
	"�������� �����",
	"������� ������������",
	"������� ������������",
	"�������� ������������",
	"������� �����",
	"������ � ���������"
};

string AlchemicalUserInterface::listOfInstructionsMenuItems[NUMBER_OF_MAIN_MENU_ITEMS] = {
	"�����",
	"����� �� ���������"
};

string AlchemicalUserInterface::listOfBuyingIngredientsMenuItems[NUMBER_OF_MAIN_MENU_ITEMS] = {
	"������� ������������ �� ���������� ������",
	"������� ����� ������������, ������� ��� � ������"
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

	// ��������� - �������
	this->alchemyProgram = nullptr;

	// ��������� ��� ������������ ���������
	this->alchemyProgramBuilder = new AlchemyProgramBuilder();

	// ������� ����� ���������
	this->alchemyProgramParser = new AlchemyProgramParser();

	this->ingredientsTableprinter = new IngredientsTablePrinter();
}

void AlchemicalUserInterface::launchMainLoop()
{
	setAlchemyProgram();

	fillAllMenu();

	printTitle();

	printExitButton();

	printAlchemist();

	menuCode = MenuCode::MainMenu;

	printMenuInLoop(mainMenu, mainMenuTitle);

	printBye();
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
				makeChoice();// !! ������������� ��������
			}
			break;

			case VK_ESCAPE:
			{
				exitFlag = true;
			}
			break;
		}
	} while (false == exitFlag);
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
	cout << goToXY(Y_COORD_AFTER_MENU_TITLE, strChoice.size() + 1);

	map<int, Ingredient*>::iterator iter = this->alchemyProgram->getIngredientsTable()->getEndIterator();

	//checkInput(id, 1, iter->first, strChoice);

	if (code == TableCode::IngredientsTable)
	{
		map<int, Ingredient*>::iterator iter = this->alchemyProgram->getIngredientsTable()->getEndIterator();

		id = checkInput(value, 1, iter->first);
	}
	else
	{

	}

	return id;
}

void AlchemicalUserInterface::makeChoice()
{
	switch (menuCode)
	{
		case MenuCode::MainMenu:
		{
			checkMainMenu();
		}
		break;

		case MenuCode::AlchemicalMenu:
		{
			checkAlchemicalMenu();
		}
		break;

		case MenuCode::InstructionsMenu:
		{
			checkInstructionsMenu();
		}
		break;

		case MenuCode::BuyingIngredientsMenu:
		{
			checkBuyingIngredientsMenu();
		}
		break;
	}
}

void AlchemicalUserInterface::checkMainMenu()
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
}

void AlchemicalUserInterface::checkInstructionsMenu()
{
	switch (this->currentYCursorCoord)
	{
		case InstructionsMenuCode::Return:
		{
			this->menuCode = MenuCode::MainMenu;
			this->currentYCursorCoord = MAIN_MENU_Y_COORD;
			//this->boundaryYCoord = MAIN_MENU_Y_COORD;

			eraseScreenAfterAlchemist();

			printMenuInLoop(mainMenu, mainMenuTitle);
		}
		break;

		case InstructionsMenuCode::Exit:
		{
			this->exitFlag = true;
		}
		break;
	}
}

void AlchemicalUserInterface::checkAlchemicalMenu()
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
	}
}

void AlchemicalUserInterface::checkBuyingIngredientsMenu()
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
		if (code == TableCode::IngredientsTable)
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
	this->currentYCursorCoord = MAIN_MENU_Y_COORD;
	//this->boundaryYCoord = MAIN_MENU_Y_COORD;

	this->menuCode = MenuCode::AlchemicalMenu;

	printMenuInLoop(alchemicalMenu, alchemicalMenuTitle);
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

	string choice = "������� id �����������: ";

	// ���� ���� ������ �� �����
	bool exit = false;

	cout << goToXY(Y_COORD_AFTER_MENU_TITLE, STANDARD_CURSOR_X_COORD);

	cout << eraseOnScreen(FROM_CURSOR_TO_SCREEN_END);

	printColoredText(choice, R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE);


	printTablePagesInLoop(TableCode::IngredientsTable, page);

	if (true == exitFlag)
		return;

	//do
	//{
	//	this->ingredientsTableprinter->print(this->alchemyProgram->getIngredientsTable(), page);

	//	printPageMenu(page);

	//	choosePage(page, TableCode::IngredientsTable, exit);

	//} while (false == exit);



	int id = chooseId(choice, TableCode::IngredientsTable);


	//// ������� �� ���������� ��� ������
	//cout << goToXY(Y_COORD_AFTER_MENU_TITLE, choice.size() + 1);
	
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
	//this->boundaryYCoord = MAIN_MENU_Y_COORD;

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
	eraseScreenAfterAlchemist();

	this->currentXCursorCoord = calculateXCoordInMiddle(title);

	cout << goToXY(Y_COORD_AFTER_ALCHEMIST, currentXCursorCoord);

	printColoredText(title, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED);
	cout << endl;
}

void AlchemicalUserInterface::printPageMenu(int page)
{
	printColoredText("�������� " + to_string(page), R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE);

	cout << "\t<-- ������� �� ���������� ��������\t ������� �� ��������� �������� -->\tENTER ����������� ����� ��������";
}

void AlchemicalUserInterface::printTablePagesInLoop(TableCode code, int& page)
{
	if (code == TableCode::IngredientsTable)
	{
		this->ingredientsTableprinter->print(this->alchemyProgram->getIngredientsTable(), page);

		printPageMenu(page);

		choosePage(page, TableCode::IngredientsTable);
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
