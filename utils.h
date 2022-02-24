#ifndef DEF_UTILS
#define DEF_UTILS

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

#define TRUE 1
#define FALSE 0

void choiceError();

void setRandomSeed();

int randomInt(int min, int max);

void printTitle(char* title);

#endif
