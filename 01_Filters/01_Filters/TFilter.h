#pragma once
#include <QImage>
#include "Exception.h"

class TFilter
{
protected:
    TFilter() = default;
    ~TFilter() = default;
    template <typename Ty> Ty clamp(Ty value, int min, int max) const;
public:
    virtual QImage applyToImage(const QImage& image) = 0;
};

template<typename Ty>
inline Ty TFilter::clamp(Ty value, int min, int max) const
{
    if (value > max)
        return max;
    if (value < min)
        return min;
    return value;
}
