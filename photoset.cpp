
#include <QtWidgets>
#include <QtPrintSupport/qtprintsupportglobal.h>
#include <QPrinter>
#include <QPrintDialog>
#include "photoset.h"
#include <QPainterPath>
#include <QFont>
#include <QLinearGradient>
#include <QDebug>
#include <QMatrix2x2>
#include <QMatrix3x3>
#include <QBrush>
#include <QGradient>
#include "photoshape.h"
#include <QStyleOption>
#include<cdialog.h>
#include<mainwindow.h>

photoset::photoset(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    modified = false;
    scribbling = false;

    filling = new int(0);
    fillbrush = new  QBrush(Qt::SolidPattern);

    myPenWidth = 1;
    myPenColor = Qt::blue;
    myPenType = Qt::SolidLine;
    type = photoset::Pen;
    adjustSize();
    cd=new cdialog;
   // setMaximumSize(400,400);

    bgColor = qRgb(255, 255, 255);
    image = QImage(700, 500, QImage::Format_RGB32);
    image.fill(bgColor);
    tempImage = image;
    moveTime = 0;
    selected = false;


}

bool photoset::openImage(const QString &fileName)

{
    QImage loadedImage;
    if (!loadedImage.load(fileName))
        return false;
   // QSize newSize = loadedImage.size();
   //resizeImage(&loadedImage, newSize);
   lastImage = loadedImage;
    image = loadedImage;
    modified = false;
    update();
    return true;
}

bool photoset::saveImage(const QString &fileName, const char *fileFormat)
{
    QImage visibleImage = image;
    resizeImage(&visibleImage, size());

    if (visibleImage.save(fileName, fileFormat)) {
        modified = false;
        return true;
    } else {
        return false;
    }
}
void photoset::resetimage()
{
     tempImage = image;
    image=lastImage;
    update();
}
void photoset::graimage()
{
    QImage ix;
    ix=image.convertToFormat(QImage::Format_ARGB32);
    for(int i=0;i<image.width();i++)
    {
        for(int j=0;j<image.height();j++)
        {
            QRgb pixel=image.pixel(i,j);
            int gray=qGray(pixel);
            image.setPixel(i,j,qRgb(gray,gray,gray));
        }
    }
    this->update();
}
void photoset::masaicimage()
{
    QImage ix;
    ix=image.convertToFormat(QImage::Format_ARGB32);

    int w=image.width()%SIZE;
    int h=image.height()%SIZE;
    qDebug()<<image.width();
    for(int i=0;i<image.width()-w;i+=SIZE)
    {
        for(int j=0;j<image.height()-h;j+=SIZE)
        {
            int r=0,g=0,b=0;
            for(int k=i;k<i+SIZE;k++)
            {
                for(int e=j;e<j+SIZE;e++)
                {
                    QColor c=image.pixelColor(k,e);
                    r+=c.red();
                    g+=c.green();
                    b+=c.blue();
                }
            }
            QColor newcolor(r/(SIZE*SIZE),g/(SIZE*SIZE),b/(SIZE*SIZE));
            for(int k=i;k<i+SIZE;k++)
            {
                for(int e=j;e<j+SIZE;e++)
                {
                    image.setPixelColor(k,e,newcolor);
                }
            }
        }
    }
    this->update();
}
void photoset::setPenColor(const QColor &newColor)
{
    myPenColor = newColor;
}

void photoset::setPenWidth(int newWidth)
{
    myPenWidth = newWidth;
}

void photoset::set2bgColor()
{
    myPenColor = bgColor;
}
void photoset::setSize(QSize s)
{
    //setMaximumSize(s.width(), s.height());
}
void photoset::setbgColor(const QColor &bgc)
{
    bgColor = bgc;
    image.fill(bgColor);
}
void photoset::setPenType(int s)
{
    myPenType = s;
}
void photoset::setShape(photoset::shape s)
{
    type = s;
}
void photoset::setMovement()
{

    type = Move;
    selected = true;

}

void photoset::setFillStyle(int *s, QBrush *brush)
{
     filling = s;
     fillbrush = brush;
}

void photoset::clearImage()

{
    image.fill(bgColor);
    modified = true;
    states.clear();
    moveStates.clear();
    update();
}
void photoset::wheelEvent(QWheelEvent *event)
{
    int value = event->angleDelta().y();
    if (value > 0)
        onZoomInImage();
    else
        onZoomOutImage();

    this->update();
}
void photoset::onZoomOutImage(void)
{
    m_ZoomValue -= 0.2;
    if (m_ZoomValue <= 0)
    {
        m_ZoomValue += 0.2;
        return;
    }

    this->update();
}

void photoset::onPresetImage(void)
{
    m_ZoomValue = 1.0;
    m_XPtInterval = 0;
    m_YPtInterval = 0;
    this->update();
}
void photoset::onZoomInImage()
{
    m_ZoomValue += 0.2;
    this->update();
}

void photoset::mousePressEvent(QMouseEvent *event)
{
    if(cd->state) {m_OldPos = event->pos();
    m_Pressed = true;
    }
    else{if(type != Move){
        moveTime = 0;
    }
    if (event->button() == Qt::LeftButton) {
        int width = qMin(image.width(), this->width());
        int height = width * 1.0 / (image.width() * 1.0 / image.height());
        height = qMin(height, this->height());
        width = height * 1.0 * (image.width() * 1.0 / image.height());

        lastPoint .rx()= (event->pos().rx()-m_XPtInterval)/(m_ZoomValue*width*1.5/image.width());
        lastPoint .ry()= (event->pos().ry()-m_YPtInterval)/(m_ZoomValue*height*1.5/image.height()) ;
        qDebug()<<lastPoint .rx()<<lastPoint .ry();

    }
    if(event->button() == Qt::LeftButton && !shapeSet.empty() && filling)
    {
        foreach(photoshape i, shapeSet)
        {
            if(i.shapetype == *filling && i.isInside(event->pos()))
            {
                QPainter painter(&image);
                painter.fillPath(i.path, *fillbrush);
                update();
                break;
            }
        }
    }}
}

void photoset::mouseMoveEvent(QMouseEvent *event)
{

    //f (event->buttons() & Qt::LeftButton && !filling)
   // {
    if(!(cd->state)&&(event->buttons() & Qt::LeftButton) /*&& !filling*/){
       int width = qMin(image.width(), this->width());
       int height = width * 1.0 / (image.width() * 1.0 / image.height());
       height = qMin(height, this->height());
       width = height * 1.0 * (image.width() * 1.0 / image.height());

       endPoint .rx()= (event->pos().rx()-m_XPtInterval)/(m_ZoomValue*width*1.5/image.width());
       endPoint .ry()= (event->pos().ry()-m_YPtInterval)/(m_ZoomValue*height*1.5/image.height()) ;
       qDebug()<<endPoint .rx()<<endPoint .ry();
        scribbling = true;
            tempImage = image;
            if(type == Pen)
            { paint(image);}
                //drawLineTo();
            else
                paint(tempImage);
            //qDebug()<<"!";
   // }

    }    else{if (!m_Pressed)
                return QWidget::mouseMoveEvent(event);

            this->setCursor(Qt::SizeAllCursor);
            QPoint pos = event->pos();
            int xPtInterval = pos.x() - m_OldPos.x();
            int yPtInterval = pos.y() - m_OldPos.y();

            m_XPtInterval += xPtInterval;
            m_YPtInterval += yPtInterval;

            m_OldPos = pos;
            this->update();}
}

void photoset::mouseReleaseEvent(QMouseEvent *event)
{
    m_Pressed = false;
    this->setCursor(Qt::ArrowCursor);
    scribbling = false;
    int width = qMin(image.width(), this->width());
    int height = width * 1.0 / (image.width() * 1.0 / image.height());
    height = qMin(height, this->height());
    width = height * 1.0 * (image.width() * 1.0 / image.height());

    endPoint .rx()= (event->pos().rx()-m_XPtInterval)/(m_ZoomValue*width*1.5/image.width());
    endPoint .ry()= (event->pos().ry()-m_YPtInterval)/(m_ZoomValue*height*1.5/image.height()) ;
    qDebug()<<endPoint .rx()<<endPoint .ry();
    image=tempImage;
    if(type != Pen && !selected && !filling)
    {paint(image);
        //image=tempImage;
    }
    if(type == Move)
        ++moveTime;


}


void photoset::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    //painter.setRenderHint(QPainter::Antialiasing);
    //if(cd->state){
    QStyleOption opt;
    opt.initFrom(this);

    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

    if (image.isNull())
        return QWidget::paintEvent(event);

    // 根据窗口计算应该显示的图片的大小
    int width = qMin(image.width(), this->width());
    int height = width * 1.0 / (image.width() * 1.0 / image.height());
    height = qMin(height, this->height());
    width = height * 1.0 * (image.width() * 1.0 / image.height());

    painter.translate( m_XPtInterval,  m_YPtInterval);
    // 缩放
    qDebug()<< m_XPtInterval<< m_YPtInterval;
    painter.scale(m_ZoomValue, m_ZoomValue);
    qDebug()<< m_ZoomValue;
    // 绘制图像
    QRect picRect(0, 0, width*1.5, height*1.5);
    if(scribbling == true && type != Pen)
    { painter.drawImage(picRect, tempImage);
        }
    else
        painter.drawImage(picRect, image);
    //else{
       // if(scribbling == true && type != Pen)
        //    painter.drawImage(0,0, tempImage);
       // else
        //    painter.drawImage(0,0, tempImage);

    //}*/

}

void photoset::resizeEvent(QResizeEvent *event)
{
    if (width() > image.width() || height() > image.height()) {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}



void photoset::paint(QImage &theImage)
{
    QPainter painter(&theImage);
    painter.setRenderHint(QPainter::Antialiasing);
    if(myPenColor == bgColor)
        myPenColor = Qt::blue;
    if(myPenType == Qt::SolidLine)
        state.pen = QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                                          Qt::RoundJoin);
    else if(myPenType == Qt::DotLine)
        state.pen = QPen(myPenColor, myPenWidth, Qt::DotLine, Qt::RoundCap,
                         Qt::RoundJoin);
    else if(myPenType == Qt::DashLine)
        state.pen = QPen(myPenColor, myPenWidth, Qt::DashLine, Qt::RoundCap,
                         Qt::RoundJoin);
    else if(myPenType == Qt::DashDotLine)
        state.pen = QPen(myPenColor, myPenWidth, Qt::DashDotLine, Qt::RoundCap,
                         Qt::RoundJoin);
    else
        state.pen = QPen(myPenColor, myPenWidth, Qt::DashDotDotLine, Qt::RoundCap,
                         Qt::RoundJoin);

    painter.setPen(state.pen);

    switch(type)
    {
        case photoset::Line:
        {
            painter.drawLine(lastPoint, endPoint);
            break;
        }
    case photoset::Rect:
    {
        QPainterPath path;
        QRect rect = QRect(lastPoint.x(), lastPoint.y(), endPoint.x(), endPoint.y());
        path.addRect(rect);
        painter.drawPath(path);
        if(scribbling == false)
        {
            QPoint v[4] = {rect.topLeft(), rect.bottomRight(), rect.bottomLeft(), rect.topRight()};
            photoshape temp(photoset::Rect, v, path);
            shapeSet.push_back(temp);
            state.path = path;
            states.push_back(state);
            state.path= state.path.subtracted(state.path);
        }
        break;
    }
    case photoset::Ellipse:
    {
         QPainterPath path;
         path.addEllipse(lastPoint.x(), lastPoint.y(), endPoint.x() - lastPoint.x(), endPoint.y() - lastPoint.y());
         painter.drawPath(path);
         if(scribbling == false)
         {
             QPoint v[4] = {lastPoint, endPoint, endPoint, lastPoint};
             photoshape temp(photoset::Ellipse, v, path);
             shapeSet.push_back(temp);
             state.path = path;
             states.push_back(state);
             state.path= state.path.subtracted(state.path);
         }
         break;
    }
    case photoset::Pen:
    {
        state.path.moveTo(lastPoint);
        state.path.lineTo(endPoint);
        painter.drawPath(state.path);
        states.push_back(state);
        state.path= state.path.subtracted(state.path);
        lastPoint = endPoint;
        break;
    }
    case photoset::Move:
    {
        if(moveTime == 0)
        {
            painter.setPen(Qt::DashLine);
            painter.drawRect(lastPoint.x(), lastPoint.y(), endPoint.x(), endPoint.y());
            pre = lastPoint;
            cur = endPoint;
        }
        if(moveTime > 1)
        {
            selected = false;
            for(QVector <State> :: iterator iter = states.begin();iter != states.end();){
                if((*iter).path.currentPosition().x()< cur.x() && (*iter).path.currentPosition().x() > pre.x() && (*iter).path.currentPosition().y() < cur.y() && (*iter).path.currentPosition().y() > pre.y())
                {
                    moveStates.push_back(*iter);
                    states.erase(iter);
                }else{
                    iter ++;
                }
            }
            for(int i = 0;i<moveStates.size();++i){
                moveStates[i].path.translate(endPoint.x()-lastPoint.x(),endPoint.y()-lastPoint.y());
            }

            lastPoint = endPoint;
            state.path= state.path.subtracted(state.path);

        }
        break;
    }
    }

    foreach (State state, states) {
        painter.setPen(state.pen);
        painter.drawPath(state.path);
    }
    foreach (State moveState, moveStates) {
        painter.setPen(moveState.pen);
        painter.drawPath(moveState.path);
    }
    state.path.moveTo(0,0);

    modified = true;
    update();
}

void photoset::resizeImage(QImage *image, const QSize &newSize)
{
    if (image->size() == newSize)
        return;
    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}

void photoset::print()
{
    QPrinter printer(QPrinter::HighResolution);//(QPrinter::PrinterMode mode = QPrinter::HighResolution);
    QPrintDialog printDialog(&printer,this);
     if (printDialog.exec() == QDialog::Accepted) {
        QPainter painter(&printer);
        QRect rect = painter.viewport();
        QSize size = image.size();
        size.scale(rect.size(), Qt::KeepAspectRatio);
        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
        painter.setWindow(image.rect());
        painter.drawImage(0, 0, image);
    }
}

