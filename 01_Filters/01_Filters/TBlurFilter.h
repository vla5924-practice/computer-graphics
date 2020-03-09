#pragma once
#include "TMatrixFilter.h"

class TBlurFilter : public TMatrixFilter
{
public:
    explicit TBlurFilter(int radius = 1);
};