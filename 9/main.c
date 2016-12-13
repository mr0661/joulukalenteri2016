//
// Created by ossis on 12.12.2016.
//

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Task warned that result might be large :)
typedef unsigned long long ulong;

const char PATH[70] = "C:\\Users\\ossis\\ClionProjects\\joulukalenteri_2016\\9\\input.txt";
const char MAX_NUMBER_LENGTH = 5;
const ulong OFF = ULONG_LONG_MAX; // Used to turn off maxDistance in countFromStream

// Saves stream into array. Saves all allowedCharacters, ignoreCharacters
// are ignored. From part 4.
ulong arrayFromStream(char array[], FILE *stream, int (*allowedCharacter)(int), int(*ignoreCharacter)(int));

// Counts from stream, until something else than allowed character or
// ignore character or if maximum has been reached, is maxDistance= -1, it is
// not used
ulong countFromStream(FILE *stream, int (*allowedCharacter)(int), int(*ignoreCharacter)(int), ulong maxDistance);

// simple rules that check certain conditions
int isCharacter(int);
int noIgnore(int);
int isNumber(int a);

// Analyses section length
ulong countSection(FILE* stream, ulong length);

int main(){
    FILE* f = fopen(PATH, "r");
    char number[MAX_NUMBER_LENGTH];
    char c;
    ulong num1;
    ulong num2;
    ulong count = countFromStream(f, isCharacter, noIgnore, OFF);

    c = (char)fgetc(f);
    while(c == '('){
        arrayFromStream(number, f, isNumber, noIgnore);
        num1 = (ulong)atoi(number);
        fgetc(f); // remove 'x
        arrayFromStream(number, f, isNumber, noIgnore);
        num2 = (ulong)atoi(number);
        fgetc(f); // remove ')'
        count += num2 * countSection(f, num1);
        count += countFromStream(f, isCharacter, noIgnore, OFF);
        c = (char)fgetc(f);
    }
    printf("Size of decompressed file:\n %llu\n", count);
    return 1;
}

ulong countSection(FILE* stream, ulong length){
    char c;
    char number[MAX_NUMBER_LENGTH];
    ulong num1;
    ulong num2;
    ulong position = 0;
    ulong count = (ulong)countFromStream(stream, isCharacter, noIgnore, length);
    if(count >= length){
        return count;
    }
    position = count;
    c = (char) fgetc(stream); // We must have reached to bracket.
    while(c == '(') {
        ++position; //keep track of position

        position += arrayFromStream(number, stream, isNumber, noIgnore);
        num1 = (ulong)atoi(number);
        fgetc(stream); // remove 'x'
        ++position;
        position += arrayFromStream(number, stream, isNumber, noIgnore);
        num2 = (ulong)atoi(number);
        fgetc(stream); // remove ')'
        ++position;

        position += num1;
        num1 = countSection(stream, num1);
        count += num1 * num2;
        num1 = (ulong)countFromStream(stream,isCharacter,noIgnore, length - position);
        count += num1;
        position += num1;
        c = (char) fgetc(stream);
        if(length == position) break;
    }
    ungetc(c, stream);
    return count;
}

ulong countFromStream(FILE *stream, int (*allowedCharacter)(int), int(*ignoreCharacter)(int), ulong maxDistance){
    int c;
    ulong i = 0;
    while(maxDistance){
        c = fgetc(stream);
        if(allowedCharacter(c)){
            ++i;
        }
        else if(!ignoreCharacter(c)) {
            ungetc(c, stream);
            return i;
        }
        if(maxDistance != OFF){
            if(maxDistance <= i){
                return maxDistance;
            }
        }
    }
    return maxDistance;
}

ulong arrayFromStream(char array[], FILE *stream, int (*allowedCharacter)(int), int(*ignoreCharacter)(int)){
    char c;
    ulong i = 0;
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
