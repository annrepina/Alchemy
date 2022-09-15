#include "KeyBoard.h"

// ������������� ����������
KeyBoard* KeyBoard::instance = nullptr;

KeyBoard::KeyBoard()
{
	this->pressedKey = ORIGINAL_VALUE;
}

KeyBoard::~KeyBoard()
{
}

KeyBoard* KeyBoard::getInstance()
{
	// ���� ��������� ��� �� ��� ������
	if (nullptr == instance)
		instance = new KeyBoard;

	// ����� ���������� ���
	return instance;
}

int KeyBoard::getPressedKey()
{
	int res = this->pressedKey;

	return res;
}

void KeyBoard::waitForKey()
{
	// ���� ������� �������
	while (!_kbhit());

	// �������
	int key;

	do {
		// ���������� ������� �������
		key = _getch();

		// �������� �� �� �������� �� ������� ��������������
	} while (FUNCTIONAL_KEY_CODE == key);

	// ����������� ������� ������
	this->pressedKey = key;
}

void KeyBoard::release()
{
	if (nullptr != instance)
	{
		delete instance;

		instance = nullptr;
	}
}