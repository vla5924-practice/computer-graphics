#pragma once
#include <QtOpenGL/QGLWidget>
#include <QtOpenGL/QGLFunctions>
#include <GL/gl.h>

class TGLWidget : public QGLWidget
{
protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void draw();
public:
    explicit TGLWidget(QWidget* pWidget = nullptr);
};
