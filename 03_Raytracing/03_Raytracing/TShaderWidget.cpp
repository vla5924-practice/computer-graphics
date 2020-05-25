#include "TShaderWidget.h"
#define GLF glFunctions->

void TShaderWidget::initializeGL()
{
    //std::cout << "gl ver " << glGetString(GL_VERSION) << '\n'; 
    glClearColor(1.f, 1.f, 1.f, 1.f);
    QGLShader* vert = new QGLShader(QGLShader::Vertex);
    vert->compileSourceFile("rtx.vert");
    QGLShader* frag = new QGLShader(QGLShader::Fragment);
    frag->compileSourceFile("rtx.frag");
    program = new QGLShaderProgram(this);
    program->addShader(vert);
    program->addShader(frag);

    //program->addShaderFromSourceFile(QGLShader::Vertex, ":/rtx.vert");
    //program->addShaderFromSourceFile(QGLShader::Fragment, ":/rtx.frag");

    if (!program->link())
    {
        std::cerr << "Error while shader linking.";
        return;
    }
    vertexDataLocation = program->attributeLocation("vertex");
    std::cout << program->log().toStdString();
}

void TShaderWidget::resizeGL(int width, int height)
{
    //glShadeModel(GL_SMOOTH);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1);
    glViewport(0, 0, width, height);
}

void TShaderWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //drawTest();
    //swapBuffers();
    
    //glClear(GL_COLOR_BUFFER_BIT);
    if (!program->bind())
    {
        std::cerr << "Error while binding.";
        return;
    }
    program->enableAttributeArray(vertexDataLocation);
    program->setAttributeArray(vertexDataLocation, vertexData, 3);
    glDrawArrays(GL_QUADS, 0, 4);
    program->disableAttributeArray(vertexDataLocation);
    program->release();
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

TShaderWidget::TShaderWidget(QWidget* parent)
    : QGLWidget(parent)
{
    constexpr int size = 12;
    GLfloat temp[] = { -1, -1, 0, 1, -1, 0, 1, 1, 0, -1, 1, 0 };
    vertexData = new GLfloat[size];
    for (int i = 0; i < size; i++)
        vertexData[i] = temp[i];
}

TShaderWidget::~TShaderWidget()
{
    delete[] vertexData;
}