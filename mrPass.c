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
    int mHTW = getStudents(g, player, STUDENT_BQN);
    int mBPS = getStudents(g, player, STUDENT_BPS);
    
    if ((mJ > 0) && (mTV > 0) && (mMoney > 0)) {
        nextAction.actionCode = START_SPINOFF;
    } else if ((mHTW > 0) && (mBPS > 0)){
        char[PATH_LIMIT] myPath = [];
        int counter = 0;
        while (counter < 150){
        }
        
        for (int i = 0; i < 150; i++){
            myPath[i] = 'L';
            
            
            if (((getARC(g, myPath)) == VACANT_ARC)){
                for (int a = 1; a < 10; a++){
                    myPath[i + a] = 'L';
                }
            }
            
            
            myPath[i] = 'R';
            if (!((getARC(g, myPath)) == VACANT_ARC)){
                continue;
            }
            myPath[i] = 'B';
            if (!((getARC(g, myPath)) == VACANT_ARC)){
                continue;
            }
        }
        
    } else {
        nextAction.actionCode = PASS;
    }
    
    return nextAction;
}

char[] randomPath(){
    bool validPath = false;
    char[PATH_LIMIT] myPath = [];
    int counter = 0;
    
    while (!validPath && counter < PATH_LIMIT){
        
    }
}
