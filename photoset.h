#ifndef PHOTOSET_H
#define PHOTOSET_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <QPainterPath>
#include <QVector>
#include <QPen>
#include<QMouseEvent>
#include "photoshape.h"
#include<cdialog.h>
#include <QPainterPath>
#define SIZE 10
class photoset    : public QWidget
{
    Q_OBJECT

struct State
{
      QPainterPath path;
      QPen pen;
};
public:
    photoset(QWidget *parent = 0);
     enum shape
    {
        Line = 1,
        Rect,
        Ellipse,
        Pen,
        Move
    };

    int *filling;
    QBrush *fillbrush;
    cdialog *cd;
    bool openImage(const QString &fileName);
    bool saveImage(const QString &fileName, const char *fileFormat);
    void setbgColor(const QColor &bgc);
    void setSize(QSize s);
    void setPenColor(const QColor &newColor);
    void setPenWidth(int newWidth);
    void setPenType(int s);
    void set2bgColor();
    void setShape(photoset::shape s);
    void setMovement();
    void setFillStyle(int *s, QBrush *brush);
    bool isModified() const { return modified; }
    QColor penColor() const { return myPenColor; }
    QColor getbgColor() const {return bgColor;}
    int penWidth() const { return myPenWidth; }
    void graimage();
    void resetimage();
    void masaicimage();

public slots:
    void clearImage();
    void print();
    void onZoomInImage();
    void onZoomOutImage();
    void onPresetImage();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
private:
    void drawLineTo();
    QImage image;
    void paint(QImage &theImage);
    void resizeImage(QImage *image, const QSize &newSize);
    bool modified;
    bool scribbling;
    bool selected;

    qreal m_ZoomValue = 1.0;
    int m_XPtInterval = 0;
    int m_YPtInterval = 0;
    QPoint m_OldPos;
    bool m_Pressed = false;


    int moveTime;
    int myPenWidth;
    int myPenType;
    photoset::shape type;
    QColor bgColor;
    QColor myPenColor;

    QImage tempImage;
    QImage lastImage;
    QPoint lastPoint;
    QPoint endPoint;
    QPoint pre;
    QPoint cur;
    //QVector<QVector<QPoint>> lines;//笔记数据
    QPainterPath  m_tmpPainterPath;   // 当前path对象
    QPolygon       m_tmpPolygon;       // path对象的数据容器
    QList<QPainterPath>     m_listPainterPath;   // 添加数据容器
    State state;
    QVector<State> states;
    QVector<State> moveStates;
    QVector<photoshape> shapeSet;
    QPainterPath ppath;
};


#endif
