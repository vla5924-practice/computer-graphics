#include "TVisualizerWidget.h"

float TVisualizerWidget::getIntensity(int16_t value) const
{
    float intensity = (static_cast<float>(value) - bin->getMin()) 
                      / (bin->getMax() - bin->getMin());
    return clamp(intensity, 0, 1);
}

void TVisualizerWidget::generateTextureImage()
{
    int width = bin->getX();
    int height = bin->getY();
    textureImage = QImage(width, height, QImage::Format_RGB32);
    for(int x = 0; x < width; x++)
        for (int y = 0; y < height; y++)
        {
            float intensity = getIntensity(bin->get(x, y, currentLayer));
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
    for (int32_t x = 0; x < bin->getX() - 1; x++)
        for (int32_t y = 0; y < bin->getY() - 1; y++)
        {
            float intensity;

            intensity = getIntensity(bin->get(x, y, currentLayer));
            glColor3f(intensity, intensity, intensity);
            glVertex2i(x, y);

            intensity = getIntensity(bin->get(x, y + 1, currentLayer));
            glColor3f(intensity, intensity, intensity);
            glVertex2i(x, y + 1);

            intensity = getIntensity(bin->get(x + 1, y + 1, currentLayer));
            glColor3f(intensity, intensity, intensity);
            glVertex2i(x + 1, y + 1);

            intensity = getIntensity(bin->get(x + 1, y, currentLayer));
            glColor3f(intensity, intensity, intensity);
            glVertex2i(x + 1, y);
        }
    glEnd();
}

void TVisualizerWidget::visualizeTexture()
{
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glTexCoord2f(0, 0);
    glVertex2i(0, 0);
    glTexCoord2f(0, 1);
    glVertex2i(0, bin->getY());
    glTexCoord2f(1, 1);
    glVertex2i(bin->getX(), bin->getY());
    glTexCoord2f(1, 0);
    glVertex2i(bin->getX(), 0);
    glEnd();
}

void TVisualizerWidget::visualizeQuadStrip()
{

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

TVisualizerWidget::TVisualizerWidget(QWidget* parent)
    : QGLWidget(parent), currentLayer(0), renderMode(RenderMode::Quads)
{
    currentLayer = 0;
    bin = new TBinaryFile;
}

TVisualizerWidget::TVisualizerWidget(const char* fileName, QWidget* parent)
    : QGLWidget(parent), currentLayer(0), renderMode(RenderMode::Quads), bin(nullptr)
{
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
    if ((layerNumber >= 0) && (layerNumber < bin->getZ()))
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
    renderMode = renderMode_;
    if (!bin)
        return;
    if (renderMode == RenderMode::Texture)
    {
        glEnable(GL_TEXTURE_2D);
        setUpTexture();
    }
    else
        glDisable(GL_TEXTURE_2D);
    paintGL();
}

int TVisualizerWidget::getVisWidth() const
{
    return bin ? bin->getX() : 0;
}

int TVisualizerWidget::getVisHeight() const
{
    return bin ? bin->getY() : 0;
}

int TVisualizerWidget::getLayersCount() const
{
    return bin ? bin->getZ() : 0;
}
