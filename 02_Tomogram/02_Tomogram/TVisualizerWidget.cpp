#include "TVisualizerWidget.h"

QColor TVisualizerWidget::transfer(int16_t value) const
{
    int intensity = clamp((value - VIS_TRANSFER_MIN) * 255 / (VIS_TRANSFER_MAX - VIS_TRANSFER_MIN), 0, 255);
    return QColor(intensity, intensity, intensity);
}

void TVisualizerWidget::initializeGL()
{
    //QGLFunctions* pFunc = QGLContext::currentContext()->functions();
    //qglClearColor(Qt::black);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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
    drawQuads(1);
    swapBuffers();
}

void TVisualizerWidget::draw()
{
    qglColor(Qt::green);

    glBegin(GL_QUADS);
    glVertex3f(0.51, 0.51, 0.51);
    glVertex3f(-0.51, 0.51, 0.51);
    glVertex3f(-0.51, -0.51, 0.51);
    glVertex3f(0.51, -0.51, 0.51);
    glEnd();
}

void TVisualizerWidget::drawQuads(int32_t layerNumber)
{
    glBegin(GL_QUADS);
    for (int32_t x = 0; x < bin.x - 1; x++)
        for (int32_t y = 0; y < bin.y - 1; y++)
        {
            QColor color;

            color = transfer(bin.get(x, y, layerNumber));
            glColor3i(color.red(), color.green(), color.blue());
            glVertex2i(x, y);

            color = transfer(bin.get(x, y + 1, layerNumber));
            glColor3i(color.red(), color.green(), color.blue());
            glVertex2i(x, y + 1);

            color = transfer(bin.get(x + 1, y + 1, layerNumber));
            glColor3i(color.red(), color.green(), color.blue());
            glVertex2i(x + 1, y + 1);

            color = transfer(bin.get(x + 1, y, layerNumber));
            glColor3i(color.red(), color.green(), color.blue());
            glVertex2i(x + 1, y);
        }
    glEnd();
}

TVisualizerWidget::TVisualizerWidget(const char* fileName, QWidget* pWidget) : QGLWidget(pWidget)
{
    bin = TBinaryFile(fileName);
}


