#ifndef ISLAND_H
#define ISLAND_H

#include "CCanvas.h"

class Island
{
public:
    Island(Texture &textureRock,Texture &textureGrass,Texture &textureTree,Texture &textureMill,Texture &texturePropeller,
           ObjModel &modelRock, ObjModel &modelGrass, ObjModel &modelTree, ObjModel &modelMill, ObjModel &modelPropeller);
    void draw();
    void rotatePropeller();
    void incrementTau(double fast);
    void incrementIsle();

private:
    double tau;
    double isle;

    // Models and textures
    Texture textureRock;
    Texture textureGrass;
    Texture textureTree;
    Texture textureMill;
    Texture texturePropeller;

    // Model loaded from .obj format
    ObjModel modelRock;
    ObjModel modelGrass;
    ObjModel modelTree;
    ObjModel modelMill;
    ObjModel modelPropeller;

};

#endif // ISLAND_H
