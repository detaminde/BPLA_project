#ifndef ATTITUDEINDICATOR_H
#define ATTITUDEINDICATOR_H

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
class AttitudeIndicator: public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
    QTimer *paintTimer;

    GLuint texture_indicator;

    void LoadGLTextures();
    void initTexture(uint index, QImage &texture1);

    GLuint drawRotateableQuad();
    GLuint drawUpDownQuad();
    GLuint drawVerticalQuad();
    GLuint drawVPointer();
public:
    explicit AttitudeIndicator(QWidget* parent = nullptr);
    ~AttitudeIndicator(){delete paintTimer;}
    struct moveable_model //сделать изменение параметра извне
    {
        GLuint model;
        GLfloat angle = 0;
    };
    moveable_model p_moveable_model[5];
    void setAngle(moveable_model* model);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;


};

#endif // ATTITUDEINDICATOR_H
