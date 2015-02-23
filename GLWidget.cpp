

#include "stdafx.h"
#include "GLWidget.h"
//#include "KCentersClustering.h"


GLWidget::GLWidget(QGLFormat format, QWidget *parent) :
    QGLWidget(format, parent),
    _isMouseDown(false),
    _zoomFactor(1.0),
    mVertexBufferObject(QOpenGLBuffer::VertexBuffer),
    mVertexArrayObject(this)
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 1, 0))
    std::cout << "Qt version is greater than 5.1.0\n";
#endif
}


GLWidget::~GLWidget()
{
}

void GLWidget::initializeGL()
{
    QGLFormat glFormat = QGLWidget::format();
    if (!glFormat.sampleBuffers())
        { std::cerr << "Could not enable sample buffers." << std::endl; return; }

    glShadeModel(GL_SMOOTH);
    glClearColor( 0.4, 0.4, 0.4, 0.0 );
    glEnable(GL_DEPTH_TEST);

    if (!mProgram.addShaderFromSourceFile(QGLShader::Vertex, "shader.vert"))
        { std::cerr << "Cannot load vertex shader." << std::endl; return; }

    if (!mProgram.addShaderFromSourceFile(QGLShader::Fragment, "shader.frag"))
        { std::cerr << "Cannot load fragment shader." << std::endl; return; }

    if ( !mProgram.link() )
        { std::cerr << "Cannot link shaders." << std::endl; return; }


    float circleData[120];
    double radius = width() < height() ? (float)width() * 0.25 : (float)height() * 0.25;
    std::cout << radius << "\n";
    for(size_t i=0; i<40; ++i)
    {
        circleData[i*3] = radius * cos(i*2*M_PI/40);
        circleData[i*3 + 1] = radius * sin(i*2*M_PI/40);
        circleData[i*3 + 2] = 0.0;
    }

    mVertexArrayObject.create();
    mVertexArrayObject.bind();

    mVertexBufferObject.create();
    mVertexBufferObject.setUsagePattern(QOpenGLBuffer::StaticDraw);

    if (!mVertexBufferObject.bind()) {
        std::cerr << "could not bind vertex buffer to the context." << std::endl;
        return;
    }

    //mVertexBufferObject.allocate(circleData, 40 * 3 * sizeof(float));

    mProgram.bind();

    mProgram.enableAttributeArray("vert");
    mProgram.setAttributeBuffer("vert", GL_FLOAT, 0, 3);

    mMvpMatrixLocation = mProgram.uniformLocation("mvpMatrix");
    mColorLocation = mProgram.uniformLocation("frag_color");
}


bool GLWidget::event( QEvent * event )
{
    return QGLWidget::event(event);
}


// This is an override function from Qt but I can't find its purpose
void GLWidget::resizeGL(int width, int height)
{
    //if (height == 0) { height = 1; }
    //mPerspMatrix.setToIdentity();
    //mPerspMatrix.perspective(60.0, (float) width / (float) height, 0.001, 1000);
    //glViewport(0, 0, width, height);


    //glViewport(0, 0, this->width(),  this->height());
}

void GLWidget::SetColor(const QColor& col)
{
    mProgram.setUniformValue(mColorLocation, col.red(), col.green(), col.blue());
}


void GLWidget::DrawLine(MyPoint p1, MyPoint p2) {

    glLineWidth(2.0);
    const GLfloat lineVertices[] = {
        p1.x, p1.y, 0.0,
        p2.x, p2.y, 0.0
    };
    mVertexBufferObject.allocate(lineVertices, 3 * 2 * sizeof(float));
    glDrawArrays(GL_LINES, 0, 2);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glViewport(0, 0, this->width(),  this->height());

    int current_width = width();
    int current_height = height();

    // Set up for orthogonal drawing to draw a circle on screen.
    // You'll want to make the rest of the function conditional on
    // whether or not we want to draw the circle this time around.

    SetColor(QColor(0.0, 0.0, 0.0));

    // Set orthographic Matrix
    QMatrix4x4 orthoMatrix;

    orthoMatrix.ortho(0.0 +  _scrollOffset.x(),
                      (float)current_width +  _scrollOffset.x(),
                      (float)current_height + _scrollOffset.y(),
                      0.0 + _scrollOffset.y(),
                      -0.1, 0.1);


    /*
    orthoMatrix.ortho(QRect(0.0 +  _scrollOffset.x(),
                            (float)current_width +  _scrollOffset.x(),
                            (float)current_height + _scrollOffset.y(),
                            0.0 + _scrollOffset.y()));
    */

    // Translate the view to the middle
    QMatrix4x4 transformMatrix;
    transformMatrix.setToIdentity();
    //transformMatrix.translate(-_scrollOffset.x(), -_scrollOffset.y(), 0.0);
    //transformMatrix.translate(width()/2.0 - 200, height()/2.0 - 200, 0.0);
    transformMatrix.scale(_zoomFactor);

    // Bind buffer object
    //mVertexBufferObject.bind();
    mProgram.setUniformValue(mMvpMatrixLocation, orthoMatrix * transformMatrix);

    // Draw buffer
    //glDrawArrays(GL_LINE_LOOP, 0, 40);

    DrawLine(MyPoint(0, 0), MyPoint(100, 0));
    DrawLine(MyPoint(0, 0), MyPoint(0, 100));
    DrawLine(MyPoint(100, 0), MyPoint(100, 100));
    DrawLine(MyPoint(0, 100), MyPoint(100, 100));

    DrawLine(MyPoint(50, -100), MyPoint(50, 200));
    DrawLine(MyPoint(-100, 50), MyPoint(200, 50));
}


// Mouse is pressed
void GLWidget::mousePressEvent(int x, int y)
{
    _isMouseDown = true;

    double dx = x + _scrollOffset.x();
    dx /= _zoomFactor;

    double dy = y + _scrollOffset.y();
    dy /= _zoomFactor;


    tempPoints.push_back(MyPoint(dx, dy));

    this->repaint();
}


// Mouse is moved
void GLWidget::mouseMoveEvent(int x, int y)
{
    double dx = x + _scrollOffset.x();
    dx /= _zoomFactor;

    double dy = y + _scrollOffset.y();
    dy /= _zoomFactor;

    if(_isMouseDown)
    {
        tempPoints.push_back(MyPoint(dx, dy));
        this->repaint();
    }
}


// Mouse is released
void GLWidget::mouseReleaseEvent(int x, int y)
{
    _isMouseDown = false;
    double dx = x + _scrollOffset.x();
    dx /= _zoomFactor;

    double dy = y + _scrollOffset.y();
    dy /= _zoomFactor;

    if(tempPoints.size() >= 2)
    {
        tempPoints.push_back(MyPoint(dx, dy));
        std::vector<MyPoint> tempPoints2;
        for(size_t a = 0; a < tempPoints.size(); a++)
        {
            tempPoints2.push_back(tempPoints[a]);
        }
        points.push_back(tempPoints2);
        tempPoints.clear();
    }
    this->repaint();
}

void GLWidget::mouseDoubleClick(int x, int y)
{
    double dx = x + _scrollOffset.x();
    dx /= _zoomFactor;

    double dy = y + _scrollOffset.y();
    dy /= _zoomFactor;
}

// Save image to file
void GLWidget::SaveImage(QString filename)
{
    // Save onscreen
    paintGL();
    glFlush();
    QImage image = this->grabFrameBuffer();
    if( !image.save( filename) ) std::cout << "Error saving image\n";
}

QMatrix4x4 GLWidget::GetCameraMatrix()
{
    // Todo: Ask if we want to keep this.
    QMatrix4x4 vMatrix;

    QMatrix4x4 cameraTransformation;
    QVector3D cameraPosition = cameraTransformation * QVector3D(0, 0, 20.0);
    QVector3D cameraUpDirection = cameraTransformation * QVector3D(0, 1, 0);

    vMatrix.lookAt(cameraPosition, QVector3D(0, 0, 0), cameraUpDirection);

    return mPerspMatrix * vMatrix * mTransformMatrix;
}

void GLWidget::TranslateWorld(float x, float y, float z) {
    // Todo: Ask if we want to keep this.
    mTransformMatrix.translate(x, y, z);
}

void GLWidget::RotateWorld(float x, float y, float z) {
    // Todo: Ask if we want to keep this.
    mTransformMatrix.rotate(x, y, z);
}

void GLWidget::ScaleWorld(float x, float y, float z) {
    // Todo: Ask if we want to keep this.
    mTransformMatrix.scale(x, y, z);
}

void GLWidget::HorizontalScroll(int val) { _scrollOffset.setX(val); }
void GLWidget::VerticalScroll(int val) { _scrollOffset.setY(val); }
void GLWidget::ZoomIn() { this->_zoomFactor += 0.05f; }
void GLWidget::ZoomOut() { this->_zoomFactor -= 0.05f; if(this->_zoomFactor < 0.1f) _zoomFactor = 0.1f; }

void GLWidget::Reset()
{
}

