#include "AlchemistBinaryReader.h"

//AlchemistBinaryReader::AlchemistBinaryReader(string path)
//{
//    this->path = path;
//}

Alchemist* AlchemistBinaryReader::readFromFile(string path)
{
    ifstream stream(path);

    if (stream.is_open())
    {
        Alchemist* alchemist = new Alchemist();

        // ������� ������ �������� � ���������� �������� ������ ����-����
        char* buffer = new char[sizeof(size_t)];

        // ��������� ���-�� ������ ������ ������� size_t
        stream.read(buffer, sizeof(size_t));

        // �������� ������� � ��������� �� ����_�, � ����� ��������������
        size_t nameSize = *(size_t*)buffer;

        delete[] buffer;

        // +1 ��� ���� ���������
        buffer = new char[nameSize + 1];

        // ��������� ���� ���
        stream.read(buffer, nameSize);

        // ���������� ���� ��������
        buffer[nameSize] = '\0';

        alchemist->setName((string)buffer);

        delete[] buffer;

        alchemist->getAlchemistLevel();

        // ������� ��������
        buffer = new char[sizeof(alchemist->getAlchemistLevel())];

        stream.read(buffer, sizeof(alchemist->getAlchemistLevel()));

        alchemist->setAlchemistLevel(*(int*)buffer);

        delete[] buffer;

        // ������� ����������
        buffer = new char[sizeof(alchemist->getSalesmanLevel())];

        stream.read(buffer, sizeof(alchemist->getSalesmanLevel()));

        alchemist->setSalesmanLevel(*(int*)buffer);

        delete[] buffer;

        // �������
        buffer = new char[sizeof(alchemist->getCapital())];

        stream.read(buffer, sizeof(alchemist->getCapital()));

        alchemist->setCapital(*(int*)buffer);

        delete[] buffer;

        return alchemist;
    }
    
    return nullptr;
}
