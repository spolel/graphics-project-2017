/************************************************************************/
/* Guards                                                               */
/************************************************************************/
#ifndef CCANVAS_H
#define CCANVAS_H

#include <iostream>
#include <QtOpenGL>
#include <QGLWidget>
#include <QTimer>

#include "Base.h"
#include "texture.hpp"

#include "ObjModel.h"
#include "PlyModel.h"

using namespace std;

/************************************************************************/
/* Canvas to draw                                                       */
/************************************************************************/
class CCanvas : public QGLWidget
{
  Q_OBJECT

public:
    explicit CCanvas(QWidget *parent = 0) : QGLWidget(parent),tau(0),
        textureRocket("../../../../project_code/train1.jpg"),
        textureBee("../../../../project_code/white.png"),
        textureBox("../../../../project_code/Models/skyBOSS.jpg"),
        textureRock("../../../../project_code/Models/rock_hard.jpg"),
        textureGrass("../../../../project_code/Models/Grass.png"),
        textureTree("../../../../project_code/Models/Tree.png"),
        textureMill("../../../../project_code/Models/Mill.png"),
        texturePropeller("../../../../project_code/Models/Propeller.png"),
        modelRocket("../../../../project_code/rocket.obj"),
        modelBee("../../../../project_code/boo.obj"),
        modelBox("../../../../project_code/Models/skyBOSS.obj"),
        modelRock("../../../../project_code/Models/rock_hard.obj"),
        modelGrass("../../../../project_code/Models/Grass.obj"),
        modelTree("../../../../project_code/Models/Tree.obj"),
        modelMill("../../../../project_code/Models/Mill.obj"),
        modelPropeller("../../../../project_code/Models/Propeller.obj")
    {
        QTimer *timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
        timer->start(10);
    }

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

private:
    double tau;
    void lookAt(const GLdouble eyex,
                const GLdouble eyey,
                const GLdouble eyez,
                const GLdouble centerx,
                const GLdouble centery,
                const GLdouble centerz,
                const GLdouble upx,
                const GLdouble upy,
                const GLdouble upz);

    void glPerspective(const GLdouble fovy,
                       const GLdouble aspect,
                       const GLdouble zNear,
                       const GLdouble zFar);


    enum View {
        Perspective = 0,    // View the scene from a perspective (from above, from a side, or whatever)
        Cockpit             // View the scene from the train cockpit (if you want, or whatever other view)
    };

    void setView(View _view);

    // Models and textures
    Texture textureRock;
    Texture textureGrass;
    Texture textureTree;
    Texture textureMill;
    Texture texturePropeller;
    Texture textureRocket;
    Texture textureBee;
    Texture textureBox;
    // Model loaded from .obj format
    ObjModel modelRock;
    ObjModel modelGrass;
    ObjModel modelTree;
    ObjModel modelMill;
    ObjModel modelPropeller;
    // Model loaded from .ply format
//    PlyModel modelTrain2;
    ObjModel modelRocket;
    ObjModel modelBee;
    ObjModel modelBox;
};

#endif
