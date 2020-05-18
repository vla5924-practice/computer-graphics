#pragma once
#include <iostream>
#include <QtWidgets/QOpenGLWidget>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QOpenGLShaderProgram>
#include <GL/glu.h>
#include <GL/gl.h>

class TShaderWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
private:
    QOpenGLShaderProgram program;
    GLfloat* vertData;
    int vertDataLocation;
protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
public:
    TShaderWidget(QWidget* = nullptr);
    ~TShaderWidget();
};