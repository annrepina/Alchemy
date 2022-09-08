#pragma once
#include "BinaryWriter.h"
#include "AlchemyLogic.h"
#include "AlchemistBinaryWriter.h"
#include "EffectsTableBinaryWriter.h"

class AlchemyLogicWriter : public BinaryWriter<AlchemyLogic>
{
public:

	AlchemyLogicWriter(AlchemyLogic* alchemyLogic, string filePath);

	~AlchemyLogicWriter();

	void write(ofstream& stream) const override;

protected:

	AlchemistBinaryWriter* alchemistBinaryWriter;

	EffectsTableBinaryWriter* effectsTableBinaryWriter;

	void clear() override;

};

