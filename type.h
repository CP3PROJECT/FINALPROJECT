#ifndef TYPE_H
#define TYPE_H

typedef struct {
    char atkName[50];
    char defName[50];
    double multiplier;
} TypeEffect;

typedef struct {
    char name[50];
    TypeEffect effects[19];
} Type;

#endif