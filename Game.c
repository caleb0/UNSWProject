
#include "Game.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#define NUM_STUDENT 6
void createVertex(Game g);
void visualiseGame(Game g);
void createRegions(Game g);


int main(int argc, char* argv[]) {
	printf("Started\n");
	makeGame();
	return EXIT_SUCCESS;
}

struct _game {
    //Region information
	region regions[NUM_REGIONS]; // create a region for each region
    
    //Vertex information
 //Creates 6 vertex pointers for each region
    
    //Global information
    int diceResult; //Result of a dice roll
    int whoseTurn; //Int of which player's turn it is
    int turnNumber; //Turn number counter
    
    //Player information
    int pKPI[NUM_UNIS]; //Have a value of KPI for each uni/player
    int pNumCampus[NUM_UNIS]; //Value of campuses for each player
    int pNumGO8[NUM_UNIS]; //Value of GO8s for each player
    int pNumIP[NUM_UNIS]; //Value of IPs for each player
    int pStudents[NUM_UNIS][NUM_STUDENT]; //Value of student types for each player
    int pPublication[NUM_UNIS]; //Value of publications for each player
    int pARC[NUM_UNIS]; //Value for ARCS for each player
    
    //Leaderboard information
    int topKPI; //Stores the top KPI value
    int topPublication; //Stores the top publication value
} game;

void makeGame() {
	printf("About to allocate a new game\n");
	Game g = malloc(sizeof(struct _game));//malloc memory for the whole game
	assert(g != NULL);
	printf("Game is not null\n");
	g->whoseTurn = -1; //terra nullis turn
	g->topKPI = NO_ONE;
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
	int i = 0;
	int a = 0;
	for (i = 0; i < NUM_REGIONS; i++) {
		printf("\n\nTile no %d, coordinate: %d, %d\n\n", i, g->regions[i].x, g->regions[i].y);
		for (a = 0; a < 6; a++) {
			printf("Vertex (%d, %d) is x: %d, y: %d\n", i, a, g->regions[i].v->x, g->regions[i].v->y);
		}
	}

};

typedef struct _game * Game;


void createRegions(Game g) {
	printf("Inside regions");
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
/*void createVertex(Game g) {
	int currentTile = 0;
	int currentVertex;
	while (currentTile < NUM_REGIONS) {
		currentVertex = 0;
		while (currentVertex < 6) {
			if (currentTile < 3) {
				if (currentVertex < 3) {
					g->vertices[currentTile][currentVertex].y = 1;
					g->vertices[currentTile][currentVertex].x = (currentVertex + 2) + 2 * currentTile;
				}
				else {
					g->vertices[currentTile][currentVertex].y = 0;
					g->vertices[currentTile][currentVertex].x = (currentVertex - 3) + 2 * currentTile;
				}
			}
			else if (currentTile < 7) {
				if (currentVertex < 3) {
					g->vertices[currentTile][currentVertex].y = 2;
					g->vertices[currentTile][currentVertex].x = (currentVertex + 1) + 2 * (currentTile - 3);
				}
				else {
					g->vertices[currentTile][currentVertex].y = 1;
					g->vertices[currentTile][currentVertex].x = (currentVertex - 4) + 2 * (currentTile - 3);
				}
			}
			else if (currentTile < 12) {
				if (currentVertex < 3) {
					g->vertices[currentTile][currentVertex].y = 3;
					g->vertices[currentTile][currentVertex].x = currentVertex + 2 * (currentTile - 7);
				}
				else {
					g->vertices[currentTile][currentVertex].y = 2;
					g->vertices[currentTile][currentVertex].x = (currentVertex - 5) + 2 * (currentTile - 7);
				}
			}
			else if (currentTile < 16) {
				if (currentVertex < 3) {
					g->vertices[currentTile][currentVertex].y = 4;
					g->vertices[currentTile][currentVertex].x = (currentVertex + 1) + 2 * (currentTile - 12);
				}
				else {
					g->vertices[currentTile][currentVertex].y = 3;
					g->vertices[currentTile][currentVertex].x = (currentVertex - 4) + 2 * (currentTile - 12);
				}
			}
			else if (currentTile < 19) {
				if (currentVertex < 3) {
					g->vertices[currentTile][currentVertex].y = 5;
					g->vertices[currentTile][currentVertex].x = (currentVertex + 2) + 2 * (currentTile - 16);
				}
				else {
					g->vertices[currentTile][currentVertex].y = 4;
					g->vertices[currentTile][currentVertex].x = (currentVertex - 3) + 2 * (currentTile - 16);
				}

			}
			currentVertex++;

		}
		currentTile++;
	}
}*/




void disposeGame(Game g) {
    free(g);
}
int getCampus(Game g, path pathToVertex) {
    return 0;
}

int getKPIpoints(Game g, int player) {
    return g->pKPI[player];
}
int getARCs(Game g, int player) {
    return g->pARC[player];
}
int getG08s(Game g, int player) {
    return g->pNumGO8[player];
}

int getCampuses(Game g, int player) {
    return g->pNumCampus[player];
}

int getIPs(Game g, int player) {
    return g->pNumIP[player];
}

int getPublications(Game g, int player) {
    return g->pPublication[player];
}

int getStudents(Game g, int player, int discipline) {
    return g->pStudents[player][discipline];
}

int getExchangeRate(Game g, int player, int disciplineFrom, int disciplineTo) {
    return 0;
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
        } else if (currentRegion < 7) {
            startOfRow = 3;
            regionCount = 7;
            currentRow = 1;
            endOfRow = 6;
            previousStartOfRow = 0;
            previousEndOfRow = 2;
        } else if (currentRegion < 12) {
            startOfRow = 7;
            regionCount = 12;
            currentRow = 2;
            endOfRow = 11;
            previousStartOfRow = 3;
            previousEndOfRow = 6;
        } else if (currentRegion < 16) {
            startOfRow = 12;
            regionCount = 16;
            currentRow = 3;
            endOfRow = 15;
            previousStartOfRow = 7;
            previousEndOfRow = 11;
        } else if (currentRegion < 19) {
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
                    g->regions[currentRegion].v[vCount] = malloc(2*(sizeof(int)));
                    g->regions[currentRegion].v[vCount]->x = vCount-currentRow;
                    g->regions[currentRegion].v[vCount]->y = currentRow + 1;
                    vCount++;
                }
                while (vCount < 6) {
                    g->regions[currentRegion].v[vCount] = malloc(2*(sizeof(int)));
                    g->regions[currentRegion].v[vCount]->x = (5 - vCount)-currentRow;
                    g->regions[currentRegion].v[vCount]->y = currentRow;
                    vCount++;
                }
            } else if (currentRow < 3) {
                while (vCount < 3) {
                    g->regions[currentRegion].v[vCount] = malloc(2*(sizeof(int)));
                    g->regions[currentRegion].v[vCount]->x = vCount - currentRow;
                    g->regions[currentRegion].v[vCount]->y = currentRow + 1;
                    vCount++;
                }
                while (vCount < 6) {
                    if (vCount == 5) {
                        g->regions[currentRegion].v[vCount] = malloc(2*(sizeof(int)));
                        g->regions[currentRegion].v[vCount]->x = (5 - vCount)-currentRow;
                        g->regions[currentRegion].v[vCount]->y = currentRow;
                        vCount++;
                    } else {
                        g->regions[currentRegion].v[vCount] = malloc(2*(sizeof(int)));
                        g->regions[currentRegion].v[vCount] = g->regions[previousStartOfRow].v[4 - vCount];
                    }
                    vCount++;
                }
            } else {
                while (vCount < 3) {
                    g->regions[currentRegion].v[vCount] = malloc(2*(sizeof(int)));
                    g->regions[currentRegion].v[vCount]->x = vCount - (4 -currentRow);
                    g->regions[currentRegion].v[vCount]->y = currentRow + 1;
                    vCount++;
                }
                while (vCount < 6) {
                    if (vCount == 3) {
                        g->regions[currentRegion].v[vCount] = malloc(2*(sizeof(int)));
                        g->regions[currentRegion].v[vCount]->x = (5 - vCount)-(4-currentRow);
                        g->regions[currentRegion].v[vCount]->y = currentRow;
                        vCount++;
                    } else {
                        g->regions[currentRegion].v[vCount] = malloc(2*(sizeof(int)));
                        g->regions[currentRegion].v[vCount] = g->regions[previousStartOfRow].v[6 - vCount];
                        vCount++;
                    }
                }
            }
        } else if (currentRegion < regionCount) {
            if (currentRow == 0) {
                while (vCount < 3) {
                    g->regions[currentRegion].v[vCount] = malloc(2*(sizeof(int)));
                    g->regions[currentRegion].v[vCount]->y = 1;
                    g->regions[currentRegion].v[vCount]->x = 2*currentRegion+vCount;
                    vCount++;
                }
                while (vCount < 6) {
                    g->regions[currentRegion].v[vCount] = malloc(2*(sizeof(int)));
                    g->regions[currentRegion].v[vCount]->y = 0;
                    g->regions[currentRegion].v[vCount]->x = 2*currentRegion+(5-vCount);
                    vCount++;
                }
            } else if (currentRegion != endOfRow) {
                while (vCount < 3) {
                    g->regions[currentRegion].v[vCount] = malloc(2*(sizeof(int)));
                    if (vCount == 0) {
                        g->regions[currentRegion].v[vCount] = g->regions[currentRegion -1].v[vCount + 2];
                    } else if (currentRow < 3) {
                        g->regions[currentRegion].v[vCount]->x = (((2*(currentRegion - startOfRow))+1)+(vCount - 1))-currentRow;
                        g->regions[currentRegion].v[vCount]->y = currentRow + 1;
                    } else {
                        g->regions[currentRegion].v[vCount]->x = (((2*(currentRegion - startOfRow))+1)+(vCount - 1))-(4 -currentRow);
                        g->regions[currentRegion].v[vCount]->y = currentRow + 1;
                    }
                    vCount++;
                }
                while (vCount < 6) {
                    g->regions[currentRegion].v[vCount] = malloc(2*(sizeof(int)));
                    if (vCount == 5) {
                        g->regions[currentRegion].v[vCount] = g->regions[currentRegion -1].v[vCount - 2];
                    } else if(currentRow < 3){
                        g->regions[currentRegion].v[vCount] = g->regions[previousStartOfRow+(currentRegion-startOfRow)].v[4 - vCount];
                    } else {
                        g->regions[currentRegion].v[vCount] = g->regions[(previousStartOfRow+(currentRegion-startOfRow))+1].v[4 - vCount];
                    }
                    vCount++;
                }
            } else {
                while (vCount < 3) {
                    g->regions[currentRegion].v[vCount] = malloc(2*(sizeof(int)));
                    if (vCount == 0) {
                        g->regions[currentRegion].v[vCount] = g->regions[currentRegion -1].v[vCount + 2];
                    } else if (currentRow < 3) {
                        g->regions[currentRegion].v[vCount]->x = (((2*(currentRegion - startOfRow))+1)+(vCount - 1))-currentRow;
                        g->regions[currentRegion].v[vCount]->y = currentRow + 1;
                    } else {
                        g->regions[currentRegion].v[vCount]->x = (((2*(currentRegion - startOfRow))+1)+(vCount - 1))-(4 -currentRow);
                        g->regions[currentRegion].v[vCount]->y = currentRow + 1;
                    }
                    vCount++;
                }
                while (vCount < 6) {
                    g->regions[currentRegion].v[vCount] = malloc(2*(sizeof(int)));
                    if (vCount == 5) {
                        g->regions[currentRegion].v[vCount] = g->regions[currentRegion -1].v[vCount - 2];
                    } else if ((vCount == 3)&&(currentRow < 3)) {
                        g->regions[currentRegion].v[vCount]->x = (((2*(currentRegion - startOfRow))+1)+(4 - vCount))-currentRow;
                        g->regions[currentRegion].v[vCount]->y = currentRow;
                    } else if (vCount == 3) {
                        g->regions[currentRegion].v[vCount] = g->regions[previousEndOfRow].v[1];
                    } else if (currentRow < 3){
                        g->regions[currentRegion].v[vCount] = g->regions[previousEndOfRow].v[2];
                    } else {
                        g->regions[currentRegion].v[vCount] = g->regions[previousEndOfRow].v[0];
                    }
                    vCount++;
                }
            }
        }
        currentRegion++;
    }
}

