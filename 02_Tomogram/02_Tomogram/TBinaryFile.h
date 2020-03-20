#pragma once
#include <fstream>
#include <cstdio>
#include "Exception.h"

class TBinaryFile
{
public:
    int32_t x, y, z;
    int16_t* dataset;
public:
    TBinaryFile();
    TBinaryFile(TBinaryFile&& other);
    TBinaryFile(const char* fileName);
    ~TBinaryFile();

    TBinaryFile& operator=(TBinaryFile&& other);
    inline const int16_t& get(int32_t x_, int32_t y_, int32_t z_) const
    {
        return dataset[static_cast<size_t>(x_ + y_ * x + z_ * y * x)];
    }

    classException(IncorrectFileNameError, "File does not exist or name is incorrect.");
    classException(IncorrectDimensionsError, "Dimensions in file are incorrect.");
};