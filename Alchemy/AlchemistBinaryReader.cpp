#include "AlchemistBinaryReader.h"

//AlchemistBinaryReader::AlchemistBinaryReader(string path)
//{
//    this->path = path;
//}

AlchemistBinaryReader::AlchemistBinaryReader()
{
}

Alchemist* AlchemistBinaryReader::readFromFile(string path, ifstream& stream)
{
    //ifstream stream(path);

    if (stream.is_open())
    {
        Alchemist* alchemist = new Alchemist();

        // ������ ���
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

        // ������ ������� ��������

        // ������ ������ ����������
        auto size = sizeof(alchemist->getAlchemistLevel());

        // ������� ��������
        buffer = new char[size];

        stream.read(buffer, size);

        alchemist->setAlchemistLevel(*(int*)buffer);

        delete[] buffer;

        // ������ ������� ����������
        // ������ ������ ���������� 
        size = sizeof(alchemist->getSalesmanLevel());

        buffer = new char[size];

        stream.read(buffer, size);

        alchemist->setSalesmanLevel(*(int*)buffer);

        delete[] buffer;

        // ������ �������
        // ������ ������ ����������

        size = sizeof(alchemist->getCapital());

        buffer = new char[size];

        stream.read(buffer, size);

        alchemist->setCapital(*(int*)buffer);

        delete[] buffer;

        return alchemist;
    }
    
    return nullptr;
}
