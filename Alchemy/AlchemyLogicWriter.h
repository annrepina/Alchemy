#pragma once
#include "BinaryWriter.h"
#include "AlchemyLogic.h"
#include "AlchemistBinaryWriter.h"
#include "EffectsTableBinaryWriter.h"
#include "IngredientsTableBinaryWriter.h"
#include "PotionTableBinaryWriter.h"

class AlchemyLogicWriter : public BinaryWriter<AlchemyLogic>
{
public:

	AlchemyLogicWriter();

	~AlchemyLogicWriter();

	void write(ofstream& stream, string filePath, AlchemyLogic* alchemyLogic) const override;

protected:

	AlchemistBinaryWriter* alchemistBinaryWriter;

	EffectsTableBinaryWriter* effectsTableBinaryWriter;

	IngredientsTableBinaryWriter* ingredientsTableBinaryWriter;

	PotionTableBinaryWriter* potionTableBinaryWriter;

	void clear() override;

};

