#include "InstructionsMenuState.h"
#include "MainMenuState.h"
#include "AlchemicalUserInterface.h"

InstructionsMenuState::InstructionsMenuState()
{
}

InstructionsMenuState::InstructionsMenuState(AlchemicalUserInterface* alchemicalUserInterface) : MenuState(alchemicalUserInterface)
{
	this->title = "Наставления начинающему алхимику";
	this->goToTitle = "Читать наставления начинающему алхимику";
	this->numberOfStates = NUMBER_OF_INSTRUCIONS_MENU_ITEMS;
}
void InstructionsMenuState::printMenu()
{
	// Сбрасываем координату каждый раз заходя в метод печати
	currentYCursorCoordState = MAIN_MENU_Y_COORD;

	setListOfCreatingFunctions();
	this->setListOfStates();

	fillMap<function<MenuState* (InstructionsMenuState&)>>(stateCreatingFunctions, listOfCreatingFunctions, currentYCursorCoordState, numberOfStates);
	fillMap<MenuState*>(menuStates, listOfStates, this->currentYCursorCoordState, this->numberOfStates);

	//cout << goToXY(this->currentYCursorCoordState + 1, STANDARD_CURSOR_X_COORD);

	printMenuTitle();

	printColoredText("Выберите действие:", R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE);
	cout << endl;

	printMenuItems();

	cout << goToXY(this->currentYCursorCoordState + 1, STANDARD_CURSOR_X_COORD);

	cout << "Ознакомьтесь с инструкцией к программе:\n"
		<< "1. Для переходу по меню пользуйтесь стрелками вверх и вних, для подтверждения выбора нажмите ENTER.\n"
		<< "2. Для выхода из программы нажмите ESC.\n"
		<< "3. Для покупки ингредиентов у Аркадии вы можете пролистать таблицу с помощью кнопок вправо-влево. Для подтверждения выбора страницы нажмите Enter.\n"
		<< "Для выхода из меню покупки нажмите ESC во время листания страниц таблицы.Для покупки ингредиента введите номер и количество ингредиента"
		<< "Выбор подтверждайте кнопкой ENTER.\n"
		<< "Следите за своими монетами, денег должно хватать для покупки ингредиентов, иначе продайте имеющиеся ингредиенты или зелья, чтобы пополнить кошелёк.\n"
		<< "4. Для покупки нового ингредиента введите название ингредиента, затем его количество, выбор подтверждайте кнопкой ENTER.\n"
		<< "Для выхода из меню покупки нового ингредиента нажмите ESC.\n"
		<< "Следите за своими монетами, денег должно хватать для покупки ингредиентов, иначе продайте имеющиеся ингредиенты или зелья, чтобы пополнить кошелёк.\n"
		<< "5. Во время создания зелий вы можете пролистать таблицу с помощью кнопок вправо-влево. Для подтверждения выбора страницы нажмите Enter\n"
		<< "Для выхода из меню покупки нажмите ESC во время листания страниц таблицы\n"
		<< "Для создания зелий введите номер 1го и 2го зелья а также выберите количество зелья, которое хотите создать, выбор подтверждайте кнопкой ENTER\n"
		<< "Выбрать можно только те зелья, которые есть у вас в инвентаре.Следите за их количеством, оно должно быть не меньше количества желаемого зелья\n"
		<< "Если у зелий эффекты не открыты, вам может повезти, вы угадаете с рецептом и создадите рабочее зелье, но к сожалению зелье может не получиться,\n"
		<< "если эффекты у ингредиентов не совпадают\n"
		<< "Для того, чтобы открыть эффекты у ингредиентов вы можете их съесть!Удачи и постарайтесь не отравиться, на вас окажет влияние эффект зелья!\n"
		<< "6. Во время поедания ингредиента вы можете узнать его неоткрытый эффект. Не ешьте ингредиенты, эффекты которых уже открыты.\n"
		<< "Вы можете пролистать таблицу ингредиентов с помощью кнопок вправо - влево.Для подтверждения выбора страницы нажмите Enter\n"
		<< "Для выхода из меню покупки нажмите ESC во время листания страниц таблицы.\n"
		<< "7. Для того, чтобы подзаработать, вы можете продать ингредиенты или зелья. Вы можете пролистать таблицу с помощью кнопок вправо-влево.\n"
		<< "Для подтверждения выбора страницы нажмите Enter. Для выхода из меню продажи нажмите ESC во время листания страниц таблицы.\n"
		<< "Для того, чтобы продать зелье или ингредиент, введите номер, а затем количество.\n"
		<< "Вводите номера только тех ингредиентов и зелий, которые есть у вас в инвентаре\n"
		<< "Для подтверждения выбора нажмите Enter.После продажи у вас прибавятся монеты\n"
		<< "8. Вы также можете поработать с вашим инвентарем, для этого выберете с чем хотите работать: имеющимися у Аркадии ингредиентами, вашими ингредиентами\n"
		<< "или зельями. Вы можете осуществить сортировку и поиск по таблице. Для выбора меню жмите кнопки вверхе/вниз, а затем ENTER для подтверждения выбора.\n"
		<< "Перед работой вы можете полистать таблицы с помощью кнопок вправо/влево, а затем подтвердить выбор с помощью ENTER или выйти в предыдущее меню нажав ESC\n"
		<< "Для сортировки пользуйтесь стрелками вверх / вниз чтобы сортировать по убыванию или возрастанию, \n"
		<< "а также кнопками вправо / влево для выбора столбца, по которому будете сортировать. \n"
		<< "Каждый раз после выбора параметров сортировки вы можете снова пролистать таблицу, чтобы посмотреть на результат.\n"
		<< "Подтверждайте выбор страницы, чтобы работать с сортировкой дальше либо жмите ESC для перехода в поиск либо другие меню.\n"
		<< "Для поиска выберите столбец фильтрации кнопками вверх / вниз, затем подвердите выбор кнопкой ENTER.Затем вводите желаемые значение.\n"
		<< "На таблице появится желаемый результат. Вы снова можете ее полистать, затем подтвердить выбор и работать с поиском дальше!\n"
		<< "Желаю успехов, начинающий алхимик!";

	cout << goToXY(this->currentYCursorCoordState, STANDARD_CURSOR_X_COORD);

	chooseMenuItem();

	this->alchemicalUserInterface->setState(this->getNextState());
}

MenuState* InstructionsMenuState::getNextState()
{
	return this->stateCreatingFunctions[currentYCursorCoordState](*this);
}

void InstructionsMenuState::setListOfStates()
{
	this->listOfStates.push_back(new ReturnMenuState(new MainMenuState(this->alchemicalUserInterface), this->alchemicalUserInterface));
}

void InstructionsMenuState::setListOfCreatingFunctions()
{
	// если вектор пустой
	if (this->listOfCreatingFunctions.empty())
	{
		this->listOfCreatingFunctions.push_back(&InstructionsMenuState::createReturnMenuState);
	}
}

ReturnMenuState* InstructionsMenuState::createReturnMenuState()
{
	return new ReturnMenuState(new MainMenuState(this->alchemicalUserInterface), this->alchemicalUserInterface);
}
