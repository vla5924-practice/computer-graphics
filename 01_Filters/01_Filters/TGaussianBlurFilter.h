#pragma once
#include "TMatrixFilter.h"
#include <cmath>

class TGaussianBlurFilter : public TMatrixFilter
{
public:
    explicit TGaussianBlurFilter(int radius = 3, int sigma = 2);
    classException(InvalidSigmaError, "Sigma parameter must have a positive value.");
};