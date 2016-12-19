//
// Created by ossis on 18.12.2016.
//
#include <stdio.h>
#include <mem.h>
#include <malloc.h>
#include "md5_outside.h"

const char PATH[70] = "C:\\Users\\ossis\\ClionProjects\\joulukalenteri_2016\\17\\input.txt";
const int INPUT_MAX_LENGTH = 8;
const int INPUT_MAX_PATH = 1200;
const int MD5_OUTPUT = 33;
const int LOCATIONS = 20000;
const int X_START = 0;
const int Y_START = 0;
const int X_END = 3;
const int Y_END = 3;

const int DOWN  = 1;
const int UP   = -1;
const int RIGHT = 1;
const int LEFT = -1;


struct Position{
    char* route;
    int x;
    int y;
};

typedef struct Position pos;

void generateMD5(const char *input1, const char *input2, char *output);

void addStartPosition(pos *new);

// C
void addNewPosition(pos *new, const pos *old, char dir);

//Frees memory allocated in p
void deletePosition(pos* p);

int allowedDirection(char c);

int main(){
    FILE* f = fopen(PATH, "r");
    char input[INPUT_MAX_LENGTH + 1];
    char output[MD5_OUTPUT];
    pos p[LOCATIONS];
    int savePosition = 1;
    int readPosition = 0;
    int shortestPrinted = 0;
    int largestPathGenerated = 0;
    fgets(input, INPUT_MAX_LENGTH + 1, f);
    addStartPosition(p);
    while(savePosition != readPosition){
        generateMD5(input, (p + readPosition)->route, output);
        if((p + readPosition)->y > 0){ // Up
            if(allowedDirection(output[0])){
                addNewPosition(p + savePosition, p + readPosition, 'U');
                savePosition = (savePosition + 1) % LOCATIONS;
            }
        }
        if((p + readPosition)->y < X_END){ // Down
            if(allowedDirection(output[1])){
                addNewPosition(p + savePosition, p + readPosition, 'D');
                if((p + savePosition)->x == X_END && (p + savePosition)->y == Y_END){
                    if(!shortestPrinted) {
                        printf((p + savePosition)->route);
                        shortestPrinted++;
                    }
                    largestPathGenerated = strlen((p + savePosition)->route);
                }
                else {
                    savePosition = (savePosition + 1) % LOCATIONS;
                }
            }
        }
        if((p + readPosition)->x > 0){ // Left
            if(allowedDirection(output[2])){
                addNewPosition(p + savePosition, p + readPosition, 'L');
                savePosition = (savePosition + 1) % LOCATIONS;
            }
        }
        if((p + readPosition)->x < Y_END){ // Right
            if(allowedDirection(output[3])){
                addNewPosition(p + savePosition, p + readPosition, 'R');
                if((p + savePosition)->x == X_END && (p + savePosition)->y == Y_END){
                    if(!shortestPrinted) {
                        printf((p + savePosition)->route);
                        shortestPrinted++;
                    }
                    largestPathGenerated = strlen((p + savePosition)->route);
                }
                else {
                    savePosition = (savePosition + 1) % LOCATIONS;
                }
            }
        }
        deletePosition(p + readPosition); // Free memory or read location

        readPosition = (readPosition + 1) % LOCATIONS;
    }
    printf(" <-- Shortest path\n%i <-- Longest distance", largestPathGenerated);
    return largestPathGenerated;
}

void generateMD5(const char *input1, const char *input2, char *output){
    char input[INPUT_MAX_LENGTH + INPUT_MAX_PATH];
    strcpy(input, input1);
    strcpy(input + INPUT_MAX_LENGTH, input2);
 //   printf(input);
 //   printf("\n");
    MDString(input, output);
}

void addStartPosition(pos *new){
    new->x = X_START;
    new->y = Y_START;
    new->route = malloc(sizeof(char));
    new->route[0] = '\0';
}

void addNewPosition(pos *new, const pos *old, char dir){
    char n[2];
    n[0] = dir;
    n[1] = '\0';
    int oldSize = strlen(old->route);
    new->route = malloc((oldSize + 2)* sizeof(char));
    strcpy(new->route, old->route);
    strcpy(new->route + oldSize, n);
    new->x = old->x;
    new->y = old->y;
    if(dir == 'D'){
        new->y += DOWN;
    }
    else if(dir == 'U'){
        new->y += UP;
    }
    else if(dir == 'L'){
        new->x += LEFT;
    }
    else if(dir == 'R'){
        new->x += RIGHT;
    }
    return;
}

void deletePosition(pos* p){
    free(p->route);
}

int allowedDirection(char c){
    return c > 'a';
}