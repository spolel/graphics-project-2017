#include "Island.h"

Island::Island(Texture &textureRock,Texture &textureGrass,Texture &textureTree,Texture &textureMill,Texture &texturePropeller,
               ObjModel &modelRock, ObjModel &modelGrass, ObjModel &modelTree, ObjModel &modelMill, ObjModel &modelPropeller):
    textureRock(textureRock),
    textureGrass(textureGrass),
    textureTree(textureTree),
    textureMill(textureMill),
    texturePropeller(texturePropeller),
    modelRock(modelRock),
    modelGrass(modelGrass),
    modelTree(modelTree),
    modelMill(modelMill),
    modelPropeller(modelPropeller)
{
    tau = 0;
    isle = 0;
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
}

void Island::draw(){
    // Rock
    glPushMatrix();
    textureRock.bind();
    glScalef(0.1f, 0.1f, 0.1f);
    glTranslatef(200.0f, 100.0f, -500.0f);
    glRotatef(50.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.0f, -sin(isle/40.0)*10.0f, 50.0f);
    modelRock.draw();
    glPopMatrix();
    textureRock.unbind();

    // Grass
    glPushMatrix();
    textureGrass.bind();
    glScalef(0.1f, 0.1f, 0.1f);
    glTranslatef(200.0f, 100.0f, -500.0f);
    glRotatef(50.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.0f, -sin(isle/40.0)*10.0f, 50.0f);
    modelGrass.draw();
    glPopMatrix();
    textureGrass.unbind();

    // Tree
    glPushMatrix();
    textureTree.bind();
    glScalef(0.1f, 0.1f, 0.1f);
    glTranslatef(220.0f, 145.0f, -490.0f);
    glRotatef(50.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.0f, -sin(isle/40.0)*10.0f, 50.0f);
    modelTree.draw();
    glPopMatrix();
    textureTree.unbind();


    // Mill
    glPushMatrix();
    textureMill.bind();
    glScalef(0.1f, 0.1f, 0.1f);
    glTranslatef(225.0f, 160.0f, -530.0f);
    //glRotatef(50.0f, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.0f, -sin(isle/40.0)*10.0f, 50.0f);
    glRotatef(30.0f, 0.0f, 1.0f, 0.0f);
    modelMill.draw();
    glPopMatrix();
    textureMill.unbind();


    // Propeller
    glPushMatrix();
    texturePropeller.bind();
    glScalef(0.1f, 0.1f, 0.1f);
    glTranslatef(211.0f, 175.0f, -523.0f); // position of the model in the world
    glTranslatef(0.0f, -sin(isle/40.0)*10.0f, 50.0f); // bobbing motion
    glRotatef(30.0f, 0.0f, 1.0f, 0.0f); // rotate the model to face the right direction
    glRotatef(tau, 1.0f, 0.0f, 0.0f); // rotation of the windmill propeller
    modelPropeller.draw();
    glPopMatrix();
    texturePropeller.unbind();
}

void Island::rotatePropeller(){
}

void Island::incrementIsle(){
    isle = isle + 1.0;
}

void Island::incrementTau(double fast){
    tau = tau + fast;
}
