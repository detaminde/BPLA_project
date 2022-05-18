#ifndef OBJLOADER_H
#define OBJLOADER_H
#include <gl/GL.h>

#include <string>
#include <vector>
#include <QVector2D>
#include <QVector3D>
#include <QFile>
#include <QDebug>

#include <QOpenGLFunctions_1_1>


class objloader
{
    struct face
    {
        struct vertex
        {
            GLuint v_i;// индекс вершины
            GLuint vt_i;// индекс текстуры
            GLuint vn_i;// индекс нормали
        };
        vertex v[3];
        face(vertex v1, vertex v2, vertex v3)//полигон, грань
        {
            v[0]=v1;
            v[1]=v2;
            v[2]=v3;
        }
    };
    std::vector<std::string> coord;
    std::vector<QVector3D> vertex;
    std::vector<QVector2D> uvs;
    std::vector<QVector3D> normals;
    std::vector<face> faces;

    objloader(){};
    // запрет на копирование и перемещение rvalue
    objloader(const objloader &) = delete;
    objloader(const objloader &&) = delete;
    objloader& operator=(const objloader &) = delete;
    objloader& operator=(const objloader &&) = delete;
public:
    static objloader& Instance() // реализация синглтона
    {
        static objloader theSingleInstance;
        return theSingleInstance;
    }
    GLuint load(const QString &filename); // загрузка файла
    GLuint draw(GLfloat offset = 0);
};

#endif // OBJLOADER_H
