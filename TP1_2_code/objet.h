#ifndef OBJET_H
#define OBJET_H

#include <QOpenGLFunctions_3_1>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QFile>
#include <QString>

#include <stdlib.h>
#include <iostream>

using namespace std;

class Objet {

private:
    QMatrix4x4 transformation; //Matrice de transformation
    vector<QVector3D> sommets; //Vertices
    vector<GLushort> indices; //Indexes

public:
    //Constructeurs
    Objet();
    Objet(QString fichier);

    //Accesseurs
    QMatrix4x4 getTransformation();
    vector<QVector3D> getSommets();
    vector<GLushort> getIndices();

    //Transformations matricielles
    void rotation(float angle, QVector3D axe);
    void translation(QVector3D valeurs);
    void zoom(QVector3D valeurs);
};

#endif // OBJET_H
