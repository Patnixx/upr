#include "drawing.h"
#include <stdio.h>

void pick_color(int color)
{
    switch (color)
    {
        case 0:
            set_red_color();
            break;
        case 1:
            set_green_color();
            break;
        case 2:
            set_blue_color();
            break;
        case 3:
            set_white_color();
            break;
        case 4:
            set_yellow_color();
            break;
        case 5:
            set_black_color();
            break;
        default:
            set_black_color();
            break;
    }
}

void cross_line(int length)
{
    for(int j = 0; j < 6; j++)
    {
        move_to(j+1, j+1);
        for (int i = 0; i < length; i++)
        {
            //white pixel
            pick_color(j);
            draw_pixel();
            move_right();

            //black/blank pixel
            set_black_color();
            draw_pixel();
            move_right();
        }
    }
}

void stairs(int length)
{
    for (int i = 0; i < 6; i++)
    {
        move_to(i+1, i+1);
        pick_color(i);
        draw_pixel();

    }
}

void flower(int width, int height)
{
    cross_line(width);
    for(int i = 0; i < width; i++)
    {
        while(i < width)
        {
            move_left();
            i++;
        }
    }
}

int main() {

    clear_screen();

    //input na kelvin
    int drawing = 0;
    scanf("%d\n", &drawing);


    switch (drawing)
    {
        case 0:
            cross_line(5);
            break;
        case 1:
            stairs(5);
            break;
        case 2:
            flower(5, 5);
            break;
        case 3:
            break;
        case 4:
            break;
    }

    return 0;
}