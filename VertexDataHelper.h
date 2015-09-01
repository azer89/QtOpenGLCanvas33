#ifndef VERTEXDATAHELPER_H
#define VERTEXDATAHELPER_H

#include "AVector.h"
#include "ALine.h"
#include "VertexData.h"

#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

class VertexDataHelper
{
public:
    VertexDataHelper(QOpenGLShaderProgram* shaderProgram);
    ~VertexDataHelper();

    // this function is awkward, should not be put in this class...
    void NeedToDrawWithColor(GLfloat num) { _shaderProgram->setUniformValue(_use_color_location, num); }

    // these functions below are pretty staandard
    void BuildLinesVertexData(std::vector<AVector> points, QOpenGLBuffer* linesVbo, QOpenGLVertexArrayObject* linesVao, QVector3D vecCol);
    void BuildPointsVertexData(std::vector<AVector> points, QOpenGLBuffer* ptsVbo, QOpenGLVertexArrayObject* ptsVao, QVector3D vecCol);
    void BuildLinesVertexData(std::vector<ALine> lines, QOpenGLBuffer* linesVbo, QOpenGLVertexArrayObject* linesVao, QVector3D vecCol);
    void BuildLinesVertexData(std::vector<ALine> lines, QOpenGLBuffer* linesVbo, QOpenGLVertexArrayObject* linesVao, QVector3D vecCol1, QVector3D vecCol2);
    void BuildVboWithColor(QVector<VertexData> data, QOpenGLBuffer* vbo);

private:
    QOpenGLShaderProgram* _shaderProgram;

    int _colorLocation;
    int _vertexLocation;
    int _use_color_location;
    int _texCoordLocation;
};

#endif // VERTEXDATAHELPER_H
