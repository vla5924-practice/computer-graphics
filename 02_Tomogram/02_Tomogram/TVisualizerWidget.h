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

    enum class ProjectionDir
    {
        XYZ,
        YZX,
        XZY
    };

protected:
    using DimensionGetter = int32_t(TBinaryFile::*)() const;
    TBinaryFile* bin;
    int32_t currentLayer;
    int16_t dataMin, dataMax;
    ProjectionDir projectionDir;
    RenderMode renderMode;
    GLuint textureId;
    QImage textureImage;
    DimensionGetter getHorizontal;
    DimensionGetter getVertical;
    DimensionGetter getDeep;

    template <typename Ty> Ty clamp(Ty value, int min, int max) const;
    float getIntensity(int16_t value) const;
    void generateTextureImage();
    void loadTexture();
    void setUpTexture();
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void visualizeQuads();
    void visualizeQuadStrip();
    void visualizeTexture();
    void drawTest();
    void setDimensionGetters(ProjectionDir projectionDir);
    int16_t getProjectedValue(int x, int y, int z) const;

public:
    explicit TVisualizerWidget(QWidget* parent = nullptr);
    explicit TVisualizerWidget(const char* fileName, QWidget* parent = nullptr);
    virtual ~TVisualizerWidget();
    void loadDatasetFile(const char* fileName);
    void resizeAuto();
    void setLayerNumber(int32_t layerNumber);
    void setRenderMode(RenderMode renderMode_);
    void setVisibleDataLimits(int16_t min, int16_t max);
    void setProjectionDir(ProjectionDir projectionDir_);

    int getVisWidth() const;
    int getVisHeight() const;
    int getLayersCount() const;

    int getDataMin() const;
    int getDataMax() const;

    classException(IncorrectLayerNumberError, "Layer does not exist.");
    classException(IncorrectDataLimitsError, "Given values are not in widest data limits.");
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