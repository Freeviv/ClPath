#pragma once

#include "datatypes.h"

#include <vector>

Point intersection(Line l1, Line l2);
Point intersection(Point p1, Point p2, Point p3, Point p4);
bool point_in_polygon(Point point, Polygon polygon);

