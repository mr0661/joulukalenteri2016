//
// Created by ossis on 14.12.2016.
//

#include <stdio.h>
#include <limits.h>
#include <mem.h>
#include <stdlib.h>

#define MAX_ITEMS 10
#define FLOORS 4
#define GROUND_FLOOR 1
/*#define POSSIBLE_NEXT_STATES 20
#define IN '0'
#define OUT '1'*/

const unsigned int PASS = 20; // Used when you want to move only one object
const unsigned int MAX_STATES_SAVED = 100000;
/*
typedef enum GeneratorCompaund{STRONTIUM, PLUOTONIUM, THULIUM, RUTHENIUM, CURIUM} compaund;

typedef enum MovableBaseUnit{MICROCHIP, GENERATOR} base;

typedef struct Part{ base t; compaund r; } part;
*/
typedef enum Direction{DOWN = -1, STAY = 0, UP = 1} dir;

typedef struct State {
    char ElevatorFloor;     // Floors 1-4: Elevator location
    char floors[MAX_ITEMS]; // Floors 1-4: Part locations
    unsigned int distanceFromStart;
} state;

enum part{SM, SG, PG, PM, RG, RM, CG, CM, TG, TM};



const char FINAL_STATE[MAX_ITEMS] = {FLOORS, FLOORS, FLOORS, FLOORS,
                                     FLOORS, FLOORS, FLOORS, FLOORS,
                                     FLOORS, FLOORS };

const state ORIGINAL_STATE = {
        .ElevatorFloor = 1,
                //SM,SG,PG,PM,RG,RM,CG,CM,TG,TM
        .floors ={ 1, 1, 1, 1, 2, 2, 2, 2, 2, 3},//F4
        .distanceFromStart = 0
};
int redundantMove(const char floor[], unsigned int ID);

unsigned int addAllPossibleStates(state states[],
                                  unsigned int current,
                                  unsigned int saveP);

void printState(state* s);

int sameState(const state* s1, const state* s2);

void cpyState(state *new, const state *old, dir direction,
              int part1ID, int part2ID );

int allowedConfiguration(char floors[]);

int uniqueState(const state states[],
                unsigned int length, const state * new);

int allowedMovement(const state* s, dir direction,
                    unsigned int ID1, unsigned int ID2 );

int main(){
    state states[MAX_STATES_SAVED];
    state states2[MAX_STATES_SAVED];
    cpyState(states, &ORIGINAL_STATE, STAY, PASS, PASS);
    cpyState(states2, &ORIGINAL_STATE, STAY, PASS, PASS);
    unsigned int savePosition = 1;
    unsigned int location = 0;
    while(savePosition < MAX_STATES_SAVED){
        savePosition = addAllPossibleStates(states,
                                            location,
                                            savePosition);

        ++location;
        if(savePosition <= location){
            printf("%i \n", (states + savePosition - 1)->distanceFromStart);
            printState(states + savePosition);
            printf("Blaah\n\n");
        }
        if( !memcmp(FINAL_STATE,
                    states[location].floors, MAX_ITEMS)) {
            printf("Final step count: %i",
                   states[location].distanceFromStart);
            return 1;
        }

    }
    printf("Error: out of array, please reserve more");
    return 0;
}

void printState(state* s) {
    for (int floor = 1; floor <= FLOORS; ++floor) {
        printf("F%i ", floor);
        if (s->ElevatorFloor == floor) printf("E ");
        else printf(". ");
        if (s->floors[0] == floor)printf("SG ");
        else printf(".  ");
        if (s->floors[1] == floor)printf("SM ");
        else printf(".  ");
        if (s->floors[2] == floor)printf("PG ");
        else printf(".  ");
        if (s->floors[3] == floor)printf("PM ");
        else printf(".  ");
        if (s->floors[4] == floor)printf("RG ");
        else printf(".  ");
        if (s->floors[5] == floor)printf("RM ");
        else printf(".  ");
        if (s->floors[6] == floor)printf("CG ");
        else printf(".  ");
        if (s->floors[7] == floor)printf("CM ");
        else printf(".  ");
        if (s->floors[8] == floor)printf("TG ");
        else printf(".  ");
        if (s->floors[9] == floor)printf("TM\n");
        else printf(".\n");
    }
    printf("\n");
}

unsigned int addAllPossibleStates(state states[],
                                  unsigned int current,
                                  unsigned int saveP) {
    dir d = DOWN;
    if (states[current].ElevatorFloor == GROUND_FLOOR) d = UP;
    while (d <= UP) {
        for (unsigned int i = 0; i < MAX_ITEMS; ++i) {
            if (allowedMovement(states + current, d, i, PASS)) {
                cpyState(states + saveP, states + current, d, i, PASS);
                if (uniqueState(states, current, states + saveP)) {
                    ++saveP; // otherwise overwritten.
                }
            }

            for (unsigned int j = i + 1; j < MAX_ITEMS; ++j) {
                if (allowedMovement(states + current, d, i, j)) {
                    cpyState(states + saveP, states + current, d, i, j);
                    if (uniqueState(states, current, states + saveP)) {
                        ++saveP; // otherwise overwritten.
                    }
                }
            }
        }
        d += 2;
        if (states[current].ElevatorFloor == FLOORS) {
            break;
        }
    }
    return saveP;
}

int allowedMovement(const state* s, dir direction,
                    unsigned int ID1, unsigned int ID2 ){
    if(ID1 != PASS){
        if (s->ElevatorFloor != s->floors[ID1]) {
            return 0; // Wrong floor
        }
        if(redundantMove(s->floors, ID1)) {
            return 0;
        }
    }
    if(ID2 != PASS){
        if(s->ElevatorFloor != s->floors[ID2]) {
            return 0; // Wrong floor
        }
    }
    if((direction == UP) && s->ElevatorFloor == FLOORS ){
        return 0; // Can't move up, already in the upmost floor.
    }
    if(direction == DOWN){
        if(!(ID1 % 2) && (ID1 != PASS)){
            return 0;
        }
        if(!(ID2 % 2) && (ID2 != PASS)){
            return 0;
        }
        if(s->ElevatorFloor == GROUND_FLOOR ) {
            return 0; // Can't move down, already in the ground floor.
        }
    }
    char newFloor = s->ElevatorFloor + direction;
    char floor[MAX_ITEMS];
    for(unsigned int i = 0; i < MAX_ITEMS; ++i){
        floor[i] = s->floors[i];
    }
    floor[ID1] += direction;
    floor[ID2] += direction;
    if(!allowedConfiguration(floor)){
        return 0;
    }
    return 1;
}

int redundantMove(const char floor[], unsigned int ID){
    ID -= ID % 2;
    for (int i = ID - 2; i >= 0; i -= 2) {
        if ((floor[ID] == floor[i]) && (floor[ID + 1] == floor[i + 1])) {
            return 1;
        }
    }
    return 0;
}

int allowedConfiguration(char floors[]){
    for(unsigned int i = 1; i < MAX_ITEMS; i += 2){
        if(floors[i] != floors[i - 1]){
            for(unsigned int j = 0; j < MAX_ITEMS; j+=2){
                if(floors[i] == floors[j]){
                    return 0;
                }
            }
        }
    }
    return 1;
}

int uniqueState(const state states[],
                unsigned int length, const state * new){
    for(unsigned int i = 0; i < length; ++i){
        if(sameState(states + i, new)){
            return 0;
        }
    }
    return 1;
}

int sameState(const state* s1, const state* s2){
    // if Elevator is in same location and each element in floor
    // is same.
    return (s1->ElevatorFloor == s2->ElevatorFloor) &&
            !memcmp(s1->floors, s2->floors, MAX_ITEMS);
}

void cpyState(state *new, const state *old, dir direction,
              int part1ID, int part2ID ){
    new->ElevatorFloor = (old->ElevatorFloor) + direction;
    for(int i = 0; i < MAX_ITEMS; i++){
        new->floors[i] = old->floors[i];
    }
    if(direction != STAY){
        if(part1ID != PASS){
            new->floors[part1ID] = new->ElevatorFloor;
        }
        if(part2ID != PASS){
            new->floors[part2ID] = new->ElevatorFloor;
        }
        new->distanceFromStart = old->distanceFromStart + 1;
    }
    else {
        new->distanceFromStart = old->distanceFromStart;
    }
}