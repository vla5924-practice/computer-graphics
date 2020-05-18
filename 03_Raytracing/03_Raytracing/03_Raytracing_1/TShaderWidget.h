#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <QtWidgets/QOpenGLWidget>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLFunctions_4_3_Core>
#include <GL/glu.h>
#include <GL/gl.h>

struct Sphere
{
    QVector3D center;
    float radius;
    QVector3D color;
    int materialIdx;
};

class TShaderWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
private:
    QOpenGLShaderProgram program;
    GLfloat* vertData;
    int vertDataLocation;
    int spheresCount;
    Sphere* spheres;
protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
public:
    TShaderWidget(QWidget* = nullptr);
    ~TShaderWidget();

    QVector3D readQVector3D(std::ifstream& in)
    {
        float x, y, z;
        in >> x >> y >> z;
        return QVector3D(x, y, z);
    }
};
