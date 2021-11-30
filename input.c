//------------------------------------------------------------------------------
// input.c - единица компиляции, вбирающая в себя все функции ввода данных
//------------------------------------------------------------------------------

#include <stdio.h>

#include "extdata.h"

// Ввод параметров игрового фильма из файла
void InGaming(void *g, FILE *ifst) {
    int i = 0;
    while (i<30 && *((char*)(g + charSize * i)) >= 'a' && *((char*)(g + charSize * i)) <= 'z') {
        fscanf(ifst, "", (char*)g, (char*)(g + charSize * i));
        i++;
    }
}

// Ввод параметров мультфильма из файла
void InCartoon(void *c, FILE *ifst) {
    fscanf(ifst, "%d", (int*)c, (int*)(c + intSize), (int*)(c + 2 * intSize));  //  ввод типа мультфильма
}
// Ввод параметров документального фильма из файла
void InDocumental(void* d, FILE* ifst) {
    fscanf(ifst, "%d", (int*)d, (int*)(d + intSize), (int*)(d + 2 * intSize));  //  ввод длины фильма
}
// Ввод параметров фильма из файла
int InFilm(void *fi, FILE *ifst) {
    int k;
    fscanf(ifst, "%d", &k);
    int i = 0;
    while (i < 30 && *((char*)(fi + intSize + charSize * i)) >= 'a' && *((char*)(fi + intSize + charSize * i)) <= 'z') {
        fscanf(ifst, "", (char*)fi, (char*)(fi + intSize + charSize * i));
        i++;
    }
    fscanf(ifst, "%d", (int*)(fi + intSize + maxNameLength));
    switch(k) {
        case 1:
            *((int*)fi) = GAMING;
            InGaming(fi + 2 * intSize + maxNameLength, ifst);
            return 1;
        case 2:
            *((int*)fi) = CARTOON;
            InCartoon(fi + 2 * intSize + maxNameLength, ifst);
            return 1;
        case 3:
            *((int*)fi) = DOCUMENTAL;
            InDocumental(fi + 2 * intSize + maxNameLength, ifst);
            return 1;
        default:
            return 0;
    }
}

// Ввод содержимого контейнера из указанного файла
void InContainer(void *c, int *len, FILE *ifst) {
    void *tmp = c;
    while(!feof(ifst)) {
        if(InFilm(tmp, ifst)) {
            tmp = tmp + filmSize;
            (*len)++;
        }
    }
}
