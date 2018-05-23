
#include <stdio.h>
#include <chrono>

#include "cpu_algorithm.hpp"
#include "utils.h"

#include "visualization.hpp"

int main(int argc, char** argv)
{
    /*
    Point p1 = {0.0,0.0};
    Point p2 = {1.0,1.0};
    Point p3 = {0.0,1.0};
    Point p4 = {1.0,0.0};
    for(int i = 0; i < 100; i++)
    {
        std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
        Point is = intersection(p1,p2,p3,p4);
        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>( t2 - t1 ).count();
        printf("Points are intersecting at x=%f,y=%f in %li ns\n",is.x,is.y,duration);
        p1.x-=i;
        p1.y-=0.5;
    }
    */
    printf("Testing now visu\n");
    visual_conf cfg;
    cfg.depth = RGB;
    cfg.path_color = {255,255,255};
    cfg.poly_color = {255,255,255};
    cfg.path = "/tmp/test.png";
    Polygon p = {{0.0,0.0},{1.0,0.0},{1.0,0.5},{0.5,0.5},{0.5,1.0},{0.0,1.0},{0.0,0.0}};
    write_to_bitmap(1000,1000,&p,nullptr,cfg);
    return 0;
}
