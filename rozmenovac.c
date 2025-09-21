#include <stdio.h>

int main() {

    int suma = 9860;
    int bankovky[] = {5000,2000,1000,500,200,100};
    //printf("Suma: %d \n", suma);

    for (int i = 0; i < 6; i++)
    {
        if(suma % bankovky[i] != 0 )
        {
            int pocet_bankoviek = suma / bankovky[i];
            int suma_prec = pocet_bankoviek * bankovky[i];
            printf("Bankovka %d: %dx \n", bankovky[i] ,pocet_bankoviek);
            suma = suma - suma_prec;
            //printf("Ostáva: %d \n", suma); //kontrola sumy
        }
        else
        {
            int pocet_bankoviek = suma / bankovky[i];
            printf("Bankovka %d: %dx \n", bankovky[i] ,pocet_bankoviek);
        }
    }
    return 0;
}