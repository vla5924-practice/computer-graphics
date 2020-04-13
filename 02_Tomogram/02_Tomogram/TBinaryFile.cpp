#include "TBinaryFile.h"

TBinaryFile::TBinaryFile()
    : x(0), y(0), z(0), min(0), max(0), dataset(nullptr)
{
}

TBinaryFile::TBinaryFile(TBinaryFile&& other)
    : x(other.x), y(other.y), z(other.z), dataset(other.dataset)
{
    other.dataset = nullptr;
}

TBinaryFile::TBinaryFile(const char* fileName) : TBinaryFile()
{
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
    min = std::numeric_limits<int16_t>::max();
    max = std::numeric_limits<int16_t>::min();
    for (size_t i = 0; i < datasetSize; i++)
    {
        fread(dataset + i, sizeof(int16_t), 1, file);
        if (dataset[i] > max)
            max = dataset[i];
        if (dataset[i] < min)
            min = dataset[i];
    }
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
