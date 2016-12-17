//
// Created by ossis on 17.12.2016.
//

#include <stdio.h>
#include <mem.h>

#define THE_FORMULA(x,y) x * x + 3 * x + 2 * x * y + y + y * y

struct Target{
    unsigned int x;
    unsigned int y;
};

typedef unsigned long long ull;
typedef unsigned int uint;
typedef struct Target target;

const ull INPUT_NUMBER = 1358;
const unsigned int MAX_DIMENSIONS = 100;
const unsigned int TARGET_ARRAY_SIZE = 10000;
const int NON_VISITED = -1;
const int WALL = -2;
const int X_START = 1;
const int Y_START = 1;

const int NEIGHTBOURS=4;
const int X_NEIGHTBOR[4] = { 0, 0, -1, 1};
const int Y_NEIGHTBOR[4] = {-1, 1,  0, 0};

const int TARGET_X = 31;
const int TARGET_Y = 39;
const uint TARGET_LOCATIONS = 50;

// Checks if location contains a "Wall"
int isWall(uint x, uint y);

// For visualization, prints distance map
void printDistanceMap(const uint map[MAX_DIMENSIONS][MAX_DIMENSIONS]);

int main(){
    int locationReached = 0;
    int endDistance = 0;
    int ct = 0; // Current target
    int st = 1; // Save target(location where new stuff is added
    target t[TARGET_ARRAY_SIZE]; // A* Open set
    int distanceChart[MAX_DIMENSIONS][MAX_DIMENSIONS]; // A* Closed set
    memset(distanceChart, NON_VISITED, sizeof(int) * MAX_DIMENSIONS * MAX_DIMENSIONS);
    t[ct].x = X_START; // Initialize starting
    t[ct].y = Y_START; // coordinates
    distanceChart[t[ct].x][t[ct].y] = 0;  // Initialize starting distance
    uint locationCount = 1;

    while(!endDistance || !locationReached){
        for(int i = 0; i < NEIGHTBOURS; i++ ){ // Add neighbours as targets unless already done to that target
            int x = t[ct].x + X_NEIGHTBOR[i];
            int y = t[ct].y + Y_NEIGHTBOR[i];
            if(x < 0 || x >= MAX_DIMENSIONS || y < 0 || y >= MAX_DIMENSIONS){
                continue;
            }
            else if(distanceChart[x][y] == NON_VISITED ){
                if(x == TARGET_X && y == TARGET_Y ){ // If destination is reached
                    endDistance = distanceChart[t[ct].x][t[ct].y] + 1;
                    break;
                }
                else if(isWall((uint)x, (uint)y)) {
                    distanceChart[x][y] = WALL;
                }
                else{
                    t[st].x = (uint)x;
                    t[st].y = (uint)y;
                    st = (1 + st) % TARGET_ARRAY_SIZE;
                    distanceChart[x][y] = distanceChart[t[ct].x][t[ct].y] + 1;
                }
            }
        }
        ct = (1 + ct) % TARGET_ARRAY_SIZE;
        if(distanceChart[t[ct].x][t[ct].y] <= TARGET_LOCATIONS){
            locationCount++;
        }
        else{
            locationReached = 1;
        }

    }
    printDistanceMap(distanceChart);
    printf("Part 1: %u\nPart 2:%u\n",endDistance, locationCount );
    return endDistance;
}

int isWall(uint x, uint y){
    ull num = THE_FORMULA(x, y);// x * x + 3 * x + 2 * x * y + y + y * y;
    num += INPUT_NUMBER;
    uint count = 0;
    // printf("%llu\n", num);
    while(num > 0){
        // printf("%llu", num%2);
        num >>= 1;
        count += num % 2;
    }
    return count % 2;
}

void printDistanceMap(const uint map[MAX_DIMENSIONS][MAX_DIMENSIONS]) {
    for(uint y = 0; y < MAX_DIMENSIONS; y++){
        for(uint x = 0; x < MAX_DIMENSIONS; x++) {
            //if(isWall(x,y)) printf("#");
            if(map[x][y] == WALL) printf("#");
            else if(map[x][y] != NON_VISITED) printf("%u", map[x][y] % 10);
            else{
                if(isWall(x,y)) printf("#");
                else printf(".");
            }

        }
        printf("\n");
    }
}