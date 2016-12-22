//
// Created by ossis on 22.12.2016.
//

#include <mem.h>
#include <malloc.h>
#include <stdio.h>

enum Direction{RIGHT, LEFT};
enum Command{SWAP_POSTION, SWAP_LETTER, ROTATE, ROTATE_BASED, REVERSE, MOVE};

typedef enum Command command;
typedef enum Direction dir;
struct Operation{
    command c;  //
    int num1;  //First argument given
    int num2;   //Latter argument given
};

typedef struct Operation operation;


const char PATH[70] = "C:\\Users\\ossis\\ClionProjects\\joulukalenteri_2016\\21\\input.txt";
const int MAX_OPERATIONS = 100;
const int INPUT_MAX = 100;
const int PASSWORD_MAX = 20;
const char *PASSWORD1 = "abcdefgh";
const char *PASSWORD2 = "fbgdceah";

const char *SWAP_POSTION_COM1 = "swap position ";
const char *SWAP_POSTION_COM2 = " with position ";
const char *SWAP_LETTER_COM1  = "swap letter ";
const char *SWAP_LETTER_COM2  = " with letter ";
const char *ROTATE_LEFT_COM1  = "rotate left ";
const char *ROTATE_RIGHT_COM1 = "rotate right ";
const char *ROTATE_BASED_COM1 = "rotate based on position of letter ";
const char *REVERSE_COM1      = "reverse positions ";
const char *REVERSE_COM2      = " through ";
const char *MOVE_COM1         = "move position ";
const char *MOVE_COM2         = " to position ";

void swapPosition(char * target, int pos1, int pos2);

void swapLetter(char * target, char let1, char let2);

void rotate(char * target, int steps, dir direction);

void rotateByLetter(char* target, char letter);

void unRotateByLetter(char* target, char letter);

void reversePosition(char* target, int pos1, int pos2);

void movePosition(char* target, int pos1, int pos2);

void extractOperation(char* input, operation * o);

void doOperation(char* password, operation * o);

void unDoOperation(char* password, operation * o);

int main(){
    char password1[PASSWORD_MAX];
    strcpy(password1, PASSWORD1);
    char password2[PASSWORD_MAX];
    strcpy(password2, PASSWORD2);
    char input[INPUT_MAX];
    FILE * f = fopen(PATH, "r");
    operation o[MAX_OPERATIONS];
    int index = 0;
    while(fgets(input, INPUT_MAX, f)){
        extractOperation(input, o + index);
        doOperation(password1, o + index);
        ++index;
    }
    int i = index;
    while( i >= 0 ){
        unDoOperation(password2, o + i--);
    }
    printf("Scrambling: ");
    printf(password1);
    printf("\nUnscrambling: ");
    printf(password2);

    printf("\n");
    return 1;
}

void swapPosition(char * target, int pos1, int pos2){
    char tmp = target[pos1];
    target[pos1] = target[pos2];
    target[pos2] = tmp;
}

void swapLetter(char * target, char let1, char let2){
    for(int index = 0; target[index] != '\0'; ++index){
        if(target[index] == let1){
            target[index] = let2;
        }
        else if(target[index] == let2){
            target[index] = let1;
        }
    }
    return;
}

void rotate(char * target, int steps, dir direction){
    int length = strlen(target);
    steps %= length;
    if(steps == 0) return;
    int moveBeginTo = (direction == LEFT ? steps : length - steps);
    char* ptr = malloc(sizeof(char) * (1 + length));
    strcpy(ptr, target);
    for(int i = 0; i < length; ++i){
        target[i] = ptr[moveBeginTo];
        moveBeginTo = (moveBeginTo + 1) % length;
    }
    free(ptr);
}

void rotateByLetter(char* target, char letter){
    int index;
    for(index = 0; target[index] != letter ; ++index);
    (index >= 4) ? rotate(target, index + 2, RIGHT) : rotate(target, index + 1, RIGHT);
}

void unRotateByLetter(char* target, char letter){
    char* ptr = malloc(sizeof(char) * (strlen(target) + 1));
    int index = 0;
    while(1) {
        strcpy(ptr, target);
        rotate(ptr, index, LEFT);
        rotateByLetter(ptr, letter);
        if(strstr(ptr, target)){
            rotate(target, index, LEFT);
            return;
        }
        index++;
    }
}

void reversePosition(char* target, int pos1, int pos2){
    int length = strlen(target);
    char *ptr = malloc((1 + length) * sizeof(char));
    strcpy(ptr, target);
    int i;
    int j = pos2;
    for(i = pos1; i != pos2; i = (i + 1) % length){
        target[i] = ptr[j];
        j--;
        if(j < 0) j += length;
    }
    target[pos2] = ptr[pos1];
    free(ptr);
}

void movePosition(char* target, int pos1, int pos2){
    char tmp = target[pos1];
    while(pos1 < pos2){
        target[pos1] = target[pos1 + 1];
        pos1++;
    }
    while(pos1 > pos2){
        target[pos1] = target[pos1 - 1];
        pos1--;
    }
    target[pos1] = tmp;
}

void extractOperation(char* input, operation * o){
    char *ptr;
    if(strstr(input, SWAP_POSTION_COM1)){
        o->c = SWAP_POSTION;
        o->num1 = strtol(input + strlen(SWAP_POSTION_COM1), &ptr, 10);
        o->num2 = strtol(ptr + strlen(SWAP_POSTION_COM2), &ptr, 10);
    }
    else if(strstr(input, SWAP_LETTER_COM1)){
        o->c = SWAP_LETTER;
        o->num1 = *(input + strlen(SWAP_LETTER_COM1));
        o->num2 = *(input + strlen(SWAP_LETTER_COM1) + strlen(SWAP_LETTER_COM2) + 1);
    }
    else if(strstr(input, ROTATE_RIGHT_COM1)){
        o->c = ROTATE;
        o->num1 = RIGHT;
        o->num2 = strtol(input + strlen(ROTATE_RIGHT_COM1), &ptr, 10);
    }
    else if(strstr(input, ROTATE_LEFT_COM1)){
        o->c = ROTATE;
        o->num1 = LEFT;
        o->num2 = strtol(input + strlen(ROTATE_LEFT_COM1), &ptr, 10);
    }
    else if(strstr(input, ROTATE_BASED_COM1)){
        o->c = ROTATE_BASED;
        o->num1 = *(input + strlen(ROTATE_BASED_COM1));
    }
    else if(strstr(input, REVERSE_COM1)){
        o->c = REVERSE;
        o->num1 = strtol(input + strlen(REVERSE_COM1), &ptr, 10);
        o->num2 = strtol(ptr + strlen(REVERSE_COM2), &ptr, 10);
    }
    else if(strstr(input, MOVE_COM1)){
        o->c = MOVE;
        o->num1 = strtol(input + strlen(MOVE_COM1), &ptr, 10);
        o->num2 = strtol(ptr + strlen(MOVE_COM2), &ptr, 10);
    }
}

void doOperation(char* password, operation * o){
    if(o->c == SWAP_POSTION){
        swapPosition(password, o->num1, o->num2);
    }
    else if(o->c == SWAP_LETTER){
        swapLetter(password, (char)o->num1, (char)o->num2);
    }
    else if(o->c == ROTATE){
        rotate(password, o->num2, (dir)o->num1);
    }
    else if(o->c == ROTATE_BASED){
        rotateByLetter(password, (char)o->num1);
    }
    else if(o->c == REVERSE){
        reversePosition(password, o->num1, o->num2);
    }
    else if(o->c == MOVE){
        movePosition(password, o->num1, o->num2);
    }
}

void unDoOperation(char* password, operation * o){
    if(o->c == SWAP_POSTION){
        swapPosition(password, o->num1, o->num2);
    }
    else if(o->c == SWAP_LETTER){
        swapLetter(password, (char)o->num1, (char)o->num2);
    }
    else if(o->c == ROTATE){
        rotate(password, o->num2, (o->num1 == RIGHT) ? LEFT : RIGHT );
    }
    else if(o->c == ROTATE_BASED){
        unRotateByLetter(password, (char)o->num1);
    }
    else if(o->c == REVERSE){
        reversePosition(password, o->num1, o->num2);
    }
    else if(o->c == MOVE){
        movePosition(password, o->num2, o->num1);
    }
}