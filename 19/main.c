//
// Created by ossis on 19.12.2016.
//

#include <stdio.h>
#include <mem.h>

#define ELF_COUNT 3017957

int main(){
    unsigned int current = 0;
    static int elfPresents[ELF_COUNT];
    for(unsigned int id = 0; id < ELF_COUNT; ++id) {
        elfPresents[id] = id + 1;
    } // Give id to each elf
    elfPresents[ELF_COUNT] = 0; // 0 Marks that Elf is not present
    unsigned int elfsLeft = ELF_COUNT;
    unsigned int removeLocation;
    unsigned int halfWayPoint = elfsLeft / 2;
    while(1 < elfsLeft) {
        removeLocation = (current + halfWayPoint) % elfsLeft;
        memcpy(elfPresents + removeLocation,
               elfPresents + removeLocation + 1,
               sizeof(int) * (elfsLeft - removeLocation));
        halfWayPoint = --elfsLeft / 2;
        if(current < removeLocation){
            ++current;
        }
        //current %= elfsLeft;
        current = elfPresents[current] ? current : 0;
    }
    printf("\n%i", elfPresents[0]);
    return elfPresents[0];
}