//
// Created by ossis on 22.12.2016.
//


#include <stdlib.h>
#include <stdio.h>
#include <mem.h>

enum Status{SMALL, VSMALL, LARGE, EMPTY, IMPORTANT};
typedef enum Status status;
const char* PATH = "C:\\Users\\ossis\\ClionProjects\\joulukalenteri_2016\\22\\input.txt";
const char* input = "/dev/grid/node-x31-y23  510T  496T    14T   97%";
const int INPUT_LENGTH = 50;
const int X_LENGTH = 32;
const int Y_LENGTH = 30;
const int X_START = 31;
const int Y_START = 0;
const int X_END = 0;
const int Y_END = 0;

const char SMALL_CHAR = '.'; // Notation used in puzzle
const char VSMALL_CHAR = 'X';
const char LARGE_CHAR = '#';
const char EMPTY_CHAR = '_';
const char IMPORTANT_CHAR = 'G';
const char END_CHAR = ':';

struct Node{
    int x;
    int y;
    int used;
    int avail;
    status stat;
};

typedef struct Node node;

// sorts nodes by Available space
void sort1(node **nodeptr);

// sorts nodes by Used space
void sort2(node **nodeptr);

// merge sort
void sort(node** rules, unsigned int length, int (*correctOrder)(const node*, const node*));

// returns 1 if rule 1 should be before rule2
int checkAvail(const node* rule1, const node* rule2);

// returns 1 if rule 1 should be before rule2
int checkUsed(const node* rule1, const node* rule2);

// Prints nodes
void printNodes(node *nodes);

int main(){
    FILE* f = fopen(PATH, "r");
    node nodes[X_LENGTH * Y_LENGTH]; // Matrix of certain length
    node *nodePtr1[X_LENGTH * Y_LENGTH];
    node *nodePtr2[X_LENGTH * Y_LENGTH];
    char row[INPUT_LENGTH];
    char* ptr;

    while(fgets(row, INPUT_LENGTH, f)){
        long x = strtol(row + 16, &ptr, 10);
        long y = strtol(ptr + 2, &ptr, 10);
        int i = Y_LENGTH * x + y;
        (nodes + i)->used = strtol(row + 28, &ptr, 10);
        (nodes + i)->avail = strtol(row + 34, &ptr, 10);
        (nodes + i)->x = x;
        (nodes + i)->y = y;
        (nodes + i)->stat = LARGE; // Assume large unless shown otherwise
    }
    for(int index = 0; index < X_LENGTH * Y_LENGTH ; ++index){
        nodePtr1[index] = nodes + index;
        nodePtr2[index] = nodes + index;
    }
    sort1(nodePtr1);
    sort2(nodePtr2);
    int count = 0;
    int targetSize = nodes[Y_LENGTH * X_START + Y_START].used;
    int tempSize;
    for(int index = 0; index < X_LENGTH * Y_LENGTH ; ++index){
        int countSame = 1;
        for(int index2 = 0; index2 < X_LENGTH * Y_LENGTH ; ++index2) {
            if((nodePtr1[index]->x != nodePtr1[index2]->x) || (nodePtr1[index]->y != nodePtr1[index2]->y)){
                if ((nodePtr1[index]->avail >= nodePtr2[index2]->used) && (nodePtr2[index2]->used > 0) ) {
                    if(nodePtr2[index2]->stat != EMPTY) {
                        nodePtr2[index]->stat = EMPTY;
                        tempSize = nodes[Y_LENGTH * nodePtr2[index2]->x + nodePtr2[index2]->y].avail +
                                   nodes[Y_LENGTH * nodePtr2[index2]->x + nodePtr2[index2]->y].used;
                        if(tempSize >= targetSize){
                            nodePtr2[index2]->stat = SMALL;
                        }
                        else{
                            nodePtr2[index2]->stat = VSMALL;
                        }
                    }
                    ++count;
                }
                else break;
                countSame = 0;
            }
        }
        if(countSame) break;
    }
    nodes[Y_LENGTH * X_START + Y_START].stat = IMPORTANT;
    printf("available: %i\n", count);
    printNodes(nodes);
    return 1;
}

void printNodes(node *nodes){
    int x = 0;
    printf("   ");
    for(int i = 0; i < Y_LENGTH; i++) (i / 10 != 0) ? printf("%i ", i / 10) : printf("  ") ;
    printf("\n   ");
    for(int i = 0; i < Y_LENGTH; i++) printf("%i ", i % 10);
    printf("\n0  ");
    for(int i = 0; i < X_LENGTH * Y_LENGTH ; ++i){
        if(x != nodes[i].x){
            x = nodes[i].x;
            printf("\n%i ", x);
            if( x < 10) printf(" ");
        }
        if(nodes[i].x == X_END && nodes[i].y == Y_END){
            printf("%c", END_CHAR);
        }
        else if(nodes[i].stat == EMPTY){
            printf("%c", EMPTY_CHAR);
        }
        else if(nodes[i].stat == VSMALL){
            printf("%c", VSMALL_CHAR);
        }
        else if(nodes[i].stat == SMALL){
            printf("%c", SMALL_CHAR);
        }
        else if(nodes[i].stat == LARGE){
            printf("%c", LARGE_CHAR);
        }
        else if(nodes[i].stat == IMPORTANT){
            printf("%c", IMPORTANT_CHAR);
        }
        printf(" ");
    }
}
//45
void sort1(node **nodeptr){
    sort(nodeptr, Y_LENGTH * X_LENGTH, checkAvail);
}

void sort2(node **nodeptr){
    sort(nodeptr, Y_LENGTH * X_LENGTH, checkUsed);
}

void sort(node** rules, unsigned int length, int (*correctOrder)(const node*, const node*)){
    if(length > 2) {
        unsigned int index1 = 0;
        unsigned int index2 = 0;
        unsigned int length1 = length / 2;
        unsigned int length2 = length - length1;
        size_t sizeOfRules = length * sizeof(node);
        node **rCopy1 = malloc(sizeOfRules);
        node **rCopy2 = rCopy1 + length1;
        memcpy(rCopy1, rules, sizeOfRules);
        sort(rCopy1, length1, correctOrder);
        sort(rCopy2, length2, correctOrder);
        for(unsigned int i = 0; i < length; i++){
            if(((index1 < length1) && correctOrder(rCopy1[index1], rCopy2[index2])) ||
               (index2 >= length2)){
                rules[i] = rCopy1[index1];
                ++index1;
            }
            else{
                rules[i] = rCopy2[index2];
                ++index2;
            }
        }
        free(rCopy1);
    }
    else if(length == 2){
        if(correctOrder(rules[0], rules[1])){
            return;
        }
        else{
            node* tmp = rules[0];
            rules[0] = rules[1];
            rules[1] = tmp;
            return;
        }
    }
}

int checkAvail(const node* rule1, const node* rule2){
    if(rule1->avail >= rule2->avail) return 1;
    return 0;
}

int checkUsed(const node* rule1, const node* rule2){
    if(rule1->used <= rule2->used) return 1;
    return 0;
}