/*
*  Mr Pass.  Brain the size of a planet!
*
*  Proundly Created by Richard Buckland
*  Share Freely Creative Commons SA-BY-NC 3.0.
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Game.h"
#include "mechanicalTurk.h"

#define STUDENT_MJ  3
#define STUDENT_MTV 4
#define STUDENT_MMONEY 5
action decideAction (Game g) {
    action nextAction;
    int player = getWhoseTurn(g);
    int mJ = getStudents (g, player, STUDENT_MJ);
    int mTV = getStudents (g, player, STUDENT_MTV);
    int mMoney = getStudents(g, player, STUDENT_MMONEY);
    if ((mJ > 0) && (mTV > 0) && (mMoney > 0)) {
        nextAction.actionCode = START_SPINOFF;
    } else {
        nextAction.actionCode = PASS;
    }
    
    return nextAction;
}
