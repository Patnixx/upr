#include <stdio.h>

int main(void) {
    FILE *f = fopen("graf.svg", "w");
    if (!f) {
        perror("Nepodarilo sa otvoriť súbor");
        return 1;
    }

    // Hlavička SVG
    fprintf(f, "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"400\" height=\"400\">\n");

    // Kruh
    fprintf(f, "  <circle cx=\"200\" cy=\"200\" r=\"100\" fill=\"red\" stroke=\"black\" stroke-width=\"3\" />\n");

    // Obdĺžnik
    fprintf(f, "  <rect x=\"100\" y=\"50\" width=\"100\" height=\"50\" fill=\"cyan\" stroke=\"black\" />\n");

    // Čiara
    fprintf(f, "  <line x1=\"0\" y1=\"0\" x2=\"400\" y2=\"400\" stroke=\"green\" stroke-width=\"2\" />\n");

    // Koniec SVG
    fprintf(f, "</svg>\n");

    fclose(f);
    printf("SVG súbor bol vytvorený: graf.svg\n");
    return 0;
}

