//
// Created by ossis on 12.12.2016.
//

#include <stdio.h>

const char FILEPATH[70] = "C:\\Users\\ossis\\ClionProjects\\joulukalenteri_2016\\6\\input.txt";
const int COLUMNS = 8;
const int CHARACTERS = 26;

int main(){
    FILE* f = fopen(FILEPATH, "r");
    char letters[COLUMNS][CHARACTERS];
    char decoded[COLUMNS];
    for(int i = 0; i < COLUMNS; i++){
        for( int j = 0; j < CHARACTERS; j++){
            letters[i][j] = 0;
        }
    }

    char c;

    c = fgetc(f);
    while(c != EOF) {
        for (int i = 0; i < COLUMNS; i++) {
            letters[i][c - 'a'] += 1;
            c = fgetc(f);
        }
        c = fgetc(f);
    }

    for(int i = 0; i < COLUMNS; i++){
        int maxn = letters[i][0];
        int maxi = 0;
        for( int j = 1; j < CHARACTERS; j++) {
            if (maxn > letters[i][j]) { //Modify this line between part 1 and 2
                maxn = letters[i][j];
                maxi = j;
            }
        }
        decoded[i] = maxi + 'a';
    }
    printf(decoded);
    printf(decoded);
    return 1;
}