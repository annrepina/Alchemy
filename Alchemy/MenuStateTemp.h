#pragma once
//#include <string>
//#include <iostream>
//#include <map>
//#include <functional>
//#include "Formatting.h"
//#include "ServiceFunctions.h"
//
//using namespace std;
//
//// ����������
//#define MAIN_MENU_Y_COORD				10		// ���������� Y ���� ��������
//
//class AlchemicalUserInterface;
//
//template<typename T>
//class MenuStateTemp
//{
//public:
//
//	// ����������� �� ���������
//	MenuStateTemp()
//	{
//		this->title = "";
//		this->goToTitle = "";
//		this->alchemicalUserInterface = nullptr;
//		this->boundaryYCoord = MAIN_MENU_Y_COORD;
//		//this->exitFlag = false;
//		this->numberOfStates = 0;
//	}
//
//	// ����������� � ����������
//	MenuStateTemp(AlchemicalUserInterface* alchemicalUserInterface)
//	{
//		this->alchemicalUserInterface = alchemicalUserInterface;
//	}
//
//	// ����������� �����������
//	MenuStateTemp(MenuStateTemp const& copyMenuState)
//	{
//		this->alchemicalUserInterface = copyMenuState.alchemicalUserInterface;
//		this->boundaryYCoord = copyMenuState.boundaryYCoord;
//		this->goToTitle = copyMenuState.goToTitle;
//		this->numberOfStates = copyMenuState.numberOfStates;
//		this->title = copyMenuState.title;
//	}
//
//	// ���������� ��������� ������������
//	MenuStateTemp& operator = (MenuStateTemp const& right)
//	{
//		if (right.alchemicalUserInterface != nullptr)
//		{
//			this->alchemicalUserInterface = right.alchemicalUserInterface;
//			this->boundaryYCoord = right.boundaryYCoord;
//			this->goToTitle = right.goToTitle;
//			this->numberOfStates = right.numberOfStates;
//			this->title = right.title;
//		}
//		// TODO: �������� ����� �������� return
//
//		return *this;
//	}
//
//	// ����������
//	virtual ~MenuStateTemp()
//	{
//		clear();
//	}
//
//	// ������ ���������
//	virtual void setAlchemicalUserInterface(AlchemicalUserInterface* alchemicalUserInterface)
//	{
//		this->alchemicalUserInterface = alchemicalUserInterface;
//	}
//
//	// ������ ����
//	virtual void printMenu()
//	{
//		// ���������� ���������� ������ ��� ������ � ����� ������
//		currentYCursorCoordState = MAIN_MENU_Y_COORD;
//
//		this->setListOfStates();
//
//		fillMap<MenuState*>(menuStates, listOfStates, this->currentYCursorCoordState, this->numberOfStates);
//
//		printMenuTitle();
//
//		printColoredText("�������� ��������:", R_AQUAMARINE, G_AQUAMARINE, B_AQUAMARINE);
//		cout << endl;
//
//		printMenuItems();
//
//		cout << goToXY(/*this->alchemicalUserInterface->getCurrentYCursorCoord()*/this->currentYCursorCoordState, STANDARD_CURSOR_X_COORD);
//
//		chooseMenuItem();
//
//		this->alchemicalUserInterface->setState(this->getNextState());
//	}
//
//	//void fillMenuStates();
//
//protected:
//
//	// ��������� ����������
//	AlchemicalUserInterface* alchemicalUserInterface;
//
//	// �������� ����
//	string title;
//
//	// �������� ���� ��� �������� � ����
//	string goToTitle;
//
//	// ������� ���������� Y ������� 
//	static int currentYCursorCoordState = MAIN_MENU_Y_COORD;
//
//	// ������� ���������� X ������� 
//	static int currentXCursorCoordState = 0;
//
//	// ��������� ���������� Y ��� ���������� ���������
//	int boundaryYCoord;
//
//	// ���-�� ��������� � ������� ���������
//	int numberOfStates;
//
//	// �������� ��������� ���������
//	virtual MenuStateTemp* getNextState() = 0;
//
//	// ������ ������ ���������
//	virtual void setListOfStates() = 0;
//
//	// ������ ������ ��������� ������ �������
//	virtual void setListOfCreatingFunctions() = 0;
//
//	// ������ �������� ����
//	virtual void printMenuTitle()
//	{
//		this->currentXCursorCoordState = calculateXCoordInMiddle(title);
//
//		//this->alchemicalUserInterface->currentXCursorCoord = calculateXCoordInMiddle(title);
//
//		//this->currentXCursorCoord = calculateXCoordInMiddle(title);
//
//		/*cout << goToXY(this->alchemicalUserInterface->getCurrentYCursorCoord() - TWO_LINES, this->alchemicalUserInterface->getCurrentXCursorCoord());*/
//
//		cout << goToXY(this->currentYCursorCoordState - TWO_LINES, this->currentXCursorCoordState);
//
//		printColoredText(title, R_DECIMAL_RED, G_DECIMAL_RED, B_DECIMAL_RED);
//
//		cout << endl;
//	}
//
//	// ������ �������� ����
//	virtual void printMenuItems()
//	{
//
//		int border = this->boundaryYCoord + this->menuStates.size();
//
//		// �������� ������������� ������
//		for (int i = this->currentYCursorCoordState; i < border; ++i)
//		{
//			if (i == this->currentYCursorCoordState)
//			{
//				printTextWithBackground(this->menuStates[i]->goToTitle, R_DECIMAL_GREY, G_DECIMAL_GREY, B_DECIMAL_GREY);
//				cout << endl;
//			}
//
//			else
//				// �������� ����� ����
//				cout << menuStates[i]->goToTitle << endl;
//		}
//	}
//
//	// ������� �������
//	virtual void chooseMenuItem()
//	{
//		this->alchemicalUserInterface->setFunc(std::bind(&AlchemicalUserInterface::isArrowKeyFalse, this->alchemicalUserInterface, _1));
//
//		// ���� ��� ������ �� �����, �� �� ����� �� ���������
//		bool innerExitFlag = false;
//
//		do
//		{
//			// ��������� ������� ������
//			this->alchemicalUserInterface->checkMenuChoice();
//
//			//checkMenuChoice();
//
//			//switch (this->keyBoard->getPressedKey())
//			switch (this->alchemicalUserInterface->getKeyBoard()->getPressedKey())
//			{
//			case VK_UP:
//			{
//				// ��������� ���������
//				/*this->alchemicalUserInterface->checkVerticalArrowsChoice(this->alchemicalUserInterface->getBoundaryYCoord(), VK_UP, menu);*/
//				this->checkVerticalArrowsChoice(this->boundaryYCoord, VK_UP);
//
//				//checkVerticalArrowsChoice(boundaryYCoord, VK_UP, menu);
//			}
//			break;
//
//			case VK_DOWN:
//			{
//				// ��������� ���������
//				this->checkVerticalArrowsChoice(this->boundaryYCoord + menuStates.size() - 1, VK_DOWN);
//
//				//checkVerticalArrowsChoice(boundaryYCoord + menu.size() - 1, VK_DOWN, menu);
//			}
//			break;
//
//			case VK_RETURN:
//			{
//				// ������� ����� ������ ����
//				//makeChoice(innerExitFlag);// !! ������������� ��������
//
//				// ����� �� �����
//				innerExitFlag = true;
//			}
//			break;
//
//			case VK_ESCAPE:
//			{
//				this->alchemicalUserInterface->setExitFlag(true);
//				//exitFlag = true;
//			}
//			break;
//			}
//		} while (false == this->alchemicalUserInterface->getExitFlag() && false == innerExitFlag);
//	}
//
//	// ������������� ������ ���������
//	std::map<int, MenuStateTemp*> menuStates;
//
//	// ������ ��������� ����� ����
//	vector<MenuStateTemp*> listOfStates;
//
//	// �������� ������ ��������� �����/����
//	void checkVerticalArrowsChoice(int borderYCoord, int keyCode)
//	{
//		// ���� ��������� ���������� �� ����� �������
//		if (borderYCoord != this->currentYCursorCoordState)
//		{
//			// ���� ������ ����
//			if (VK_DOWN == keyCode)
//			{
//				// �������� ����� ���� ��� ���������
//				cout << menuStates[currentYCursorCoordState]->goToTitle;
//
//				// ����������� ����������
//				++this->currentYCursorCoordState;
//			}
//			// ���� ������ �����
//			else
//				// ��������� ����������
//				--this->currentYCursorCoordState;
//
//			// ��������� �� �����������
//			cout << goToXY(this->currentYCursorCoordState, 0);
//
//			printMenuItems();
//
//			// ������������ � ����������
//			cout << goToXY(currentYCursorCoordState, 0);
//		}
//	}
//
//	// �������� ������
//	virtual void clear()
//	{
//		for (auto state : this->listOfStates)
//		{
//			delete state;
//
//			state = nullptr;
//		}
//	}
//
//	// Map �������, ������� ������� ������ � �� ����� - ���������� ������� ����
//	map<int, function<MenuStateTemp* (T&)> > stateCreatingFunctions;
//
//	// ��������� map �������, ������� ������� ������ � �� �����
//	void fillStateCreatingFunctions()
//	{
//		// ��������� ���� � ������������� �������
//		int startKey = this->currentYCursorCoordState;
//
//		// ��������� ������������� ������
//		for (int i = 0; i < this->numberOfStates; ++i, ++startKey)
//		{
//			stateCreatingFunctions.emplace(startKey, this->listOfCreatingFunctions[i]);
//		}
//	}
//
//	// ������ �������, ������� ������� ������
//	vector< function<MenuStateTemp* (T&)> > listOfCreatingFunctions;
//
//private:
//
//};


