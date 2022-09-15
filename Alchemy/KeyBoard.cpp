#include "KeyBoard.h"

// инициализация экземпляра
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
	// Если экземпляр еще не был создан
	if (nullptr == instance)
		instance = new KeyBoard;

	// иначе возвращаем его
	return instance;
}

int KeyBoard::getPressedKey()
{
	int res = this->pressedKey;

	return res;
}

void KeyBoard::waitForKey()
{
	// ждем нажатия клавиши
	while (!_kbhit());

	// Клавиша
	int key;

	do {
		// записываем нажатую клавишу
		key = _getch();

		// Проверка на то является ли клавиша функциональной
	} while (FUNCTIONAL_KEY_CODE == key);

	// Присваиваем нажатую кнопку
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