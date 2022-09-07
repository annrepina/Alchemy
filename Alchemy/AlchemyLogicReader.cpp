#include "AlchemyLogicReader.h"

AlchemyLogicReader::AlchemyLogicReader()
{
	this->alchemistBinaryReader = new AlchemistBinaryReader();
}

AlchemyLogic* AlchemyLogicReader::readFromFile(string path, ifstream& stream)
{
	//stream.open(stream, ios::in);

	// открываем файл
	stream.open(path);

	alchemistBinaryReader->readFromFile(path, stream);




	return nullptr;
}

Alchemist* AlchemyLogicReader::returnAlchemist(string path, ifstream& stream)
{
	// открываем файл
	stream.open(path);

	return alchemistBinaryReader->readFromFile(path, stream);


}
