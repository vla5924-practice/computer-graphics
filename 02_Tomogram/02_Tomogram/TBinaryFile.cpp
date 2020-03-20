#include "TBinaryFile.h"

TBinaryFile::TBinaryFile()
{
    x = y = z = 0;
    dataset = nullptr;
}

TBinaryFile::TBinaryFile(TBinaryFile&& other)
{
    x = other.x;
    y = other.y;
    z = other.z;
    dataset = other.dataset;
    other.dataset = nullptr;
}

TBinaryFile::TBinaryFile(const char* fileName) : TBinaryFile()
{
    /*std::ifstream file;
    file.open(fileName, std::ios::in | std::ios::binary);
    if (!file.is_open())
        throw IncorrectFileNameError();
    file >> x;
    file >> y;
    file >> z;
    if ((x <= 0) || (y <= 0) || (z <= 0))
        throw IncorrectDimensionsError();
    size_t datasetSize = static_cast<size_t>(x * y * z);
    dataset = new int16_t[datasetSize];
    for (size_t i = 0; i < datasetSize; i++)
        file >> dataset[i];
    file.close();*/

    FILE* file;
    file = fopen(fileName, "rb");
    if (!file)
        throw IncorrectFileNameError();
    fread(&x, sizeof(int32_t), 1, file);
    fread(&y, sizeof(int32_t), 1, file);
    fread(&z, sizeof(int32_t), 1, file);
    if ((x <= 0) || (y <= 0) || (z <= 0))
        throw IncorrectDimensionsError();
    size_t datasetSize = static_cast<size_t>(x * y * z);
    dataset = new int16_t[datasetSize];
    for (size_t i = 0; i < datasetSize; i++)
        fread(dataset + i, sizeof(int16_t), 1, file);
    fclose(file);
}

TBinaryFile::~TBinaryFile()
{
    if (dataset)
        delete[] dataset;
}

TBinaryFile& TBinaryFile::operator=(TBinaryFile&& other)
{
    if (this == &other)
        return *this;
    if (dataset)
        delete[] dataset;
    x = other.x;
    y = other.y;
    z = other.z;
    dataset = other.dataset;
    other.dataset = nullptr;
    return *this;
}
