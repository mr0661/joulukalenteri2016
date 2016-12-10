//
// Created by ossis on 10.12.2016.
// Part two of third day of Christmas -challenge
//
#include <stdio.h>
#include <stdlib.h>

const int MAX_NUMBERS = 4;
const char FILENAME[70] = "C:\\Users\\ossis\\ClionProjects\\joulukalenteri_2016\\3\\input.txt";
const int MODE = 9;
const int X_START = 0;
const int Y_START = 3;
const int Z_START = 6;

// Tests if char c is number, returns 1 if it is, 0 otherwise
int isNum(char c);

// Searches from file pointer forward until number is found, then
// translates that to int and returns that value. FILE *f will continue
// one character after last recorded number.
int getNextNum(FILE *f);

// Given side lengths of x, y, and z, sees triangle can be formed using
// theses values (on typical flat surface)
int allowedTriangle(int x, int y, int z);

int main(){
    FILE *f = fopen(FILENAME,"r");
    int count = 0;
    int numbers[MODE];

    while(1){
        for(int i = 0; i < MODE; ++i) {
            numbers[i] = getNextNum(f);
        }
        // all values need to larger than 0, zero indicates EOF
        // in part two, numbers are gone through in sets of three
        for(int i = 0; i < Y_START; i++){
            if(numbers[X_START + i] && numbers[Y_START + i] &&
                    numbers[Z_START + i]) {
                if (allowedTriangle(numbers[X_START + i],
                                    numbers[Y_START + i],
                                    numbers[Z_START + i])) {
                    ++count;
                }

            }
            else{
                printf("Reached to the end, final value: %i", count);
                return count;
            }
        }
        printf("looppi\n");
    }
}

int isNum(char c){
    if(c >= 48 && c <= 57){
        return 1;
    }
    else{
        return 0;
    }
}

int getNextNum(FILE *f){
    char number[MAX_NUMBERS];
    while(1){
        int c = fgetc(f);
        if(isNum(c)){
            number[0] = c;
            for(int i = 1; i < MAX_NUMBERS ; ++i){
                c = fgetc(f);
                if(isNum(c)){
                    number[i] = c;
                }
                else if(c == EOF){
                    if (i == 1){
                        return 0;
                    }
                    else{
                        number[i]='\0';
                        return atoi(number);
                    }
                }
                else{
                    number[i]='\0';
                    return atoi(number);
                }

            }
        }
        else if(c == EOF){
            return 0;
        }

    }
}

int allowedTriangle(int x, int y, int z){
    if( x >= (y + z) ) return 0;
    if( y >= (x + z) ) return 0;
    if( z >= (y + x) ) return 0;
    return 1;

}