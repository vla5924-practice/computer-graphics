#include "TShaderWidget.h"

TShaderWidget::TShaderWidget(QWidget* parent)
    : QOpenGLWidget(parent)
{
    constexpr int size = 12;
    GLfloat temp[] = { -1, -1, 0, 1, -1, 0, 1, 1, 0, -1, 1, 0 };
    vertData = new GLfloat[size];
    for (int i = 0; i < size; i++)
        vertData[i] = temp[i];
}

TShaderWidget::~TShaderWidget()
{
    delete[] vertData;
}

void TShaderWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    QOpenGLShader vert(QOpenGLShader::Vertex);
    vert.compileSourceFile("vert.glsl");
    QOpenGLShader frag(QOpenGLShader::Fragment);
    frag.compileSourceFile("frag.glsl");
    program.addShader(&vert);
    program.addShader(&frag);
    if (!program.link())
    {
        qWarning("Error while linking\n");
        return;
    }
    vertDataLocation = program.attributeLocation("vertex");
    qDebug() << QString("Log program");
    qDebug() << program.log();
}

void TShaderWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void TShaderWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    if (!program.bind())
        return;
    program.enableAttributeArray(vertDataLocation);
    program.setAttributeArray(vertDataLocation, vertData, 3);
    glDrawArrays(GL_QUADS, 0, 4);
    program.disableAttributeArray(vertDataLocation);
    program.release();
}