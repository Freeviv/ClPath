#pragma once

#include <math.h>
#include <vector>

struct Point
{
    float x = NAN;
    float y = NAN;
}__attribute__((packed));

struct Line
{
    Point p1;
    Point p2;
}__attribute__((packed));

typedef std::vector<Point> Polygon;
typedef std::vector<Point> Path;
