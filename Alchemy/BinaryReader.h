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

	virtual T* readFromFile(string path, ifstream& stream) = 0;
};

