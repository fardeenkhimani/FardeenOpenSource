#include "main.h"

#include <stdio.h>
#include <stdlib.h>

#include "gba.h"

#include "images/startImage.h"
#include "images/boxImage.h"
#include "images/endImage.h"

Box playerBox;

enum gba_state {
  START,
  START_TEXT,
  PLAY1,
  PLAY2,
  WIN,
  WIN2,
  LOSE,
  RESTART,
};

int main(void) {
  REG_DISPCNT = MODE3 | BG2_ENABLE;
  // Manipulate REG_DISPCNT here to set Mode 3. //

  // Save current and previous state of button input.
  u32 previousButtons = BUTTONS;
  u32 currentButtons = BUTTONS;

  //initialize time:
  int time = 0;

  int speed = 3;

  //set Title for Start Screen.

  char title[] = "Press ENTER to Start!";
  int goalCol = 100;
  int goalRow = 100;
  int pseudoGoalCol = 100;
  int pseudoGoalRow = 30;
  char buffer[30];

  // Load initial application state
  enum gba_state state = START;

  while (1) {
    currentButtons = BUTTONS; // Load the current state of the buttons


    /* TODO: */
    // Manipulate the state machine below as needed //
    // NOTE: Call waitForVBlank() before you draw

    switch (state) {
      case START:
        time = 0;
        drawFullScreenImageDMA(startImage);
        state = START_TEXT;
        break;
      case START_TEXT:
        drawString(40,65,title,BLACK);
        drawString(70,60,"Chose the right one",BLACK);
        drawString(90,60,"before time runs out!",BLACK);

        if (KEY_DOWN(BUTTON_START, currentButtons)) {
            state = PLAY1;
        }
        if (KEY_DOWN(BUTTON_SELECT, currentButtons)) {
            state = RESTART;
        }
        break;
      case PLAY1:
        waitForVBlank();
        fillScreenDMA(BLACK);

        Box *boxptr, playerBox;
        boxptr = &playerBox;
        (*boxptr).row = 100;
        (*boxptr).col = 20;
        drawImageDMA((*boxptr).row, (*boxptr).col,40,40,boxImage);
        drawRectDMA(goalCol,goalRow,60,60,GRAY);
        drawRectDMA(pseudoGoalRow,pseudoGoalCol,60,60,GRAY);
        state = PLAY2;
        break;
      case PLAY2:
        waitForVBlank();
        drawImageDMA((*boxptr).row, (*boxptr).col, 40, 40, boxImage);
        sprintf(buffer, "Seconds: %d", time / 60);
        drawRectDMA(5, 110, 80, 25, BLACK);
        drawString(5, 110, buffer, WHITE);

        if (KEY_DOWN(BUTTON_UP, currentButtons)) {
          moveBox(boxptr, -speed, 0);
        }
        if (KEY_DOWN(BUTTON_DOWN, currentButtons)) {
          moveBox(boxptr, speed, 0);
        }
        if (KEY_DOWN(BUTTON_RIGHT, currentButtons)) {
          moveBox(boxptr, 0, speed);
        }
        if (KEY_DOWN(BUTTON_LEFT, currentButtons)) {
          moveBox(boxptr, 0, -speed);
          }

        //initialize top left's x and y coordinates.
        int topLeftX = (*boxptr).col;
        int topRightX = topLeftX + 40;
        int topLeftY = (*boxptr).row;
        int topRightY = topLeftY + 40;

        int reachedgoal = 0;

        if (topRightX >= goalCol && topRightX <= goalCol + 60 && topLeftY >= goalRow && topLeftY <= goalRow + 60) {
          reachedgoal = rand() % 2 + 1;
        } else if (topRightX >= goalCol && topRightX <= goalCol + 60 && topRightY >= goalRow && topRightY <= goalRow + 60) {
          reachedgoal = rand() % 2 + 1;
        } else if (topLeftX >= goalCol && topLeftX <= goalCol + 60 && topLeftY >= goalRow && topLeftY <= goalRow + 60) {
          reachedgoal = rand() % 2 + 1;
        } else if (topLeftX >= goalCol && topLeftX <= goalCol + 60 && topRightY >= goalRow && topRightY <= goalRow + 60) {
          reachedgoal = rand() % 2 + 1;
        }

        if (topRightX >= pseudoGoalCol && topRightX <= pseudoGoalCol + 60 && topLeftY >= pseudoGoalRow && topLeftY <= pseudoGoalRow + 60) {
          reachedgoal = rand() % 2 + 1;
        } else if (topRightX >= pseudoGoalCol && topRightX <= pseudoGoalCol + 60 && topRightY >= pseudoGoalRow && topRightY <= pseudoGoalRow + 60) {
          reachedgoal = rand() % 2 + 1;
        } else if (topLeftX >= pseudoGoalCol && topLeftX <= pseudoGoalCol + 60 && topLeftY >= pseudoGoalRow && topLeftY <= pseudoGoalRow + 60) {
          reachedgoal = rand() % 2 + 1;
        } else if (topLeftX >= pseudoGoalCol && topLeftX <= pseudoGoalCol + 60 && topRightY >= pseudoGoalRow && topRightY <= pseudoGoalRow + 60) {
          reachedgoal = rand() % 2 + 1;
        }



        //60Hz so 600 = 10 seconds.
        if (time == 300) {
            state = LOSE;
        }

        if (reachedgoal == 1) {
            fillScreenDMA(BLACK);
            drawImageDMA((*boxptr).row, (*boxptr).col, 40, 40, boxImage);
            state = WIN;
        }
        if (reachedgoal == 2) {
            fillScreenDMA(BLACK);
            drawImageDMA((*boxptr).row, (*boxptr).col, 40, 40, boxImage);
            state = LOSE;
        }
        if (KEY_DOWN(BUTTON_SELECT, currentButtons)) {
          state = RESTART;
        }


        time++;

        break;
      case WIN:
        waitForVBlank();
        drawFullScreenImageDMA(endImage);


        state = WIN2;
        break;
      case WIN2:
        waitForVBlank();
        drawString(40,65,"You won king!!", BLUE);
        sprintf(buffer, "TIME TAKEN: %d", time / 60);
        drawString(5, 140, buffer, BLACK);
        if (KEY_DOWN(BUTTON_SELECT, currentButtons)) {
              state = RESTART;
            }

        break;
      case LOSE:
           fillScreenDMA(RED);
           drawString(40, 95, "GAME OVER LOSER!", BLACK);
           if (KEY_DOWN(BUTTON_SELECT, currentButtons)) {
             state = RESTART;
           }

          break;
      case RESTART:

          state = START;
          break;
    }
    waitForVBlank();
    previousButtons = currentButtons; // Store the current state of the buttons
  }

    UNUSED(previousButtons);

  return 0;
}
void moveBox(Box *b, int row, int col) {
    drawRectDMA((*b).row, (*b).col, 40, 40, BLACK);
      // fillScreenDMA(BLACK);
      if ((((*b).row + row) >= 0) && ((*b).row + row) <= (HEIGHT - 40)) {
        (*b).row += row;
      }
      if ((((*b).col + col) >= 0) && ((*b).col + col) <= (WIDTH - 40)) {
        (*b).col += col;
      }
      drawImageDMA((*b).row, (*b).col, 40, 40, boxImage);
}
