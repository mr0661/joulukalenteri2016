//
// Created by ossis on 24.12.2016.
//

#include <stdio.h>
#include <mem.h>
#include <ctype.h>
#include <limits.h>

#define TARGET_COUNT 8
#define ROW_LENGTH 183
#define COLUMN_LENGTH 37
#define TOTAL_LENGTH COLUMN_LENGTH * ROW_LENGTH
#define DIRECTIONS 4

const char* PATH = "C:\\Users\\ossis\\ClionProjects\\joulukalenteri_2016\\24\\input.txt";
const int EMPTY = -1;
const char WALL_CHR = '#';
const char FLOOR_CHR = '.';
const char START_CHR = '0';
const char *TARGET_CHR = "01234567";


const int X_DIR[DIRECTIONS] = {1, -1, 0, 0};
const int Y_DIR[DIRECTIONS] = {0, 0, 1, -1};
struct Point{
    int x;
    int y;
};
typedef struct Point point;
struct Target{
    point p;
    int id;
    int distance[TARGET_COUNT];
};
typedef struct Target target;

void findDistances(target *t, const char map[COLUMN_LENGTH][ROW_LENGTH]);

unsigned int iterTrough(const target * targets, const target current, const char * possibileTargetIDs);
unsigned int countShortestRoute(const target *targets, const target current, int id1, int id2);

int main(){
    FILE* f = fopen(PATH, "r");

    char row[ROW_LENGTH];
    char map[COLUMN_LENGTH][ROW_LENGTH];
    target targets[TARGET_COUNT];
    int index = 0; // = COLUMN LENGTH // in the end of first loop
    //fgets(row, ROW_LENGTH, f);
    while(fgets(row, ROW_LENGTH, f)){
        strcpy(map[index], row);
        char *ptr = strpbrk(row, TARGET_CHR);
        while(ptr != NULL){
            targets[*ptr - '0'].p.x = index;
            targets[*ptr - '0'].p.y = (int)(ptr - row);
            targets[*ptr - '0'].id = *ptr - '0';
            ptr = strpbrk(ptr + 1, TARGET_CHR);
        }
        ++index;
    }
    for(index = 0; index < TARGET_COUNT; ++index){
        findDistances(targets + index, map);
    }
    //index = iterTrough(targets, targets[4], TARGET_CHR + 5);
    index = iterTrough(targets, targets[0], TARGET_CHR + 1);
    printf("%i", index);
    return index;
}

unsigned int iterTrough(const target * targets, const target current, const char * possibileTargetIDs){
    if(strlen(possibileTargetIDs) == 2){
        return countShortestRoute(targets, current,
                                  possibileTargetIDs[0] - '0', possibileTargetIDs[1] - '0');
    }
    char newTarget[TARGET_COUNT + 1];
    unsigned int shortestLength = UINT_MAX; // Lets choose some large uint value
    unsigned int length;
    for(int i = 0; i < strlen(possibileTargetIDs);++i){
        strcpy(newTarget, possibileTargetIDs);
        strcpy(newTarget + i, possibileTargetIDs + i + 1);
        length = iterTrough(targets, targets[possibileTargetIDs[i] - '0'], newTarget);
        length += + current.distance[possibileTargetIDs[i] - '0'];
        if(shortestLength > length){
            shortestLength = length;
        }
    }
    return shortestLength;
}

unsigned int countShortestRoute(const target *targets, const target current, int id1, int id2){
    int length1 = current.distance[id1] + targets[id1].distance[id2];
    int length2 = current.distance[id2] + targets[id2].distance[id1];
    return (unsigned int)((length1 < length2) ? length1: length2);
}

void findDistances(target *t, const char map[COLUMN_LENGTH][ROW_LENGTH]){
    t->distance[t->id] = 0;
    int mapRoute[COLUMN_LENGTH][ROW_LENGTH];
    for(unsigned int i = 0; i < COLUMN_LENGTH; ++i){
        for(unsigned int j = 0; j < ROW_LENGTH; ++j) {
            mapRoute[i][j] = EMPTY;
        }
    }
    point openSet[TOTAL_LENGTH];
    int position = 0;
    int save = 1;
    openSet[0] = t->p;
    mapRoute[t->p.x][t->p.y] = 0;
    while(position != save){
        // First search possible ways to continue from this point
        for(int i = 0; i < DIRECTIONS ; ++i ) {
            if(map[openSet[position].x + X_DIR[i]][openSet[position].y + Y_DIR[i]] != WALL_CHR) {
                if (mapRoute[openSet[position].x + X_DIR[i]][openSet[position].y + Y_DIR[i]] == EMPTY) {
                    mapRoute[openSet[position].x + X_DIR[i]][openSet[position].y + Y_DIR[i]] =
                            mapRoute[openSet[position].x][openSet[position].y] + 1;
                    openSet[save].x = openSet[position].x + X_DIR[i];
                    openSet[save].y = openSet[position].y + Y_DIR[i];
                    save++;
                }
            }
        }
        // Check if current is point of interest;
        if(isdigit(map[openSet[position].x][openSet[position].y])){
            t->distance[map[openSet[position].x][openSet[position].y] - '0'] =
                    mapRoute[openSet[position].x][openSet[position].y];
        }
        position++;
    }
    return;/*
    for( int j = 0; j < COLUMN_LENGTH; ++j){
        for(int i = 0; i < ROW_LENGTH; ++i){
            if(mapRoute[j][i] < 0){
                printf(".");
            }
            else {
                printf("%i", mapRoute[j][i] % 10);
            }
        }
        printf("\n");
    }*/
}