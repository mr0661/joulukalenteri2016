//
// Created by ossis on 12.12.2016.
//
#include "md5.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

const int OUTPUT_LENGTH = 32;
const int T_length = 64;
const int SIZE_OF_PADDING = 64; // size in bytes
const int SIZE_OF_END_PAD = 8; // size in bytes
const int LENGTH_OF_END_PAD = 56;
const char FIRST_PAD = 0x1000;
const char ZERO_PAD = 0x0000;

void MD5(char* input, char* output){
    unsigned long T[T_length];
    generateT(T);
    unsigned long a = 0x01234567;
    unsigned long b = 0x89abcdef;
    unsigned long c = 0xfedcba98;
    unsigned long d = 0x76543210;
    pad(input);
}


void generateT(unsigned long output[]){
    long double s;
    unsigned long l;
    char c[40];
    for(int i = 0; i < T_length; ++i){
        s = sin(i + 1);
        s = (s > 0) ? s : (0 - s);
        s = 4294967296 * s;
        s = floor(s);
        l = (unsigned long)s;
        itoa(l,c,16);
        printf(c);
        output[i] = s;
    }
}

void pad(char* input){
    int length = strlen(input);
    int appendLength = length % SIZE_OF_PADDING;
    int extraLength = (appendLength < LENGTH_OF_END_PAD) ?
                      (LENGTH_OF_END_PAD - appendLength ) :
                      (SIZE_OF_PADDING + SIZE_OF_PADDING - appendLength );
    realloc(input, sizeof(char)*(length));
    *(input) = FIRST_PAD;
    for(int i = 1; i < extraLength; i++){
        *(input + length + i) = FIRST_PAD;
    }
    printf(input);
    return;
}