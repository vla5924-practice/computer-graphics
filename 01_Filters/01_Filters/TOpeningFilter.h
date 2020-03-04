#pragma once
#include "TDilationFilter.h"
#include "TErosionFilter.h"

class TOpeningFilter : public TErosionFilter, public TDilationFilter
{
public:
    explicit TOpeningFilter(int radius = 1);
    TOpeningFilter(std::vector<bool> mask);
    ~TOpeningFilter() = default;
    QImage applyToImage(const QImage& image);
};