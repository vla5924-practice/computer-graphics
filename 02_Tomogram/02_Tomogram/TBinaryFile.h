#pragma once
#include <fstream>
#include <cstdio>
#include <limits>
#include "Exception.h"

class TBinaryFile
{
private:
    int32_t x, y, z;
    int16_t* dataset;
    int16_t min, max;
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
    inline int32_t getX() const { return x; }
    inline int32_t getY() const { return y; }
    inline int32_t getZ() const { return z; }
    inline int16_t getMin() const { return min; }
    inline int16_t getMax() const { return max; }

    classException(IncorrectFileNameError, "File does not exist or name is incorrect.");
    classException(IncorrectDimensionsError, "Dimensions in file are incorrect.");
};