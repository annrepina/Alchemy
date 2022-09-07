#pragma once
#include "BinaryWriter.h"
#include "AlchemyLogic.h"
#include "AlchemistBinaryWriter.h"

class AlchemyLogicWriter : public BinaryWriter<AlchemyLogic>
{
public:

	AlchemyLogicWriter(AlchemyLogic& alchemyLogic, string filePath);

	void write(ofstream& stream) const override;

	//void appointAlchemist(Alchemist& alchemist);

protected:

	AlchemistBinaryWriter* alchemistBinaryWriter;

};

