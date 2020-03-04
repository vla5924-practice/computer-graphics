#pragma once
#include "TErosionFilter.h"
#include "TDilationFilter.h"

class TClosingFilter : public TDilationFilter, public TErosionFilter
{
public:
    explicit TClosingFilter(int radius = 1);
    TClosingFilter(std::vector<bool> mask);
    ~TClosingFilter() = default;
    QImage applyToImage(const QImage& image);
};