#ifndef PLANE_FRAME_H
#define PLANE_FRAME_H

#include "Windows.h"

#include <QtWidgets/QWidget>
#include <QtOpenGL>
#include <QOpenGLWidget>
#include <gl/GL.h>
#include <gl/GLU.h>
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"GLU32.lib")
#include <QSurfaceFormat>
#include <QTimer>
#include <QKeyEvent>

#include "objloader.h"
class plane_frame : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
    QTimer *paintTimer;
    GLfloat angle = 0;
    GLuint model[3];
    GLuint texture[3];
    GLuint torus = 0;
    GLuint texture_count = 0;
    GLuint model_count = 0;

    GLfloat xRot, yRot, Zrot;
    QPoint mPos;

    void initLight();
    void LoadGLTextures();
    void initTexture(uint index, QImage &texture1);
    GLuint drawCube();
    int loadObject(const QString &filename);

    virtual void mousePressEvent(QMouseEvent* ) override;
    virtual void mouseMoveEvent(QMouseEvent* ) override;
public:
    plane_frame(QWidget *parent = nullptr);
    ~plane_frame()
    {
        delete paintTimer;
    }
protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
};

#endif // PLANE_FRAME_H
