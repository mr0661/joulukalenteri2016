//
// Created by ossis on 23.12.2016.
//

//
// Created by ossis on 17.12.2016.
//

#include <stdio.h>
#include <mem.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>

enum Operator{CPY, INC, DEC, JNZ, TGL};

const char REGISTER_START_VALUE = 0;
const char *COPY_STR = "cpy";
const char *INCREMENT_STR = "inc";
const char *DECREMENT_STR = "dec";
const char *JUMP_STR = "jnz";
const char *TOGGLE_STR = "tgl";
const int NULL_REG_ID = CHAR_MAX;
const char ID_HASH = 'a';
const int AFTER_COMMAND_LOCATION = 4;
const int BASE = 10;
const char *PATH = "C:\\Users\\ossis\\ClionProjects\\joulukalenteri_2016\\23\\input.txt";

const unsigned int COMMAND_MAX = 100;
const unsigned int REGISTER_MAX = 5;
const unsigned int ROW_MAX= 30;
typedef enum Operator operator;

struct Command{
    operator o;
    char regID1;
    char regID2;
    int value1;
    int value2;
};
typedef struct Command com;

void makeCommand(com *new, char input[]);

void tgl(com *command);
void cpy(int value, int *reg);
void inc(int *reg);
void dec(int *reg);
void jnz(unsigned int *programPointer, int condition, int jump);

int main() {
    FILE* f = fopen(PATH, "r+");
    com commands[COMMAND_MAX];
    int registers[REGISTER_MAX];
    memset(registers, REGISTER_START_VALUE, REGISTER_MAX * sizeof(int));
    registers['c' - ID_HASH] = 1; // For part 2
    char row[ROW_MAX];
    unsigned int programLength = 0;
    unsigned int programPointer = 0;
    while (1) {
        fgets(row, ROW_MAX, f);
        makeCommand(commands + programLength, row);
        if(feof(f)){
            break;
        }
        ++programLength;
    }

    while(programPointer <= programLength){
        if(commands[programPointer].o == CPY){
            if(commands[programPointer].regID1 != NULL_REG_ID){
                cpy(*(registers + commands[programPointer].regID1), registers + commands[programPointer].regID2);
            }
            else{
                cpy(commands[programPointer].value1, registers + commands[programPointer].regID2);
            }
        }
        else if(commands[programPointer].o == JNZ){
            jnz(&programPointer,
                commands[programPointer].regID1 == NULL_REG_ID ? commands[programPointer].value1 : *(registers + commands[programPointer].regID1),
                commands[programPointer].regID2 == NULL_REG_ID ? commands[programPointer].value2 : *(registers + commands[programPointer].regID2));
            continue;
        }
        else if(commands[programPointer].o == INC){
            inc(registers + commands[programPointer].regID1);
        }
        else if(commands[programPointer].o == DEC){
            dec(registers + commands[programPointer].regID1);
        }
        programPointer++;
    }

    return 0;
}

void makeCommand(com *new, char input[]){
    char *ptr1;
    char *ptr2;
    if(!memcmp(input, COPY_STR, strlen(COPY_STR))||
       !memcmp(input, JUMP_STR, strlen(JUMP_STR))){
        if(!memcmp(input, COPY_STR, strlen(COPY_STR))){
            new->o = CPY;
        }
        else{
            new->o = JNZ;
        }
        if (isalpha(input[strlen(JUMP_STR) + 1])){
            new->regID1 = input[strlen(JUMP_STR) + 1] - ID_HASH;
            ptr1 = input + strlen(JUMP_STR) + 3;
        }
        else{
            new->regID1 = NULL_REG_ID;
            new->value1 = strtol(input + strlen(COPY_STR) + 1, &ptr1, BASE);
            ++ptr1;
        }
        if(isalpha(ptr1[0])){
            new->regID2 = ptr1[0] - ID_HASH;
        }
        else{
            new->regID2 = NULL_REG_ID; // Mark that register is not used
            new->value2 = strtol(ptr1, &ptr2, BASE);
        }
        return;
    }
    if(!memcmp(input, INCREMENT_STR, strlen(INCREMENT_STR))) {
        new->o = INC;
    }
    if(!memcmp(input, DECREMENT_STR, strlen(DECREMENT_STR))) {
        new->o = DEC;
    }
    new->regID1 = input[strlen(INCREMENT_STR) + 1] - ID_HASH;
    return;

}

void tgl(com *command){
    if(command->o == TGL){

    }
    else if(command->o == INC){

    }
    else if(command->o == DEC){

    }
    else if(command->o == JNZ){

    }
    else if(command->o == CPY){

    }
}

void cpy(int value, int *reg){
    *reg = value;
}
void inc(int *reg){
    ++(*reg);
}

void dec(int *reg){
    --(*reg);
}

void jnz(unsigned int *programPointer, int condition, int jump){
    if(condition) {
        *programPointer += jump;
    }
    else{
        ++(*programPointer);
    }
}