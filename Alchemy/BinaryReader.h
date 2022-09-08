#pragma once
#include <string>
#include <fstream>

using namespace std;

template <typename T>
class BinaryReader
{
public:

	BinaryReader()
	{
	}

    virtual ~BinaryReader()
    {
        //clear();
    }

    virtual T* readFromFile(string path, ifstream& stream) = 0;

protected:

    // ������ �����
	virtual string readString(ifstream& stream)
	{
        // ������� ������ �������� � ���������� �������� ������ ����-����
        char* buffer = new char[sizeof(size_t)];

        // ��������� ���-�� ������ ������ ������� size_t
        stream.read(buffer, sizeof(size_t));

        // �������� ������� � ��������� �� ����_�, � ����� ��������������
        size_t textSize = *(size_t*)buffer;

        delete[] buffer;

        // +1 ��� ���� ���������
        buffer = new char[textSize + 1];

        // ��������� ���� ���
        stream.read(buffer, textSize);

        // ���������� ���� ��������
        buffer[textSize] = '\0';

        string res = (string)buffer;

        delete[] buffer;

        return res;
	}

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

    virtual bool readBool(ifstream& stream)
    {
        auto size = sizeof(bool);

        char* buffer = new char[size];

        stream.read(buffer, size);

        bool res = *(bool*)buffer;

        delete[] buffer;

        return res;
    }




    virtual void clear() = 0;
};

