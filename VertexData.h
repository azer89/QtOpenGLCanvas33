#ifndef VERTEXDATA_H
#define VERTEXDATA_H

#include <QVector2D>
#include <QVector3D>

/**
* Reza Adhitya Saputra
* radhitya@uwaterloo.ca
* February 2016
*/

// https://raw.githubusercontent.com/azer89/WVS/2fe0614a71b5596812650bb7ee63ae20d777c08b/GLWidget.cpp

struct VertexData
{
    QVector3D position;
    QVector2D texCoord;
    QVector3D color;

public:

    VertexData(QVector3D position, QVector2D texCoord, QVector3D color)
    {
        this->position = position;
        this->texCoord = texCoord;
        this->color = color;
    }

    VertexData(QVector3D position, QVector2D texCoord)
    {
        this->position = position;
        this->texCoord = texCoord;
        this->color = QVector3D();
    }

    VertexData()
    {
        this->position = QVector3D();
        this->texCoord = QVector2D();
        this->color = QVector3D();
    }
};

#endif // VERTEXDATA_H
