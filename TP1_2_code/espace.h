#ifndef ESPACE_H
#define ESPACE_H

#include <QOpenGLFunctions_3_1>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>

#include <stdlib.h>
#include <iostream>
#include <vector>

#include "objet.h"

using namespace std;

class Espace{

private:
    vector<Espace> sousEspaces; //Sous-espace contenus dans l'espace
    vector<Objet> objets; //Objets contenus dans l'espace

public:
    //Constructeurs
    Espace();

    //Accesseurs
    vector<Objet*> getAllObjets();

    //Gestion des collections
    void ajoutSousEspace(Espace unEspace);
    void ajoutObjet(Objet unObjet);
    Espace getSousEspace(int index);
    Objet getObjet(int index);
    void supprSousEspace(int index);
    void supprObjet(int index);
    void clearSousEspace();
    void clearObjet();

    //Transformations matricielles
    void rotation(float angle, QVector3D axe);
    void translation(QVector3D valeurs);
    void zoom(QVector3D valeurs);
};

#endif // ESPACE_H
