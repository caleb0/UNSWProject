#include "Game.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#define NUM_STUDENT 6
#define NORTH_EAST 0
#define EAST 1
#define SOUTH_EAST 2
#define SOUTH_WEST 3
#define WEST 4
#define NORTH_WEST 5
typedef struct _game * Game;

typedef struct _vertex {
    int x;
    int y;
    int info;// See defines above
} vertex; //A Vector struct for storing coordinates


typedef struct _retrainingCentre {
    vertex *v1;
    vertex *v2;
    int studentType; //
} retrainingCentre;


typedef struct _arc {
    vertex *v1;
    vertex *v2;
    int info; // See defines above
} arc;

typedef struct _region {
    int x; //x coord
    int y; //y coord
    int diceValue; // dice value
    int dicipline; // what dicipline is on the region
    vertex *v[6];
} region;

typedef struct _player {
    int pKPI; //Have a value of KPI for each uni/player
    int pNumCampus; //Value of campuses for each player
    int pNumGO8; //Value of GO8s for each player
    int pNumIP; //Value of IPs for each player
    int pStudents[NUM_STUDENT]; //Value of student types for each player
    int pPublication; //Value of publications for each player
    int pARC;
}player;

struct _game {
    //Region information
    region regions[NUM_REGIONS]; // create a region for each region
    player Players[NUM_UNIS];//Player information
    
    int diceResult; //Result of a dice roll
    int whoseTurn; //Int of which player's turn it is
    int turnNumber; //Turn number counter
    int topPublication; //Stores the top publication value
    int topARC; //Stores which player has the most ARC grants
};
void createVertex(Game g);
void visualiseGame(Game g);
void createRegions(Game g);
void makeGame();
void makeAction(Game g, action a);
arc *pathtoArc (Game g, action a);
vertex *pathToVertex(Game g, action a);
vertex* getEndPointOfPath(Game g, action a);
int isLegalAction(Game g, action a);
//static void parsePath(action a);

int main(int argc, char* argv[]) {
    printf("Started\n");
    makeGame();
    return EXIT_SUCCESS;
}

void makeGame() {
    printf("About to allocate a new game\n");
    Game g = malloc(sizeof(struct _game));//malloc memory for the whole game
    assert(g != NULL);
    printf("Game is not null\n");
    g->whoseTurn = -1; //terra nullis turn
    g->topARC = NO_ONE;
    g->topPublication = NO_ONE;
    printf("foo\n");
    createVertex(g);
    printf("Made a new game\n");
    createRegions(g);
    printf("Created regions\n");
    visualiseGame(g);
    //return g;
}

void visualiseGame(Game g) {
    printf("Visualising vertices\n");
    int i = 0;
    int a = 0;
    for (i = 0; i < NUM_REGIONS; i++) {
        printf("\n\nTile no %d, coordinate: %d, %d\n\n", i, g->regions[i].x, g->regions[i].y);
        for (a = 0; a < 6; a++) {
            printf("Vertex (%d, %d) is x: %d, y: %d\n", i, a, g->regions[i].v[a]->x, g->regions[i].v[a]->y);
        }
    }
    
}


void createRegions(Game g) {
    printf("Inside regions\n");
    int xValue = 0;
    int tileID = 0;
    while (xValue < 3) {
        g->regions[tileID].y = 0;
        g->regions[tileID].x = xValue;
        xValue++;
        tileID++;
    }
    xValue = 0;
    while (xValue < 4) {
        g->regions[tileID].y = 1;
        g->regions[tileID].x = xValue;
        xValue++;
        tileID++;
    }
    xValue = 0;
    while (xValue < 5) {
        g->regions[tileID].y = 2;
        g->regions[tileID].x = xValue;
        xValue++;
        tileID++;
    }
    xValue = 1;
    while (xValue < 5) {
        g->regions[tileID].y = 3;
        g->regions[tileID].x = xValue;
        xValue++;
        tileID++;
    }
    xValue = 2;
    while (xValue < 5) {
        g->regions[tileID].y = 4;
        g->regions[tileID].x = xValue;
        xValue++;
        tileID++;
    }
    
}


void makeAction(Game g, action a) {
    if (!isLegalAction(g, a)){
        return;
    }
    //check if legal action
    else if (a.actionCode == PASS) {
        //do nothing
        //add 1 to turn
        g->turnNumber++;
    }
    else if (a.actionCode == BUILD_CAMPUS) {
        //assign student to vertex campus
        vertex* p = pathToVertex(g, a);
        p->info = ((g->turnNumber)%3)+1;
    }
    else if (a.actionCode == BUILD_GO8) {
        vertex *p = pathToVertex(g, a);
        p->info = ((g->turnNumber)%3)+4;
    }
    else if (a.actionCode == OBTAIN_ARC) {
        arc *p = pathtoArc(g,a);
        p->info = ((g->turnNumber)%3)+1;
    }
    else if (a.actionCode == START_SPINOFF) {
        //generate number between 1 and 3
        //if number == 1 -> change action code to OB_IP
        //else -> change action code to OB_PUB
        int randNum = (rand() % 3) + 1;
        if (randNum == 1) {
            a.actionCode = OBTAIN_IP_PATENT;
        } else {
            a.actionCode = OBTAIN_PUBLICATION;
        }
        makeAction(g, a);
    }
    else if (a.actionCode == OBTAIN_PUBLICATION) {
        //increases players publication by 1
        //check who has highest publication amount
    }
    else if (a.actionCode == OBTAIN_IP_PATENT) {
        //increase players ip count by 1
        //each ip = 10 KPI
    }
    else if (a.actionCode == RETRAIN_STUDENTS) {
        // g->p
    }
}


//playercounter starts off at 0
//increases on every turn
//playercounter % 3 + 1 == curentplayer
/*legal acitino (game g, action a){
 vertex point;
 arc side;
 destination =  convertPath2Pos(action a, &side, &point); take the address of both a path and a point
 if (a.actionCode == PASS){
 return true
 } else if (BUILD_CAMPUS){
 check if students > campus requirements
 return true
 else return false
 } else if (BUILD_G08){
 check if destination.info == currentplayer
 check if currentplayer has enough students
 return true
 else
 return false
 } else if (OBTAIN_ARC){
 } else if (RETRAIN){
 get exchange rate
 see if player has enough of fromdicipline
 return true
 else
 return false
 }
 }
 */

/*static void parsePath(action a) {
 vertex that starts at (5, 6)
 //int i = 0
 //if a.actionCode == OBTAIN_ARC{
 paseArc(action a)
 } else {}
 while (action.destionation[i] != \0){
 if (action.destination[i] == 'L'){
 x -= 1
 } else if (action.destination[i] == 'R'){
 x += 1
 } else if (action.destination[i] == 'B'){
 y -= 1
 }
 }
 }
 return;
 }
 */

arc *pathtoArc (Game g, action a) {
    arc *newArc = malloc(sizeof(arc));
    vertex *end;
    vertex *prev;
    int prevX;
    int prevY;
    int heading;
    
    end = getEndPointOfPath (g, a);
    
    int counter = 0;
    //change heading
    while (a.destination[counter] != '\0') {
        if (a.destination[counter] == 'L') {
            if (heading != NORTH_EAST) {
                heading--;
            } else {
                heading = NORTH_WEST;
            }
        } else if (a.destination[counter] == 'R') {
            if (heading != NORTH_WEST) {
                heading++;
            } else {
                heading = NORTH_EAST;
            }
        } else if (a.destination[counter] == 'B') {
            if (heading <= SOUTH_EAST) {
                heading = heading + 3;
            } else {
                heading = heading - 3;
            }
        }
    }

    prevX = end->x;
    prevY = end->y;
    if (heading <= SOUTH_EAST) {
        heading = heading + 3;
    } else {
        heading = heading - 3;
    }
    if (heading == NORTH_EAST) {
        prevX++;
    } else if (heading == EAST) {
        prevX++;
    } else if (heading == SOUTH_EAST) {
        prevY--;
    } else if (heading == SOUTH_WEST) {
        prevX--;
    } else if (heading == WEST) {
        prevX--;
    } else if (heading == NORTH_WEST) {
        prevY++;
    }
    newArc->info = VACANT_ARC;
    
    int i = 0;
    int b = 0;
    while ((g->regions[i].v[b]->y != end->y) && (g->regions[i].v[b]->x != end->x)) {
        b = 0;
        while (((b < 6) && ((g->regions[i].v[b]->y != end->y) && (g->regions[i].v[b]->x != end->x)))) {
            b++;
        }
        i++;
    }
    prev = g->regions[i].v[b];

    newArc->v1 = end;
    newArc->v2 = prev;
    return newArc;
}

vertex *pathToVertex (Game g, action a) {
    vertex *endVertex;
    endVertex = getEndPointOfPath (g, a);
    return endVertex;
}

vertex *getEndPointOfPath (Game g, action a) {
    int counter = 0;
    int heading = SOUTH_EAST;
    int x = 5;
    int y = 6;
    while (a.destination[counter] != '\0') {
        //change x,y
        if (heading == NORTH_EAST) {
            if (a.destination[counter] == 'L') {
                y++;
            } else if (a.destination[counter] == 'R') {
                x++;
            } else if (a.destination[counter] == 'B') {
                x--;
            }
        } else if (heading == EAST) {
            if (a.destination[counter] == 'L') {
                x++;
            } else if (a.destination[counter] == 'R') {
                y--;
            } else if (a.destination[counter] == 'B') {
                x--;
            }
        } else if (heading == SOUTH_EAST) {
            if (a.destination[counter] == 'L') {
                x++;
            } else if (a.destination[counter] == 'R') {
                x--;
            } else if (a.destination[counter] == 'B') {
                y++;
            }
        } else if (heading == SOUTH_WEST) {
            if (a.destination[counter] == 'L') {
                y--;
            } else if (a.destination[counter] == 'R') {
                x--;
            } else if (a.destination[counter] == 'B') {
                x++;
            }
        } else if (heading == WEST) {
            if (a.destination[counter] == 'L') {
                x--;
            } else if (a.destination[counter] == 'R') {
                y++;
            } else if (a.destination[counter] == 'B') {
                x++;
            }
        } else if (heading == NORTH_WEST) {
            if (a.destination[counter] == 'L') {
                x--;
            } else if (a.destination[counter] == 'R') {
                x++;
            } else if (a.destination[counter] == 'B') {
                y--;
            }
        }
        //change heading
        if (a.destination[counter] == 'L') {
            if (heading != NORTH_EAST) {
                heading--;
            } else {
                heading = NORTH_WEST;
            }
        } else if (a.destination[counter] == 'R') {
            if (heading != NORTH_WEST) {
                heading++;
            } else {
                heading = NORTH_EAST;
            }
        } else if (a.destination[counter] == 'B') {
            if (heading <= SOUTH_EAST) {
                heading = heading + 3;
            } else {
                heading = heading - 3;
            }
        }
        counter++;
    }


    vertex *endVertex;
    int i = 0;
    int b = 0;
    while ((g->regions[i].v[b]->y != y) && (g->regions[i].v[b]->x != x)) {
        b = 0;
        while (((b < 6) && ((g->regions[i].v[b]->y != y) && (g->regions[i].v[b]->x != x)))) {
            b++;
        }
        i++;
    }
    endVertex = g->regions[i].v[b];
    return endVertex;
}

void disposeGame(Game g) {
    // frees the memory pointed to by g
    int currentRegion = 0;
    int vCount;
    while (currentRegion < NUM_REGIONS) {
        vCount = 0;
        while (vCount < 6) {
            free(g->regions[currentRegion].v[vCount]);
            vCount++;
        }
        currentRegion++;
    }
    //frees g
    free(g);
}
int getCampus(Game g, path pathToVertex) {
    return 0;
}

int getKPIpoints(Game g, int player) {
    return g->Players[player].pKPI;
}
int getARCs(Game g, int player) {
    return g->Players[player].pARC;
}
int getGO8s(Game g, int player) {
    return g->Players[player].pNumGO8;
}

int getCampuses(Game g, int player) {
    return g->Players[player].pNumCampus;
}

int getIPs(Game g, int player) {
    return g->Players[player].pNumIP;
}

int getPublications(Game g, int player) {
    return g->Players[player].pPublication;
}

int getStudents(Game g, int player, int discipline) {
    return g->Players[player].pStudents[discipline];
}

int getExchangeRate(Game g, int player, int disciplineFrom, int disciplineTo) {
    return 0;
}

int isLegalAction(Game g, action a) {
    return 1;
}


void createVertex(Game g) {
    int currentRegion = 0;
    int vCount = 0;
    int startOfRow = 0;
    int regionCount = 0;
    int currentRow = 0;
    int endOfRow = 0;
    int previousStartOfRow = 0;
    int previousEndOfRow = 0;
    while (currentRegion < NUM_REGIONS) {
        if (currentRegion < 3) {
            startOfRow = 0;
            regionCount = 3;
            currentRow = 0;
            endOfRow = 2;
        }
        else if (currentRegion < 7) {
            startOfRow = 3;
            regionCount = 7;
            currentRow = 1;
            endOfRow = 6;
            previousStartOfRow = 0;
            previousEndOfRow = 2;
        }
        else if (currentRegion < 12) {
            startOfRow = 7;
            regionCount = 12;
            currentRow = 2;
            endOfRow = 11;
            previousStartOfRow = 3;
            previousEndOfRow = 6;
        }
        else if (currentRegion < 16) {
            startOfRow = 12;
            regionCount = 16;
            currentRow = 3;
            endOfRow = 15;
            previousStartOfRow = 7;
            previousEndOfRow = 11;
        }
        else if (currentRegion < 19) {
            startOfRow = 16;
            regionCount = 19;
            currentRow = 4;
            endOfRow = 18;
            previousStartOfRow = 12;
            previousEndOfRow = 15;
        }
        vCount = 0;
        if (currentRegion == startOfRow) {
            if (currentRow == 0) {
                while (vCount < 3) {
                    g->regions[currentRegion].v[vCount] = malloc(3 * (sizeof(int)));
                    g->regions[currentRegion].v[vCount]->x = vCount - currentRow;
                    g->regions[currentRegion].v[vCount]->y = currentRow + 1;
                    vCount++;
                }
                while (vCount < 6) {
                    g->regions[currentRegion].v[vCount] = malloc(3 * (sizeof(int)));
                    g->regions[currentRegion].v[vCount]->x = (5 - vCount) - currentRow;
                    g->regions[currentRegion].v[vCount]->y = currentRow;
                    vCount++;
                }
            }
            else if (currentRow < 3) {
                while (vCount < 3) {
                    g->regions[currentRegion].v[vCount] = malloc(3 * (sizeof(int)));
                    g->regions[currentRegion].v[vCount]->x = vCount - currentRow;
                    g->regions[currentRegion].v[vCount]->y = currentRow + 1;
                    vCount++;
                }
                while (vCount < 6) {
                    if (vCount == 5) {
                        g->regions[currentRegion].v[vCount] = malloc(3 * (sizeof(int)));
                        g->regions[currentRegion].v[vCount]->x = (5 - vCount) - currentRow;
                        g->regions[currentRegion].v[vCount]->y = currentRow;
                        vCount++;
                    }
                    else {
                        g->regions[currentRegion].v[vCount] = malloc(3 * (sizeof(int)));
                        g->regions[currentRegion].v[vCount] = g->regions[previousStartOfRow].v[4 - vCount];
                    }
                    vCount++;
                }
            }
            else {
                while (vCount < 3) {
                    g->regions[currentRegion].v[vCount] = malloc(3 * (sizeof(int)));
                    g->regions[currentRegion].v[vCount]->x = vCount - (4 - currentRow);
                    g->regions[currentRegion].v[vCount]->y = currentRow + 1;
                    vCount++;
                }
                while (vCount < 6) {
                    if (vCount == 3) {
                        g->regions[currentRegion].v[vCount] = malloc(3 * (sizeof(int)));
                        g->regions[currentRegion].v[vCount]->x = (5 - vCount) - (4 - currentRow);
                        g->regions[currentRegion].v[vCount]->y = currentRow;
                        vCount++;
                    }
                    else {
                        g->regions[currentRegion].v[vCount] = malloc(3 * (sizeof(int)));
                        g->regions[currentRegion].v[vCount] = g->regions[previousStartOfRow].v[6 - vCount];
                        vCount++;
                    }
                }
            }
        }
        else if (currentRegion < regionCount) {
            if (currentRow == 0) {
                while (vCount < 3) {
                    g->regions[currentRegion].v[vCount] = malloc(3 * (sizeof(int)));
                    g->regions[currentRegion].v[vCount]->y = 1;
                    g->regions[currentRegion].v[vCount]->x = 2 * currentRegion + vCount;
                    vCount++;
                }
                while (vCount < 6) {
                    g->regions[currentRegion].v[vCount] = malloc(3 * (sizeof(int)));
                    g->regions[currentRegion].v[vCount]->y = 0;
                    g->regions[currentRegion].v[vCount]->x = 2 * currentRegion + (5 - vCount);
                    vCount++;
                }
            }
            else if (currentRegion != endOfRow) {
                while (vCount < 3) {
                    g->regions[currentRegion].v[vCount] = malloc(3 * (sizeof(int)));
                    if (vCount == 0) {
                        g->regions[currentRegion].v[vCount] = g->regions[currentRegion - 1].v[vCount + 2];
                    }
                    else if (currentRow < 3) {
                        g->regions[currentRegion].v[vCount]->x = (((2 * (currentRegion - startOfRow)) + 1) + (vCount - 1)) - currentRow;
                        g->regions[currentRegion].v[vCount]->y = currentRow + 1;
                    }
                    else {
                        g->regions[currentRegion].v[vCount]->x = (((2 * (currentRegion - startOfRow)) + 1) + (vCount - 1)) - (4 - currentRow);
                        g->regions[currentRegion].v[vCount]->y = currentRow + 1;
                    }
                    vCount++;
                }
                while (vCount < 6) {
                    g->regions[currentRegion].v[vCount] = malloc(3 * (sizeof(int)));
                    if (vCount == 5) {
                        g->regions[currentRegion].v[vCount] = g->regions[currentRegion - 1].v[vCount - 2];
                    }
                    else if (currentRow < 3) {
                        g->regions[currentRegion].v[vCount] = g->regions[previousStartOfRow + (currentRegion - startOfRow)].v[4 - vCount];
                    }
                    else {
                        g->regions[currentRegion].v[vCount] = g->regions[(previousStartOfRow + (currentRegion - startOfRow)) + 1].v[4 - vCount];
                    }
                    vCount++;
                }
            }
            else {
                while (vCount < 3) {
                    g->regions[currentRegion].v[vCount] = malloc(3 * (sizeof(int)));
                    if (vCount == 0) {
                        g->regions[currentRegion].v[vCount] = g->regions[currentRegion - 1].v[vCount + 2];
                    }
                    else if (currentRow < 3) {
                        g->regions[currentRegion].v[vCount]->x = (((2 * (currentRegion - startOfRow)) + 1) + (vCount - 1)) - currentRow;
                        g->regions[currentRegion].v[vCount]->y = currentRow + 1;
                    }
                    else {
                        g->regions[currentRegion].v[vCount]->x = (((2 * (currentRegion - startOfRow)) + 1) + (vCount - 1)) - (4 - currentRow);
                        g->regions[currentRegion].v[vCount]->y = currentRow + 1;
                    }
                    vCount++;
                }
                while (vCount < 6) {
                    g->regions[currentRegion].v[vCount] = malloc(3 * (sizeof(int)));
                    if (vCount == 5) {
                        g->regions[currentRegion].v[vCount] = g->regions[currentRegion - 1].v[vCount - 2];
                    }
                    else if ((vCount == 3) && (currentRow < 3)) {
                        g->regions[currentRegion].v[vCount]->x = (((2 * (currentRegion - startOfRow)) + 1) + (4 - vCount)) - currentRow;
                        g->regions[currentRegion].v[vCount]->y = currentRow;
                    }
                    else if (vCount == 3) {
                        g->regions[currentRegion].v[vCount] = g->regions[previousEndOfRow].v[1];
                    }
                    else if (currentRow < 3) {
                        g->regions[currentRegion].v[vCount] = g->regions[previousEndOfRow].v[2];
                    }
                    else {
                        g->regions[currentRegion].v[vCount] = g->regions[previousEndOfRow].v[0];
                    }
                    vCount++;
                }
            }
        }
        currentRegion++;
    }
}
