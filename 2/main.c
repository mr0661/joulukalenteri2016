//
// Created by ossis on 9.12.2016.
//
#include <stdio.h>

int MAX_KEY = 2;
int MIN_KEY = 0;

const char UP = 'U';
const char DOWN = 'D';
const char RIGHT = 'R';
const char LEFT = 'L';
const char FILENAME[70] = "C:\\Users\\ossis\\ClionProjects\\joulukalenteri_2016\\2\\input.txt";
                                              //  012
const char NUMPAD[3][3] = { {'7','4','1'},    //2 123
                            {'8','5','2'},    //1 456 - Actual keypad
                            {'9','6','3'} };  //0 789
const int PASSWORD_MAX_LENGTH = 10;

int isDirection(char c);

int main(){
    FILE *f = fopen(FILENAME,"r");
    char password[PASSWORD_MAX_LENGTH];
    int count = 0;

    while(1){
        int x = 1;
        int y = 1;
        while(1){
            char c = fgetc(f);
            if(isDirection(c)){
                if(c == RIGHT){
                    if(x < MAX_KEY) x++;
                }
                else if(c == LEFT){
                    if( x > MIN_KEY ) x--;
                }
                else if(c == UP){
                    if( y < MAX_KEY ) y++;
                }
                else if(c == DOWN){
                    if( y > MIN_KEY ) y--;
                }
            }
            else if(c == EOF){
                password[count] = NUMPAD[x][y];
                password[count+1] = '\0';
                printf("Keycode: %s \n", password);
                return 1;
            }
            else{
                printf("%c %c | ", x+48, y+48);
                password[count] = NUMPAD[x][y];
                count++;
            }
        }
    }
}

int isDirection(char c){
    return c == RIGHT || c == LEFT || c == UP || c == DOWN;
}