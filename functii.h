#ifndef PROIECTSORTARE_FUNCTII_H
#define PROIECTSORTARE_FUNCTII_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void generare(int n, char nume_lista_principala[])
//
// Acesta funcție generează un fișier în binar cu o listă de n elemente numere întregi random
// cu numele din nume_lista_principala[] si afișează timpul de execuție.
//
{
    FILE *lista = fopen(nume_lista_principala, "wb");

    if (lista == NULL) {
        printf("Eroare la deschiderea fisierului\n");
        exit(1);
    }

    printf("Generare lista cu %d elemente...\n", n);
    int x;
    clock_t t;
    t = clock();
    for (int i = 0; i < n; i++) {
        x = rand();
        fwrite(&x, sizeof(int), 1, lista);
    }
    t = clock() - t;
    double time_taken = ((double) t) / CLOCKS_PER_SEC; // in seconds
    printf("\nGenerarea a %d elemente a durat %f secunde pentru executie\n", n, time_taken);
    fclose(lista);
//    exemple de timp pentru generare lista 1 miliard
//    Generarea a 1000000000 elemente a durat 27.280879 secunde pentru executie
//    Generarea a 1000000000 elemente a durat 27.072718 secunde pentru executie
//    Generarea a 1000000000 elemente a durat 26.985164 secunde pentru executie
}

int* lista_primele_n_elemente(int nr_elemente, char nume_lista_principala[])
//
//  Această funcție returnează o listă cu primele n elemente din lista principală
//  (în cazul testului nostru, cea de 1 miliard).
//
{
    int* a = malloc(nr_elemente * sizeof(int));
    FILE* lista = fopen(nume_lista_principala, "rb");
    for (int i = 0; i < nr_elemente; i++)
        fread(&a[i], sizeof(int), 1, lista);
    fclose(lista);
    return a;
}

void afisare(char nume_lista[])
//
//  Această funcție citește elementele numere întregi dintr-un fișier
//  binar și le afișează în linia de comandă.
//
{
    FILE* lista = fopen(nume_lista, "rb");
    int n;
    while (fread(&n, sizeof(int), 1, lista))
        printf("%d\n", n);
    fclose(lista);
}

void scriere(int lista[], int n, char nume_fisier[])
//
//  Această funcție primește ca parametrii o listă de numere întregi, n lungimea listei și un șir
//  de caractere care reprezintă numele unui fișier care urmează să fie creat și în care se vor scrie
//  în binar toate elementele listei.
//
{
    FILE* f = fopen(nume_fisier, "wb");
    for (int i=0; i < n; i++) {
        fwrite(&lista[i], sizeof(int), 1, f);
    }
    fclose(f);
}

char* generare_nume_fisier(char nume_fisier[], int n)
//
//  Această funcție returnează un șir de caractere format din cel primit ca parametru și numărul n.
//  Această funcție a fost creata pentru a ajuta funcțiile de sortare
//  în generarea fișierelor într-un mod organizat.
//
{
    char* numar = malloc(11); // șirul de caractere pentru a transforma cifrele în caractere
    strcpy(numar, "0000000000"); // inițializare șir
    char* cifra = malloc(2);
    strcpy(cifra, "0");
    char temp;
    cifra[0] = (char)(n%10 + '0');
    n /= 10;
    strcpy(numar, cifra);
    while (n) {
        cifra[0] = (char)(n%10 + '0');
        n /= 10;
        strcat(numar, cifra);
    }
    int i, left, right, len;
    len = (int)strlen(numar); // Lungimea șirului numar
    left = 0; // Indexul din partea stângă
    right = len - 1; // Indexul din partea dreaptă
    // Folosim un for pentru a inversa șirul deoarece a fost creat invers
    for (i = left; i <right; i++)
    {
        temp = numar[i];
        numar[i] = numar[right];
        numar[right] = temp;
        right--;
    }
    // compunerea șirului final
    char* s = malloc(100);
    strcpy(s, nume_fisier);
    strcat(s, "_");
    strcat(s, numar);
    strcat(s, ".bin");
    free(numar);
    free(cifra);
    return s;
}

void swap(int *x, int *y)
//
//  Această funcție interschimbă 2 elemente.
//
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

char* bubble_sort(int n, char* nume_lista_principala, double* time_taken)
{
    char* nume_fisier = generare_nume_fisier("Bubble_Sort", n);
    int* lista = lista_primele_n_elemente(n, nume_lista_principala);

    clock_t t;
    t = clock();
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (lista[j] > lista[j + 1])
                swap(&lista[j], &lista[j+1]);
    t = clock() - t;
    *time_taken += ((double)t)/CLOCKS_PER_SEC; // în secunde

    scriere(lista, n, nume_fisier);
    free(lista);
    return nume_fisier;
}

char* selection_sort(int n, char* nume_lista_principala, double* time_taken)
//
//  Algoritmul de sortare SelectionSort
//
{
    char* nume_fisier = generare_nume_fisier("Selection_Sort", n);
    int* lista = lista_primele_n_elemente(n, nume_lista_principala);

    clock_t t;
    t = clock();
    int min_idx;
    for (int i = 0; i < n-1; i++)
    {
        // Găsim cel mai mic element din lista nesortată
        min_idx = i;
        for (int j = i+1; j < n; j++)
            if (lista[j] < lista[min_idx])
                min_idx = j;
        // Interschimbăm elementul găsit cu primul din listă
        if(min_idx != i)
            swap(&lista[min_idx], &lista[i]);
    }
    t = clock() - t;
    *time_taken += ((double)t)/CLOCKS_PER_SEC; // în secunde

    scriere(lista, n, nume_fisier);
    free(lista);
    return nume_fisier;
}

char* insertion_sort(int n, char* nume_lista_principala, double* time_taken)
//
//  Algoritmul de sortare InsertionSort
//
{
    char* nume_fisier = generare_nume_fisier("Insertion_Sort", n);
    int* lista = lista_primele_n_elemente(n, nume_lista_principala);

    clock_t t;
    t = clock();
    int key, j;
    for (int i = 1; i < n; i++) {
        key = lista[i];
        j = i - 1;

        // Mutăm elementele listei mai mari decât elementul key
        // în dreapta poziției sale curente
        while (j >= 0 && lista[j] > key) {
            lista[j + 1] = lista[j];
            j = j - 1;
        }
        lista[j + 1] = key;
    }
    t = clock() - t;
    *time_taken += ((double)t)/CLOCKS_PER_SEC; // în secunde

    scriere(lista, n, nume_fisier);
    free(lista);
    return nume_fisier;
}

int partition(int lista[], int low, int high)
//
//  Algoritmul de compartimentare pentru QuickSort
//
{
    int pivot = lista[high]; // pivot
    int i= (low - 1); // Poziția celui mai mic element
    // Poziția corectă de pivot găsită până acum

    for (int j = low; j <= high - 1; j++)
        // Daca elementul curent este mai mic decât pivotul
        if (lista[j] < pivot) {
            i++; // Incrementăm indexul celui mai mic element
            swap(&lista[i], &lista[j]);
        }
    swap(&lista[i + 1], &lista[high]);
    return (i + 1);
}

void quickSort(int lista[], int low, int high)
//
//  Algoritmul separat pentru QuickSort (deoarece este recursiv)
//
{
    if (low < high) {
        // pi împarte lista
        int pi = partition(lista, low, high);

        // Sortare separată a celor 2 jumătăți
        quickSort(lista, low, pi - 1);
        quickSort(lista, pi + 1, high);
    }
}

char* quick_sort(int n, char* nume_lista_principala, double* time_taken)
//
//  Algoritmul de sortare QuickSort
//
{
    char* nume_fisier = generare_nume_fisier("Quick_Sort", n);
    int* lista = lista_primele_n_elemente(n, nume_lista_principala);

    clock_t t;
    t = clock();
    quickSort(lista, 0, n-1);
    t = clock() - t;
    *time_taken += ((double)t)/CLOCKS_PER_SEC; // în secunde

    scriere(lista, n, nume_fisier);
    free(lista);
    return nume_fisier;
}

void merge(int lista[], int l, int m, int r)
//
//  Algortimul de combinare pentru MergeSort
//
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // liste temporare
    int* L = malloc(sizeof(int) * n1);
    int* R = malloc(sizeof(int) * n2);

    // Copierea elementelor în listele temporare
    for (i = 0; i < n1; i++)
        L[i] = lista[l + i];
    for (j = 0; j < n2; j++)
        R[j] = lista[m + 1 + j];

    // Combinarea listelor temporare înapoi în lista principală
    i = 0; // Indexul inițial al primei sub-liste
    j = 0; // Indexul inițial al celeilalte sub-liste
    k = l; // Indexul inițial pentru lista finală
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            lista[k] = L[i];
            i++;
        }
        else {
            lista[k] = R[j];
            j++;
        }
        k++;
    }

    // Copierea elementelor rămase din prima sub-listă
    while (i < n1) {
        lista[k] = L[i];
        i++;
        k++;
    }

    // Copierea elementelor rămase din cealaltă sub-listă
    while (j < n2) {
        lista[k] = R[j];
        j++;
        k++;
    }
    free(L);
    free(R);
}

void mergeSort(int lista[], int l, int r)
//
//  Algoritmul separat pentru MergeSort (deoarece este recursiv)
//
{
    if (l < r) {
        int m = l + (r - l) / 2;

        // Sortarea jumătăților
        mergeSort(lista, l, m);
        mergeSort(lista, m + 1, r);

        merge(lista, l, m, r);
    }
}

char* merge_sort(int n, char* nume_lista_principala, double* time_taken)
//
//  Algoritmul de sortare QuickSort
//
{
    char* nume_fisier = generare_nume_fisier("Merge_Sort", n);
    int* lista = lista_primele_n_elemente(n, nume_lista_principala);

    clock_t t;
    t = clock();
    mergeSort(lista, 0, n-1);
    t = clock() - t;
    *time_taken += ((double)t)/CLOCKS_PER_SEC; // în secunde

    scriere(lista, n, nume_fisier);
    free(lista);
    return nume_fisier;
}

void verificare_sortare(char* nume_lista)
//
//  Algoritmul verifică dacă toate elementele dintr-un fișier sunt sortate
//
{
    FILE* lista = fopen(nume_lista, "rb");
    int sortat = 1, actual, anterior;

    fread(&anterior, sizeof(int), 1, lista);
    while (fread(&actual, sizeof(int), 1, lista)) {
        if (anterior > actual) {
            sortat = 0;
            break;
        }
        anterior = actual;
    }

    if (sortat)
        printf("Lista %s este sortata\n", nume_lista);
    else
        printf("Lista %s NU este sortata\n", nume_lista);

    fclose(lista);
}

void executie_sortari(int elemente[], int n, char* nume_lista_principala)
{
    double* timp = malloc(sizeof(double));
    char* nume_fisier;
    for (int i = 0; i < n; i++) {
        if (elemente[i] <= 1000000) { // limita de 1 milion de elemente din cauza timpului de execuție
            printf("\nSe sorteaza %d elemente cu BubbleSort...\n", elemente[i]);
            *timp = 0;
            nume_fisier = bubble_sort(elemente[i], nume_lista_principala, timp);
            printf("BubbleSort a sortat %d elemente in %lf secunde\n", elemente[i], *timp);
            verificare_sortare(nume_fisier);
            free(nume_fisier);
        }

        if (elemente[i] <= 1000000) { // limita de 1 milion de elemente din cauza timpului de execuție
            printf("\nSe sorteaza %d elemente cu SelectionSort...\n", elemente[i]);
            *timp = 0;
            nume_fisier = selection_sort(elemente[i], nume_lista_principala, timp);
            printf("SelectionSort a sortat %d elemente in %lf secunde\n", elemente[i], *timp);
            verificare_sortare(nume_fisier);
            free(nume_fisier);
        }

        if (elemente[i] <= 1000000) { // limita de 1 milion de elemente din cauza timpului de execuție
            printf("\nSe sorteaza %d elemente cu InsertionSort...\n", elemente[i]);
            *timp = 0;
            nume_fisier = insertion_sort(elemente[i], nume_lista_principala, timp);
            printf("InsertionSort a sortat %d elemente in %lf secunde\n", elemente[i], *timp);
            verificare_sortare(nume_fisier);
            free(nume_fisier);
        }

        printf("\nSe sorteaza %d elemente cu QuickSort...\n", elemente[i]);
        *timp = 0;
        nume_fisier = quick_sort(elemente[i], nume_lista_principala, timp);
        printf("QuickSort a sortat %d elemente in %lf secunde\n", elemente[i], *timp);
        verificare_sortare(nume_fisier);
        free(nume_fisier);

        printf("\nSe sorteaza %d elemente cu MergeSort...\n", elemente[i]);
        *timp = 0;
        nume_fisier = merge_sort(elemente[i], nume_lista_principala, timp);
        printf("MergeSort a sortat %d elemente in %lf secunde\n", elemente[i], *timp);
        verificare_sortare(nume_fisier);
        free(nume_fisier);
    }
    free(timp);
}

#endif //PROIECTSORTARE_FUNCTII_H
