
#include "VertexDataHelper.h"

/**
 * radhitya@uwaterloo.ca
 *
 *
 *
 */

VertexDataHelper::VertexDataHelper(QOpenGLShaderProgram* shaderProgram)
{
    this->_shaderProgram      = shaderProgram;
    this->_colorLocation      = _shaderProgram->attributeLocation("vertexColor");
    this->_vertexLocation     = _shaderProgram->attributeLocation("vert");
    this->_use_color_location = _shaderProgram->uniformLocation("use_color");
    this->_texCoordLocation   = _shaderProgram->attributeLocation("uv");
}

VertexDataHelper::~VertexDataHelper()
{
}

void VertexDataHelper::BuildLinesVertexData(std::vector<AVector> points, QOpenGLBuffer* linesVbo, QOpenGLVertexArrayObject* linesVao, QVector3D vecCol)
{
    if(points.size() == 0) return;

    bool isInit = false;
    if(!linesVao->isCreated())
    {
        linesVao->create();
        linesVao->bind();
        isInit = true;
    }

    QVector<VertexData> data;
    for(uint a = 0; a < points.size() - 1; a ++)
    {
        data.append(VertexData(QVector3D(points[a].x, points[a].y,  0), QVector2D(), vecCol));
        data.append(VertexData(QVector3D(points[a+1].x, points[a+1].y,  0), QVector2D(), vecCol));
    }

    BuildVboWithColor(data, linesVbo);

    if(isInit) { linesVao->release(); }
}

void VertexDataHelper::BuildLinesVertexData(std::vector<ALine> lines, QOpenGLBuffer* linesVbo, QOpenGLVertexArrayObject* linesVao, QVector3D vecCol1, QVector3D vecCol2)
{
    bool isInit = false;
    if(!linesVao->isCreated())
    {
        linesVao->create();
        linesVao->bind();
        isInit = true;
    }

    QVector<VertexData> data;
    for(uint a = 0; a < lines.size(); a++)
    {
        data.append(VertexData(QVector3D(lines[a].XA, lines[a].YA,  0), QVector2D(), vecCol1));
        data.append(VertexData(QVector3D(lines[a].XB, lines[a].YB,  0), QVector2D(), vecCol2));
    }

    BuildVboWithColor(data, linesVbo);

    if(isInit) { linesVao->release(); }
}

void VertexDataHelper::BuildQuadsVertexData(std::vector<ALine> lines, QOpenGLBuffer* vbo, QOpenGLVertexArrayObject* vao, QVector3D vecCol)
{
	if (vao->isCreated()) { vao->destroy(); }

	vao->create();
	vao->bind();

	QVector<VertexData> data;
	for (uint a = 0; a < lines.size() - 1; a += 2)
	{
		data.append(VertexData(QVector3D(lines[a].XA, lines[a].YA, 0), QVector2D(), vecCol));
		data.append(VertexData(QVector3D(lines[a].XB, lines[a].YB, 0), QVector2D(), vecCol));

		data.append(VertexData(QVector3D(lines[a + 1].XB, lines[a + 1].YB, 0), QVector2D(), vecCol));
		data.append(VertexData(QVector3D(lines[a + 1].XA, lines[a + 1].YA, 0), QVector2D(), vecCol));

	}

	vbo->create();
	vbo->bind();
	vbo->allocate(data.data(), data.size() * sizeof(VertexData));

	quintptr offset = 0;

	_shaderProgram->enableAttributeArray(_vertexLocation);
	_shaderProgram->setAttributeBuffer(_vertexLocation, GL_FLOAT, 0, 3, sizeof(VertexData));

	offset += sizeof(QVector3D);
	offset += sizeof(QVector2D);

	_shaderProgram->enableAttributeArray(_colorLocation);
	_shaderProgram->setAttributeBuffer(_colorLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

	vao->release();
}

void VertexDataHelper::BuildTrianglesVertexData(std::vector<ALine> lines, QOpenGLBuffer* vbo, QOpenGLVertexArrayObject* vao, QVector3D vecCol)
{
	// need to be implemented
}

void VertexDataHelper::BuildLinesVertexData(std::vector<ALine> lines, QOpenGLBuffer* linesVbo, QOpenGLVertexArrayObject* linesVao, QVector3D vecCol)
{
    bool isInit = false;
    if(!linesVao->isCreated())
    {
        linesVao->create();
        linesVao->bind();
        isInit = true;
    }

    QVector<VertexData> data;
    for(uint a = 0; a < lines.size(); a++)
    {
        data.append(VertexData(QVector3D(lines[a].XA, lines[a].YA,  0), QVector2D(), vecCol));
        data.append(VertexData(QVector3D(lines[a].XB, lines[a].YB,  0), QVector2D(), vecCol));
    }

    BuildVboWithColor(data, linesVbo);

    if(isInit) { linesVao->release(); }
}


void VertexDataHelper::BuildPointsVertexData(std::vector<AVector> points, QOpenGLBuffer* ptsVbo, QOpenGLVertexArrayObject* ptsVao, QVector3D vecCol)
{
    bool isInit = false;
    if(!ptsVao->isCreated())
    {
        ptsVao->create();
        ptsVao->bind();
        isInit = true;
    }

    QVector<VertexData> data;
    for(uint a = 0; a < points.size(); a++)
        { data.append(VertexData(QVector3D(points[a].x, points[a].y,  0), QVector2D(), vecCol)); }

    BuildVboWithColor(data, ptsVbo);

    if(isInit) { ptsVao->release(); }
}



void VertexDataHelper::BuildVboWithColor(QVector<VertexData> data, QOpenGLBuffer* vbo)
{
    if(!vbo->isCreated()) { vbo->create(); }
    vbo->bind();
    vbo->allocate(data.data(), data.size() * sizeof(VertexData));

    quintptr offset = 0;

    _shaderProgram->enableAttributeArray(_vertexLocation);
    _shaderProgram->setAttributeBuffer(_vertexLocation, GL_FLOAT, 0, 3, sizeof(VertexData));

    offset += sizeof(QVector3D);
    offset += sizeof(QVector2D);

    _shaderProgram->enableAttributeArray(_colorLocation);
    _shaderProgram->setAttributeBuffer(_colorLocation, GL_FLOAT, offset, 3, sizeof(VertexData));
}


