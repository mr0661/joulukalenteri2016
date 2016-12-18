//
// Created by ossis on 18.12.2016.
//

#include <stdio.h>
#include <mem.h>

#define MAX_STR 35651584
typedef unsigned int uint;

const char PATH[70] = "C:\\Users\\ossis\\ClionProjects\\joulukalenteri_2016\\16\\input.txt";


// Generates data from seed based on some fun 'fractal'
// it adds 0, and then original reversed and inverted.
uint generateData(char * input, uint maxLength);

// Produces checksum based on input, if length is even, should be
// processed again to get real checksum(repeat until odd number is found)
uint checksum(char * input);

static char input[MAX_STR];  // Only way to handle really large array

int main(){
    FILE* f = fopen(PATH, "r");
    long l;
    uint length = 0;

    fgets(input, 40, f);
    while(generateData(input, MAX_STR) < MAX_STR);
    while(!(checksum(input) % 2));
    printf(input);
    return 1;
}

uint generateData(char * input, uint maxLength){
    uint length = strlen(input);
    uint index = 1;
    input[length] = '0';
    for(int i = length - 1; i >= 0; i--){
        if(*(input + i)=='0'){
            input[length + index] = '1';
        }
        else{
            input[length + index] = '0';
        }
        ++index;
        if(length + index >= maxLength){
            input[length + index] = '\0';
            return maxLength;
        }
    }
    input[length + index] = '\0';
    return length * 2 + 1;
}

uint checksum(char * input){
    int index = 0;
    while(input[index * 2] != '\0' ){
        if(input[index * 2] == input[index * 2 + 1]){
            input[index] = '1';
        }
        else if(input[index * 2] != input[index * 2 + 1]){
            input[index] = '0';
        }
        index++;
    }
    input[index] = '\0';
    return index;
}