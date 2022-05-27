#pragma once
//#include <string>
//#include <conio.h>
//#include <functional>
//#include "Formatting.h"
//#include "KeyBoard.h"
#include "Alchemist.h"
//#include "EffectsTableBuilder.h"
#include "IngredientsTable.h"
#include "EffectsTable.h"

//using namespace std;
//
//using std::placeholders::_1;

//// ����������
//#define TITLE_Y_COORD			1		// ���������� Y ������� ��� ������ �������� ���������
//#define Y_COORD_AFTER_TITLE		4		// ���������� Y ����� ������� ���������
//
//// ���� ������
//#define VK_1					0x31	// ������� 1
//#define VK_2					0x32	// ������� 2
//#define VK_NUMPAD1				0x61	// ������� �������� ���������� 1
//#define VK_NUMPAD2				0x62	// ������� �������� ���������� 2
//#define VK_ESCAPE				0x1B	// ������� ESC
//#define VK_RETURN				0x0D	// ������� Enter

class AlchemyProgram
{
public:

	// ����������� �� ���������
	AlchemyProgram();

#pragma region �������

	// ������ ��� ������� ��������
	void setEffectsTable(EffectsTable* effectsTable);

	// ������ ��� ������� ������������
	void setIngredientsTable(IngredientsTable* ingredientsTable);

#pragma endregion �������




#pragma region �������

	// ������ ��� ��������
	Alchemist* getAlchemist();

#pragma endregion �������

	//// ������ �������� ����� ���������
	//void launchMainLoop();

private:

	// ������� (������������)
	Alchemist* alchemist;

	// ������� ��������
	EffectsTable* effectsTable;

	// ������� ������������
	IngredientsTable* ingredientsTable;

	//// ��������� ������� ��������
	//EffectsTableBuilder* effectsTableBuilder;



//	// ������� ��� ����������
//	function<bool(int)> func;
//
//	// ���������� � - ������ �������� ���������
//	int titleXCoord;
//
	//// �������� ���������
	//string title = "������������";
//
//	//// ������� ������������� �������
//	//int key;
//	
//	// ��������� ����������
//	KeyBoard* keyBoard;
//
//	// ����������� ���������� � ��� ����������
//	void setXCoord();
//
//	//// ��������� ������� ������
//	//void getKey();
//
//	//// �������� ������ � ����
//	//void checkMenuChoice(/*int key, */function<bool(int)> condition /*bool (*condition) (int key)*/);
//
//	// �������� ������ � ����
//	void checkMenuChoice();
//
//	// ���������� ��������
//	void doAlchemy();
//
//
//
//	// �������� ��������� ���������
//	void printTitle();
//
//	// ������ ����
//	void printMenu();
//
//	// ������ ����������
//	void printInstructions();
//
//	// ������� �� ������� ��, ����� �������� ���������
//	void eraseScreenAfterTitle();
//
//
//
//#pragma region ���������
//
//	// �������� ��� ������ ������������ � ������� ����
//	bool isMenuChoiceFalse(int key);
//
//	// �������� ��� ������ ����������� ��� �������� ����
//	bool isContinueGameFalse(int key);
//
//	// ���������� ������ ���������� ��� �����
//	bool isContinue(int key);
//
//#pragma endregion ���������

};

