#include "AlchemistBinaryReader.h"

AlchemistBinaryReader::AlchemistBinaryReader()
{
}

AlchemistBinaryReader::~AlchemistBinaryReader()
{
    clear();
}

Alchemist* AlchemistBinaryReader::readFromFile(string path, ifstream& stream)
{
    if (stream.is_open())
    {
        Alchemist* alchemist = new Alchemist();

        string name = this->readString(stream);
        alchemist->setName(name);

        int value = readInt(stream);
        alchemist->setAlchemistLevel(value);

        value = readInt(stream);
        alchemist->setSalesmanLevel(value);

        value = readInt(stream);
        alchemist->setCapital(value);

        return alchemist;
    }
    
    return nullptr;
}

void AlchemistBinaryReader::clear()
{
}
