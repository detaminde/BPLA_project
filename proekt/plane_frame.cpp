#include "Windows.h"
#include "plane_frame.h"

plane_frame::plane_frame(QWidget* parent) : QOpenGLWidget(parent)
{
    //resize(400, 200);
    paintTimer = new QTimer(this);
    setAttribute(Qt::WA_DeleteOnClose);
    connect(paintTimer, SIGNAL(timeout()), this, SLOT(repaint()));
    paintTimer->start(16);
}

void plane_frame::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    qreal aspectratio = qreal(w) / qreal(h);//соотношение сторон

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();// сброс матрицы проекции
    gluPerspective(90.0, aspectratio, 0.1, 100.0);

    //инициализация модели вида проекции
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void plane_frame::mousePressEvent(QMouseEvent * mo)
{
    mPos = mo->pos();
}
void plane_frame::mouseMoveEvent(QMouseEvent * mo)
{
    xRot += (180/M_PI *(mo->pos().y() - mPos.y())) / 10;
    yRot += (180/M_PI *(mo->pos().x() - mPos.x())) / 10;
    //mPos = mo->pos();

}
void plane_frame::initializeGL()
{

    initializeOpenGLFunctions();
    glEnable(GL_MULTISAMPLE);
    LoadGLTextures();
    glEnable(GL_TEXTURE_2D);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    initLight();
    model[0] = objloader::Instance().load("C:\\Users\\User\\Documents\\QTfiles\\proekt\\proekt\\models\\plane\\fuselage.obj");
    model[1] = drawCube();
    //torus = objloader::Instance().load("")
}

void plane_frame::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTranslatef(0,0, -5.5);
    glScalef(0.01f, 0.01f, 0.01f);
    //glDeleteLists(torus, 1);
    //torus = objloader::Instance().draw(angle/180);
    //glCallList(torus);
    //glTranslatef(0,0, 0.1f);
    glRotatef(xRot, 1, 0, 0);
    glRotatef(yRot, 0, 1, 0);
    glBindTexture(GL_TEXTURE_2D, texture[texture_count]);
    glCallList(model[model_count]);
}
void plane_frame::initTexture(uint index, QImage &texture1)
{
    texture1.convertTo(QImage::Format_RGBA8888);
    glBindTexture(GL_TEXTURE_2D, texture[index]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, GLsizei(texture1.width()),
                 GLsizei(texture1.height()), 0,
                 GL_RGBA, GL_UNSIGNED_BYTE,
                 texture1.bits());
}
void plane_frame::LoadGLTextures()//закинуть текстурку
{
    glGenTextures(3, texture);

    QImage texture1;
    texture1.load("C:\\Users\\User\\Documents\\QTfiles\\proekt\\proekt\\models\\textures\\bricks.jpg");
    initTexture(0, texture1);
}

void plane_frame::initLight()
{
    GLfloat light_ambient[] = {0 , 0 , 0 ,0};
    GLfloat light_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light_position[] = {0, 0, 2.0, 1.0};

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}
GLuint plane_frame::drawCube()
{
    GLuint num = glGenLists(1);
    glNewList(num, GL_COMPILE);

    glBegin(GL_QUADS);
    glNormal3f( 0.0f, 0.0f, 1.0f);     // Нормаль указывает на наблюдателя
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Низ лево
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Низ право
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Верх право
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Верх лево

                    // Задняя грань
    glNormal3f( 0.0f, 0.0f,-1.0f);     // Нормаль указывает от наблюдателя
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Низ право
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Верх право
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Верх лево
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Низ лево

                    // Верхняя грань
    glNormal3f( 0.0f, 1.0f, 0.0f);     // Нормаль указывает вверх
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Верх лево
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Низ лево
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Низ право
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Верх право

                    // Нижняя грань
    glNormal3f( 0.0f,-1.0f, 0.0f);     // Нормаль указывает вниз
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Верх право
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Верх лево
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Низ лево
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Низ право

                    // Правая грань
    glNormal3f( 1.0f, 0.0f, 0.0f);     // Нормаль указывает вправо
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);	// Низ право
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);	// Верх право
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Верх лево
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);	// Низ лево

                    // Левая грань
    glNormal3f(-1.0f, 0.0f, 0.0f);     // Нормаль указывает влево
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);	// Низ лево
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);	// Низ право
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);	// Верх право
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);	// Верх лево
    glEnd();

    glEndList();
    return num;
}

