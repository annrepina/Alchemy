#include "AlchemyLogicWriter.h"

AlchemyLogicWriter::AlchemyLogicWriter(/*AlchemyLogic* alchemyLogic, *//*string filePath*/)
{
	this->alchemistBinaryWriter = new AlchemistBinaryWriter();
	this->effectsTableBinaryWriter = new EffectsTableBinaryWriter();
	this->ingredientsTableBinaryWriter = new IngredientsTableBinaryWriter();
	this->potionTableBinaryWriter = new PotionTableBinaryWriter();
}

AlchemyLogicWriter::~AlchemyLogicWriter()
{
	clear();
}

void AlchemyLogicWriter::write(ofstream& stream, string filePath, AlchemyLogic* alchemyLogic) const
{
	BinaryWriter::write(stream, filePath, alchemyLogic);

	Alchemist* alchemist = alchemyLogic->getAlchemist();
	alchemistBinaryWriter->write(stream, filePath, alchemist);

	EffectsTable* effectsTable = alchemyLogic->getEffectsTable();
	effectsTableBinaryWriter->write(stream, filePath, effectsTable);

	IngredientsTable* ingredientsTable = alchemyLogic->getIngredientsTable();
	ingredientsTableBinaryWriter->write(stream, filePath, ingredientsTable);

	PotionTable* potionTable = alchemyLogic->getPotionTable();
	potionTableBinaryWriter->write(stream, filePath, potionTable);
	
	// в конце закрываем
	stream.close();
}

void AlchemyLogicWriter::clear()
{
	delete this->alchemistBinaryWriter;
	this->alchemistBinaryWriter = nullptr;

	delete this->effectsTableBinaryWriter;
	this->effectsTableBinaryWriter = nullptr;

	delete this->ingredientsTableBinaryWriter;
	this->ingredientsTableBinaryWriter = nullptr;

	delete this->potionTableBinaryWriter;
	this->potionTableBinaryWriter = nullptr;
}