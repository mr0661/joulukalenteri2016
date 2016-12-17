//
// Created by ossis on 13.12.2016.
//
#include <stdio.h>
#include <stdint.h>
#include <mem.h>
#include <stdlib.h>

typedef unsigned int uint;

enum valueHolderType{OUTPUT, ROBOT};
typedef enum valueHolderType type;

struct Robot{
    uint hiTargetID, lowTargetID, chip1ID, chip2ID;
    type hiIsRobot, lowIsRobot;
};
typedef struct Robot bot;

const uint EMPTY = UINT16_MAX;
const uint ROBOT_MAX = 300;
const uint OUTPUT_MAX = 20;
const uint LARGEST_VALUE = 73;
const uint MAX_LENGTH = 30;
const char PATH[70] = "C:\\Users\\ossis\\ClionProjects\\joulukalenteri_2016\\10\\input.txt";

const uint BOT_TEXT1 = 3;
const uint BOT_TEXT2 = 13;
const uint BOT_TEXT3 = 12;

//Start robot by putting in EMPTY values
void startBot(bot *robot);

int giveRobotRules(bot * robot, uint lowID, type typeLow,
                    uint hiID, type typeHi);

void giveChip(uint outputs[OUTPUT_MAX][LARGEST_VALUE],
              bot *robots, uint targetID, uint chipID);

void dealChips(uint outputs[OUTPUT_MAX][LARGEST_VALUE],
               bot *robots, uint TargetID);

uint arrayFromStream(char array[], FILE *stream,
                     int (*allowedCharacter)(int),
                     int(*ignoreCharacter)(int));

int isCharacter(int a);

int noIgnore(int a);

int isNumber(int a);

int isSpace(int a);

int main(){
    bot robots[ROBOT_MAX];
    uint outputs[OUTPUT_MAX][LARGEST_VALUE];
    char input[MAX_LENGTH];
    uint num1, num2, num3;
    unsigned long long num4;
    type isBot1, isBot2;
    char c = '\n';
    FILE* f = fopen(PATH, "r");
    for(uint i = 0; i < ROBOT_MAX; ++i) startBot(robots + i);
    for(uint i = 0; i < OUTPUT_MAX; ++i)
        for(uint j = 0; j < LARGEST_VALUE; ++j) outputs[i][j] = 0;
    while (c == '\n') {
        // only two choices, and can be determined by length
        if (BOT_TEXT1 == arrayFromStream(input, f, isCharacter, isSpace)) {
            arrayFromStream(input, f, isNumber, isSpace);
            num1 = (uint) atoi(input);
            (BOT_TEXT2 == arrayFromStream(input, f, isCharacter, isSpace)) ?
            (isBot1 = ROBOT) : (isBot1 = OUTPUT);
            arrayFromStream(input, f, isNumber, isSpace);
            num2 = (uint) atoi(input);
            BOT_TEXT3 == arrayFromStream(input, f, isCharacter, isSpace) ?
            (isBot2 = ROBOT) : (isBot2 = OUTPUT);
            arrayFromStream(input, f, isNumber, isSpace);
            num3 = (uint) atoi(input);
            if(giveRobotRules(robots + num1, num2, isBot1, num3, isBot2)){
                dealChips(outputs, robots, num1);
            }
        }
        else {
            arrayFromStream(input, f, isNumber, isSpace);
            num1 = (uint) atoi(input);
            arrayFromStream(input, f, isCharacter, isSpace);
            arrayFromStream(input, f, isNumber, isSpace);
            num2 = (uint) atoi(input);
            giveChip(outputs, robots, num2, num1);
        }
        c = (char) fgetc(f);
    }
    num4 = 1;
    for(uint i = 0; i < OUTPUT_MAX; ++i) {
        for (uint j = 0; j < LARGEST_VALUE; ++j) {
            if(outputs[i][j]) {
                num1 = outputs[i][j];
                num4 *= j;
                break;
            }
        }
    }
    return 1;
}

void startBot(bot *robot){
    robot->chip1ID = EMPTY;
    robot->chip2ID = EMPTY;
    robot->hiTargetID = EMPTY;
    robot->lowTargetID = EMPTY;
}

void giveChip(uint outputs[OUTPUT_MAX][LARGEST_VALUE],
              bot *robots, uint targetID, uint chipID){
    if(EMPTY == (robots[targetID].chip1ID)){
        robots[targetID].chip1ID = chipID;
    }
    else{ // Order chips so that higher value is in chip1ID
        if(chipID > robots[targetID].chip1ID ){
            robots[targetID].chip2ID = robots[targetID].chip1ID;
            robots[targetID].chip1ID = chipID;
        }
        else{
            robots[targetID].chip2ID = chipID;
        }
        /*printf("Robot %i, passes value %i and %i\n", targetID,
               robots[targetID].chip2ID, robots[targetID].chip1ID );*/
        dealChips(outputs, robots, targetID);
    }
}

void dealChips(uint outputs[OUTPUT_MAX][LARGEST_VALUE],
               bot robots[ROBOT_MAX], uint dealerID){
    // If rules aren't set yet wont't try to deal
    static uint outputMultiplicy = 1;
    if(robots[dealerID].hiTargetID == EMPTY) return;
    if(robots[dealerID].hiIsRobot){ // High is robot
        giveChip(outputs, robots, robots[dealerID].hiTargetID,
                 robots[dealerID].chip1ID);
    }
    else{       // High is output
        ++outputs[robots[dealerID].hiTargetID][robots[dealerID].chip1ID];
        if(robots[dealerID].hiTargetID <= 2) {
            outputMultiplicy *= robots[dealerID].chip1ID;
            printf("%i\n", outputMultiplicy );
        }
    }
    if(robots[dealerID].lowIsRobot){ // Low value target is robot
        giveChip(outputs, robots, robots[dealerID].lowTargetID,
                 robots[dealerID].chip2ID);
    }
    else{  //or it can be output
        ++outputs[robots[dealerID].lowTargetID][robots[dealerID].chip2ID];
        if(robots[dealerID].lowTargetID <= 2) {
            outputMultiplicy *= robots[dealerID].chip2ID;
            printf("%i\n", outputMultiplicy);
        }
    }
    robots[dealerID].chip1ID = EMPTY;
    robots[dealerID].chip2ID = EMPTY;
}

int giveRobotRules(bot * robot, uint lowID, type typeLow,
                    uint hiID, type typeHi){
    robot->hiTargetID = hiID;
    robot->hiIsRobot = typeHi;
    robot->lowTargetID = lowID;
    robot->lowIsRobot = typeLow;
    if (robot->chip2ID != EMPTY)
        return 1;
    else {
        return 0;
    }
}

uint arrayFromStream(char array[], FILE *stream,
                     int (*allowedCharacter)(int),
                     int(*ignoreCharacter)(int)){
    char c;
    uint i = 0;
    while(1){
        c = (char)fgetc(stream);
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
    return (('a' <= a) && ('z' >= a)) || (('A' <= a) && ('Z' >= a));
}

int noIgnore(int a){
    return 0;
}

int isNumber(int a){
    return ('0' <= a) &&('9' >= a);
}

int isSpace(int a){
    return a == ' ';
}