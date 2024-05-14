 #include "photoshape.h"

photoshape::photoshape(){
    shapetype = 1;
}

bool photoshape::isInside(QPoint point)
{
    if(shapetype > 1)
    {
        if(point.x() > vertex[0].x() && point.x() < vertex[1].x() && point.y() < vertex[2].y() && point.y() > vertex[3].y())
            return true;
     }
    return false;
}
