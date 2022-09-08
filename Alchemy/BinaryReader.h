#pragma once
#include <string>
#include <fstream>

using namespace std;

template <typename T>
class BinaryReader
{
public:

	BinaryReader()
	{
	}

    virtual ~BinaryReader()
    {
        //clear();
    }

    virtual T* readFromFile(string path, ifstream& stream) = 0;

protected:

    // читаем текст
	virtual string readString(ifstream& stream)
	{
        // создаем буффер размером с переменной хранящей размер чего-либо
        char* buffer = new char[sizeof(size_t)];

        // считывает кол-во байтов равное размеру size_t
        stream.read(buffer, sizeof(size_t));

        // приводим сначала в указатель на сайз_т, а потом разыменовываем
        size_t textSize = *(size_t*)buffer;

        delete[] buffer;

        // +1 для нуль терминала
        buffer = new char[textSize + 1];

        // считываем само имя
        stream.read(buffer, textSize);

        // записываем нуль терминал
        buffer[textSize] = '\0';

        string res = (string)buffer;

        delete[] buffer;

        return res;
	}

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

    virtual bool readBool(ifstream& stream)
    {
        auto size = sizeof(bool);

        char* buffer = new char[size];

        stream.read(buffer, size);

        bool res = *(bool*)buffer;

        delete[] buffer;

        return res;
    }




    virtual void clear() = 0;
};

