#pragma once

#include <iostream>
//#include <QtWidgets/QOpenGLWidget>
//#include <QtGui/QOpenGLFunctions>
//#include <QtGui/QOpenGLShaderProgram>
#include <QtOpenGL/QGLWidget>
#include <QtOpenGL/QGLShaderProgram>
#include <GL/glu.h>
#include <GL/gl.h>

class TShaderWidget : public QGLWidget
{
    Q_OBJECT
    //QOpenGLFunctions* F;
    QGLShaderProgram shaderProg;
    //QGLShaderProgram shaderProg;
    GLfloat* vertexData;
    int vertexDataLocation;

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void drawTest();

public:
    TShaderWidget(QWidget* parent = nullptr);
    ~TShaderWidget();

};