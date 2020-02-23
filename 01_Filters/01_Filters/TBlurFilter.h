#pragma once
#include "TMatrixFilter.h"

class TBlurFilter : public TMatrixFilter
{
public:
    explicit TBlurFilter(int matrixRadius_ = 1);
    ~TBlurFilter() = default;
};