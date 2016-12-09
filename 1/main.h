//
// Created by ossis on 8.12.2016.
//

#ifndef JOULUKALENTERI2016_MAIN_H
#define JOULUKALENTERI2016_MAIN_H
typedef enum DIRECTION{NORTH, SOUTH, WEST, EAST} Direction;
// Place your own path here
const char INPUT_FILENAME[65] = "C:\\Users\\ossis\\ClionProjects\\joulukalenteri_2016\\1\\input.txt";
const char SINGLE_INPUT_MAX_LENGTH = 5;
const unsigned int MAX_POSITIONS = 200;

// Returns absolute value
int abs(int a);

// Moves position(pos) towards direrction(dir), for amount of length(len)
void move(int pos[], Direction dir, unsigned int len );

// Interprets left-right direction(lr), and changes compass direction(dir)
// accordingly. Returns the new Direction.
Direction newDirection(char lr,Direction dir);

#endif //JOULUKALENTERI2016_MAIN_H
