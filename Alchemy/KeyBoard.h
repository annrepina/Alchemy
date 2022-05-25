#pragma once
#include <conio.h>

#define ORIGINAL_VALUE -1				// Исходное значение кнопки

#define FUNCTIONAL_KEY_CODE		224		// Код функциональной клавиши

// Класс - клавиатура 
class KeyBoard
{
public:

	// Статический метод для получения единственного экземпляра класса
	static KeyBoard* getInstance();

	// Геттер для нажатой клавиши
	int getPressedKey();

	// Ждет нажатия клавиши
	void waitForKey();

	// Функция высвобождения памяти
	static void release();


private:

	// Единственный экземпляр клавиатуры
	static KeyBoard* instance;

	// Приватный конструктор по умолчанию
	KeyBoard();

	// Приватный деструктор
	~KeyBoard();

	// Удаленный конструктор копирования
	KeyBoard(const KeyBoard& source) = delete;

	// Удаленный оператор присваивания
	KeyBoard& operator=(const KeyBoard& source) = delete;

	// Нажатая клавиша
	int pressedKey;
};

