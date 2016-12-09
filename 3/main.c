//
// Created by ossis on 10.12.2016.
//
#include <stdio.h>
#include <stdlib.h>

const int MAX_NUMBERS = 4;
const char FILENAME[70] = "C:\\Users\\ossis\\ClionProjects\\joulukalenteri_2016\\3\\input.txt";

int isNum(char c);
int getNextNum(FILE *f);

int main(){
    FILE *f = fopen(FILENAME,"r");
    int count = 0;
    int x;
    int y;
    int z;

    while(count<MAX_NUMBERS){
        x = getNextNum(f);
        y = getNextNum(f);
        z = getNextNum(f);


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
                if(!isNum(c)){
                    number[i]='\0';
                    return atoi(number);
                }
                number[i] = c;
            }
        }

    }
}