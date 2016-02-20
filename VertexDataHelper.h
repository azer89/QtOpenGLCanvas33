#ifndef VERTEXDATAHELPER_H
#define VERTEXDATAHELPER_H

/*#include "AVector.h"
#include "ALine.h"
#include "ATriangle.h"
#include "ABox.h"*/
#include "VertexData.h"

#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>

// forward declaration
struct AVector;
struct ALine;
struct ATriangle;
struct ABox;

/**
* Reza Adhitya Saputra
* radhitya@uwaterloo.ca
* February 2016
*/

class VertexDataHelper
{
public:
    VertexDataHelper(QOpenGLShaderProgram* shaderProgram);
    ~VertexDataHelper();

    // this function is awkward, should not be put in this class...
    void NeedToDrawWithColor(GLfloat num) { _shaderProgram->setUniformValue(_use_color_location, num); }

    // these functions below are pretty staandard
    void BuildLinesVertexData( std::vector<AVector> points, QOpenGLBuffer* linesVbo, QOpenGLVertexArrayObject* linesVao, QVector3D vecCol);
    void BuildPointsVertexData(std::vector<AVector> points, QOpenGLBuffer* ptsVbo,   QOpenGLVertexArrayObject* ptsVao,   QVector3D vecCol);
    void BuildLinesVertexData( std::vector<ALine>   lines,  QOpenGLBuffer* linesVbo, QOpenGLVertexArrayObject* linesVao, QVector3D vecCol);
    void BuildLinesVertexData( std::vector<ALine>   lines,  QOpenGLBuffer* linesVbo, QOpenGLVertexArrayObject* linesVao, QVector3D vecCol1, QVector3D vecCol2);
    
	void BuildVboWithColor(    QVector<VertexData>  data,   QOpenGLBuffer* vbo);

	// todo: add UV values :)
	// https://raw.githubusercontent.com/azer89/WVS/2fe0614a71b5596812650bb7ee63ae20d777c08b/GLWidget.cpp
	void BuildQuadsVertexData(std::vector<ABox> boxes, QOpenGLBuffer* vbo, QOpenGLVertexArrayObject* vao);
	void BuildQuadsVertexData(std::vector<ABox> boxes, QOpenGLBuffer* vbo, QOpenGLVertexArrayObject* vao, QVector3D vecCol);
	void BuildTrianglesVertexData(std::vector<ATriangle> triangles, QOpenGLBuffer* vbo, QOpenGLVertexArrayObject* vao, QVector3D vecCol);

private:
    QOpenGLShaderProgram* _shaderProgram;

    int _colorLocation;
    int _vertexLocation;
    int _use_color_location;
    int _texCoordLocation;	
};

#endif // VERTEXDATAHELPER_H
