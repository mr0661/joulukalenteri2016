//
// Created by ossis on 19.12.2016.
//

#include <stdio.h>

const char PATH[70] = "C:\\Users\\ossis\\ClionProjects\\joulukalenteri_2016\\18\\input.txt";
const int ROW_LENGTH = 101;
const int MAX_ROWS = 400000;
const int ROWS_SAVED = 2;

const char TRAP = '^';
const char SAFE = '.';

enum EdgeState{NOT_EDGE, LEFT_EDGE, RIGHT_EDGE};
typedef enum EdgeState edge;

// given row as input, resolves next row as a output.
void resolveRow(char* output, const char* input);

//Evaluates status of one location. middle location given, will
//evaluate *backwards*. The edgeState blocks evaluation to the
//direction (e.g. in the left end doesn't check left side).
char status(const char* input, edge edgeState);

// Counts how many characters match to "safe" signal.
int countSafe(const char* input);

int main(){
    FILE* f = fopen(PATH, "r");
    int count = 0;
    int index = 0;
    char map[ROWS_SAVED][ROW_LENGTH];
    fgets(map[0], ROW_LENGTH, f);
    count += countSafe(map[0]);
    while(index < MAX_ROWS - 1){
        ++index;
        resolveRow(map[index % 2], map[(1 + index) % 2]);
        count += countSafe(map[index % 2]);
    }
    return count;
}

int countSafe(const char* input){
    int index = 0;
    int count = 0;
    while(*(input + index)!= '\0'){
        if( *(input + index) == SAFE){
            count++;
        }
        index++;
    }
    return count;
}

void resolveRow(char* output, const char* input){
    *output = status(input, LEFT_EDGE);
    int index = 1;
    while(*(input + index + 1) != '\0'){
        *(output + index) = status(input + index, NOT_EDGE);
        ++index;
    }
    *(output + index) = status(input + index, RIGHT_EDGE);
    *(output + index + 1) = '\0';
    return;
}

char status(const char* input, edge edgeState){
    char center = *input;
    char left   = (edgeState == LEFT_EDGE)  ? SAFE : *(input - 1);
    char right  = (edgeState == RIGHT_EDGE) ? SAFE : *(input + 1);
    if((left == TRAP)&&(center == TRAP)&&(right != TRAP)) return TRAP;
    if((left != TRAP)&&(center == TRAP)&&(right == TRAP)) return TRAP;
    if((left == TRAP)&&(center != TRAP)&&(right != TRAP)) return TRAP;
    if((left != TRAP)&&(center != TRAP)&&(right == TRAP)) return TRAP;
    return SAFE;
}