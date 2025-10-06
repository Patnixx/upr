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

void stairs(int length, int color)
{
    for (int i = 0; i < length; i++)
    {
        pick_color(color);
        draw_pixel();
        move_right();
        move_down();

    }
}

void flower(int width, int height, int col, int row)
{
    int mid_slash = width / 2;
    int mid_mod = width % 2;
    int mid = mid_slash + mid_mod;
    int stem = height - width;
    int length = 1;

    while(length < (width + 1))
    {
        if(row != 1)
            move_to(length+height+1, col);
        else
            move_to(length, col);
        if(length == width || length == 1)
        {
            pick_color(0);
            for(int i = 0; i < (width-2); i++)
            {
                move_right();
                draw_pixel();
            }
        }
        else if(length == mid)
        {
            int l = mid_slash;
            pick_color(0);
            while(l > 0)
            {
                draw_pixel();
                move_right();
                l--;
            }
            pick_color(4);
            draw_pixel();
            int r = mid_slash;
            pick_color(0);
            while(r > 0)
            {
                move_right();
                draw_pixel();
                r--;
            }
        }
        else
        {

            pick_color(0);
            for (int i = 0; i < width; i++)
            {
                draw_pixel();
                move_right();
            }   
        }
        length++;
    }
    
    if(row == 2)
        move_to(length + height + 1, col+mid_slash);
    else
        move_to(width + 1, col+mid_slash);
    for(int i = 0; i < stem; i++)
    {
        pick_color(1);
        draw_pixel();
        move_down();
    }
}

void flower_field(int rows, int cols)
{
    for(int i = 1; i <= rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            flower(3, 6, j*4 + 2, i);
        }
        move_to(i*6 + 1, 2);
    }
}

void goku()
{
    //hair
    move_to(1, 2);
    set_blue_color();
    draw_pixel();
    move_right();
    draw_pixel();
    move_to(2, 1);
    draw_pixel();
    move_right();

    //face
    set_yellow_color();
    draw_pixel();

    //neck
    move_down();
    set_red_color();
    draw_pixel();
    move_right();
    set_yellow_color();
    draw_pixel();

    //body
    set_red_color();
    move_to(4, 1);
    draw_pixel();
    move_right();
    set_yellow_color();
    draw_pixel();
    move_right();
    draw_pixel();
    move_right();
    set_yellow_color();
    draw_pixel();

    //legs
    move_to(5, 2);
    set_red_color();
    draw_pixel();
    move_to(6,1);
    draw_pixel();
    move_right();
    move_right();
    draw_pixel();
    move_down();

    //kamehameha
    char kamehameha[] = "KAMEHAMEHA!!!";
    move_to(3, 5);
    
    for(int i = 0; i < 13; i++)
    {
        reset_color();
        printf("%c", kamehameha[i]);
        set_blue_color();
        move_down();
        move_left();
        draw_pixel();
        move_right();
        move_up();
        animate();
    }
    move_to(10, 1);
}

int main() {

    clear_screen();

    //input na kelvin
    int drawing = 4;
    //scanf("%d\n", &drawing);


    switch (drawing)
    {
        case 0:
            cross_line(5);
            break;
        case 1:
            stairs(5, 1);
            move_to(4, 7);
            stairs(11, 2);
            move_to(7, 12);
            stairs(5, 4);
            break;
        case 2:
            flower(7, 12, 1, 1);
            flower(5, 10, 9, 1);
            flower(3, 8, 15, 1);
            break;
        case 3:
            flower_field(4, 5);
            break;
        case 4:
            goku();
            break;
    }

    return 0;
}