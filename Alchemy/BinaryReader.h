#pragma once
#include <string>
#include <fstream>

using namespace std;

// Класс который читает другие классы из бинарного файла
template <typename T>
class BinaryReader
{
public:

    // Конструктор по умолчанию
	BinaryReader()
	{
	}

    // Виртуальный деструктор
    virtual ~BinaryReader()
    {
    }

    // Читать из бинарного файла
    virtual T* readFromFile(string path, ifstream& stream) = 0;

protected:

    // Читать size_t из бинарного файла
    virtual size_t readSize_t(ifstream& stream)
    {
        size_t size = sizeof(size_t);

        // создаем буффер размером с переменной хранящей размер чего-либо
        char* buffer = new char[size];

        // считывает кол-во байтов равное размеру size_t
        stream.read(buffer, size);

        // приводим сначала в указатель на сайз_т, а потом разыменовываем
        size_t textSize = *(int*)buffer;

        delete[] buffer;

        return textSize;
    }

    // читаем текст из бинарного файла
	virtual string readString(ifstream& stream)
	{
        size_t textSize = readSize_t(stream);

        // +1 для нуль терминала        
        char* buffer = new char[textSize + 1];             

        // считываем само имя
        stream.read(buffer, textSize);

        // записываем нуль терминал
        buffer[textSize] = '\0';

        string res = (string)buffer;

        delete[] buffer;

        return res;
	}

    // Читать int из бинарного файла
    virtual int readInt(ifstream& stream)
    {
        // узнаем размер переменной
        auto size = sizeof(int);

        // создаем буфер данного размера
        char* buffer = new char[size];

        stream.read(buffer, size);

        int res = *(int*)buffer;

        delete[] buffer;

        return res;
    }

    // Читать bool из бинарного файла
    virtual bool readBool(ifstream& stream)
    {
        auto size = sizeof(bool);

        char* buffer = new char[size];

        stream.read(buffer, size);

        bool res = *(bool*)buffer;

        delete[] buffer;

        return res;
    }

    // Очистить память
    virtual void clear() = 0;
};

