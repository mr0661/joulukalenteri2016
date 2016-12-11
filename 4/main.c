//
// Created by ossis on 10.12.2016.
//

#include <stdio.h>
#include <stdlib.h>

struct AlphabetCount{
    char c;
    int count;
};

typedef struct AlphabetCount ac;

const char END_CHARACTER = '\0';
const char FILEPATH[70] = "C:\\Users\\ossis\\ClionProjects\\joulukalenteri_2016\\4\\input.txt";
const char SAVE_PATH[70] = "C:\\Users\\ossis\\ClionProjects\\joulukalenteri_2016\\4\\output.txt";
const int MAX_ROOM_CODE_LENGTH = 70;
const int MAX_ID_LENGTH = 7;
const int CHECKSUM_LENGTH = 5;
const int MAX_CHARACTERS = 26; // Total count of characters
const int MIN_CHARACTER = 'a'; // Smallest character
const int MAX_CHARACTER = 'z'; // Largest character

void addToArray(ac array[], const char c);
int isCharacter(int c);

// Saves stream into array. Saves all allowedCharacters, ignoreCharacters
// are ignored, but
int arrayFromStream(char array[], FILE *stream, int (*allowedCharacter)(int), int(*ignoreCharacter)(int));

// sorts array based on simple rules
int sortArray(ac array[]);

// logic which is used to sort
int correctSpot(ac n, ac old);

// Clean stream until character matching with allowedCharacter found
int cleanStream(FILE *stream, int(*allowedCharacter)(int));
//Checks if character is a dash
int isDash(int c);
//Checks if character is number character
int isNum(int c);

// Return always false independently on given value
int noIgnore(int i);

// shifts any character forward equal to shift, z->a, only lowercase
// letters
int shiftChar(int c, int shift);

// shift array
void shiftArray(char array[], int shift);

int main(){
    ac a[MAX_CHARACTERS + 1];
    FILE *f = fopen(FILEPATH,"r");
    FILE *output = fopen(SAVE_PATH, "w+");
    char roomcode[MAX_ROOM_CODE_LENGTH];
    char number[MAX_ID_LENGTH];
    char checksum[CHECKSUM_LENGTH];
    int length;
    int correctOrder;
    char c = ' ';
    int sum = 0;

    while (1){
        a[0].c = END_CHARACTER; // in practise nulls ac -array
        // first save 'room code'
        length = arrayFromStream(roomcode, f, isCharacter, isDash);
        for(int i = 0; i < length; ++i){
            addToArray(a, roomcode[i]);
        }
        if(!length){

            return sum;
        }
        sortArray(a);
        // second save room id
        length = arrayFromStream(number, f, isNum, isDash);

        // third save checksum
        fgetc(f); // removes starting bracket
        arrayFromStream(checksum, f, isCharacter, noIgnore);
        correctOrder = 1;
        for(int i = 0; i < CHECKSUM_LENGTH; ++i){
            if(checksum[i] != a[i].c){
                correctOrder = 0;
                break;
            }
        }
        if (correctOrder) {
            sum += atoi(number);
            shiftArray(roomcode, atoi(number));
            printf(roomcode);
            printf("\n");
            fputs(roomcode, output);
            fputs(number, output);
            fputc('\n', output);
        }
        cleanStream(f, isCharacter);
    }
}


void addToArray(ac array[], const char characer){
    for(int i = 0; i < MAX_CHARACTERS; i++){
        if(array[i].c == characer){
            ++array[i].count;
            return;
        }
        else if(array[i].c == END_CHARACTER) {
            array[i].c = characer;
            array[i].count = 1;
            array[i + 1].c = END_CHARACTER;
            return;
        }
    }
    printf("Error: ac array not initialized");
    return;
}

int isCharacter(int c){
    if(c <= MAX_CHARACTER && c >= MIN_CHARACTER){
        return 1;
    }
    else{
        return 0;
    }
}

int isDash(int c){
    return c == '-';
}

int arrayFromStream(char array[], FILE *stream, int (*allowedCharacter)(int), int(*ignoreCharacter)(int)){
    int c;
    int i = 0;
    while(1){
        c = fgetc(stream);
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

int cleanStream(FILE *stream, int(*allowedCharacter)(int)){
    int c;
    while(1){
        c = fgetc(stream);
        if(allowedCharacter(c)){
            ungetc(c,stream);
            return 1;
        }
        else if(c == EOF){
            return 0;
        }
    }
}

int isNum(int i){
    return (i >= 48) && (i <= 57);
}

int noIgnore(int i){
    return 0;
}

// Sort using insertion sort (arrays are small)
int sortArray(ac array[]){
    // find length of array
    int length = 0;
    ac * a;
    int *indexes;

    while(array[length].c != END_CHARACTER){
        length++;
    }
    a = (ac *) malloc(sizeof(ac) * length);
    indexes = (int *) malloc(sizeof(int) * length);
    for(int i = 0; i < length ; ++i){
        indexes[i] = i;
        a[i] = array[i];
    }
    for(int i = 0; i < length; ++i){
        for(int j = 0; j < i; ++j){
            if (correctSpot(array[indexes[i]],array[indexes[j]])){
                for(int k = i; k > j; --k ){
                    indexes[k] = indexes[k - 1];
                }
                indexes[j] = i;
                break;
            }
        }
    }

    for(int i = 0; i < length; ++i ){
        array[i] = a[indexes[i]];
    }
    free(a);
    return length;

}
int correctSpot(ac n, ac old){
    if(n.count > old.count){
        return 1;
    }
    else if(n.count < old.count){
        return 0;
    }
    else if( n.c < old.c){
        return 1;
    }
    else{
        return 0;
    }
}

void shiftArray(char array[], int shift){
    int i = 0;
    while(array[i] != '\0'){
        array[i] = shiftChar(array[i], shift);
        i++;
    }
}

int shiftChar(int c, int shift){
    c = c - MIN_CHARACTER + shift;
    char value = (c % (MAX_CHARACTER - MIN_CHARACTER + 1)) + MIN_CHARACTER;
    return (c % (MAX_CHARACTER - MIN_CHARACTER + 1)) + MIN_CHARACTER;
}