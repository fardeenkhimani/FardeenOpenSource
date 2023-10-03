#ifndef MAIN_H
#define MAIN_H

#include "gba.h"

    typedef struct box {
        int row;
        int col;
    }Box;

    void moveBox(Box *boxptr, int row, int col);
    int rand(void);

/*
* For example, for a Snake game, one could be:
*
* struct snake {
*   int heading;
*   int length;
*   int row;
*   int col;
* };
*
* Example of a struct to hold state machine data:
*
* struct state {
*   int currentState;
*   int nextState;
* };
*
*/

#endif
