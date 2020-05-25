#include "TShaderWidget.h"

TShaderWidget::TShaderWidget(QWidget* parent)
    : QOpenGLWidget(parent), dx(0), dy(0), dz(0)
{
    constexpr int size = 12;
    GLfloat temp[] = { -1, -1, 0, 1, -1, 0, 1, 1, 0, -1, 1, 0 };
    vertData = new GLfloat[size];
    for (int i = 0; i < size; i++)
        vertData[i] = temp[i];
    spheres = nullptr;
    spheresCount = 0;
}

TShaderWidget::~TShaderWidget()
{
    delete[] vertData;
}

void TShaderWidget::initializeGL()
{
    initializeOpenGLFunctions();
    std::cout << "OpenGL " << glGetString(GL_VERSION) << '\n';
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    readSpheres();
    //initializeBuffers();
    initializeShaders();
    readCamera();
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
    std::ifstream file("config.dat");
    if (!file.is_open())
        return;
    std::string vertPath, fragPath;
    file >> vertPath >> fragPath;
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
}

void TShaderWidget::initializeBuffers()
{
    QOpenGLFunctions_4_4_Core* F = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_4_Core>();
    GLuint ssbo = 0;
    GLsizeiptr bufferSize = spheresCount * sizeof(Sphere);
    F->glGenBuffers(1, &ssbo);
    std::cerr << F->glGetError();
    F->glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
    std::cerr << F->glGetError();
    F->glBufferData(GL_SHADER_STORAGE_BUFFER, bufferSize, spheres, GL_DYNAMIC_COPY);
    std::cerr << F->glGetError();
    // Now bind the buffer to the zeroth GL_SHADER_STORAGE_BUFFER binding point
    F->glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, ssbo);
    std::cerr << F->glGetError();
    //for (int i = 0; i < spheresCount; i++)
    //    F->glBufferSubData(GL_SHADER_STORAGE_BUFFER, i * sizeof(Sphere), sizeof(Sphere), spheres + i);
}

void TShaderWidget::readCamera()
{
    std::ifstream file("camera.dat");
    if (!file.is_open())
        return;
    if (!program.bind())
        qWarning("Error while shader binding");
    program.setUniformValue("camera.position", scanVector(file));
    program.setUniformValue("camera.view", scanVector(file));
    program.setUniformValue("camera.up", scanVector(file));
    program.setUniformValue("camera.side", scanVector(file));
    program.setUniformValue("scale", QVector2D(width(), height()));
    program.release();
}

void TShaderWidget::readSpheres()
{
    std::ifstream file("spheres.dat");
    if (!file.is_open())
        return;
    file >> spheresCount;
    spheres = new Sphere[spheresCount];
    for (int i = 0; i < spheresCount; i++)
    {
        GLfloat x, y, z, radius, r, g, b;
        GLint materialIdx;
        file >> x >> y >> z >> radius >> r >> g >> b >> materialIdx;
        spheres[i] = Sphere(x, y, z, radius, r, g, b, materialIdx);
    }
}

QVector3D TShaderWidget::scanVector(std::ifstream& in)
{
    float x, y, z;
    in >> x >> y >> z;
    return QVector3D(x, y, z);
}

int TShaderWidget::scanInt(std::ifstream& in)
{
    int n;
    in >> n;
    return n;
}
