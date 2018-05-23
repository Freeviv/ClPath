#include "visualization.hpp"

#include <stdint.h>
#include <cstring>
#include <math.h>

#include "external/lodepng/lodepng.h"

#define PNG_DEBUG 3
#include <png.h>

#define BIT_DEPTH 8


/*
function line(x0, y0, x1, y1)
    real deltax := x1 - x0
    real deltay := y1 - y0
    real deltaerr := abs(deltay / deltax)    // Assume deltax != 0 (line is not vertical),
          // note that this division needs to be done in a way that preserves the fractional part
    real error := 0.0 // No error at start
    int y := y0
    for x from x0 to x1
        plot(x,y)
        error := error + deltaerr
        while error ≥ 0.5 then
            y := y + sign(deltay) * 1
            error := error - 1.0

*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

void abort_(const char * s, ...)
{
        va_list args;
        va_start(args, s);
        vfprintf(stderr, s, args);
        fprintf(stderr, "\n");
        va_end(args);
        abort();
}

void write_png_file(uint8_t *img,int width, int height,char* file_name,bool gray)
{
    png_byte color_type = (gray) ? PNG_COLOR_TYPE_GRAY : PNG_COLOR_TYPE_RGB;

    png_structp png_ptr;
    png_infop info_ptr;
    png_bytep * row_pointers;



    /* create file */
    FILE *fp = fopen(file_name, "wb");
    if (!fp)
        abort_("[write_png_file] File %s could not be opened for writing", file_name);


    /* initialize stuff */
    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!png_ptr)
        abort_("[write_png_file] png_create_write_struct failed");

    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr)
        abort_("[write_png_file] png_create_info_struct failed");

    if (setjmp(png_jmpbuf(png_ptr)))
        abort_("[write_png_file] Error during init_io");

    png_init_io(png_ptr, fp);


    /* write header */
    if (setjmp(png_jmpbuf(png_ptr)))
        abort_("[write_png_file] Error during writing header");

    png_set_IHDR(png_ptr, info_ptr, width, height,
                 BIT_DEPTH, color_type, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_write_info(png_ptr, info_ptr);


    /* write bytes */
    if (setjmp(png_jmpbuf(png_ptr)))
        abort_("[write_png_file] Error during writing bytes");

    png_write_image(png_ptr, row_pointers);


    /* end write */
    if (setjmp(png_jmpbuf(png_ptr)))
        abort_("[write_png_file] Error during end of write");

    png_write_end(png_ptr, NULL);

    /* cleanup heap allocation */
    for (int y = 0; y < height; y++)
        free(row_pointers[y]);
    free(row_pointers);

    fclose(fp);
}

void draw_straight(uint8_t *img, int width, int y0, int y1, int x, bool gray, Color c)
{
    uint8_t *pixel;
    size_t size;
    if(gray)
    {
        pixel = new unsigned char;
        *pixel = (c.r + c.g + c.b) / 3;
        size = sizeof(char);
    }
    else
    {
        pixel = (unsigned char*)&c;
        size = sizeof(Color);
    }

    for(int h = y0; h < y1; ++h)
    {
        size_t pos = (h * width + x) * ((gray) ? 1 : 3);
        memcpy(img + pos, pixel, size);
    }
    if(gray)
        delete pixel;
}

void draw_line(uint8_t *img, int width, int height, int x0, int y0, int x1, int y1, bool gray, Color c)
{
    double delta_x = x1 - x0;
    double delta_y = y1 - y0;
    double delta_err = fabs(delta_y / delta_x);
    double error = 0.0;
    int y = y0;
    uint8_t *pixel;
    size_t size;
    if(gray)
    {
        pixel = new unsigned char;
        *pixel = (c.r + c.g + c.b) / 3;
        size = sizeof(char);
    }
    else
    {
        pixel = (unsigned char*)&c;
        size = sizeof(Color);
    }

    for(int x = x0; x < x1; ++x)
    {
        size_t pos = (y * width + x) * ((gray) ? 1 : 3);
        memcpy(img + pos,pixel,size);
        error += delta_err;
        if (error >= 0.5) {
            ++y;
            error -= 1.0;
        }
    }
    if(gray)
        delete pixel;
}

void write_to_bitmap(int width, int height, Polygon *poly, Path *p, visual_conf conf)
{
    size_t img_size = width * height * conf.depth;
    uint8_t *img = new uint8_t[img_size];
    memset(img,255,img_size);
    if (poly != nullptr)
    {
        for(int i = 0; i < poly->size() - 1; ++i)
        {
            Point p1 = poly->at(i);
            Point p2 = poly->at(i + 1);
            draw_line(img,width,height,p1.x,p1.y,p2.x,p2.y,conf.depth == GRAY,conf.poly_color);
        }
        Point first = poly->front();
        Point last = poly->back();
        draw_line(img,width,height,first.x,first.y,last.x,last.y,conf.depth == GRAY,conf.poly_color);
    }

    std::vector<unsigned char> im;
    im.assign(img,img+img_size);
    lodepng::encode(conf.path,im,width,height,(conf.depth == GRAY) ? LCT_GREY : LCT_RGB,8);
    delete[] img;
}
