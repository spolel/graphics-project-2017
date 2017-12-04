#ifndef OBJMODEL_H
#define OBJMODEL_H

#include <QtOpenGL>
#include "Point3.h"
#include "Point2.h"

class ObjModel
{
public:
    ObjModel(const std::string &_path);
    void init();
    void draw();
    Point3d center;
    Point3d getCenter();

private:
    std::vector<GLfloat> fvertices;
    std::vector<GLfloat> fuvs;
    std::vector<GLfloat> fnormals; // Won't be used at the moment

    GLuint vertexBuffer;
    GLuint uvBuffer;
    GLuint normalBuffer;
};

#endif // SPHERE_H
