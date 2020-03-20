#pragma once
#include <QtOpenGL/QGLWidget>
#include <QtOpenGL/QGLFunctions>
#include <GL/gl.h>
#include "TBinaryFile.h"

constexpr int VIS_TRANSFER_MIN = 0;
constexpr int VIS_TRANSFER_MAX = 2000;

class TVisualizerWidget : public QGLWidget
{
protected:
    TBinaryFile bin;
    
    template <typename Ty> Ty clamp(Ty value, int min, int max) const;
    QColor transfer(int16_t value) const;
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void draw();
    void drawQuads(int32_t layerNumber);

    TVisualizerWidget() = default;

public:
    explicit TVisualizerWidget(const char* fileName, QWidget* pWidget = nullptr);
};

template<typename Ty>
inline Ty TVisualizerWidget::clamp(Ty value, int min, int max) const
{
    if (value > max)
        return max;
    if (value < min)
        return min;
    return value;
}
