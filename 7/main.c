//
// Created by ossis on 12.12.2016.
//
#include <stdio.h>
#include <string.h>

const int MAX_ROW_LENGTH = 256;
const char PATH[70] = "C:\\Users\\ossis\\ClionProjects\\joulukalenteri_2016\\7\\input.txt";
const int MAX_ABABS = 10;
const int ABA_LENGTH = 3;
const int ABA_POS = 2;      // length - 1, just to make code neater
const int ABBA_LENGTH = 4;
const int ABBA_POS = 3;     // length - 1, just to make code neater

int supportsTLS(char IP7row[]);

int supportsSSL(char IP7row[]);

int isAbbaSequence(char *seq);

int isAbaSequence(char *seq);

int main(){
    char row[MAX_ROW_LENGTH];
    int countTLS = 0;
    int countSSL = 0;
    FILE* f = fopen(PATH, "r");
    while(fgets(row, MAX_ROW_LENGTH, f) != NULL) {
        // printf(row);
        if(supportsTLS(row)) {
            ++countTLS;
        }
        if(supportsSSL(row)){
            ++countSSL;
        }
        // printf("\n");
    }
    return countSSL;
}

int supportsSSL(char IP7row[]) {
    int location = 0;
    char aba[MAX_ABABS][ABA_LENGTH]; // Holds each found aba
    int countAbas = 0;
    char bab[MAX_ABABS][ABA_LENGTH]; // Holds each found bab
    int countBabs = 0;
    // First collect all ABA and BAB sequences
    while(IP7row[location + ABA_POS] != '\0' &&
            IP7row[location + ABA_POS] != '\n' ){
        if(IP7row[location + ABA_POS] == '['){
            location += ABA_LENGTH;
            while(IP7row[location + ABA_POS] != ']'){
                if(isAbaSequence(IP7row + location)){
                    for(int i = 0; i < ABA_LENGTH; ++i){
                        bab[countBabs][i] = IP7row[location + i];
                    }
                    countBabs++;
                }
                ++location;
            }
            location += ABA_LENGTH;
        }
        if(isAbaSequence(IP7row + location)){
            for(int i = 0; i < ABA_LENGTH; ++i){
                aba[countAbas][i] = IP7row[location + i];
            }
            countAbas++;
        }
        location++;
    }
    // Then compare them to each other
    for(int i = 0; i < countAbas; i++){
        for( int j = 0 ; j < countBabs; j++){
            if((aba[i][0] == bab[j][1]) &&
               (aba[i][1] == bab[j][0])){
                return 1;
            }
        }
    }
    return 0;
}

// note: doesn't use constants as this would need to be remade if
// ABA_LENGTH != 3
int isAbaSequence(char *seq){
    //printf("%c%c%c", seq[0],seq[1],seq[2]);
    if((seq[0]== seq[2])){
        if((seq[0] != seq[1])){
            return 1;
        }
    }
    return 0;
}


int supportsTLS(char IP7row[]){
    int location = 0;
    int isSupport = 0;
    while(IP7row[location + ABBA_POS] != '\0' &&
            IP7row[location + ABBA_POS] != '\n' ){
        if(IP7row[location + ABBA_POS] == '['){
            location += ABBA_LENGTH;
            while(IP7row[location + ABBA_POS] != ']'){
                if(isAbbaSequence(IP7row + location)){
                    return 0;
                }
                ++location;
            }
            location += 4;
        }
        if(!isSupport){
            if(isAbbaSequence(IP7row + location)){
                isSupport = 1;
            }
        }
        location++;
    }
    return isSupport;
}
// note: doesn't use constants as this would need to be remade if
// ABBA_LENGTH != 4
int isAbbaSequence(char *seq){
    // printf("%c%c%c%c", seq[0],seq[1],seq[2],seq[3]);
    if((seq[0]== seq[3])){
        if((seq[0] != seq[1])){
            if((seq[1] == seq[2])){
                return 1;
            }
        }
    }
    return 0;
}