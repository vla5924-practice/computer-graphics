#pragma once
#include <QtOpenGL/QGLWidget>
#include <QtOpenGL/QGLFunctions>
#include <GL/gl.h>
#include "TBinaryFile.h"

constexpr int32_t VIS_TRANSFER_IMIN = 0;
constexpr int32_t VIS_TRANSFER_IMAX = 200;
constexpr float VIS_TRANSFER_FMIN = 0.0f;
constexpr float VIS_TRANSFER_FMAX = 200.0f;

class TVisualizerWidget : public QGLWidget
{
protected:
    TBinaryFile* bin;
    int32_t currentLayer;

    template <typename Ty> Ty clamp(Ty value, int min, int max) const;
    QColor transfer(int16_t value) const;
    float getIntensity(int16_t value) const;
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void drawQuads(int32_t layerNumber);
    void drawTest();

public:
    explicit TVisualizerWidget(QWidget* parent = nullptr);
    explicit TVisualizerWidget(const char* fileName, QWidget* parent = nullptr);
    virtual ~TVisualizerWidget();
    void loadDatasetFile(const char* fileName);
    void resizeAuto();
    void setLayerNumber(int32_t layerNumber);

    int getVisWidth() const;
    int getVisHeight() const;
    int getLayersCount() const;

    classException(IncorrectLayerNumberError, "Layer does not exist.");
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