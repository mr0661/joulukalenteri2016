//
// Created by ossis on 11.12.2016.
//
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "md5.h"

const char FILEPATH[70] = "C:\\Users\\ossis\\ClionProjects\\joulukalenteri_2016\\5\\input.txt";
const int EXTRA_SPACE = 10;
const int LOCATIONS_REQUIRED = 8;
const int MD5_OUTPUT_LENGTH = 32;
const int CHARACTERS_REQUIRED = 5;
const char THE_CHARACTER = '0';

void generateMD5(char * input, int input_length, int added_index, char output[]);

int main(){
    FILE *f = fopen(FILEPATH, "r");
    char *input;
    //char input[30];
    int length;
    int index = 0;
    int locations_found = 0;
    char password[LOCATIONS_REQUIRED];
    char MD5output[MD5_OUTPUT_LENGTH];

    fseek(f, 0, SEEK_END);
    length = ftell(f) + 1;
    fseek(f,0,SEEK_SET);
    input = (char*)malloc(sizeof(char) * length);
    fgets(input, length, f);
    while(locations_found < LOCATIONS_REQUIRED){
        generateMD5(input, length, index, MD5output);
        int enoughZeros = 1;
        for(int i = 0; i < CHARACTERS_REQUIRED; i++){
            if(MD5output[i] != THE_CHARACTER){
                enoughZeros = 0;
                break;
            }
        }
        if(enoughZeros){
            password[locations_found++] = MD5output[CHARACTERS_REQUIRED];
        }
        index++;
    }
    free(input);
    printf(password);
    return 1;
}

void generateMD5(char * input, int input_length, int added_index, char output[]){
    unsigned int lengthOfIndex = (unsigned int)floor(log(added_index)) + 1;
    //char number[1];
    //char *number;
    //number = (char*)malloc(sizeof(char) * (lengthOfIndex));
    //itoa(added_index, number, 10);
    realloc(input, (input_length + lengthOfIndex) * sizeof(char));
    itoa(added_index, input + input_length - 1, 10);

    MD5(input, output);
    for(int i = 0; i < MD5_OUTPUT_LENGTH; i++){
        output[i] = '0' + rand()%20;
    }
}