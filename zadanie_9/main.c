#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

//structs from scripts
typedef unsigned char byte;
typedef struct {
    byte id_length;
    byte color_map_type;
    byte image_type;
    byte color_map[5];
    byte x_origin[2];
    byte y_origin[2];
    byte width[2];
    byte height[2];
    byte depth;
    byte descriptor;
} TGAHeader;

typedef struct {
    byte blue;
    byte green;
    byte red;
} Pixel;

typedef struct {
    int width;
    int height;
    Pixel* pixels;
    TGAHeader header;
} Image;

typedef struct {
    int upper;
    int lower;
    int total;
} Totals;

int header_width(TGAHeader * self) {
    int h_width = 0;
    memcpy(&h_width, self->width, 2);
    return h_width;
}

int header_height(TGAHeader * self) {
    int h_height = 0;
    memcpy(&h_height, self->height, 2);
    return h_height;
}

Image load_img(const char *path) {
    FILE *f = fopen(path, "rb");
    TGAHeader header = {0};
    assert(fread(&header, sizeof(TGAHeader), 1, f) == 1);

    int width = header_width(&header);
    int height = header_height(&header);

    Pixel* pixels = (Pixel*) malloc(sizeof(Pixel) * width * height);
    assert(fread(pixels, sizeof(Pixel) * width * height, 1, f) == 1);

    return (Image){width, height, pixels, header};
}

void write_lines(Image image, const char *path) {
    FILE *output_file = fopen(path, "wb");
    fwrite(&image.header, sizeof(TGAHeader), 1, output_file);
    fwrite(image.pixels, sizeof(Pixel) * image.width * image.height, 1, output_file);
    fclose(output_file);
}

void colorise(Pixel *pixel, int color){
    int index = 3;
    int color_arr[18] = {0, 0, 255, 0, 165, 255, 0, 255, 255, 0, 255, 0, 255, 0, 0, 128, 0, 128}; //red, oragne, yellow, green, blue, purple
    byte blue, green, red = 0;

    for(int i = index*color; i < (index*color)+index; i++) {
        if(i % 3 == 0) blue = color_arr[i]; 
        else if(i % 3 == 1) green = color_arr[i];
            else red = color_arr[i];
    }

    pixel->red = red;
    pixel->green = green;
    pixel->blue = blue;
}

void find_total(Totals *totals){
    char line[101] = {0};

    fgets(line, sizeof(line), stdin);
    char *rows = strtok(line, " ");

    int upper = atoi(rows);
    rows = strtok(NULL, " ");
    int lower = atoi(rows);

    totals->upper = upper;
    totals->lower = lower;
    totals->total = upper + lower;
}

void fill_alphabeth(Image *alphabeth, const char *font_path){
    for(int i = 0; i < 26; i++){
        char path[101] = {0};
        sprintf(path, "%s/%c.tga", font_path, 'A' + i);
        alphabeth[i] = load_img(path);
    }
}

void return_image(int offset_x, int offset_y, char *text, int len, Image *image, Image *alphabeth) {

    int current_x = offset_x;
    for (int i = 0; i < len; i++) {
        if (text[i] == ' ') {
            current_x += 7;
            continue;
        }

        int index = text[i] - 'A';
        Image *font_image = &alphabeth[index];

        for (int j = 0; j < font_image->height; j++) {
            for (int k = 0; k < font_image->width; k++) {
                Pixel *font_pixel = &font_image->pixels[j * font_image->width + k];

                if (font_pixel->red == 0 && font_pixel->green == 0 && font_pixel->blue == 0) {
                    continue;
                }

                if (font_pixel->red == 255 && font_pixel->green == 255 && font_pixel->blue == 255) {
                    int color = i % 6;
                    colorise(font_pixel, color);
                }

                int dst_y = offset_y + j;
                int dst_x = current_x + k;
                if (dst_y >= 0 && dst_y < image->height && dst_x >= 0 && dst_x < image->width) {
                    Pixel *image_pixel = &image->pixels[dst_y * image->width + dst_x];
                    *image_pixel = *font_pixel;
                }
            }
        }
        current_x += font_image->width;
    }
}

int main(int argc, char* argv[]) {
    if(argc != 4) {
        printf("Wrong parameters\n");
        return 1;
    }

    const char* i_path  = argv[1];
    const char* o_path = argv[2];
    const char* f_path = argv[3];

    FILE *file = fopen(i_path, "rb");
    if(!file) {
        printf("Could not load image\n");
        return 1;
    }

    Image image = load_img(i_path);
    Totals totals = {0};
    find_total(&totals);
    int total = totals.total;
    Image alphabeth[26];
    fill_alphabeth(alphabeth, f_path);

    for(int i = 0; i < total; i++) {
        char text[101] = {0};
        fgets(text, sizeof(text), stdin);
        size_t len = strlen(text);

        if(text[len-1] == '\n') {
            text[len-1] = '\0';
            len--;
        }

        for(size_t j = 0; j < len; j++) {
            text[j] = toupper(text[j]);
        }

        int text_width = 0;
        for(size_t k = 0; k < len; k++) {
            if(text[k] == ' ') {
                text_width += 7;
            }
            if(text[k] >= 'A' && text[k] <= 'Z') {
                int index = text[k] - 'A';
                text_width += alphabeth[index].width;
            }
        }

        if(i >= totals.upper){
            int offset_x = (image.width - text_width) / 2;
            int offset_y = image.height - ((totals.total - i) * 30) - 4;    //pripadne zmenit hodnoty lebo som sa s nimi hral tak moc ze uz neviem co bolo najkrajsie
            return_image(offset_x, offset_y, text, len, &image, alphabeth); // 30 je offset riadkov dole, 4 je offset od vrchu obrazku
        }
        else {
            int offset_x = (image.width - text_width) / 2;
            int offset_y = 4 + (i * 30);
            return_image(offset_x, offset_y, text, len, &image, alphabeth);
        }
    }
    write_lines(image, o_path);
    fclose(file);
}