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

        //skybox
        textureSkyBox("../../../../project_code/Textures/skybox-texture.png"),
        modelSkyBox("../../../../project_code/Models/skybox-model.obj"),

        // island 1
        textureRock("../../../../project_code/Textures/island-texture.png"),
        modelRock("../../../../project_code/Models/island-model.obj"),

        textureTree("../../../../project_code/Textures/tree-texture.png"),
        modelTree("../../../../project_code/Models/tree-low-1-model.obj"),

        textureMill("../../../../project_code/Textures/mill-texture.png"),
        modelMill("../../../../project_code/Models/mill-model.obj"),

        texturePropeller("../../../../project_code/Textures/propeller-texture.png"),
        modelPropeller("../../../../project_code/Models/propeller-model.obj"),


        //SEAGULL
        textureSeagull("../../../../project_code/Textures/seagull-texture.png"),

        seagullBody("../../../../project_code/Models/seagull-body.obj"),
        seagullLeft("../../../../project_code/Models/seagull-left-wing.obj"),
        seagullRight("../../../../project_code/Models/seagull-right-wing.obj"),

        //SEAGULL 1
        textureSeagull1("../../../../project_code/Textures/seagull-texture.png"),

        seagullBody1("../../../../project_code/Models/seagull-body.obj"),
        seagullLeft1("../../../../project_code/Models/seagull-left-wing.obj"),
        seagullRight1("../../../../project_code/Models/seagull-right-wing.obj"),

        //UFO
        textureUfo("../../../../project_code/Textures/ufo-texture.png"),

        ufoBody("../../../../project_code/Models/ufo-model.obj"),
        ufoLeg1("../../../../project_code/Models/ufo-leg-1-model.obj"),
        ufoLeg2("../../../../project_code/Models/ufo-leg-2-model.obj"),
        ufoLeg3("../../../../project_code/Models/ufo-leg-3-model.obj"),

        //BIG ISLAND
        textureBigIsland("../../../../project_code/Textures/mountain-island-texture.png"),

        modelBigIsland("../../../../project_code/Models/mountain-island-model.obj"),
        modelForest("../../../../project_code/Models/forest-model.obj"),

        //clouds
        textureCloud("../../../../project_code/Textures/cloud-texture.png"),

        modelCloud("../../../../project_code/Models/cloud-model.obj"),
        modelCloud1("../../../../project_code/Models/cloud-model.obj"),
        modelCloud2("../../../../project_code/Models/cloud-model.obj")

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
    bool start = false;
    double beginpos = 0;
    double retract = 0;
    double tempTau = 0;

    void setView(int view);

    // Models and textures
    Texture textureSkyBox;
    ObjModel modelSkyBox;

    Texture textureRock;
    ObjModel modelRock;

    Texture textureTree;
    ObjModel modelTree;

    Texture textureMill;
    ObjModel modelMill;

    Texture texturePropeller;
    ObjModel modelPropeller;

//    Texture textureRock1;
//    Texture textureTree1;
//    Texture textureMill1;
//    Texture texturePropeller1;
//    ObjModel modelRock1;
//    ObjModel modelTree1;
//    ObjModel modelMill1;
//    ObjModel modelPropeller1;

    Texture textureSeagull;
    Texture textureSeagull1;

    Texture textureUfo;

    ObjModel seagullBody;
    ObjModel seagullLeft;
    ObjModel seagullRight;

    ObjModel seagullBody1;
    ObjModel seagullLeft1;
    ObjModel seagullRight1;

    ObjModel ufoBody;
    ObjModel ufoLeg1;
    ObjModel ufoLeg2;
    ObjModel ufoLeg3;

    //BIG ISLAND
    Texture textureBigIsland;
    ObjModel modelBigIsland;
    ObjModel modelForest;

    //Clouds

    Texture textureCloud;
    ObjModel modelCloud;
    ObjModel modelCloud1;
    ObjModel modelCloud2;

};

#endif
