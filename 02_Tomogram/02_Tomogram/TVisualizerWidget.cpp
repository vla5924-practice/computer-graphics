#include "TVisualizerWidget.h"

float TVisualizerWidget::getIntensity(int16_t value) const
{
    float intensity = (value - dataMin) / float(dataMax - dataMin);
    return clamp(intensity, 0, 1);
}

void TVisualizerWidget::generateTextureImage()
{
    int width = getVisWidth();
    int height = getVisHeight();
    textureImage = QImage(width, height, QImage::Format_RGB32);
    for(int x = 0; x < width; x++)
        for (int y = 0; y < height; y++)
        {
            float intensity = getIntensity(getProjectedValue(x, y, currentLayer));
            textureImage.setPixelColor(x, y, QColor::fromRgbF(intensity, intensity, intensity));
        }
}

void TVisualizerWidget::loadTexture()
{
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureImage.width(), 
        textureImage.height(), 0, GL_BGRA, GL_UNSIGNED_BYTE, textureImage.bits());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void TVisualizerWidget::setUpTexture()
{
    generateTextureImage();
    loadTexture();
    updateGL();
}

void TVisualizerWidget::initializeGL()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glGenTextures(1, &textureId);
}

void TVisualizerWidget::resizeGL(int width, int height)
{
    glShadeModel(GL_SMOOTH);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, getVisWidth(), 0, getVisHeight(), -1, 1);
    glViewport(0, 0, width, height);
}

void TVisualizerWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    switch (renderMode)
    {
    case RenderMode::Quads:
        visualizeQuads();
        break;
    case RenderMode::QuadStrip:
        visualizeQuadStrip();
        break;
    case RenderMode::Texture:
        visualizeTexture();
        break;
    }
    swapBuffers();
}

void TVisualizerWidget::visualizeQuads()
{
    glBegin(GL_QUADS);
    int32_t xMax = getVisWidth() - 2;
    int32_t yMax = getVisHeight() - 2;
    for (int32_t x = 0; x <= xMax ; x++)
        for (int32_t y = 0; y <= yMax; y++)
        {
            float intensity;

            intensity = getIntensity(getProjectedValue(x, y, currentLayer));
            glColor3f(intensity, intensity, intensity);
            glVertex2i(x, y);

            intensity = getIntensity(getProjectedValue(x, y + 1, currentLayer));
            glColor3f(intensity, intensity, intensity);
            glVertex2i(x, y + 1);

            intensity = getIntensity(getProjectedValue(x + 1, y + 1, currentLayer));
            glColor3f(intensity, intensity, intensity);
            glVertex2i(x + 1, y + 1);

            intensity = getIntensity(getProjectedValue(x + 1, y, currentLayer));
            glColor3f(intensity, intensity, intensity);
            glVertex2i(x + 1, y);
        }
    glEnd();
}

void TVisualizerWidget::visualizeTexture()
{
    glBegin(GL_QUADS);
    int height = getVisHeight();
    int width = getVisWidth();
    glColor3f(1, 1, 1);
    glTexCoord2f(0, 0);
    glVertex2i(0, 0);
    glTexCoord2f(0, 1);
    glVertex2i(0, height);
    glTexCoord2f(1, 1);
    glVertex2i(width, height);
    glTexCoord2f(1, 0);
    glVertex2i(width, 0);
    glEnd();
}

void TVisualizerWidget::visualizeQuadStrip()
{
    glBegin(GL_QUAD_STRIP);
    int32_t xMax = getVisWidth() - 2;
    int32_t yMax = getVisHeight() - 2;
    float intensity;
    intensity = getIntensity(getProjectedValue(0, 0, currentLayer));
    glColor3f(intensity, intensity, intensity);
    glVertex2i(0, 0);
    intensity = getIntensity(getProjectedValue(0, 1, currentLayer));
    glColor3f(intensity, intensity, intensity);
    glVertex2i(0, 1);
    for (int32_t x = 1; x <= xMax; x++)
        for (int32_t y = 1; y <= yMax; y++)
        {
            intensity = getIntensity(getProjectedValue(x, y, currentLayer));
            glColor3f(intensity, intensity, intensity);
            glVertex2i(x, y);

            intensity = getIntensity(getProjectedValue(x, y + 1, currentLayer));
            glColor3f(intensity, intensity, intensity);
            glVertex2i(x, y + 1);
        }
    glEnd();
}

void TVisualizerWidget::drawTest()
{
    glBegin(GL_QUADS);
    glColor3f(1, 0, 0);
    glVertex2f(0, 100);
    glColor3f(0, 1, 0);
    glVertex2f(100, 100);
    glColor3f(0, 0, 1);
    glVertex2f(100, 0);
    glColor3f(1, 1, 1);
    glVertex2f(0, 0);
    glEnd();
}

void TVisualizerWidget::setDimensionGetters(ProjectionDir projectionDir)
{
    switch (projectionDir)
    {
    case ProjectionDir::XYZ:
        getHorizontal = &TBinaryFile::getX;
        getVertical = &TBinaryFile::getY;
        getDeep = &TBinaryFile::getZ;
        break;
    case ProjectionDir::ZXY:
        getHorizontal = &TBinaryFile::getX;
        getVertical = &TBinaryFile::getZ;
        getDeep = &TBinaryFile::getY;
        break;
    case ProjectionDir::YZX:
        getHorizontal = &TBinaryFile::getZ;
        getVertical = &TBinaryFile::getY;
        getDeep = &TBinaryFile::getX;
        break;
    }
}

int16_t TVisualizerWidget::getProjectedValue(int x, int y, int z) const
{
    switch (projectionDir)
    {
    case ProjectionDir::XYZ:
        return bin->get(x, y, z);
    case ProjectionDir::ZXY:
        return bin->get(z, x, y);
    case ProjectionDir::YZX:
        return bin->get(y, z, x);
    }
    return 0;
}

TVisualizerWidget::TVisualizerWidget(QWidget* parent)
    : QGLWidget(parent), currentLayer(0), renderMode(RenderMode::Quads), 
    dataMin(0), dataMax(1), bin(nullptr)
{
    setProjectionDir(ProjectionDir::XYZ);
}

TVisualizerWidget::TVisualizerWidget(const char* fileName, QWidget* parent)
    : QGLWidget(parent), currentLayer(0), renderMode(RenderMode::Quads), bin(nullptr)
{
    setProjectionDir(ProjectionDir::XYZ);
    loadDatasetFile(fileName);
}

TVisualizerWidget::~TVisualizerWidget()
{
    if (bin)
        delete bin;
}

void TVisualizerWidget::loadDatasetFile(const char* fileName)
{
    if (bin)
        delete bin;
    bin = new TBinaryFile(fileName);
    dataMin = bin->getMin();
    dataMax = bin->getMax();
    resizeAuto();
}

void TVisualizerWidget::resizeAuto()
{
    resize(getVisWidth(), getVisHeight());
}

void TVisualizerWidget::setLayerNumber(int32_t layerNumber)
{
    if (!bin)
        return;
    if ((layerNumber >= 0) && (layerNumber < getLayersCount()))
    {
        currentLayer = layerNumber;
        if (renderMode == RenderMode::Texture)
            setUpTexture();
        paintGL();
    }
    else
        throw IncorrectLayerNumberError();
}

void TVisualizerWidget::setRenderMode(RenderMode renderMode_)
{
    if (!bin)
        return;
    renderMode = renderMode_;
    if (renderMode == RenderMode::Texture)
    {
        glEnable(GL_TEXTURE_2D);
        setUpTexture();
    }
    else
        glDisable(GL_TEXTURE_2D);
    paintGL();
}

void TVisualizerWidget::setVisibleDataLimits(int16_t min, int16_t max)
{
    if ((min >= max) || (min < bin->getMin()) || (max > bin->getMax()))
        throw IncorrectDataLimitsError();
    dataMin = min;
    dataMax = max;
    setRenderMode(renderMode);
}

void TVisualizerWidget::setProjectionDir(ProjectionDir projectionDir_)
{
    setDimensionGetters(projectionDir_);
    projectionDir = projectionDir_;
    setRenderMode(renderMode);
    resizeAuto();
}

int TVisualizerWidget::getVisWidth() const
{
    return bin ? (bin->*getHorizontal)() : 0;
}

int TVisualizerWidget::getVisHeight() const
{
    return bin ? (bin->*getVertical)() : 0;
}

int TVisualizerWidget::getLayersCount() const
{
    return bin ? (bin->*getDeep)() : 0;
}

int TVisualizerWidget::getCurrentDataMin() const
{
    return dataMin;
}

int TVisualizerWidget::getCurrentDataMax() const
{
    return dataMax;
}

int TVisualizerWidget::getDataMin() const
{
    return bin ? bin->getMin() : 0;
}

int TVisualizerWidget::getDataMax() const
{
    return bin ? bin->getMax() : 1;
}
