#pragma once
#include <string>
#include <fstream>

using namespace std;

// ����� ������� ������ ������ ������ �� ��������� �����
template <typename T>
class BinaryReader
{
public:

    // ����������� �� ���������
	BinaryReader()
	{
	}

    // ����������� ����������
    virtual ~BinaryReader()
    {
    }

    // ������ �� ��������� �����
    virtual T* readFromFile(string path, ifstream& stream) = 0;

protected:

    // ������ size_t �� ��������� �����
    virtual size_t readSize_t(ifstream& stream)
    {
        size_t size = sizeof(size_t);

        // ������� ������ �������� � ���������� �������� ������ ����-����
        char* buffer = new char[size];

        // ��������� ���-�� ������ ������ ������� size_t
        stream.read(buffer, size);

        // �������� ������� � ��������� �� ����_�, � ����� ��������������
        size_t textSize = *(int*)buffer;

        delete[] buffer;

        return textSize;
    }

    // ������ ����� �� ��������� �����
	virtual string readString(ifstream& stream)
	{
        size_t textSize = readSize_t(stream);

        // +1 ��� ���� ���������        
        char* buffer = new char[textSize + 1];             

        // ��������� ���� ���
        stream.read(buffer, textSize);

        // ���������� ���� ��������
        buffer[textSize] = '\0';

        string res = (string)buffer;

        delete[] buffer;

        return res;
	}

    // ������ int �� ��������� �����
    virtual int readInt(ifstream& stream)
    {
        // ������ ������ ����������
        auto size = sizeof(int);

        // ������� ����� ������� �������
        char* buffer = new char[size];

        stream.read(buffer, size);

        int res = *(int*)buffer;

        delete[] buffer;

        return res;
    }

    // ������ bool �� ��������� �����
    virtual bool readBool(ifstream& stream)
    {
        auto size = sizeof(bool);

        char* buffer = new char[size];

        stream.read(buffer, size);

        bool res = *(bool*)buffer;

        delete[] buffer;

        return res;
    }

    // �������� ������
    virtual void clear() = 0;
};

