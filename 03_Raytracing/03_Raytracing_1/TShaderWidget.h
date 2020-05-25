#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <QtWidgets/QOpenGLWidget>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QOpenGLFunctions_4_3_Core>
#include <QtGui/QOpenGLBuffer>
#include <GL/glu.h>
#include <GL/gl.h>
#include <QKeyEvent>
#include <QWheelEvent>

struct Sphere
{
    GLfloat center[4];
    GLfloat radius;
    GLfloat color[4];
    GLint materialIdx;

    Sphere() = default;
    Sphere(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLfloat r, GLfloat g, GLfloat b, GLint materialIdx)
        : radius(radius), materialIdx(materialIdx)
    {
        center[0] = x;
        center[1] = y;
        center[2] = z;
        color[0] = r;
        color[1] = g;
        color[2] = b;
    }
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

    float camPosX, camPosY, camPosZ;
    float lightPosX, lightPosY, lightPosZ;

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    void initializeShaders();
    void initializeBuffers();

    void readCamera();
    void readLight();
    void readSpheres();

    QVector3D scanVector(std::ifstream& in);
    int scanInt(std::ifstream& in);

    void keyPressEvent(QKeyEvent* e) override;
    void wheelEvent(QWheelEvent* e) override;

public:
    TShaderWidget(QWidget* = nullptr);
    ~TShaderWidget();

};
