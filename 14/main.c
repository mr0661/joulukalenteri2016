//
// Created by ossis on 18.12.2016.
//
#include <stdlib.h>
#include "md5_outside.h"

const char INPUT[9] = "zpqevtbw";
const int INPUT_LENGTH = 8;
const int TARGET_KEY = 64;
const int MD5_OUTPUT = 33;
const int MD5_INPUT_LENGTH = 33;
const int NEXT_HASHES = 1000;
const int EXTRA_HASHING = 2016; // Exhange to 0 for Part 1


//Uses outside function to generate MD5
void generateMD5(char *input, int input_length, int added_index, char *output);

// returns first character that is three times in row
// return 0 if no such character
char firstRule(char* str);

// returns 1 if character is found five times in row
// return 0 if it isn't found
int secondRule(char* str, char character);

int main(){
    char output1[MD5_OUTPUT];
    char output2[MD5_OUTPUT];
    char input[MD5_INPUT_LENGTH];
    char preCounted[NEXT_HASHES + 1][MD5_OUTPUT];
    unsigned int target = 0;
    unsigned int index = 0;
    unsigned int count = 0;
    char c;
    strcpy(input, INPUT);
    for(unsigned int i = 0; i <= NEXT_HASHES; ++i){
        generateMD5(input, INPUT_LENGTH, index + i, output1);
        for(unsigned int j = 0; j < EXTRA_HASHING; j++){
            MDString(output1, output2);
            strcpy(output1, output2);
        }
        strcpy(preCounted[i], output1);
    }
    while (1) {
        c = firstRule(preCounted[target]);
        if(c) {
            for (unsigned int i = 0; i <= NEXT_HASHES; ++i) {
                if(i != target) {
                    if (secondRule(preCounted[i], c)) {
                        count++;
                        printf("%u**%u**\n",count, index);
                        if (count >= TARGET_KEY) {
                            return 1;
                        }
                        break;
                    }
                }
            }
        }
        generateMD5(input, INPUT_LENGTH, index + NEXT_HASHES + 1, output1);
        for(unsigned int j = 0; j < EXTRA_HASHING; j++){
            MDString(output1, output2);
            strcpy(output1, output2);
        }
        strcpy(preCounted[target], output1);
        ++index;
        target = (target + 1) % (NEXT_HASHES + 1);
        //printf("%u**%u**\n",count, index);
    }
}

void generateMD5(char *input, int input_length, int added_index, char *output){
    if (added_index != -1) {
        itoa(added_index, input + input_length, 10);
    }
    MDString(input, output);
}

char firstRule(char* str){
    unsigned int i = 0;
    while(str[i + 2] != '\0'){
        if((str[i] == str[i + 1]) && (str[i + 2] == str[i + 1])){
            return str[i];
        }
        ++i;
    }
    return 0;
}

int secondRule(char* str, char character){
    unsigned int index = 0;
    while(str[index + 4] != '\0'){
        if((str[index] == str[index + 1]) &&
                (str[index + 1] == str[index + 2]) &&
                (str[index + 2] == str[index + 3]) &&
                (str[index + 3] == str[index + 4]) &&
                (str[index + 4] == character)){
            return 1;
        }
        ++index;
    }
    return 0;
}