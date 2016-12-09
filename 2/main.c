//
// Created by ossis on 9.12.2016.
//
#include <stdio.h>

/*
// Task 1:
int MAX_KEY[3] = [2,2,2];
int MIN_KEY[3] = [0,0,0];
                                              //  012
const char NUMPAD[3][3] = { {'7','4','1'},    //2 123
                            {'8','5','2'},    //1 456 - Actual keypad
                            {'9','6','3'} };  //0 789
int X_START = 1
int Y_START = 1
*/

// Task 2:
int MAX_KEY[5] = {2,3,4,3,2};
int MIN_KEY[5] = {2,1,0,1,2};
const char NUMPAD[5][5] =   {{'F','F','5','F','F'},
                             {'F','A','6','2','F'},
                             {'D','B','7','3','1'},
                             {'F','C','8','4','F'},
                             {'F','F','9','F','F'}};
int X_START = 0;
int Y_START = 2;

const char UP = 'U';
const char DOWN = 'D';
const char RIGHT = 'R';
const char LEFT = 'L';
const char FILENAME[70] = "C:\\Users\\ossis\\ClionProjects\\joulukalenteri_2016\\2\\input.txt";
const int PASSWORD_MAX_LENGTH = 10;

int isDirection(char c);

int main(){
    FILE *f = fopen(FILENAME,"r");
    char password[PASSWORD_MAX_LENGTH];
    int count = 0;

    while(1){
        int x = X_START;
        int y = Y_START;
        while(1){
            char c = fgetc(f);
            if(isDirection(c)){
                if(c == RIGHT){
                    if(x < MAX_KEY[y]) x++;
                }
                else if(c == LEFT){
                    if( x > MIN_KEY[y]) x--;
                }
                else if(c == UP){
                    if( y < MAX_KEY[x]) y++;
                }
                else if(c == DOWN){
                    if( y > MIN_KEY[x]) y--;
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