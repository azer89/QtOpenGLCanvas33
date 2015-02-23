

#include "stdafx.h"

#include "GLContainer.h"

#include <QGridLayout>

GLContainer::GLContainer(QWidget *parent) :
    QAbstractScrollArea (parent),
    ctrlPressed(false),
    mousePressed(false),
    sWidth(20),
    sHeight(20),
    prevNum(-1),
    scrollMoved(false)
{
    QGLFormat format;
    format.setVersion(4, 0);
    format.setProfile(QGLFormat::CompatibilityProfile);
    format.setSampleBuffers(true);

    glWidget = new GLWidget(format);
    glWidget->setObjectName(QStringLiteral("myGLImageDisplay"));

    setViewport(glWidget);

    horizontalScrollBar()->setSingleStep(10);
    horizontalScrollBar()->setPageStep(100);

    verticalScrollBar()->setSingleStep(10);
    verticalScrollBar()->setPageStep(100);

    connect(horizontalScrollBar(), SIGNAL(valueChanged(int)),this, SLOT(HScrollChanged(int)));
    connect(verticalScrollBar(),   SIGNAL(valueChanged(int)),this, SLOT(VScrollChanged(int)));

    setMouseTracking(true);

    doubleClickTimer = new QTimer(this); connect(doubleClickTimer, SIGNAL(timeout()), this, SLOT(DummyFunction()));
    doubleClickTimeout = 100;

    //UpdateViewport(true);
    this->justInitialized = true;
}

void GLContainer::UpdateViewport(bool putInMiddle)
{
    QSize barSize = QSize(this->width() - sWidth, this->height() - sHeight);

    float zoomFactor = glWidget->GetZoomFactor();
    //QSize canvasSize  = glWidget->GetCanvasSize();

    //QSize borderLimit( 10, 10);

    //int img_width =	canvasSize.width()  * zoomFactor;
    //int img_height = canvasSize.height() * zoomFactor;

    int img_width = 100 * zoomFactor;
    int img_height  = 100 * zoomFactor;

    float xSPos;
    float ySPos;
    if(!putInMiddle)
    {
        float xNormPos = mousePos.x() + xPrevF;
        float yNormPos = mousePos.y() + yPrevF;
        xNormPos /= prevZoomFactor;
        yNormPos /= prevZoomFactor;

        float xRev = xNormPos * zoomFactor;
        float yRev = yNormPos * zoomFactor;
        xSPos = xRev - mousePos.x();
        ySPos = yRev - mousePos.y();
    }

    int leftRange = 0;
    int rightRange = 0;
    int upRange = 0;
    int downRange = 0;

    float hPos = 0;
    float vPos = 0;

    int xGap = abs(barSize.width() - img_width);
    int yGap = abs(barSize.height() - img_height);

    if(img_width <= barSize.width())
    {
        if(putInMiddle)hPos = -xGap * 0.5; //
        else hPos = xSPos;

        leftRange = -img_width - xGap;
        rightRange = img_width;

    }
    else
    {
        if(putInMiddle) hPos = xGap * 0.5;
        else hPos = xSPos;
        leftRange = -img_width + xGap;
        rightRange = img_width;
    }

    if(img_height <= barSize.height())
    {
        if(putInMiddle) vPos = -yGap * 0.5;
        else vPos = ySPos;

        upRange =  -img_height -yGap;
        downRange = img_height;

    }
    else
    {
        if(putInMiddle) vPos = yGap * 0.5;
        else vPos = ySPos;
        upRange = -img_height + yGap;
        downRange = img_height;
    }

    xPrevF = hPos;
    yPrevF = vPos;

    horizontalScrollBar()->setRange(leftRange, rightRange);
    verticalScrollBar()->setRange(upRange, downRange);

    horizontalScrollBar()->setSliderPosition(hPos);
    verticalScrollBar()->setSliderPosition(vPos);
}

void GLContainer::paintEvent(QPaintEvent *event)
{

    if(this->justInitialized)
    {
        UpdateViewport(true);
        this->justInitialized = false;
    }



    // please fix me
    if(this->width() != glWidget->width() || this->height() != glWidget->height())
    {
        glWidget->setFixedWidth(this->width());
        glWidget->setFixedHeight(this->height());
    }

    QAbstractScrollArea::paintEvent(event);
    glWidget->updateGL();
}

bool GLContainer::event(QEvent * event)
{
    //if(scrollMoved)
    //{
    //    UpdateViewport(false);
    //}
    //else
    //{

    //    UpdateViewport(true);

    //}

    if(event->type() == QEvent::Resize)
    {
        std::cout << "resize\n";
    }

    bool evResult = QAbstractScrollArea::event(event);
    return evResult;
}

void GLContainer::SetScrolls()
{
    horizontalScrollBar()->setVisible(true);
    verticalScrollBar()->setVisible(true);

    prevZoomFactor = 1.0f;

    // nasty code here...
    bool shouldZoom = true;
    do
    {
        //int _w = this->width();
        //int _h = this->height();
        //QSize imgSize = glWidget->GetCanvasSize();
        QSize imgSize(100, 100);
        double zoomFactor = glWidget->GetZoomFactor();

        if((double)this->width()  < (double)imgSize.width() * zoomFactor ||  (double)this->height() < (double)imgSize.height() *zoomFactor)
        { glWidget->ZoomOut(); }
        else
        { shouldZoom = false; }
    } while (shouldZoom);
    UpdateViewport(true);
}

void GLContainer::VScrollChanged(int val)
{
    yPrevF = val;
    glWidget->VerticalScroll(val);
    this->scrollMoved = true;
}
void GLContainer::HScrollChanged(int val)
{
    xPrevF = val;
    glWidget->HorizontalScroll(val);
    this->scrollMoved = true;
}

void GLContainer::DummyFunction()
{
    doubleClickTimer->stop();
}

void GLContainer::mousePressEvent(QMouseEvent *event)
{
    if(doubleClickTimer->isActive())
    {
        doubleClickTimer->stop();
        glWidget->mouseDoubleClick(event->x(), event->y());
    }
    else
    {
    }

    this->mousePressed = true;

    if(!this->ctrlPressed)
    {
        glWidget->mousePressEvent(event->x(), event->y());
    }

    if(this->ctrlPressed)
    {
        this->prevMousePos = mousePos;
        this->prevScrollPos.setX(horizontalScrollBar()->sliderPosition());
        this->prevScrollPos.setY(verticalScrollBar()->sliderPosition());
    }
}

void GLContainer::mouseMoveEvent(QMouseEvent *event)
{
    mousePos.setX(event->x());
    mousePos.setY(event->y());

    if(this->ctrlPressed && this->mousePressed)
    {
        int xDelta = mousePos.x() - prevMousePos.x();
        int yDelta = mousePos.y() - prevMousePos.y();
        horizontalScrollBar()->setSliderPosition(prevScrollPos.x() - xDelta);
        verticalScrollBar()->setSliderPosition(prevScrollPos.y() - yDelta);
    }

    glWidget->mouseMoveEvent(event->x(), event->y());
}

void GLContainer::mouseReleaseEvent(QMouseEvent *event)
{
    this->mousePressed = false;
    if(!this->ctrlPressed)
    {
        glWidget->mouseReleaseEvent(event->x(), event->y());
    }

    doubleClickTimer->start(doubleClickTimeout);
}

void GLContainer::wheelEvent(QWheelEvent* event)
{
    bool scrollDir = (event->delta() > 0) ? true : false;	// negative means scroll down, positive is otherwise
    prevZoomFactor = glWidget->GetZoomFactor();		// for anchor zoom

    if(scrollDir) glWidget->ZoomOut();
    else glWidget->ZoomIn();

    float zoomFactor = glWidget->GetZoomFactor() * 100.0;

    // update scrollbars
    UpdateViewport();
}

void GLContainer::keyPressEvent(QKeyEvent *event)
{
    //if(event->key() == Qt::Key_C) { this->glWidget->DoClustering(); }

    glWidget->updateGL();
}

void GLContainer::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Control) { this->ctrlPressed = false; }
}

// get renderer
GLWidget* GLContainer::GetGLWidget()
{
    return this->glWidget;
}

/*
void GLContainer::DoClustering(int k)
{
    this->glWidget->DoClustering(k);
}
*/

