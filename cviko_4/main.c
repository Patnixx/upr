#include <stdio.h>

void div(int x, int y, int* res, int* rem) {
    *res = x / y;
    *rem = x % y;
}


int main() {
    /*int number = 0;

    int* pointer = NULL;

    pointer = &number;

    int* p2 = &number;

    *pointer = 5; //prepise number cez adresu pointeru

    printf("number=%d\n", number);
    printf("*pointer=%d\n", *pointer);
    return 0;*/

    int res = 0;
    int rem = 0;
    div(13, 5, &res, &rem);
    printf("Result: %d, Remainder: %d\n", res, rem);
}