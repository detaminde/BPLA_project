#include "attitudeindicator.h"

extern GLfloat plane_angle;
extern GLfloat plane_height;

AttitudeIndicator::AttitudeIndicator(QWidget* parent)
    : QOpenGLWidget(parent)
{
    paintTimer = new QTimer(this);
    setAttribute(Qt::WA_DeleteOnClose);
    connect(paintTimer, SIGNAL(timeout()), this, SLOT(repaint()));
    paintTimer->start(16);
}

void AttitudeIndicator::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    //qreal aspectratio = qreal(w) / qreal(h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();// сброс матрицы проекции
    //gluPerspective(90.0, aspectratio, 0.1, 100.0);
    glOrtho(-1, 1, -1, 1, 0.5, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void AttitudeIndicator::initializeGL()
{
    initializeOpenGLFunctions();
    //LoadGLTextures();
    glEnable(GL_MULTISAMPLE);
    //glEnable(GL_TEXTURE_2D);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    p_moveable_model[0].model = objloader::Instance().load("C:\\Users\\User\\Documents\\QTfiles\\proekt\\proekt\\models\\attIndicator\\krujok.obj");
    //нарисовать модельки плоскостей
    p_moveable_model[1].model = objloader::Instance().load("C:\\Users\\User\\Documents\\QTfiles\\proekt\\proekt\\models\\attIndicator\\rotateable_plane.obj");
    p_moveable_model[2].model = objloader::Instance().load("C:\\Users\\User\\Documents\\QTfiles\\proekt\\proekt\\models\\attIndicator\\hor_stick.obj");
    p_moveable_model[3].model = objloader::Instance().load("C:\\Users\\User\\Documents\\QTfiles\\proekt\\proekt\\models\\attIndicator\\vert_stick.obj");



}

void AttitudeIndicator::paintGL()//вместо цвета просто наложить текстуру с цветом
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -2.0f);
    glRotatef(90, 1, 0, 0);
    glScalef(0.3f, 0.3f, 0.3f);
    glCallList(p_moveable_model[0].model);

    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -3.0f);
    glRotatef(90, 1, 0, 0);
    glScalef(0.3f, 0.3f, 0.3f);
    glRotatef(plane_angle, 0, 1, 0);
    glTranslatef(0, 0, plane_height);
    glCallList(p_moveable_model[1].model);//иконка самолёта

    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -3.0f);
    glRotatef(90, 1, 0, 0);
    glScalef(0.3f, 0.3f, 0.3f);
    glCallList(p_moveable_model[2].model);// горизонтальная ось

    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -3.0f);
    glRotatef(90, 1, 0, 0);
    glScalef(0.3f, 0.3f, 0.3f);
    glCallList(p_moveable_model[3].model); // вертикальная ось
}
void AttitudeIndicator::initTexture(uint index, QImage &texture1)
{
    texture1.convertTo(QImage::Format_RGBA8888);
        glBindTexture(GL_TEXTURE_2D, texture_indicator);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, GLsizei(texture1.width()),
                     GLsizei(texture1.height()), 0,
                     GL_RGBA, GL_UNSIGNED_BYTE,
                     texture1.bits());
}
void AttitudeIndicator::LoadGLTextures()
{
    glGenTextures(1, &texture_indicator);

    QImage texture1;
    texture1.load("");
    initTexture(0, texture1);
}

GLuint AttitudeIndicator::drawRotateableQuad()
{
    GLuint num = glGenLists(1);
    glNewList(num, GL_COMPILE);

    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.8471f, 0);
    glVertex3d(-1, -1, 0);glVertex3d(1, -1, 0);
    glVertex3d(1, 0, 0);glVertex3d(-1, 0, 0);
    glEnd();

    glEndList();
    return num;
}
GLuint AttitudeIndicator::drawUpDownQuad()
{
    GLuint num = glGenLists(1);
    glNewList(num, GL_COMPILE);

    glBegin(GL_QUADS);
    glColor3f(0.9569f, 0.7686f, 0.1882f);
    glVertex3d(-0.75, -1, -1.5);glVertex3d(0.75, -1, -1.5);
    glVertex3d(0.75, 0, -1.5);glVertex3d(-0.75, 0, -1.5);
    glEnd();

    glEndList();
    return num;
}
GLuint AttitudeIndicator::drawVerticalQuad()
{
    GLuint num = glGenLists(1);
    glNewList(num, GL_COMPILE);

    glBegin(GL_QUADS);



    glEnd();

    glEndList();
    return num;
}
GLuint AttitudeIndicator::drawVPointer()
{
    GLuint num = glGenLists(1);
    glNewList(num, GL_COMPILE);

    glBegin(GL_TRIANGLES);

    glEnd();

    glEndList();
    return num;
}
