#pragma once
#include "TMatrixFilter.h"

class TMotionBlurFilter : public TMatrixFilter
{
public:
    explicit TMotionBlurFilter(int radius = 1);
    ~TMotionBlurFilter() = default;
};