#include "objet.h"

Objet::Objet() {
    transformation = QMatrix4x4(0.0f, 0.0f, 0.0f, 0.0f,
                                0.0f, 0.0f, 0.0f, 0.0f,
                                0.0f, 0.0f, 0.0f, 0.0f,
                                0.0f, 0.0f, 0.0f, 0.0f);
}

Objet::Objet(QString fichier) {
    transformation = QMatrix4x4(0.0f, 0.0f, 0.0f, 0.0f,
                                0.0f, 0.0f, 0.0f, 0.0f,
                                0.0f, 0.0f, 0.0f, 0.0f,
                                0.0f, 0.0f, 0.0f, 0.0f);

    QFile qFile(fichier);
       if (!qFile.open(QIODevice::ReadOnly | QIODevice::Text))
              assert(false);

       QString line = qFile.readLine();
       line = line.chopped(1);

       assert(line == "OFF");

       line = qFile.readLine();
       line = line.chopped(1);
       QStringList fields = line.split(" ");

       int vsize = fields[0].toInt();
       int isize = fields[1].toInt();

       for (int i = 0; i < vsize; ++i)
       {
           line = qFile.readLine();
           line = line.chopped(1);
           fields = line.split(" ");
           float x, y, z;
           x = fields[0].toFloat();
           y = fields[1].toFloat();
           z = fields[2].toFloat();
           QVector3D v = QVector3D(x, y, z);
           sommets.push_back(v);
       }

       for (int i = 0; i < isize; ++i)
       {
           line = qFile.readLine();
           line = line.chopped(1);
           fields = line.split(" ");
           indices.push_back(fields[0].toInt());
           indices.push_back(fields[1].toInt());
           indices.push_back(fields[2].toInt());
       }

       qFile.close();
}

//Accesseurs
QMatrix4x4 Objet::getTransformation() {
    return transformation;
}

vector<QVector3D> Objet::getSommets() {
    return sommets;
}

vector<GLushort> Objet::getIndices() {
    return indices;
}

//Transformation matricielles

void Objet::rotation(float angle, QVector3D axe) {
    transformation.rotate(angle, axe);
}

void Objet::translation(QVector3D valeurs) {
    transformation.translate(valeurs);
}

void Objet::zoom(QVector3D valeurs) {
    transformation.scale(valeurs);
}
