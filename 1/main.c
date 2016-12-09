//
// Created by mr0661 on 8.12.2016.
//
#include <stdio.h>
#include <stdlib.h>
#include "main.h"

// Returns distance to headquarter location
int main(){
    FILE *f  = fopen(INPUT_FILENAME,"r");
    int c1 = fgetc(f);  //Is used to find directional character
    int c2;     //Is used to find length character
    char n[SINGLE_INPUT_MAX_LENGTH];    // Used for saving number
    int position[2] = {0,0};    // Saves current position
    Direction d = NORTH;    // Saves current direction
    int positions[MAX_POSITIONS][2];    // Saves whole path
    positions[0][0] = position[0];  // Position in x
    positions[0][1] = position[1]; // Position in y
    unsigned int count = 0;     // Keeps track on count
    int cuttingPoint[2];    // Used to save cutting point

    while(c1 != EOF && c1 != 'X'){
        if (c1 == 'R'||c1 == 'L'){
            for (unsigned int i = 0; i < SINGLE_INPUT_MAX_LENGTH; i++){
                c2 = fgetc(f);
                if (c2 >= 48 && c2 <= 57){
                    n[i] = c2;
                }
                else{   // If character not number between is found
                    // ends saving characters and ends string
                    // and loop
                    n[i] = '\0';
                    break;
                }
            }
            d = newDirection(c1, d);
            move(position, d, atoi(n));
            for(int i = count - 2; i > 0; i -= 2){
                /*
                 * Depending on direction, checks if segments cross.
                 * Assumes chess grid movement. First cutting point
                 * is found, and then it is checked if it is between
                 * segments.
                 */
                if( d == NORTH || d == SOUTH){
                    cuttingPoint[0] = position[0];
                    cuttingPoint[1] = positions[i][1];
                    if ((cuttingPoint[1] - position[1]) *
                        (cuttingPoint[1] - positions[count][1]) <= 0){
                        if(((cuttingPoint[0] - positions[i][0]) *
                            (cuttingPoint[0] - positions[i - 1][0])) <= 0){
                            return abs(cuttingPoint[0]) +
                                   abs(cuttingPoint[1]);
                        }
                    }
                }
                    /*
                     * Previous was for when movement is vertical,
                     * next is when movement is horizontal.
                     */
                else{
                    cuttingPoint[0] = positions[i][0];
                    cuttingPoint[1] = position[1];
                    if ((cuttingPoint[0] - position[0]) *
                        (cuttingPoint[0] - positions[count][0]) <= 0){
                        if(((cuttingPoint[1] - positions[i][1]) *
                            (cuttingPoint[1] - positions[i - 1][1])) <= 0){
                            return abs(cuttingPoint[0]) +
                                   abs(cuttingPoint[1]);
                        }
                    }
                }
            };
            count++;
            positions[count][0] = position[0];
            positions[count][1] = position[1];
        }
        c1 = fgetc(f);
    }
    return abs(position[0]) + abs(position[1]);
}

void move(int pos[], Direction dir, unsigned int len ){
    switch(dir) {
        case NORTH :
            pos[1] += len;
            break;
        case SOUTH :
            pos[1] -= len;
            break;
        case EAST :
            pos[0] += len;
            break;
        case WEST :
            pos[0] -= len;
            break;
        default:
            printf("Unknown direction");
    }
}

Direction newDirection(char lr,Direction dir){
    switch(dir) {
        case NORTH :
            if(lr == 'L'){
                return WEST;
            }
            else{
                return EAST;
            }
        case SOUTH :
            if(lr == 'L'){
                return EAST;
            }
            else{
                return WEST;
            }
        case EAST :
            if(lr == 'L'){
                return NORTH;
            }
            else{
                return SOUTH;
            }
        case WEST :
            if(lr == 'L'){
                return SOUTH;
            }
            else{
                return NORTH;
            }
        default:
            printf("Error: Unknown direction");
            return NORTH;
    }
}

int abs(int a){
    if(a > 0) return a;
    return -a;
}