#include "AlchemistBinaryReader.h"

//AlchemistBinaryReader::AlchemistBinaryReader(string path)
//{
//    this->path = path;
//}

AlchemistBinaryReader::AlchemistBinaryReader()
{
}

Alchemist* AlchemistBinaryReader::readFromFile(string path, ifstream& stream)
{
    //ifstream stream(path);

    if (stream.is_open())
    {
        Alchemist* alchemist = new Alchemist();

        // читаем имя
        // создаем буффер размером с переменной хранязей размер чего-либо
        char* buffer = new char[sizeof(size_t)];

        // считывает кол-во байтов равное размеру size_t
        stream.read(buffer, sizeof(size_t));

        // приводим сначала в указатель на сайз_т, а потом разыменовываем
        size_t nameSize = *(size_t*)buffer;

        delete[] buffer;

        // +1 для нуль терминала
        buffer = new char[nameSize + 1];

        // считываем само имя
        stream.read(buffer, nameSize);

        // записываем нуль терминал
        buffer[nameSize] = '\0';

        alchemist->setName((string)buffer);

        delete[] buffer;

        // читаем уровень алхимика

        // узнаем размер переменной
        auto size = sizeof(alchemist->getAlchemistLevel());

        // уровень алхимика
        buffer = new char[size];

        stream.read(buffer, size);

        alchemist->setAlchemistLevel(*(int*)buffer);

        delete[] buffer;

        // читаем уровень продажника
        // узнаем размер переменной 
        size = sizeof(alchemist->getSalesmanLevel());

        buffer = new char[size];

        stream.read(buffer, size);

        alchemist->setSalesmanLevel(*(int*)buffer);

        delete[] buffer;

        // читаем капитал
        // узнаем размер переменной

        size = sizeof(alchemist->getCapital());

        buffer = new char[size];

        stream.read(buffer, size);

        alchemist->setCapital(*(int*)buffer);

        delete[] buffer;

        return alchemist;
    }
    
    return nullptr;
}
