//
// Created by rober on 25.04.2019.
//

#ifndef DROGI_INTLIST_H
#define DROGI_INTLIST_H

typedef struct IntegerList IntList;

struct IntegerList {
    int val;
    IntList *next;
};

IntList* newIntList(int val);

int addIntAfter(IntList *where, int val);

void addIntList(IntList *where, IntList *list);

void freeIntList(IntList *list);

void removeNextInt(IntList *it);

IntList* nextInt(IntList *it);


#endif //DROGI_INTLIST_H
