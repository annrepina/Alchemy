#include "AlchemyLogicWriter.h"
//#include "AlchemistBinaryWriter.h"

AlchemyLogicWriter::AlchemyLogicWriter(AlchemyLogic* alchemyLogic, string filePath) : BinaryWriter(alchemyLogic, filePath)
{
	this->alchemistBinaryWriter = new AlchemistBinaryWriter(alchemyLogic->getAlchemist(), this->filePath);
	this->effectsTableBinaryWriter = new EffectsTableBinaryWriter(alchemyLogic->getEffectsTable(), this->filePath);
	this->effectBinaryWriter = new EffectBinaryWriter(alchemyLogic->getEffectsTable()->getEffectByKey(10), this->filePath);
}

AlchemyLogicWriter::~AlchemyLogicWriter()
{
	clear();
}

void AlchemyLogicWriter::write(ofstream& stream) const
{
	if ("" == this->filePath)
		throw "Invalid file path";

	stream.open(filePath, ios::out | ios::binary | ios::trunc);

	alchemistBinaryWriter->write(stream);
	//effectBinaryWriter->write(stream);

	effectsTableBinaryWriter->write(stream);


	
	// в конце закрываем
	stream.close();
}

void AlchemyLogicWriter::clear()
{
	delete this->alchemistBinaryWriter;
	delete this->effectsTableBinaryWriter;
}

//void AlchemyLogicWriter::appointAlchemist(Alchemist& alchemist)
//{
//	this->alchemistBinaryWriter = new AlchemistBinaryWriter(alchemist, this->filePath);
//}

