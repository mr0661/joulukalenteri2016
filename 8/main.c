//
// Created by ossis on 12.12.2016.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int SCREEN_HEIGHT = 6;
const int SCREEN_WIDTH = 50;
const int MAX_ROW = 30;
const int MAX_NUMBER_LENGTH = 4;
const char EMPTY = ' ';
const char LIT = 'o';
const char ROT[7] = "rotate";
const char COL[7] ="column";
const char RECT[5] = "rect";
const char PATH[70] = "C:\\Users\\ossis\\ClionProjects\\joulukalenteri_2016\\8\\input.txt";

// Prints current screen usint EMPTY and LIT symbols defined above
void printScreen(const char screen[SCREEN_HEIGHT][SCREEN_WIDTH]);

// Counts current lights
int countLights(const char screen[SCREEN_HEIGHT][SCREEN_WIDTH]);

// Lits rectangle area
void rectangle(char screen[SCREEN_HEIGHT][SCREEN_WIDTH],
               int column, int distance);

// shfts column, overflow goes to other side
void rotateColumn(char screen[SCREEN_HEIGHT][SCREEN_WIDTH],
                  int column, int shift);

// moves column to certain direction, overflow goes to other side
void rotateRow(char screen[SCREEN_HEIGHT][SCREEN_WIDTH],
               int column, int shift);

// Saves stream into array. Saves all allowedCharacters, ignoreCharacters
// are ignored. From part 4.
int arrayFromStream(char array[], FILE *stream, int (*allowedCharacter)(int), int(*ignoreCharacter)(int));

// simple rules that check certain conditions
int isCharacter(int);
int noIgnore(int);
int isNumber(int a);
int notB(int a);    // also checks if EOF
int notEndl(int a); // also checks if EOF

int main(){
    char screen[SCREEN_HEIGHT][SCREEN_WIDTH];
    char number1[MAX_NUMBER_LENGTH];
    char number2[MAX_NUMBER_LENGTH];
    char row[MAX_ROW];
    int count;

    for(int i = 0; i < SCREEN_HEIGHT; ++i){
        for(int j = 0; j < SCREEN_WIDTH; ++j){
            screen[i][j] = EMPTY;
        }
    }
    FILE* f = fopen(PATH, "r");
    while(arrayFromStream(row, f, isCharacter, noIgnore)) {
        // For rectangle
        if (0 == strcmp(row, RECT)) {
            fgetc(f);//remove space
            arrayFromStream(number1, f, isNumber, noIgnore);
            fgetc(f);//remove x
            arrayFromStream(number2, f, isNumber, noIgnore);
            fgetc(f);//remove endl
            rectangle(screen, atoi(number1), atoi(number2));
        }// For rotate
        else if (0 == strcmp(row, ROT)) {
            fgetc(f);//remove space
            arrayFromStream(row, f, isCharacter, noIgnore);
            arrayFromStream(number1, f, isNumber, notB);
            arrayFromStream(number2, f, isNumber, notEndl);
            fgetc(f);//remove endl
            if(0 == strcmp(row, COL)){
                rotateColumn(screen, atoi(number1), atoi(number2));
            }
            else{
                rotateRow(screen, atoi(number1), atoi(number2));
            }
        }
    }
    printScreen(screen);
    count = countLights(screen);
    //count = countLights(screen);
    return count;
}

void rotateColumn(char screen[SCREEN_HEIGHT][SCREEN_WIDTH],
                  int column, int shift){
    char save[SCREEN_HEIGHT];
    for(int i = 0; i < SCREEN_HEIGHT; ++i){
        save[i] = screen[i][column];
    }
    for(int i = 0; i < SCREEN_HEIGHT; ++i){
        screen[(i + shift) % SCREEN_HEIGHT][column] = save[i];
    }
}

void rotateRow(char screen[SCREEN_HEIGHT][SCREEN_WIDTH],
                  int column, int shift){
    char save[SCREEN_WIDTH];
    for(int i = 0; i < SCREEN_WIDTH; ++i){
        save[i] = screen[column][i];
    }
    for(int i = 0; i < SCREEN_WIDTH; ++i){
        screen[column][(i + shift) % SCREEN_WIDTH] = save[i];
    }
}

void rectangle(char screen[SCREEN_HEIGHT][SCREEN_WIDTH],
               int a, int b){
    for(int i = 0; i < a; ++i){
        for( int j = 0; j < b; ++j){
            screen[j][i] = LIT;
        }
    }

}

int countLights(const char screen[SCREEN_HEIGHT][SCREEN_WIDTH]){
    int count = 0;
    for(int i = 0; i < SCREEN_HEIGHT; ++i){
        for(int j = 0; j < SCREEN_WIDTH; ++j){
            if(screen[i][j] == LIT) count++;
        }
        printf("\n");
    }
    return count;
}

void printScreen(const char screen[SCREEN_HEIGHT][SCREEN_WIDTH]){
    for(int i = 0; i < SCREEN_HEIGHT; ++i){
        for(int j = 0; j < SCREEN_WIDTH; ++j){
            //screen[i][j] = '.';
            printf("%c", screen[i][j]);
        }
        printf("\n");
    }
    return;
}

int arrayFromStream(char array[], FILE *stream, int (*allowedCharacter)(int), int(*ignoreCharacter)(int)){
    int c;
    int i = 0;
    while(1){
        c = fgetc(stream);
        if(allowedCharacter(c)) {
            array[i] = c;
            ++i;
        }
        else if(!ignoreCharacter(c)){
            array[i] = '\0';
            // if character was not part of allowed group returns
            // character back to stream and returns size of array
            ungetc(c, stream);
            return i;
        }
    }
}

int isCharacter(int a){
    return ('a' <= a) && ('z' >= a);
}

int noIgnore(int a){
    return 0;
}

int isNumber(int a){
    return ('0' <= a) &&('9' >= a);
}
int notB(int a){
    return ('b' != a) && (EOF != a) ;
}

int notEndl(int a){
    return ('\n' != a) && (EOF != a);
}