/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "geometryengine.h"

#include <QVector2D>
#include <QVector3D>
#include <iostream>

//! [0]
GeometryEngine::GeometryEngine()
    : indexBuf(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();

    // Initializes cube geometry and transfers it to VBOs
    //initCubeGeometry();
    //initPlaneGeometry();
}

GeometryEngine::~GeometryEngine()
{
    arrayBuf.destroy();
    indexBuf.destroy();
}
//! [0]

VertexData* GeometryEngine::sommetsToVertexData() {
    vector<QVector3D> lesSommets = obj.getSommets();
    VertexData *vertices = new VertexData[lesSommets.size()];

    for(int i = 0; i < lesSommets.size(); i++) {
        vertices[i] = {lesSommets[i], QVector2D(0.0f, 0.0f)};
    }

    return vertices;
}

GLushort* GeometryEngine::indicesToTab() {
    vector<GLushort> lesIndices = obj.getIndices();
    GLushort* indices = new GLushort[lesIndices.size()];

    for(int i = 0; i < lesIndices.size(); i++) {
        indices[i] = lesIndices[i];
    }

    return indices;
}

void GeometryEngine::initCubeGeometry()
{
    // For cube we would need only 8 vertices but we have to
    // duplicate vertex for each face because texture coordinate
    // is different.
    VertexData vertices[] = {
        // Vertex data for face 0
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(0.0f, 0.0f)},  // v0
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D(0.33f, 0.0f)}, // v1
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(0.0f, 0.5f)},  // v2
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v3

        // Vertex data for face 1
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D( 0.0f, 0.5f)}, // v4
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.33f, 0.5f)}, // v5
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.0f, 1.0f)},  // v6
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.33f, 1.0f)}, // v7

        // Vertex data for face 2
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.5f)}, // v8
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(1.0f, 0.5f)},  // v9
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.66f, 1.0f)}, // v10
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(1.0f, 1.0f)},  // v11

        // Vertex data for face 3
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.0f)}, // v12
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(1.0f, 0.0f)},  // v13
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(0.66f, 0.5f)}, // v14
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(1.0f, 0.5f)},  // v15

        // Vertex data for face 4
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(0.33f, 0.0f)}, // v16
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.0f)}, // v17
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v18
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D(0.66f, 0.5f)}, // v19

        // Vertex data for face 5
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v20
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.66f, 0.5f)}, // v21
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(0.33f, 1.0f)}, // v22
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.66f, 1.0f)}  // v23
    };

    // Indices for drawing cube faces using triangle strips.
    // Triangle strips can be connected by duplicating indices
    // between the strips. If connecting strips have opposite
    // vertex order then last index of the first strip and first
    // index of the second strip needs to be duplicated. If
    // connecting strips have same vertex order then only last
    // index of the first strip needs to be duplicated.
    GLushort indices[] = {
        0,  1,  2,  3,  3,     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
        4,  4,  5,  6,  7,  7, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
        8,  8,  9, 10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
        12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
        16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
        20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
    };

    //! [1]
    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(vertices, 24 * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indices, 34 * sizeof(GLushort));
    //! [1]
}

void GeometryEngine::initPlaneGeometry() {

    VertexData vertices[256]; //On a 256 sommets

    //float paramX1, paramX2, paramY; //Ces floats serviront de paramètres pour les coordonnées
    int compteur = 0; //Le compteur servira à concaténer les sommets.

    /*for(int i = 0; i < 16; i++) {
        paramX = (float)i / 16.0f;
        for(int j = 0; j < 16; j++) {
            paramY = (float)j / 16.0f;
            vertices[compteur] = {QVector3D(paramX, paramY, 1.0f), QVector2D((paramX + 1.0f) / 2.0f,(paramX + 1.0f) / 2.0f)};
            compteur++;
         }
    }*/

    /*for(int i = 0; i < 8; i++) { //On va déclarer deux sommets par colonne par itération, on va donc jusqu'à 8
        paramX1 = (float)(i * 2) / 16.0f;
        paramX2 = (float)((i * 2) + 1) / 16.0f;
        for(int j = 0; j < 16; j++) { //On déclare une colonne par itération, donc on va jusqu'à 16
            paramY = (float)j / 16.0f;
            vertices[compteur] = {QVector3D(paramX1, paramY, 1.0f), QVector2D((paramX1 + 1.0f) / 2.0f,(paramY + 1.0f) / 2.0f)};
            compteur++;
            vertices[compteur] = {QVector3D(paramX2, paramY, 1.0f), QVector2D((paramX2 + 1.0f) / 2.0f,(paramY + 1.0f) / 2.0f)};
            compteur++;
        }
    }*/

    int dimensionX = 16; //Nombre de sommets par lignes
    int dimensionY = 16; //Nombre de sommets par colonnes
    int taille = dimensionX * dimensionY; //Nombre total de sommets

    float paramX = 1.0f / (float)dimensionX; //Pas en X
    float paramY = 1.0f / (float)dimensionY; //Pas en Y

    int random = std::rand() % 100;

    for(int i = 0; i < dimensionX - 1; i+= 2) { //On génère deux sommets par itération, chacuns sur deux colonnes
        for(int j = 0; j < dimensionY; j++) {
            vertices[compteur] = {QVector3D(i * paramX, j * paramY, (float)random * 0.01f), QVector2D((i * paramX + 1.0f) / 2.0f,(j * paramY + 1.0f) / 2.0f)};
            compteur++;
            vertices[compteur] = {QVector3D((i + 1) * paramX, j * paramY, (float)random * 0.01f), QVector2D((i * paramX + 1.0f) / 2.0f,(j * paramY + 1.0f) / 2.0f)};
            compteur++;
        }
    }

    compteur = 0;
    GLushort indices[270];

    /*for(int i = 0; i < 254; i++) {
            indices[compteur] = i;
            indices[compteur + 1] = i + 1;


        }*/


    //On trace la série de lignes facile à tracer

    for(int i = 0; i < taille; i++) { //On met les sommets dans l'ordre
        indices[compteur] = i;
        compteur++;
        if((i + 1) % (2 * dimensionY) == 0 && i > 0) { //A chaque changement de ligne on duplique le dernier sommet et le suivent
            indices[compteur] = i;
            compteur++;
            if(i < 255) {
                indices[compteur] = i + 1;
                compteur++;
            }
        }
    }

    //On trace la série de ligne manquantes
    int ligne1 = 1;
    int ligne2 = 32;
    for(int i =0; i < 8; i++) {
        int depart1 = ligne1;
        int depart2 = ligne2;
        while(ligne1 < depart1 + 30) {
            indices[compteur] = ligne1;
            compteur++;
            indices[compteur] = ligne2;
            compteur++;
            ligne1+= 2;
            ligne2+= 2;
        }
        ligne1 = depart1 + 32;
        ligne2 = depart2 + 32;
    }

    std::cout << compteur << std::endl;

    for(int i = 0; i < 511; i++)
        std::cout << indices[i] << " ";
    std::cout << std::endl;

    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(vertices, 256 * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indices, 270 * sizeof(GLushort));
}

void GeometryEngine::initObjectGeometry(Objet unObjet) {
    obj = unObjet;
    VertexData* vertices = sommetsToVertexData();
    GLushort* indices = indicesToTab();

    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(vertices, obj.getSommets().size() * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indices, obj.getIndices().size() * sizeof(GLushort));
}

//! [2]
void GeometryEngine::drawCubeGeometry(QOpenGLShaderProgram *program)
{
    // Tell OpenGL which VBOs to use
    arrayBuf.bind();
    indexBuf.bind();

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int texcoordLocation = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(texcoordLocation);
    program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLE_STRIP, 34, GL_UNSIGNED_SHORT, 0);
}
//! [2]
void GeometryEngine::drawPlaneGeometry(QOpenGLShaderProgram *program)
{

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // Tell OpenGL which VBOs to use
    arrayBuf.bind();
    indexBuf.bind();

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int texcoordLocation = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(texcoordLocation);
    program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLE_STRIP, 270, GL_UNSIGNED_SHORT, 0);
}

void GeometryEngine::drawObjectGerometry(QOpenGLShaderProgram *program) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // Tell OpenGL which VBOs to use
    arrayBuf.bind();
    indexBuf.bind();

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int texcoordLocation = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(texcoordLocation);
    program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLES, obj.getIndices().size(), GL_UNSIGNED_SHORT, 0);
}
