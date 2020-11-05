#include "espace.h"

//Constructeurs
Espace::Espace() {

}

//Accesseurs
vector<Objet*> Espace::getAllObjets() {
   vector<Objet*> lesObjets;
   for(int i = 0; i < objets.size(); i++)
       lesObjets.push_back(&objets[i]);
   for(int i = 0; i < sousEspaces.size(); i++) {
       vector<Objet*> sousObjets = sousEspaces[i].getAllObjets();
       lesObjets.insert(lesObjets.end(), sousObjets.begin(), sousObjets.end());
   }
    return lesObjets;
}

//Gestion des collections
void Espace::ajoutSousEspace(Espace unEspace) {
    sousEspaces.push_back(unEspace);
}

void Espace::ajoutObjet(Objet unObjet) {
    objets.push_back(unObjet);
}

Espace Espace::getSousEspace(int index) {
    return sousEspaces[index];
}

Objet Espace::getObjet(int index) {
    return objets[index];
}

void Espace::supprSousEspace(int index) {
    sousEspaces.erase(sousEspaces.begin() + index);
}

void Espace::supprObjet(int index) {
    objets.erase(objets.begin() + index);
}

void Espace::clearSousEspace() {
    sousEspaces.clear();
}

void Espace::clearObjet() {
    objets.clear();
}

//Transformations matricielles
void Espace::rotation(float angle, QVector3D axe) {
    for(int i = 0; i < sousEspaces.size(); i++) {
        sousEspaces[i].rotation(angle, axe);
    }

    for(int i = 0; i < objets.size(); i++) {
        objets[i].rotation(angle, axe);
    }
}

void Espace::translation(QVector3D valeurs) {
    for(int i = 0; i < sousEspaces.size(); i++) {
        sousEspaces[i].translation(valeurs);
    }

    for(int i = 0; i < objets.size(); i++) {
        objets[i].translation(valeurs);
    }
}

void Espace::zoom(QVector3D valeurs) {
    for(int i = 0; i < sousEspaces.size(); i++) {
        sousEspaces[i].zoom(valeurs);
    }

    for(int i = 0; i < objets.size(); i++) {
        objets[i].zoom(valeurs);
    }
}
