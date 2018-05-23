#pragma once

#include <string>

enum IMAGE_DEPTH
{
    GRAY = 1,
    RGB = 3
};

struct Color
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
} __attribute__((packed));

struct visual_conf
{
    IMAGE_DEPTH depth;
    Color poly_color;
    Color path_color;
    std::string path;
};
