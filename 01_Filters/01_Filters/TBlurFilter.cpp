#include "TBlurFilter.h"

TBlurFilter::TBlurFilter(int matrixRadius_) : TMatrixFilter(matrixRadius_)
{
    int matrixSize = getMatrixSize();
    matrix.resize(static_cast<size_t>(matrixSize * matrixSize));
    for (int i = 0; i < matrixSize; i++)
        for (int j = 0; j < matrixSize; j++)
            matrix[i * matrixSize + j] = 1.0f / (matrixSize * matrixSize);
}
