//
// Created by ossis on 18.12.2016.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef unsigned int uint;
const char PATH[70] = "C:\\Users\\ossis\\ClionProjects\\joulukalenteri_2016\\15\\input.txt";
const uint MAX_INPUT_ROW = 70;
const uint MAX_DISKS = 9;
const uint POS1 = 11;
const uint POS2 = 41;
const uint TARGET_LOCATION = 0;

struct Disk{
    uint currentPosition;
    uint positions;
};
typedef struct Disk disk;

int main(){
    uint diskCount = 0;
    char row[MAX_INPUT_ROW];
    disk disks[MAX_DISKS];
    char * ptr;
    FILE* f = fopen(PATH, "r");

    while(fgets(row, MAX_INPUT_ROW, f)) {
        printf(row);
        disks[diskCount].positions = (uint) strtol(row + POS1, &ptr, 10);
        // Represent position disk will during certain time
        disks[diskCount].currentPosition = ((uint) strtol(ptr + POS2, &ptr, 10)
                                        + diskCount + 1) % disks[diskCount].positions;
        printf(" 1:%u  2:%u\n", disks[diskCount].positions,
               disks[diskCount].currentPosition);
        ++diskCount;
    }
    uint falledTrough;
    uint time = 0;
    while(1){//time < UINT16_MAX){
        falledTrough = 1;
        for(uint i = 0; i < diskCount; ++i){
            if(disks[i].currentPosition != TARGET_LOCATION){
                falledTrough = 0;
            }
            disks[i].currentPosition = (disks[i].currentPosition +
                                        1) % disks[i].positions;
        }
        if(falledTrough){
            break;
        }
        ++time;
    }
    return time;
}