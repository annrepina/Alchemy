#pragma once
#include "WorkWithIngredientTableMenuState.h"
#include "ReturnMenuState.h"
#include "PotionTablePrinter.h"

#define MINIMUM_NUMBER_OF_POTIONTS								1	// ����������� ���-�� �����

class AlchemicalMenuState;

class WorkWithPotionTableMenuState : public WorkWithIngredientTableMenuState
{
public:

	WorkWithPotionTableMenuState();

	WorkWithPotionTableMenuState(AlchemicalUserInterface* alchemicalUserInterface);

	//~WorkWithTablesMenuState() override;

	// ������ ����
	void printMenu() override;

protected:

	void setContent() override;

	PotionTablePrinter* potionTablePrinter;

	//virtual void sortData();

	void setListOfColumnTitles() override;

	void launchFilterMenu() override;

	void launchSortingMenu() override;

	// ������� ������� �������� ���������� ��� ������� � �������?
	bool isStringColumn(int numberOfColumn) override;

	// ��������� ����������
	void sortData() override;

	void filterData() override;

private:

	// �������� ��������� ���������
	MenuState* getNextState() override;

	// ������ ������ ���������
	void setListOfStates() override;

	// ������ ������ ��������� ������ �������
	void setListOfCreatingFunctions() override;

	// Map �������, ������� ������� ������ � �� ����� - ���������� ������� ����
	map<int, function<MenuState* (WorkWithPotionTableMenuState&)> > stateCreatingFunctions;

	// ������ �������, ������� ������� ������
	vector< function<MenuState* (WorkWithPotionTableMenuState&)> > listOfCreatingFunctions;

	// ������� ��������� - ���� �����
	ReturnMenuState* createReturnMenuState();
};

