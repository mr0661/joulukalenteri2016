//
// Created by ossis on 21.12.2016.
//

#include <stdio.h>
#include <stdlib.h>
#include <mem.h>
#include <afxres.h>

// Marks what rule type is used in case it needs to be changed
typedef unsigned long long rt;

struct Rule{
    rt banBegin;
    rt banEnd;
};
typedef struct Rule rule;

const char PATH[70] = "C:\\Users\\ossis\\ClionProjects\\joulukalenteri_2016\\20\\input.txt";
const unsigned int MAX_RULES = 1200;
const unsigned int MAX_ROW = 100;
const int BASE = 10;
const rt MAX_IP = 4294967295;

void sort(rule* rules, unsigned int length);

int correctOrder(const rule* r1, const rule* r2);

rt main(){
    FILE* f = fopen(PATH, "r");
    rule rules[MAX_RULES];
    char row[MAX_ROW];
    char* ptr;

    unsigned int index = 0;
    while(fgets(row, MAX_ROW, f)) {
        rules[index].banBegin = strtoull(row, &ptr, BASE);
        rules[index].banEnd = strtoull(ptr + 1, 0, BASE);
        ++index;
    }
    sort(rules, index);
    unsigned int count = 0;
    rt currentSmallest = 0;
    rt smallestRule = 0;
    for(unsigned int i = 0; i < index; ++i){
        if(currentSmallest < rules[i].banBegin){
            if(!smallestRule){ // Assume smallest rule isn't 0
                smallestRule = currentSmallest;
            }
            count += rules[i].banBegin - currentSmallest;

        }
        currentSmallest = max(rules[i].banEnd + 1, currentSmallest);
    }
    count += MAX_IP - (currentSmallest - 1); //if las IP:S aren't blocked, this checks for that
    printf("Available IPs:%u\nSmallest available:%llu", count, smallestRule);
    return 1;
}


// Merge sort, used memory extensive approach, but it should be little faster
void sort(rule* rules, unsigned int length){
    if(length > 2) {
        unsigned int index1 = 0;
        unsigned int index2 = 0;
        unsigned int length1 = length / 2;
        unsigned int length2 = length - length1;
        size_t sizeOfRules = length * sizeof(rule);
        rule *rCopy1 = malloc(sizeOfRules);
        rule *rCopy2 = rCopy1 + length1;
        memcpy(rCopy1, rules, sizeOfRules);
        sort(rCopy1, length1);
        sort(rCopy2, length2);
        for(unsigned int i = 0; i < length; i++){
            if(((index1 < length1) && correctOrder(&rCopy1[index1], &rCopy2[index2])) ||
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
        if(correctOrder(&rules[0], &rules[1])){
            return;
        }
        else{
            rule tmp = rules[0];
            rules[0] = rules[1];
            rules[1] = tmp;
            return;
        }

    }
}

int correctOrder(const rule* r1, const rule* r2){
    if(r1->banBegin < r2->banBegin){
        return 1;
    }
    else if(r1->banBegin > r2->banBegin){
        return 0;
    }
    if(r1->banEnd < r2->banEnd){
        return 1;
    }
    else if(r1->banEnd > r2->banEnd){
        return 0;
    }
    return 1;
}