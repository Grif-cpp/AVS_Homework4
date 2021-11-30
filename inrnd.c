//------------------------------------------------------------------------------
// inrnd.c - единица компиляции, вбирающая функции генерации случайных данных
//------------------------------------------------------------------------------

#include <stdlib.h>

#include "extdata.h"

// rnd.c - содержит генератор случайных чисел в диапазоне от 1 до 20
int Random() {
    return rand() % 20 + 1;
}

// Случайный ввод параметров игрового фильма
void InRndGaming(void *r) {
    int len = rand % 30 + 1;
    for (int i = 0; i < len; i++) {
        *((int*)(r + charSize * i)) = 'a' + rand() % 26;
    }
}

// Случайный ввод параметров мультфильма
void InRndCartoon(void *c) {
    int k = rand() % 3 + 1;
    if (k == 1) {
        *((int*)c) = DRAWN;
    } else if (k == 2) {
        *((int*)c) = DOLLHOUSE;
    } else if (k == 3){
        *((int*)c) = PLASTILINE;
    } else {
        return 0;
    }
}
// Случайный ввод параметров документального фильма
void InRndDocumental(void* d) {
    *((int*)d) = rand() % 100 + 1920;
    int len = rand % 30 + 1;
    for (int i = 0; i < len; i++) {
        *((int*)(d + charSize * i)) = 'a' + rand() % 26;
    }
}

// Случайный ввод обобщенной фигуры
int InRndFilm(void *fi) {
    int k = rand() % 3 + 1;
    int len = rand % 30 + 1;
    for (int i = 0; i < len; i++) {
        *((int*)(fi + intSize + charSize * i)) = 'a' + rand() % 26;
    }
    switch(k) {
        case 1:
            *((int*)fi) = GAMING;
            InRndGaming(fi + intSize);
            return 1;
        case 2:
            *((int*)fi) = CARTOON;
            InRndCartoon(fi + intSize);
            return 1;
        case 3:
            *((int*)fi) = DOCUMENTAL;
            InRndDocumental(fi + intSize);
        default:
            return 0;
    }
}

// Случайный ввод содержимого контейнера
void InRndContainer(void *c, int *len, int size) {
    void *tmp = c;
    while(*len < size) {
        if(InRndFilm(tmp)) {
            tmp = tmp + filmSize;
            (*len)++;
        }
    }
}
