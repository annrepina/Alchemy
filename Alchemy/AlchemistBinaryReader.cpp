#include "AlchemistBinaryReader.h"

//AlchemistBinaryReader::AlchemistBinaryReader(string path)
//{
//    this->path = path;
//}

Alchemist* AlchemistBinaryReader::readFromFile(string path)
{
    ifstream stream(path);

    if (stream.is_open())
    {
        Alchemist* alchemist = new Alchemist();

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

        alchemist->getAlchemistLevel();

        // уровень алхимика
        buffer = new char[sizeof(alchemist->getAlchemistLevel())];

        stream.read(buffer, sizeof(alchemist->getAlchemistLevel()));

        alchemist->setAlchemistLevel(*(int*)buffer);

        delete[] buffer;

        // уровень продажника
        buffer = new char[sizeof(alchemist->getSalesmanLevel())];

        stream.read(buffer, sizeof(alchemist->getSalesmanLevel()));

        alchemist->setSalesmanLevel(*(int*)buffer);

        delete[] buffer;

        // капитал
        buffer = new char[sizeof(alchemist->getCapital())];

        stream.read(buffer, sizeof(alchemist->getCapital()));

        alchemist->setCapital(*(int*)buffer);

        delete[] buffer;

        return alchemist;
    }
    
    return nullptr;
}
