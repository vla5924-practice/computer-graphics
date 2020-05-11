#include "TShaderWidget.h"
#define GLF glFunctions->

void TShaderWidget::initializeGL()
{
    //F = QOpenGLContext::currentContext()->functions();
    glClearColor(1.f, 1.f, 1.f, 1.f);
    QGLShader vert(QGLShader::Vertex);
    vert.compileSourceFile("rtx.vert");
    QGLShader frag(QGLShader::Fragment);
    frag.compileSourceFile("rtx.frag");
    shaderProg.addShader(&vert);
    shaderProg.addShader(&frag);
    if (!shaderProg.link())
    {
        std::cerr << "Error while shader linking.";
        return;
    }
    vertexDataLocation = shaderProg.attributeLocation("vertex");
    std::cout << shaderProg.log().toStdString();
}

void TShaderWidget::resizeGL(int width, int height)
{
    glShadeModel(GL_SMOOTH);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 1, 0, 1, -1, 1);
    glViewport(0, 0, width, height);
}

void TShaderWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //drawTest();
    //swapBuffers();
    
    //glClear(GL_COLOR_BUFFER_BIT);
    if (!shaderProg.bind())
    {
        std::cerr << "Error while binding.";
        return;
    }
    shaderProg.enableAttributeArray(vertexDataLocation);
    shaderProg.setAttributeArray(vertexDataLocation, vertexData, 3);
    glDrawArrays(GL_QUADS, 0, 4);
    shaderProg.disableAttributeArray(vertexDataLocation);
    shaderProg.release();
}

void TShaderWidget::drawTest()
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

TShaderWidget::TShaderWidget(QWidget* parent) : QGLWidget(parent)
{
}

TShaderWidget::~TShaderWidget()
{
}
