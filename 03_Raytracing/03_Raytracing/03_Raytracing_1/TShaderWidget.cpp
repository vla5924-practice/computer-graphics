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

    /*QOpenGLFunctions_4_3_Core* F = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_3_Core>();
    GLuint ssbo = 0;
    spheresCount = 1;
    spheres = new Sphere;
    F->glGenBuffers(1, &ssbo);
    F->glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
    F->glBufferData(GL_SHADER_STORAGE_BUFFER, spheresCount * sizeof(Sphere), spheres, GL_DYNAMIC_COPY);
    // Now bind the buffer to the zeroth GL_SHADER_STORAGE_BUFFER binding point
    F->glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbo);*/

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    initializeShaders();
}

void TShaderWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    program.setUniformValue("scale", QVector2D(width(), height()));
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

void TShaderWidget::initializeShaders()
{
    std::ifstream config("config.dat");
    if (!config.is_open())
        return;
    std::string vertPath, fragPath;
    config >> vertPath >> fragPath;
    QOpenGLShader vert(QOpenGLShader::Vertex);
    vert.compileSourceFile(vertPath.c_str());
    QOpenGLShader frag(QOpenGLShader::Fragment);
    frag.compileSourceFile(fragPath.c_str());
    program.addShader(&vert);
    program.addShader(&frag);
    if (!program.link())
    {
        qWarning("Error while linking\n");
        return;
    }
    vertDataLocation = program.attributeLocation("vertex");
    qDebug() << program.log();
    if (!program.bind())
        qWarning("Error while shader binding");
    program.setUniformValue("camera.position", readVector(config));
    program.setUniformValue("camera.view", readVector(config));
    program.setUniformValue("camera.up", readVector(config));
    program.setUniformValue("camera.side", readVector(config));
    program.setUniformValue("scale", QVector2D(width(), height()));
    program.release();
}

QVector3D TShaderWidget::readVector(std::ifstream& in)
{
    float x, y, z;
    in >> x >> y >> z;
    return QVector3D(x, y, z);
}