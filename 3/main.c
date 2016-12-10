//
// Created by ossis on 10.12.2016.
//
#include <stdio.h>
#include <stdlib.h>

const int MAX_NUMBERS = 4;
const char FILENAME[70] = "C:\\Users\\ossis\\ClionProjects\\joulukalenteri_2016\\3\\input.txt";
const int MODE = 3;

int isNum(char c);
int getNextNum(FILE *f);
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
        if(numbers[0] && numbers[1] && numbers[2]){
            if (allowedTriangle(numbers[0],numbers[1],numbers[2])){
                ++count;
            }
        }
        else{
            printf("Reached to the end, final value: %i", count);
            return count;
        }
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