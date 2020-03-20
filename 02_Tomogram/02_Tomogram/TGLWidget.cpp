#include "TGLWidget.h"

void TGLWidget::initializeGL()
{
    //QGLFunctions* pFunc = QGLContext::currentContext()->functions();
    qglClearColor(Qt::black);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void TGLWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, height, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

void TGLWidget::paintGL()
{
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
    draw();
    //swapBuffers();
}

void TGLWidget::draw()
{
    qglColor(Qt::green);

    glBegin(GL_QUADS);
    glVertex3f(0.51, 0.51, 0.51);
    glVertex3f(-0.51, 0.51, 0.51);
    glVertex3f(-0.51, -0.51, 0.51);
    glVertex3f(0.51, -0.51, 0.51);
    glEnd();
}

TGLWidget::TGLWidget(QWidget* pWidget) : QGLWidget(pWidget)
{
}


