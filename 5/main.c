//
// Created by ossis on 11.12.2016.
// Outside MD5 implementation used, not included here, does
// something odd to stuff, or might have been debugger, or something
// Completes task, but code is horrid.
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "md5_outside.h"

const char FILEPATH[70] = "C:\\Users\\ossis\\ClionProjects\\joulukalenteri_2016\\5\\input.txt";
const int LOCATIONS_REQUIRED = 9;
const int MD5_OUTPUT_LENGTH = 32;
const int CHARACTERS_REQUIRED = 5;
const char THE_CHARACTER = '0';

void generateMD5(char * input, int input_length, int added_index, char output[]);

int main(){
    FILE *f = fopen(FILEPATH, "r");
    //char *input;
    char input[100];
    int length;
    int index = 0;
    int locations_found = 0;
    char password[LOCATIONS_REQUIRED];
    int freep[LOCATIONS_REQUIRED];
    for(int i = 0; i < LOCATIONS_REQUIRED; i++){
        password[i] = ' ';
        freep[i] = 1;
    }
    char MD5output[MD5_OUTPUT_LENGTH];
    int position;
    fseek(f, 0, SEEK_END);
    length = ftell(f) + 1;
    fseek(f,0,SEEK_SET);
    //input = (char*)malloc(sizeof(char) * length);
    fgets(input, length, f);
    while(locations_found < LOCATIONS_REQUIRED - 1){
        generateMD5(input, length, index, MD5output);
        int enoughZeros = 1;
        for(int i = 0; i < CHARACTERS_REQUIRED; i++){
            if(MD5output[i] != THE_CHARACTER){
                enoughZeros = 0;
                break;
            }
        }
        if(enoughZeros){
            position = MD5output[5] - '0';
            if((position >= 0) && (position <= 7)){
                if(freep[position + 1]) {
                    password[position + 1] = MD5output[6];
                    locations_found++;
                    freep[position + 1] = 0;
                    printf(password);
                }
            }
        }
        index++;
    }
    //free(input);
    return 1;
}

void generateMD5(char *input, int input_length, int added_index, char *output){
    unsigned int lengthOfIndex = (unsigned int)floor(log10(added_index)) + 1;
    //char number[1];
    //char *number;
    //number = (char*)malloc(sizeof(char) * (lengthOfIndex));
    //itoa(added_index, number, 10);
    //realloc(input, (input_length + lengthOfIndex) * sizeof(char));
    itoa(added_index, input + input_length - 1, 10);
    MDString(input, output);
}

