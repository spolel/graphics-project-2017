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

#include "Island.h"

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
        textureTree("../../../../project_code/Models/tree_tex.png"),
        textureMill("../../../../project_code/Models/Mill.png"),
        texturePropeller("../../../../project_code/Models/Propeller.png"),
        textureRock1("../../../../project_code/Models/rock_hard.jpg"),
        textureGrass1("../../../../project_code/Models/Grass.png"),
        textureTree1("../../../../project_code/Models/tree_tex.png"),
        textureMill1("../../../../project_code/Models/Mill.png"),
        texturePropeller1("../../../../project_code/Models/Propeller.png"),
        modelRocket("../../../../project_code/rocket.obj"),
        modelBee("../../../../project_code/boo.obj"),
        modelBox("../../../../project_code/Models/skyBOSS.obj"),
        modelRock("../../../../project_code/Models/rock_hard.obj"),
        modelGrass("../../../../project_code/Models/Grass.obj"),
        modelTree("../../../../project_code/Models/tree.obj"),
        modelMill("../../../../project_code/Models/mill_body.obj"),
        modelPropeller("../../../../project_code/Models/prop.obj"),
        modelRock1("../../../../project_code/Models/rock_hard.obj"),
        modelGrass1("../../../../project_code/Models/Grass.obj"),
        modelTree1("../../../../project_code/Models/tree.obj"),
        modelMill1("../../../../project_code/Models/mill_body.obj"),
        modelPropeller1("../../../../project_code/Models/prop.obj")
    {
        QTimer *timer = new QTimer(this);
        connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
        timer->start(10);
    }

protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void keyPressEvent(QKeyEvent *e);

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


//    enum View {
//        Perspective = 0,    // View the scene from a perspective (from above, from a side, or whatever)
//        Cockpit,             // View the scene from the train cockpit (if you want, or whatever other view)
//        Rotation,
//        SecondIsle
//    };

    int view = 1;

    void setView(int view);

    // Models and textures
    Texture textureRock;
    Texture textureGrass;
    Texture textureTree;
    Texture textureMill;
    Texture texturePropeller;
    Texture textureRock1;
    Texture textureGrass1;
    Texture textureTree1;
    Texture textureMill1;
    Texture texturePropeller1;
    Texture textureRocket;
    Texture textureBee;
    Texture textureBox;
    // Model loaded from .obj format
    ObjModel modelRock;
    ObjModel modelGrass;
    ObjModel modelTree;
    ObjModel modelMill;
    ObjModel modelPropeller;
    ObjModel modelRock1;
    ObjModel modelGrass1;
    ObjModel modelTree1;
    ObjModel modelMill1;
    ObjModel modelPropeller1;
    // Model loaded from .ply format
//    PlyModel modelTrain2;
    ObjModel modelRocket;
    ObjModel modelBee;
    ObjModel modelBox;
};

#endif
