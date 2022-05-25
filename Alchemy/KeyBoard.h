#pragma once
#include <conio.h>

#define ORIGINAL_VALUE -1				// �������� �������� ������

#define FUNCTIONAL_KEY_CODE		224		// ��� �������������� �������

// ����� - ���������� 
class KeyBoard
{
public:

	// ����������� ����� ��� ��������� ������������� ���������� ������
	static KeyBoard* getInstance();

	// ������ ��� ������� �������
	int getPressedKey();

	// ���� ������� �������
	void waitForKey();

	// ������� ������������� ������
	static void release();


private:

	// ������������ ��������� ����������
	static KeyBoard* instance;

	// ��������� ����������� �� ���������
	KeyBoard();

	// ��������� ����������
	~KeyBoard();

	// ��������� ����������� �����������
	KeyBoard(const KeyBoard& source) = delete;

	// ��������� �������� ������������
	KeyBoard& operator=(const KeyBoard& source) = delete;

	// ������� �������
	int pressedKey;
};

