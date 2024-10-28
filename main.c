#include "functii.h"
#include <stdio.h>

int main() {
    int nr_elemente_lista_principala = 1000000000;
    char nume_lista_principala[] = {"lista1000000000.bin"};

    generare(nr_elemente_lista_principala, nume_lista_principala);

    int numar_elemente_sortari[] = {
            10,
            100,
            1000,
            10000,
            100000,
            1000000,
            10000000,
            100000000,
            1000000000
    };

    executie_sortari(numar_elemente_sortari, 9, nume_lista_principala);

    return 0;
}
