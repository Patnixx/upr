#include "drawing.h"
#include <stdio.h>

//gcc terminal_na_lsd.c -o terminal_na_lsd

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
            reset_color();
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

//dufam ze mas rad dragon ball ;) (v zivote som to nevidel) 

void clear_body()
{
    for(int i = 0; i < 5; i++)
    {
        move_to(i+5, 1);
        for(int j = 0; j < 6; j++)
        {
            reset_color();
            draw_pixel();
            move_right();
        }
    }
    move_to(1, 1);
}

void body_frame1()
{
    move_to(5, 3);
    set_red_color();
    for (int i = 0; i < 2; i++)
    {
        draw_pixel();
        move_right();
    }

    move_to(6, 2);
    for (int i = 0; i < 4; i++)
    {
        draw_pixel();
        move_right();
    }

    move_to(7, 2);
    set_yellow_color();
    draw_pixel();
    move_right();
    set_red_color();
    for (int i = 0; i < 2; i++)
    {
        draw_pixel();
        move_right();
    }
    set_yellow_color();
    draw_pixel();

    move_to(8, 1);
    draw_pixel();
    move_to(8,3);
    set_red_color();
    for (int i = 0; i < 2; i++)
    {
        draw_pixel();
        move_right();
    }
    move_right();
    set_yellow_color();
    draw_pixel();
    
    move_to(9,3);
    set_red_color();
    for (int i = 0; i < 2; i++)
    {
        draw_pixel();
        move_right();
    }
}

void body_frame2()
{
    move_to(5, 3);
    set_red_color();
    for (int i = 0; i < 2; i++)
    {
        draw_pixel();
        move_right();
    }

    move_to(6, 2);
    for (int i = 0; i < 4; i++)
    {
        draw_pixel();
        move_right();
    }

    move_to(7, 2);
    set_yellow_color();
    draw_pixel();
    move_right();
    set_red_color();
    for (int i = 0; i < 2; i++)
    {
        draw_pixel();
        move_right();
    }
    set_yellow_color();
    draw_pixel();
    move_right();
    draw_pixel();

    move_to(8,3);
    draw_pixel();
    move_right();
    draw_pixel();

    move_to(9,3);
    set_red_color();
    for (int i = 0; i < 2; i++)
    {
        draw_pixel();
        move_right();
    }
}

void body_frame3()
{
    move_to(5, 3);
    set_red_color();
    for (int i = 0; i < 2; i++)
    {
        draw_pixel();
        move_right();
    }

    move_to(6, 2);
    for (int i = 0; i < 2; i++)
    {
        draw_pixel();
        move_right();
    }
    set_yellow_color();
    for (int i = 0; i < 2; i++)
    {
        draw_pixel();
        move_right();
    }
    
    move_to(7, 2);
    for (int i = 0; i < 3; i++)
    {
        draw_pixel();
        move_right();
    }
    

    move_to(8,3);
    set_red_color();
    for (int i = 0; i < 2; i++)
    {
        draw_pixel();
        move_right();
    }
    set_yellow_color();
    draw_pixel();

    move_to(9,3);
    set_red_color();
    for (int i = 0; i < 2; i++)
    {
        draw_pixel();
        move_right();
    }
}

void body_frame4()
{
    move_to(5, 3);
    set_red_color();
    for (int i = 0; i < 2; i++)
    {
        draw_pixel();
        move_right();
    }
    move_right();
    set_yellow_color();
    draw_pixel();

    move_to(6, 2);
    set_red_color();
    draw_pixel();
    move_right();
    set_yellow_color();
    for (int i = 0; i < 3; i++)
    {
        draw_pixel();
        move_right();
    }

    move_to(7,3);
    set_red_color();
    for (int i = 0; i < 2; i++)
    {
        draw_pixel();
        move_right();
    }
    set_yellow_color();
    move_right();
    draw_pixel();

    move_to(8,3);
    set_red_color();
    for (int i = 0; i < 2; i++)
    {
        draw_pixel();
        move_right();
    }
    
    move_to(9,3);
    set_red_color();
    for (int i = 0; i < 2; i++)
    {
        draw_pixel();
        move_right();
    }
}

void goku()
{
    //hair+face
    move_to(1, 2);
    for (int i = 0; i < 3; i++)
    {
        set_blue_color();
        draw_pixel();
        move_right();
        reset_color();
        draw_pixel();
        move_right();
    }
    move_to(2, 2);
    set_blue_color();
    for (int i = 0; i < 4; i++)
    {
        draw_pixel();
        move_right();
    }
    move_to(3, 2);
    set_blue_color();
    for (int i = 0; i < 2; i++)
    {
        draw_pixel();
        move_right();
    }
    set_yellow_color();
    draw_pixel();
    move_to(4, 2);
    set_blue_color();
    draw_pixel();
    move_right();
    set_yellow_color();
    for (int i = 0; i < 2; i++)
    {
        draw_pixel();
        move_right();
    }

    //legs
    move_to(10,2);
    set_red_color();
    draw_pixel();
    move_to(10,5);
    draw_pixel();
    move_to(11,1);
    draw_pixel();
    move_right();
    draw_pixel();
    move_to(11,5);
    draw_pixel();
    move_right();
    draw_pixel();
    move_to(12,1);
    draw_pixel();
    move_to(12,6);
    draw_pixel();

    //body
    body_frame1();
    animate_ms(500);
    clear_body();
    body_frame2();
    animate_ms(500);
    clear_body();
    body_frame3();
    animate_ms(500);
    clear_body();
    body_frame4();
    animate_ms(500);

    //kamehameha
    move_to(6, 6);
    
    for(int i = 0; i < 60; i++)
    {
        set_blue_color();
        draw_pixel();
        move_right();
        draw_pixel();
        move_right();
        animate_ms(50);
    }


    move_to(13,10); //move kvoli textu v terminali

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
            stairs(5, 1);
            move_to(1, 5);
            stairs(11, 2);
            move_to(1, 9);
            stairs(5, 4);
            move_to(15, 1);
            break;
        case 2:
            flower(7, 12, 1, 1);
            flower(5, 10, 15, 1);
            flower(3, 8, 9, 1);
            move_to(15, 1);
            break;
        case 3:
            flower_field(2, 8);
            move_to(15, 1);
            break;
        case 4:
            goku();
            break;
    }

    return 0;
}