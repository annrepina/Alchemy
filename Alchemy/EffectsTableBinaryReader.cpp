#include "EffectsTableBinaryReader.h"

EffectsTableBinaryReader::EffectsTableBinaryReader()
{
}

EffectsTableBinaryReader::~EffectsTableBinaryReader()
{
    clear();
}

EffectsTable* EffectsTableBinaryReader::readFromFile(string path, ifstream& stream)
{
    if (stream.is_open())
    {
        EffectsTable* effectsTable = new EffectsTable();

        int id = this->readInt(stream);
        effectsTable->setId(id);

        int size = this->readInt(stream);

        EffectBinaryReader* effectBinaryReader = new EffectBinaryReader();;

        for (int i = 0; i < size; ++i)
        {
            int key = readInt(stream);

            Effect* effect = effectBinaryReader->readFromFile(path, stream);

            effectsTable->add(effect, key);
        }

        return effectsTable;
    }

    return nullptr;
}

void EffectsTableBinaryReader::clear()
{
}
