#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QMatrix4x4>
#include <QtOpenGL/QGLWidget>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

#include "APath.h"

/**
* Reza Adhitya Saputra
* radhitya@uwaterloo.ca
* February 2016
*/

// forward declaration
struct AVector;
struct ALine;
struct ATriangle;
struct ABox;
//struct APath; // cannot forward declaration ?
struct VertexData;
class VertexDataHelper;

class GLWidget : public QGLWidget
{
    Q_OBJECT

private:
	// image
	QImage _imgOriginal;
	QImage _imgGL;
	GLuint _imgID;

	// boxes
	std::vector<ABox>		 _boxes;
	QOpenGLBuffer            _boxVbo;
	QOpenGLVertexArrayObject _boxVao;

	// triangles
	std::vector<ATriangle>   _triangles;
	QOpenGLBuffer            _triangleVbo;
	QOpenGLVertexArrayObject _triangleVao;

    VertexDataHelper* _vDataHelper;

    bool   _isMouseDown;
    float  _zoomFactor;
    QPoint _scrollOffset;

    // image size
    int _img_width;
    int _img_height;

    float _slice;

    // shader
    QOpenGLShaderProgram* _shaderProgram;

    // points
	APath					 _path;
    //std::vector<AVector>   _points;
    QOpenGLBuffer            _pointsVbo;
    QOpenGLVertexArrayObject _pointsVao;

    // path
    QOpenGLBuffer            _linesVbo;
    QOpenGLVertexArrayObject _linesVao;

	// multiple paths
	//APath					  _tempPath;
	size_t					 _pathsDataSize;
	std::vector<QVector3D>	 _pathsColors;
	std::vector<APath>		 _paths;
	QOpenGLBuffer            _pathsVbo;
	QOpenGLVertexArrayObject _pathsVao;


    // for rendering
    int        _mvpMatrixLocation;
    int        _colorLocation;
    int        _vertexLocation;
    int        _use_color_location;
    QMatrix4x4 _perspMatrix;
    QMatrix4x4 _transformMatrix;

public:
    // constructor
    GLWidget( QGLFormat format, QWidget *parent = 0);
    // destructor
    ~GLWidget();

    QSize GetCanvasSize() { return QSize(_img_width, _img_height); }

    void AddSlice();
    void RemoveSlice();

    // zoom in handle
    void ZoomIn();
    // zoom out handle
    void ZoomOut();
    // set zoom value
    void SetZoom(int val){this->_zoomFactor = val;}
    // get zoom value
    float GetZoomFactor() { return this->_zoomFactor; }

    // set horizontal scroll position
    void HorizontalScroll(int val);
    // set vertical scroll position
    void VerticalScroll(int val);
    // get scroll position (horizontal and vertical)
    QPoint GetScrollOffset() {return this->_scrollOffset;}

    // mouse press
    void mousePressEvent(int x, int y);
    // mouse move
    void mouseMoveEvent(int x, int y);
    // mouse release
    void mouseReleaseEvent(int x, int y);
    // mouse double click
    void mouseDoubleClick(int x, int y);

protected:
	// qt event
	bool event(QEvent * event);
	// init opengl
	void initializeGL();
	// draw
	void paintGL();

	void resizeGL(int width, int height);

private:
	void CreateCurve();			 // remove this
	void PaintCurve();			 // remove this
	void BuildCurveVertexData(); // remove this

	void SaveToSvg();
	void SetImage(QString img);
};

#endif // GLWIDGET_H
