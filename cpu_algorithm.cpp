#include "cpu_algorithm.hpp"

#include <math.h>

Point intersection(Line l1, Line l2)
{
    return intersection(l1.p1, l1.p2, l2.p1, l2.p2);
}

Point intersection(Point p1, Point p2, Point p3, Point p4)
{
    Point ret;
    // Store the values for fast access and easy
    // equations-to-code conversion
    float x1 = p1.x, x2 = p2.x, x3 = p3.x, x4 = p4.x;
    float y1 = p1.y, y2 = p2.y, y3 = p3.y, y4 = p4.y;
 
    float d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    // If d is zero, there is no intersection
    if (d == 0) return ret;
 
    // Get the x and y
    float pre = (x1*y2 - y1*x2), post = (x3*y4 - y3*x4);
    float x = ( pre * (x3 - x4) - (x1 - x2) * post ) / d;
    float y = ( pre * (y3 - y4) - (y1 - y2) * post ) / d;
 
    // Check if the x and y coordinates are within both lines
    if ( x < fmin(x1, x2) || x > fmax(x1, x2) || x < fmin(x3, x4) || x > fmax(x3, x4) ) return ret;
    if ( y < fmin(y1, y2) || y > fmax(y1, y2) || y < fmin(y3, y4) || y > fmax(y3, y4) ) return ret;
 
    // Return the point of intersection

    ret.x = x;
    ret.y = y;
    return ret;
}

bool point_in_polygon(Point point, Polygon polygon)
{
    int i, j, nvert = polygon.size();
    bool c = false;

    for(i = 0, j = nvert - 1; i < nvert; j = i++) {
        if( ( (polygon[i].y >= point.y ) != (polygon[j].y >= point.y) ) &&
                (point.x <= (polygon[j].x - polygon[i].x) * (point.y - polygon[i].y) / (polygon[j].y - polygon[i].y) + polygon[i].x)
                )
            c = !c;
    }

    return c;
}
