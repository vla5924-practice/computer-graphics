#pragma once
#include <QtWidgets/QOpenGLWidget>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QOpenGLShaderProgram>
#include <GL/gl.h>

class TShaderWidget : public QOpenGLWidget
{
    QOpenGLFunctions* glFunctions;
    QOpenGLShaderProgram shaderProg;
    GLfloat* vertexData;
    int vertexDataLocation;

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

public:
    TShaderWidget(QWidget* parent = nullptr);
    ~TShaderWidget();

};