#include <stdio.h>
#include <stdlib.h>

#define BINS 9

/* pomocná funkcia: zistí počet číslic nezáporného čísla */
static int num_digits_unsigned(unsigned int x) {
    int d = 1;
    while (x >= 10u) {
        x /= 10u;
        d++;
    }
    return d;
}

/* načítanie n čísel a naplnenie histogramu counts[0..8] pre interval [m, m+8] */
static void read_histogram(int counts[BINS], int *invalid_count, int n, int m) {
    int i;
    for (i = 0; i < BINS; i++) counts[i] = 0;
    *invalid_count = 0;

    for (i = 0; i < n; i++) {
        int v;
        if (scanf("%d", &v) != 1) {
            /* ak chýba ďalšie číslo, považujeme to za nevalid (ale podľa testov vstupy budú korektné) */
            (*invalid_count)++;
            /* pokúsime sa preskočiť token */
            scanf("%*s");
            continue;
        }
        if (v >= m && v <= m + (BINS - 1)) {
            counts[v - m]++;
        } else {
            (*invalid_count)++;
        }
    }
}

/* vykreslenie horizontálneho histogramu */
static void print_horizontal(int counts[BINS], int invalid_count, int m) {
    int i, j;
    unsigned int max_number = (unsigned int)(m + (BINS - 1));
    int width = num_digits_unsigned(max_number);

    for (i = 0; i < BINS; i++) {
        int value = m + i;
        int digits = num_digits_unsigned((unsigned int)value);
        int spaces = width - digits;

        /* pravé zarovnanie čísla */
        for (j = 0; j < spaces; j++) putchar(' ');
        printf("%d", value);

        /* ak sa hodnota vyskytla, vypíš medzeru a # tak krát, koľko je výskytov */
        if (counts[i] > 0) {
            putchar(' ');
            for (j = 0; j < counts[i]; j++) putchar('#');
        }
        putchar('\n');
    }

    /* invalid riadok */
    if (invalid_count >= 0) {
        printf("invalid:");
        if (invalid_count > 0) putchar(' ');
        for (j = 0; j < invalid_count; j++) putchar('#');
        putchar('\n');
    }
}

/* vykreslenie vertikálneho histogramu (bonus)
   Predpoklad: rozsah histogramu je [1,9] (teda m by mal byť 1) alebo aspoň hodnoty sú jednociferné.
   Prvá (ľavá) kolóna je "i" so štítkom pre invalid počty. */
static void print_vertical(int counts[BINS], int invalid_count, int m) {
    int i, r;
    int maxh = invalid_count;
    for (i = 0; i < BINS; i++) if (counts[i] > maxh) maxh = counts[i];

    /* vypíšeme riadky od maxh nadol po 1 */
    for (r = maxh; r >= 1; r--) {
        /* invalid column (oznacena 'i') */
        if (invalid_count >= r) putchar('#'); else putchar(' ');
        putchar(' '); /* medzera medzi stĺpcami */

        /* ostatné stĺpce pre hodnoty m..m+8 */
        for (i = 0; i < BINS; i++) {
            if (counts[i] >= r) putchar('#'); else putchar(' ');
            if (i < BINS - 1) putchar(' ');
        }
        putchar('\n');
    }

    /* štítky pod histogramom:
       prvý stĺpec 'i' (pre invalid), potom hodnoty m..m+8 (predpoklad jednociferné podľa zadania pre tento bonus) */
    putchar('i');
    putchar(' ');
    for (i = 0; i < BINS; i++) {
        int value = m + i;
        /* ak predpokladáme jednociferné, stačí vypísať číslo a medzeru;
           ak by hodnoty mali viac číslic, stĺpce by neboli zarovnané —
           zadanie však explicitne povoluje predpoklad [1,9] pre vertikálny bonus. */
        printf("%d", value);
        if (i < BINS - 1) putchar(' ');
    }
    putchar('\n');
}

int main(void) {
    char mode;
    /* načítame znak, pričom preskočíme whitespace pred ním */
    if (scanf(" %c", &mode) != 1) {
        fprintf(stderr, "Neplatny mod vykresleni\n");
        return 1;
    }

    if (mode != 'h' && mode != 'v') {
        /* neplatný mód vykreslenia */
        printf("Neplatny mod vykresleni\n");
        return 1;
    }

    int n, m;
    if (scanf("%d %d", &n, &m) != 2) {
        /* neplatné vstupné údaje */
        fprintf(stderr, "Chyba vstupu\n");
        return 1;
    }

    if (n < 0 || m < 0) {
        /* podľa zadania su n a m nezáporné */
        fprintf(stderr, "Chyba vstupu\n");
        return 1;
    }

    int counts[BINS];
    int invalid_count = 0;
    read_histogram(counts, &invalid_count, n, m);

    if (mode == 'h') {
        print_horizontal(counts, invalid_count, m);
    } else {
        /* vertical */
        /* pre vertikálny režim zadanie dovoluje predpokladať rozsah [1,9].
           Ak m nie je 1, vertikálne vykreslenie môže byť nezarovnané, ale stále ho vykreslíme. */
        print_vertical(counts, invalid_count, m);
    }

    return 0;
}