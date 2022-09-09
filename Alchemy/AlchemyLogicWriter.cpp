#include "AlchemyLogicWriter.h"
//#include "AlchemistBinaryWriter.h"

AlchemyLogicWriter::AlchemyLogicWriter(/*AlchemyLogic* alchemyLogic, *//*string filePath*/)
{
	this->alchemistBinaryWriter = new AlchemistBinaryWriter();
	this->effectsTableBinaryWriter = new EffectsTableBinaryWriter();
}

AlchemyLogicWriter::~AlchemyLogicWriter()
{
	clear();
}

void AlchemyLogicWriter::write(ofstream& stream, string filePath, AlchemyLogic* alchemyLogic) const
{
	//if ("" == filePath)
	//	throw "Invalid file path";

	//stream.open(filePath, ios::out | ios::binary | ios::trunc);

	BinaryWriter::write(stream, filePath, alchemyLogic);

	Alchemist* alchemist = alchemyLogic->getAlchemist();
	alchemistBinaryWriter->write(stream, filePath, alchemist);

	EffectsTable* effectsTable = alchemyLogic->getEffectsTable();
	effectsTableBinaryWriter->write(stream, filePath, effectsTable);


	
	// в конце закрываем
	stream.close();
}

void AlchemyLogicWriter::clear()
{
	delete this->alchemistBinaryWriter;
	delete this->effectsTableBinaryWriter;
}



