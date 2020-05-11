#include "TShaderWidget.h"
#define GLF glFunctions->

void TShaderWidget::initializeGL()
{
    glFunctions = QOpenGLContext::currentContext()->functions();
    GLF glClearColor(1.f, 1.f, 1.f, 1.f);
    QOpenGLShader vert(QOpenGLShader::Vertex);
    vert.compileSourceFile("rtx.vert");
    QOpenGLShader frag(QOpenGLShader::Fragment);
    frag.compileSourceFile("rtx.frag");
    shaderProg.addShader(&vert);
    shaderProg.addShader(&frag);
    if (!shaderProg.link())
    {
        qWarning("Error while shader linking.");
        return;
    }
    vertexDataLocation = shaderProg.attributeLocation("vertex");
    qDebug() << shaderProg.log();
}

void TShaderWidget::resizeGL(int width, int height)
{
    GLF glViewport(0, 0, width, height);
}

void TShaderWidget::paintGL()
{
    GLF glClear(GL_COLOR_BUFFER_BIT);
    if (!shaderProg.bind())
        return;
    shaderProg.enableAttributeArray(vertexDataLocation);
    shaderProg.setAttributeArray(vertexDataLocation, vertexData, 3);
    GLF glDrawArrays(GL_QUADS, 0, 4);
    shaderProg.disableAttributeArray(vertexDataLocation);
    shaderProg.release();
}

TShaderWidget::TShaderWidget(QWidget* parent) : QOpenGLWidget(parent)
{
}

TShaderWidget::~TShaderWidget()
{
}
