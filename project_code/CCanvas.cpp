#include "CCanvas.h"
#include "Base.h"
#include "Sphere.h"
#include "qevent.h"

using namespace std;

double fast = 0.8;

//-----------------------------------------------------------------------------



void CCanvas::initializeGL()
{

    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);			   // black background
    glClearDepth(1.0f);								   // depth buffer setup
    glEnable(GL_DEPTH_TEST);						   // enables depth testing
    glDepthFunc(GL_LEQUAL);							   // the type of depth testing to do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // really nice perspective calculations
    glShadeModel(GL_SMOOTH);

    // One light source
    glEnable(GL_LIGHTING);

    glEnable(GL_LIGHT0);
    /*
     * The position is transformed by the modelview matrix when glLightfv is called (just as if it were
     * a point), and it is stored in eye coordinates. If the w component of the position is 0.0,
     * the light is treated as a directional source. Diffuse and specular lighting calculations take
     * the light's direction, but not its actual position, into account, and attenuation is disabled.
     * Otherwise, diffuse and specular lighting calculations are based on the actual location of the
     * light in eye coordinates, and attenuation is enabled. The default position is (0,0,1,0); thus,
     * the default light source is directional, parallel to, and in the direction of the -z axis.
     */
    GLfloat lightpos[] = {0.0, 0.0, 6.0, 100.0};
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

    GLfloat lightAmb[]  = {10, 10, 10};
    GLfloat lightDiff[] = {0.9, 0.9, 0.9};
    GLfloat lightSpec[] = {0.9, 0.9, 0.9};

    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpec);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  lightAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  lightDiff);

    /*
     * Before you can use the texture you need to initialize it by calling the setTexture() method.
     * Before you can use OBJ/PLY model, you need to initialize it by calling init() method.
     */
    textureRock.setTexture();
    textureGrass.setTexture();
    textureTree.setTexture();
    textureMill.setTexture();
    texturePropeller.setTexture();
    modelRock.init();
    modelGrass.init();
    modelTree.init();
    modelMill.init();
    modelPropeller.init();
    textureRocket.setTexture();
    textureBee.setTexture();
    textureBox.setTexture();

    modelRocket.init();
    modelBox.init();
    modelBee.init();
}

//-----------------------------------------------------------------------------

void CCanvas::glPerspective(const GLdouble fovy, const GLdouble aspect, const GLdouble zNear, const GLdouble zFar)
{
    const GLdouble d = 1.0 / tan(fovy / 360.0 * PI);
    const GLdouble delta = zNear - zFar;

    GLdouble *mat = new GLdouble[16];

    mat[0] = d / aspect;
    mat[1] = 0.0;
    mat[2] = 0.0;
    mat[3] = 0.0;

    mat[4] = 0.0;
    mat[5] = d;
    mat[6] = 0.0;
    mat[7] = 0.0;

    mat[8]  = 0.0;
    mat[9]  = 0.0;
    mat[10] = (zNear + zFar) / delta;
    mat[11] = -1.0;

    mat[12] = 0.0;
    mat[13] = 0.0;
    mat[14] = 2.0 * zNear * zFar / delta;
    mat[15] = 0.0;

    glMultMatrixd(mat);

    delete[] mat;
}

void CCanvas::lookAt(const GLdouble eyex,
                     const GLdouble eyey,
                     const GLdouble eyez,
                     const GLdouble centerx,
                     const GLdouble centery,
                     const GLdouble centerz,
                     const GLdouble upx,
                     const GLdouble upy,
                     const GLdouble upz)
{
    GLdouble *mat = new GLdouble[16];

    // TODO: add computation for the lookat here!
    Point3d X, Y, Z;

    // create new coordinate system
    Z = Point3d(eyex - centerx, eyey - centery, eyez - centerz);
    Z.normalize();

    // compute Y and X
    Y = Point3d(upx, upy, upz);
    X = Y ^ Z;

    // recompute X
    Y = Z ^ X;

    // normalize
    X.normalize();
    Y.normalize();

    Point3d eye(eyex, eyey, eyez);

    mat[0] = X.x();
    mat[1] = X.y();
    mat[2] = X.z();
    mat[3] = -X * eye;

    mat[4] = Y.x();
    mat[5] = Y.y();
    mat[6] = Y.z();
    mat[7] = -Y * eye;

    mat[8]  = Z.x();
    mat[9]  = Z.y();
    mat[10] = Z.z();
    mat[11] = -Z * eye;

    mat[12] = 0.0;
    mat[13] = 0.0;
    mat[14] = 0.0;
    mat[15] = 1.0;

    glMultMatrixd(mat);

    delete[] mat;
}

void CCanvas::resizeGL(int width, int height)
{
    // set up the window-to-viewport transformation
    glViewport(0, 0, width, height);

    // vertical camera opening angle
    double beta = 60.0;

    // aspect ratio
    double gamma;
    if(height > 0) gamma = width / (double)height;
    else gamma = width;

    // front and back clipping plane at
    double n = -0.01;
    double f = -1000.0;

    // frustum corners
    // double t = -tan(beta * 3.14159 / 360.0) * n;
    // double b = -t;
    // double r = gamma * t;
    // double l = -r;

    // set projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // glFrustum(l,r, b,t, -n,-f);

    // alternatively, directly from alpha and gamma
    glPerspective(beta, gamma, -n, -f);
}

//-----------------------------------------------------------------------------

void CCanvas::setView(View _view) {
    switch(_view) {
    case Perspective:
        glTranslatef(0.0, -20.0, -40.0);
        //glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
        break;
    case Cockpit:
        // Maybe you want to have an option to view the scene from the train cockpit, up to you
        break;
    }
}

void CCanvas::paintGL()
{
    //glutKeyboardFunc(MyKeyboardFunc);
    //cout << tau*2 << "\n";
    tau=tau+fast;
    // clear screen and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set model-view matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Setup the current view
    setView(View::Perspective);

    // You can always change the light position here if you want
    GLfloat lightpos[] = {0.0f, 0.0f, 10.0f, 0.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

    /**** Axes in the global coordinate system ****/
    /*
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_LINES);
        glVertex3f(-6.0f, 0.0f, 0.0f);
        glVertex3f(6.0f, 0.0f, 0.0f);
    glEnd();
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);
        glVertex3f(0.0f, -6.0f, 0.0f);
        glVertex3f(0.0f, 6.0f, 0.0f);
    glEnd();
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_LINES);
        glVertex3f(0.0f, 0.0f, -6.0f);
        glVertex3f(0.0f, 0.0f, 6.0f);
    glEnd();
    */
    //glEnable(GL_LIGHTING);

    /**** Setup and draw your objects ****/

    // You can freely enable/disable some of the lights in the scene as you wish
    //glEnable(GL_LIGHT0);
    //glDisable(GL_LIGHT1);
    // Before drawing an object, you can set its material properties
    /*
    glColor3f(0.5f, 0.5f, 0.5f);
    GLfloat amb[]  = {0.1f, 0.1f, 0.1f};
    GLfloat diff[] = {0.7f, 0.7f, 0.7f};
    GLfloat spec[] = {0.1f, 0.1f, 0.1f};
    GLfloat shin = 0.0001;
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diff);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &shin);
    */

    // Drawing the object with texture

    // Rock
    glPushMatrix();
    textureRock.bind();
    glScalef(0.1f, 0.1f, 0.1f);
    glTranslatef(0.0f, 100.0f, 50.0f);
    glRotatef(50.0f, 0.0f, 1.0f, 0.0f);
    modelRock.draw();
    glPopMatrix();
    textureRock.unbind();

// Grass
    glPushMatrix();
    textureGrass.bind();
    glScalef(0.1f, 0.1f, 0.1f);
    glTranslatef(0.0f, 100.0f, 50.0f);
    glRotatef(50.0f, 0.0f, 1.0f, 0.0f);
    modelGrass.draw();
    glPopMatrix();
    textureGrass.unbind();

// Tree
    glPushMatrix();
    textureTree.bind();
    glScalef(0.1f, 0.1f, 0.1f);
    glTranslatef(0.0f, 100.0f, 50.0f);
    glRotatef(50.0f, 0.0f, 1.0f, 0.0f);
    modelTree.draw();
    glPopMatrix();
    textureTree.unbind();

// Mill
    glPushMatrix();
    textureMill.bind();
    glScalef(0.1f, 0.1f, 0.1f);
    glTranslatef(0.0f, 100.0f, 50.0f);
    glRotatef(50.0f, 0.0f, 1.0f, 0.0f);
    modelMill.draw();
    glPopMatrix();
    textureMill.unbind();


    // Propeller
    glPushMatrix();
//    glTranslatef(-prop.x(), -prop.y(), -prop.z());
    texturePropeller.bind();
//    glRotatef(tau, 0.0f, 0.0f, 1.0f);
//    tau += 1.0f;
//    glTranslatef(prop.x(), prop.y(), prop.z());
    glScalef(0.1f, 0.1f, 0.1f);
    glTranslatef(0.0f, 100.0f, 50.0f);
    glRotatef(50.0f, 0.0f, 1.0f, 0.0f);
    modelPropeller.draw();
    glPopMatrix();
    texturePropeller.unbind();

    // You can stack new transformation matrix if you don't want
    // the previous transformations to apply on this object
//BOX
    glPushMatrix();
    textureBox.bind();
    glTranslated(0, 10, 0);
    glScaled(360, 360, 360);
    //glScaled(tau*2,tau*2,tau*2);
    modelBox.draw();
    textureBox.unbind();
    glPopMatrix();

//ROCKET
    glPushMatrix();
     textureRocket.bind();
    glTranslated(0, 0, 0);
    //glRotated(0,0,0,0);
    glRotated(0+tau,1,0,0);
    modelRocket.draw();
    textureRocket.unbind();
    glPopMatrix();

//BEE
    glPushMatrix();
    textureBee.bind();
    glTranslated(0, 20, 30);
    glRotated(90,0,1,0);
    //modelBee.draw();
    textureBee.unbind();
    glPopMatrix();
}
