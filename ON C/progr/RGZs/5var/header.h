#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <string.h>

// Прототипы функций
void wswap(wchar_t *a, wchar_t *b);
void generateAnagrams(wchar_t *word, int start, int end, FILE *output);

#endif