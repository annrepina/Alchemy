#include "AlchemyLogicWriter.h"
//#include "AlchemistBinaryWriter.h"

AlchemyLogicWriter::AlchemyLogicWriter(AlchemyLogic& alchemyLogic, string filePath) : BinaryWriter(alchemyLogic, filePath)
{
	this->alchemistBinaryWriter = new AlchemistBinaryWriter(*alchemyLogic.getAlchemist(), this->filePath);
}

void AlchemyLogicWriter::write(ofstream& stream) const
{
	if ("" == this->filePath)
		throw "Invalid file path";

	stream.open(filePath, ios::out | ios::binary | ios::trunc);

	alchemistBinaryWriter->write(stream);
}

//void AlchemyLogicWriter::appointAlchemist(Alchemist& alchemist)
//{
//	this->alchemistBinaryWriter = new AlchemistBinaryWriter(alchemist, this->filePath);
//}

