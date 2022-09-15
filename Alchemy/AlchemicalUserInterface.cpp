#include "AlchemicalUserInterface.h"

AlchemicalUserInterface::AlchemicalUserInterface() : UserInterface()
{
	this->wasExit = false;
	this->currentYCursorCoord = MAIN_MENU_Y_COORD;
	this->boundaryYCoord = MAIN_MENU_Y_COORD;
	this->instructionsMenuTitle = "���������� � ��������� \"������������\"";
	this->mainMenuTitle = "������� ����";
	this->alchemicalMenuTitle = "���� �������";
	this->buyingIngredientsMenuTitle = "������� ������������";
	this->buingFaultMenuTitle = "������������ ������� ��� ������� ����������� �";
	this->title = "������������";
	this->pathForWriting = "AlchemyLogicBinary.txt";

	// ��������� - �������
	this->alchemyLogic = nullptr;

	// ��������� ��� ������������ ���������
	this->alchemyLogicBuilder = new AlchemyLogicBuilder();

	this->alchemyLogicWriter = new AlchemyLogicWriter();
	this->alchemyLogicReader = new AlchemyLogicReader();

	this->ingredientsTableprinter = new IngredientsTablePrinter();
	this->potionTablePrinter = new PotionTablePrinter();

	this->state = new MainMenuState(this);
}

AlchemicalUserInterface::~AlchemicalUserInterface()
{
	// �������� ���������� �������� ������
	UserInterface::~UserInterface();

	clear();
}

void AlchemicalUserInterface::launchProgram()
{
	setAlchemyLogic();
	setTables();

	calculateTablesData();

	fillInTablesContent();

	addSubscribers();

	printAlchemyLogic();

	writeAlchemyLogic();
}

#pragma region �������

int AlchemicalUserInterface::getBoundaryYCoord()
{
	return this->boundaryYCoord;
}

bool AlchemicalUserInterface::getWasExit()
{
	return this->wasExit;
}

AlchemyLogic* AlchemicalUserInterface::getAlchemyLogic()
{
	return this->alchemyLogic;
}

IngredientsTablePrinter* AlchemicalUserInterface::getIngredientsTablePrinter()
{
	return this->ingredientsTableprinter;
}

PotionTablePrinter* AlchemicalUserInterface::getPotionTablePrinter()
{
	return this->potionTablePrinter;
}

#pragma endregion �������

#pragma region �������

void AlchemicalUserInterface::setState(MenuState* state)
{
	if (state != nullptr)
	{
		if (this->state != nullptr)
		{
			delete this->state;
			this->state = nullptr;
		}

		this->state = state;
	}
}

void AlchemicalUserInterface::setWasExit(bool exit)
{
	this->wasExit = exit;
}

void AlchemicalUserInterface::setTables()
{
	// �������� � ������� �������
	this->ingredientsTableprinter->setTable(this->alchemyLogic->getIngredientsTable());
	this->potionTablePrinter->setTable(this->alchemyLogic->getPotionTable());
}

void AlchemicalUserInterface::setAlchemyLogic()
{
	// ������ �� ����
	bool isFileEmpty = isFileForReadingEmpty();

	if (isFileEmpty)
	{
		// ������� ��������� �������
		this->alchemyLogicBuilder->buildAlchemyProgram();

		// ��������� ��������� ��������� �������
		this->alchemyLogic = this->alchemyLogicBuilder->getResult();
	}
	else
	{
		ifstream istream;

		this->alchemyLogic = alchemyLogicReader->readFromFile(this->pathForWriting, istream);
	}
}

bool AlchemicalUserInterface::isFileForReadingEmpty()
{
	bool res = false;

	ifstream stream;

	// ��������� ����
	stream.open(this->pathForWriting, std::ios::binary);

	int end = stream.peek();

	if (end == EOF) 
	{
		if (stream.eof())
			res = true;
	}

	stream.close();

	return res;
}

#pragma endregion �������

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
				wasExit = true;
			}
			break;
		}
	} while (false == wasExit && false == exit);
}

void AlchemicalUserInterface::choosePageWhileSorting(vector<vector<string>> content, int page, TableCode code, int numberOfColumn, bool orderOfSorting)
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
				if (checkHorizontalArrowChoice(content.size(), page, code, VK_LEFT))
				{
					printTablePagesInLoopWhileSorting(content, code, page, numberOfColumn, orderOfSorting);
					exit = true;
				}
			}
			break;

			case VK_RIGHT:
			{
				// ��������� ���������
				if (checkHorizontalArrowChoice(content.size(), page, code, VK_RIGHT))
				{
					printTablePagesInLoopWhileSorting(content, code, page, numberOfColumn, orderOfSorting);
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
				wasExit = true;
			}
			break;
		}
	} while (false == wasExit && false == exit);
}

void AlchemicalUserInterface::choosePageFromAvailableContentOfIngredientsTable(int page)
{
	this->func = std::bind(&AlchemicalUserInterface::isPageChoiceFalse, this, _1);

	// ���� ���� ������ �� �����
	bool exit = false;

	int contentSize = this->ingredientsTableprinter->getNumberOfAvailableContent();

	do
	{
		// ��������� ������� ������
		checkMenuChoice();

		switch (this->keyBoard->getPressedKey())
		{
			case VK_LEFT:
			{
				if (checkHorizontalArrowChoice(contentSize, page, TableCode::IngredientTable, VK_LEFT))
				{
					printIngredientsTableWithAvailableToUserElements(page);
					exit = true;
				}
			}
			break;

			case VK_RIGHT:
			{
				// ��������� ���������
				if (checkHorizontalArrowChoice(contentSize, page, TableCode::IngredientTable, VK_RIGHT))
				{
					printIngredientsTableWithAvailableToUserElements(page);
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
				wasExit = true;
			}
		break;
		}
	} while (false == wasExit && false == exit);
}

void AlchemicalUserInterface::chooseColumnAndOrderOfSorting(int& numberOfColumn, bool& orderOfSorting, TableCode code)
{
	this->func = std::bind(&AlchemicalUserInterface::isColumnAndOrderChoiceFalse, this, _1);

	// ���� ���� ������ �� �����
	bool exit = false;

	int page = FIRST_PAGE;

	do
	{
		// ��������� ������� ������
		checkMenuChoice();

		switch (this->keyBoard->getPressedKey())
		{
			case VK_LEFT:
			{
				if (checkHorizontalArrowChoice(numberOfColumn, VK_LEFT, code))
					exit = true;
			}
			break;

			case VK_RIGHT:
			{
				// ��������� ���������
				if (checkHorizontalArrowChoice(numberOfColumn, VK_RIGHT, code))
					exit = true;
			}
			break;

			case VK_DOWN:
			{
				if (checkVerticalArrowChoice(orderOfSorting, VK_DOWN, code))
					exit = true;

			}
			break;

			case VK_UP:
			{
				if (checkVerticalArrowChoice(orderOfSorting, VK_UP, code))
					exit = true;
			}
			break;

			case VK_RETURN:
			{
				exit = true;
			}
			break;

			case VK_ESCAPE:
			{
				wasExit = true;
			}
			break;
		}
	} while (false == wasExit && false == exit);
}

void AlchemicalUserInterface::calculateTablesData()
{
	// ������� ������ �� �������� 
	this->ingredientsTableprinter->calculateData();
	this->potionTablePrinter->calculateData();
}

void AlchemicalUserInterface::fillInTablesContent()
{
	// ��������� ������� ���������
	this->ingredientsTableprinter->fillInTableContent();
	this->potionTablePrinter->fillInTableContent();
}

void AlchemicalUserInterface::addSubscribers()
{
	// ��������� �����������
	this->alchemyLogic->getIngredientsTable()->subscribe(this->ingredientsTableprinter);
	this->alchemyLogic->getPotionTable()->subscribe(this->potionTablePrinter);
}

void AlchemicalUserInterface::chooseExit()
{
	this->func = std::bind(&AlchemicalUserInterface::isEscKeyFalse, this, _1);

	do
	{
		// ��������� ������� ������
		checkMenuChoice();

		if (this->keyBoard->getPressedKey() == VK_ESCAPE)
		{
			wasExit = true;
		}

	} while (false == wasExit);
}

int AlchemicalUserInterface::chooseId(TableCode code)
{
	int id = 0;

	string value = "";

	string errorText = "������� �������� �� ���������� � �������, ���������� �����: ";

	if (code == TableCode::IngredientTable)
	{
		auto iter = --this->alchemyLogic->getIngredientsTable()->getEndIterator();

		id = checkInput(value, 1, iter->first, errorText, Y_COORD_AFTER_MENU_TITLE_2, STANDARD_CURSOR_X_COORD);
	}
	else
	{
		auto iter = --this->alchemyLogic->getPotionTable()->getEndIterator();

		id = checkInput(value, 1, iter->first, errorText, Y_COORD_AFTER_MENU_TITLE_2, STANDARD_CURSOR_X_COORD);
	}

	return id;
}

int AlchemicalUserInterface::chooseNumber(string strChoice, int yCoord)
{
	int number = 0;

	string value = "";

	// ������� �� ���������� ��� ������
	cout << goToXY(yCoord, strChoice.size() + 1);

	string errorText = "������ �������� �� ��������, ���������� �����: ";

	number = checkInput(value, 1, MAX_INT, errorText, yCoord, STANDARD_CURSOR_X_COORD);

	return number;
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
		int numberOfLines;

		// ���� ������������� ������� ������������
		if (code == TableCode::IngredientTable)
			numberOfLines = ingredientsTableprinter->getNumberOfLines();

		// ���� ������������� ������� �����
		else 
			numberOfLines = potionTablePrinter->getNumberOfLines();


		if (numberOfLines > page * NUMBER_OF_CONTENT_LINES)
		{
			++page;
			return true;
		}
		else
			return false;
	}
}

bool AlchemicalUserInterface::checkHorizontalArrowChoice(int contentSize, int& page, TableCode code, int keyCode)
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
		if (contentSize > page * NUMBER_OF_CONTENT_LINES)
		{
			++page;
			return true;
		}
		else
			return false;
	}
}

bool AlchemicalUserInterface::checkHorizontalArrowChoice(int& numberOfColums, int keyCode, TableCode code)
{
	if (VK_LEFT == keyCode)
	{
		// ���� ��� �� ������ �������
		if (DEFAULT_NUMBER_OF_COLUMN < numberOfColums)
		{
			--numberOfColums;
			return true;
		}

		else
			return false;
	}

	else
	{
		int totalNumberOfColumns;

		// ���� ������������� ������� ������������
		if (code == TableCode::IngredientTable)
			totalNumberOfColumns = ingredientsTableprinter->getNumberOfColumns();

		// ���� ������������� ������� �����
		else
			totalNumberOfColumns = potionTablePrinter->getNumberOfColumns();

		// ���� ��� �� ��������� �������
		if (totalNumberOfColumns > numberOfColums)
		{
			++numberOfColums;
			return true;
		}
		else
			return false;
	}
}

bool AlchemicalUserInterface::checkVerticalArrowChoice(bool& orderOfSorting, int keyCode, TableCode code)
{
	if (VK_UP == keyCode)
	{
		// ���� ��� ��� �� ���������� �� �����������
		if (ASCENDING_ORDER_OF_SORTING != orderOfSorting)
		{
			orderOfSorting = ASCENDING_ORDER_OF_SORTING;
			return true;
		}

		else
			return false;
	}

	else
	{
		// ���� ��� ��� �� ���������� �� ��������
		if (DESCENDING_ORDER_OF_SORTING != orderOfSorting)
		{
			orderOfSorting = DESCENDING_ORDER_OF_SORTING;
			return true;
		}
		else
			return false;
	}
}

void AlchemicalUserInterface::eraseScreenAfterAlchemist()
{
	cout << goToXY(Y_COORD_AFTER_ALCHEMIST, STANDARD_CURSOR_X_COORD);
	cout << eraseOnScreen(FROM_CURSOR_TO_SCREEN_END);
}

void AlchemicalUserInterface::clear()
{
	if (nullptr != this->alchemyLogic)
	{
		delete this->alchemyLogic;
		this->alchemyLogic = nullptr;
	}

	if (nullptr != this->alchemyLogicBuilder)
	{
		delete this->alchemyLogicBuilder;
		this->alchemyLogicBuilder = nullptr;
	}

	if (nullptr != this->alchemyLogicWriter)
	{
		delete this->alchemyLogicWriter;
		this->alchemyLogicWriter = nullptr;
	}

	if (nullptr != this->alchemyLogicReader)
	{
		delete this->alchemyLogicReader;
		this->alchemyLogicReader = nullptr;
	}

	if (nullptr != this->ingredientsTableprinter)
	{
		delete this->ingredientsTableprinter;
		this->ingredientsTableprinter = nullptr;
	}

	if (nullptr != this->potionTablePrinter)
	{
		delete this->potionTablePrinter;
		this->potionTablePrinter = nullptr;
	}

	if (nullptr != this->state)
	{
		delete this->state;
		this->state = nullptr;
	}
}

void AlchemicalUserInterface::writeAlchemyLogic()
{
	ofstream stream;

	this->alchemyLogicWriter->write(stream, this->pathForWriting, this->alchemyLogic);
}

#pragma region ������ ������

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
}

void AlchemicalUserInterface::printBye()
{
	eraseScreenAfterAlchemist();

	printColoredText("�� ������ �������!", R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED);
}

void AlchemicalUserInterface::printAlchemist()
{
	// ���� ���� ������ � ��� ������
	if ("" == this->alchemyLogic->getAlchemist()->getName())
	{
		cout << "������� ���� ���: ";

		string name;

		do {

			enter(name);

			if (name == "")
				continue;

			else
				break;

		} while (true);

		this->alchemyLogic->getAlchemist()->setName(name);
	}

	eraseScreenAfterTitle();

	this->alchemyLogic->getAlchemist()->print();
}

void AlchemicalUserInterface::printMenuTitle(string title)
{
	this->currentXCursorCoord = calculateXCoordInMiddle(title);

	cout << goToXY(this->currentYCursorCoord - TWO_LINES, currentXCursorCoord);

	printColoredText(title, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED);

	cout << endl;
}

void AlchemicalUserInterface::printPageMenu(int page)
{
	string strPage = "�������� " + to_string(page + 1);

	int numberOfSymbols = strPage.size();

	cout << goToXY(PAGE_Y_COORD, 0);

	cout << eraseSymbolsOnScreen(to_string(numberOfSymbols));

	printColoredText("�������� " + to_string(page), R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE);

	cout << "\t<-- ������� �� ���������� ��������\t ������� �� ��������� �������� -->\tENTER ����������� ����� ��������\t ESC - �����";
}

void AlchemicalUserInterface::printTablePagesInLoop(TableCode code, int& page)
{
	if (code == TableCode::IngredientTable)
		this->ingredientsTableprinter->print(page);

	else
		this->potionTablePrinter->print(page);

	printPageMenu(page);

	choosePage(page, code);
}

void AlchemicalUserInterface::printTablePagesInLoopWhileSorting(vector<vector<string>> content, TableCode code, int& page, int numberOfColumn, bool orderOfSorting)
{
	if (code == TableCode::IngredientTable)
		this->ingredientsTableprinter->print(content, page, numberOfColumn, orderOfSorting);

	else
		this->potionTablePrinter->print(content, page, numberOfColumn, orderOfSorting);

	printPageMenu(page);

	choosePageWhileSorting(content, page, code, numberOfColumn, orderOfSorting);
}

void AlchemicalUserInterface::printIngredientsTableWithAvailableToUserElements(int& page)
{
	if (this->ingredientsTableprinter->getNumberOfAvailableContent() <= (page - 1) * NUMBER_OF_CONTENT_LINES)
		return;

	this->ingredientsTableprinter->printAvailableElements(page);

	printPageMenu(page);

	choosePageFromAvailableContentOfIngredientsTable(page);
}

void AlchemicalUserInterface::printAlchemyLogic()
{
	printTitle();

	printExitButton();

	do
	{
		printAlchemist();

		// �������� �� ��������������
		eraseScreenAfterAlchemist();

		this->state->printMenu();

	} while (wasExit == false);

	printBye();
}

#pragma endregion ������ ������

bool AlchemicalUserInterface::isPageChoiceFalse(int key)
{
	bool res = VK_LEFT != key && VK_RIGHT != key && VK_ESCAPE != key && VK_RETURN != key;

	return res;
}

bool AlchemicalUserInterface::isColumnAndOrderChoiceFalse(int key)
{
	bool res = VK_LEFT != key && VK_RIGHT != key && VK_ESCAPE != key && VK_RETURN != key && VK_UP != key && VK_DOWN != key;

	return res;
}