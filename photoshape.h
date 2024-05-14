#ifndef PHOTOSHAPE_H
#define PHOTOSHAPE_H

#include <QPoint>
#include <QPainterPath>
class photoshape
{
public:
    int shapetype;
    QPoint vertex[4]; // vertex[0]--left(upleft) , vertex[1]--right(bottomright), vertex[2]--bottom(bottomleft), vertex[3]--up(upright)..the description inside the brakect is for rectangle.
    QPainterPath path;
    photoshape();
    photoshape(int type, QPoint v[4], QPainterPath p):shapetype(type), path(p){for(int i = 0; i < 4; i ++) vertex[i] = v[i];}
    bool isInside(QPoint point);

};

#endif // PHOTOSHAPE_H
