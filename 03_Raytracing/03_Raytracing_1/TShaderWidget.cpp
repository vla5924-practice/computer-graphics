#include "TShaderWidget.h"

TShaderWidget::TShaderWidget(QWidget* parent)
    : QOpenGLWidget(parent), 
    camPosX(0), camPosY(0), camPosZ(0), 
    lightPosX(0), lightPosY(0), lightPosZ(0)
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
    readLight();
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
    QOpenGLFunctions_4_3_Core* F = QOpenGLContext::currentContext()->versionFunctions<QOpenGLFunctions_4_3_Core>();
    GLuint ssbo = 0;
    GLsizeiptr bufferSize = spheresCount * sizeof(Sphere);
    F->glGenBuffers(1, &ssbo);
    F->glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
    F->glBufferData(GL_SHADER_STORAGE_BUFFER, bufferSize, spheres, GL_DYNAMIC_COPY);
    F->glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, ssbo);
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
    QVector3D camPos = scanVector(file);
    camPosX = camPos.x();
    camPosY = camPos.y();
    camPosZ = camPos.z();
    program.setUniformValue("camera.position", camPos);
    program.setUniformValue("camera.view", scanVector(file));
    program.setUniformValue("camera.up", scanVector(file));
    program.setUniformValue("camera.side", scanVector(file));
    program.setUniformValue("scale", QVector2D(width(), height()));
    program.release();
}

void TShaderWidget::readLight()
{
    std::ifstream file("light.dat");
    if (!file.is_open())
        return;
    if (!program.bind())
        qWarning("Error while shader binding");
    QVector3D lightPos = scanVector(file);
    lightPosX = lightPos.x();
    lightPosY = lightPos.y();
    lightPosZ = lightPos.z();
    program.setUniformValue("light.position", lightPos);
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

void TShaderWidget::keyPressEvent(QKeyEvent* e)
{
    quint32 key = e->nativeVirtualKey();
    constexpr float delta = 2;
    if (key == Qt::Key_W)
        camPosY += delta;
    else if (key == Qt::Key_A)
        camPosX -= delta;
    else if (key == Qt::Key_S)
        camPosY -= delta;
    else if (key == Qt::Key_D)
        camPosX += delta;
    else if (key == Qt::Key_T)
        lightPosY += delta;
    else if (key == Qt::Key_F)
        lightPosX -= delta;
    else if (key == Qt::Key_G)
        lightPosY -= delta;
    else if (key == Qt::Key_H)
        lightPosX += delta;
    else if (key == Qt::Key_V)
        lightPosZ -= delta;
    else if (key == Qt::Key_B)
        lightPosZ += delta;
    else if (key == Qt::Key_L)
        std::cout << "light.position = { " << lightPosX << ", " << lightPosY << ", " << lightPosZ << " };\n";
    else if (key == Qt::Key_C)
        std::cout << "camera.position = { " << camPosX << ", " << camPosY << ", " << camPosZ << " };\n";
    if (!program.bind())
        return;
    QVector3D camPos(camPosX, camPosY, camPosZ);
    QVector3D lightPos(lightPosX, lightPosY, lightPosZ);
    program.setUniformValue("camera.position", camPos);
    program.setUniformValue("light.position", lightPos);
    program.release();
    update();
}

void TShaderWidget::wheelEvent(QWheelEvent* e)
{
    QPoint angleDelta = e->angleDelta();
    const float delta = angleDelta.y() / 40.0f;
    camPosZ += delta;
    if (!program.bind())
        return;
    QVector3D camPos(camPosX, camPosY, camPosZ);
    program.setUniformValue("camera.position", camPos);
    program.release();
    update();
}
