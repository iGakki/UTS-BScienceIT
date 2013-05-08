#ifndef _POINT_H
#define _POINT_H

struct point
{
    // struct to store coordinates
    
    int x;
    int y;
    
    point() : x(-1), y(-1)
    {
    }
    
    point(int xx, int yy) : x(xx), y(yy)
    {
    }
    
    void setPoint(int xx, int yy)
    {
       x = xx;
       y = yy;
    }
};

#endif
