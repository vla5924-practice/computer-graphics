#pragma once
#include <QtOpenGL/QGLWidget>
#include <QtOpenGL/QGLFunctions>
#include <GL/gl.h>
#include "TBinaryFile.h"

class TVisualizerWidget : public QGLWidget
{
public:
    enum class RenderMode
    {
        Quads,
        QuadStrip,
        Texture
    };

protected:
    TBinaryFile* bin;
    int32_t currentLayer;
    RenderMode renderMode;
    GLuint textureId;
    QImage textureImage;

    template <typename Ty> Ty clamp(Ty value, int min, int max) const;
    float getIntensity(int16_t value) const;
    void generateTextureImage();
    void loadTexture();
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void visualizeQuads();
    void visualizeQuadStrip();
    void visualizeTexture();
    void drawTest();

public:
    explicit TVisualizerWidget(QWidget* parent = nullptr);
    explicit TVisualizerWidget(const char* fileName, QWidget* parent = nullptr);
    virtual ~TVisualizerWidget();
    void loadDatasetFile(const char* fileName);
    void resizeAuto();
    void setLayerNumber(int32_t layerNumber);
    void setRenderMode(RenderMode renderMode_);

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