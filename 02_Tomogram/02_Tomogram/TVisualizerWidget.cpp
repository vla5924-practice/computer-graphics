#include "TVisualizerWidget.h"

QColor TVisualizerWidget::transfer(int16_t value) const
{
    int intensity = clamp((value - VIS_TRANSFER_IMIN) * 255 / (VIS_TRANSFER_IMAX - VIS_TRANSFER_IMIN), 0, 255);
    return QColor(intensity, intensity, intensity);
}

float TVisualizerWidget::getIntensity(int16_t value) const
{
    float val = static_cast<float>(value);
    float intensity = (val - VIS_TRANSFER_FMIN) / (VIS_TRANSFER_FMAX - VIS_TRANSFER_FMIN);
    return clamp(intensity, 0, 255);
}

void TVisualizerWidget::initializeGL()
{
    //QGLFunctions* pFunc = QGLContext::currentContext()->functions();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void TVisualizerWidget::resizeGL(int width, int height)
{
    glShadeModel(GL_SMOOTH);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, bin.x, 0, bin.y, -1, 1);
    glViewport(0, 0, width, height);
}

void TVisualizerWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawQuads(currentLayer);
    //drawTest();
    //swapBuffers();
}

void TVisualizerWidget::drawQuads(int32_t layerNumber)
{
    glBegin(GL_QUADS);
    for (int32_t x = 0; x < bin.x - 1; x++)
        for (int32_t y = 0; y < bin.y - 1; y++)
        {
            float intensity;

            intensity = getIntensity(bin.get(x, y, layerNumber));
            glColor3f(intensity, intensity, intensity);
            glVertex2i(x, y);

            intensity = getIntensity(bin.get(x, y + 1, layerNumber));
            glColor3f(intensity, intensity, intensity);
            glVertex2i(x, y + 1);

            intensity = getIntensity(bin.get(x + 1, y + 1, layerNumber));
            glColor3f(intensity, intensity, intensity);
            glVertex2i(x + 1, y + 1);

            intensity = getIntensity(bin.get(x + 1, y, layerNumber));
            glColor3f(intensity, intensity, intensity);
            glVertex2i(x + 1, y);
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

TVisualizerWidget::TVisualizerWidget(const char* fileName, QWidget* pWidget) : QGLWidget(pWidget)
{
    bin = TBinaryFile(fileName);
    currentLayer = 40;
}

void TVisualizerWidget::resizeAuto()
{
    resize(bin.x, bin.y);
}


