<<<<<<< HEAD
#include "Game.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
=======
#include "game.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
>>>>>>> origin/master
#define NUM_STUDENT 6
void makeGame();
void createVertex(Game g);
void visualiseGame(Game g);
void createRegions(Game g);

<<<<<<< HEAD
int main(int argc, char* argv[]) {
	printf("Started\n");
	makeGame();
	return EXIT_SUCCESS;
}
=======
typedef struct _vector {
    double x;
    double y;
} Vector2; //A Vector struct for storing coordinates
>>>>>>> origin/master

struct _game {
    //Region information
	region regions[NUM_REGIONS]; // create a region for each region
    
    //Vertex information
    vertex vertices[NUM_REGIONS][6]; //Creates 6 vertex pointers for each region
    
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
<<<<<<< HEAD
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
			printf("Vertex (%d, %d) is x: %d, y: %d\n", i, a, g->vertices[i][a].x, g->vertices[i][a].y);
		}
	}
=======
};

typedef struct _game * Game;

int main(int argc, char* argv[]){
    printf("Started game\n");
    makeGame();
    return EXIT_SUCCESS;
}




void vertexSetToZeroZero(Vector2 * v) {
    v->y = 0;
    v->x = 0;
}

Game makeGame() {

    printf("Making a new game\n");
    Game g = malloc(sizeof(struct _game));
    printf("Made new game\n");//malloc memory for the whole game
    assert(g != NULL);
    g->whoseTurn = -1; //terra nullis turn
    g->topKPI = NO_ONE;
    g->topPublication = NO_ONE;
    printf("About to create vertecies\n");
    createVertices(g);

    //printf("Here\n");
    //assert(g->vertices[0][0]->x);
    g->vertices[0][0]->y;
        printf("Moo\n");
printf("%p\n", g->vertices[0][0]);
        printf("p\n");
    //printf("%d, %d\n",g->vertices[0][0]->x, g->vertices[0][0]->y);
printf("Not here\n");

    vertexSetToZeroZero(g->vertices[0][0]);
    return g;
>>>>>>> origin/master
}

void createRegions(Game g) {
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

<<<<<<< HEAD
void createVertex(Game g) {
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
=======

void createVertices(Game g) {

    int currentTile = 0;
    int currentVertex;
    while (currentTile < NUM_REGIONS) {
        currentVertex = 0;
        while (currentVertex < 6) {
            if (currentTile < 3) {
                if (currentVertex < 3) {
                    g->vertices[currentTile][currentVertex]->y = 1;
                    g->vertices[currentTile][currentVertex]->x = (currentVertex + 2) + 2 * currentTile;
                }
                else {
                    g->vertices[currentTile][currentVertex]->y = 0;
                    g->vertices[currentTile][currentVertex]->x = (currentVertex - 3) + 2 * currentTile;
                }
            }
            else if (currentTile < 7) {
                if (currentVertex < 3) {
                    g->vertices[currentTile][currentVertex]->y = 2;
                    g->vertices[currentTile][currentVertex]->x = (currentVertex + 1) + 2 * (currentTile - 3);
                }
                else {
                    g->vertices[currentTile][currentVertex]->y = 1;
                    g->vertices[currentTile][currentVertex]->x = (currentVertex - 4) + 2 * (currentTile - 3);
                }
            }
            else if (currentTile < 12) {
                if (currentVertex < 3) {
                    g->vertices[currentTile][currentVertex]->y = 3;
                    g->vertices[currentTile][currentVertex]->x = currentVertex + 2 * (currentTile - 7);
                }
                else {
                    g->vertices[currentTile][currentVertex]->y = 2;
                    g->vertices[currentTile][currentVertex]->x = (currentVertex - 5) + 2 * (currentTile - 7);
                }
            }
            else if (currentTile < 16) {
                if (currentVertex < 3) {
                    g->vertices[currentTile][currentVertex]->y = 4;
                    g->vertices[currentTile][currentVertex]->x = (currentVertex + 1) + 2 * (currentTile - 12);
                }
                else {
                    g->vertices[currentTile][currentVertex]->y = 3;
                    g->vertices[currentTile][currentVertex]->x = (currentVertex - 4) + 2 * (currentTile - 12);
                }
            }
            else if (currentTile < 19) {
                if (currentVertex < 3) {
                    g->vertices[currentTile][currentVertex]->y = 5;
                    g->vertices[currentTile][currentVertex]->x = (currentVertex + 2) + 2 * (currentTile - 16);
                }
                else {
                    g->vertices[currentTile][currentVertex]->y = 4;
                    g->vertices[currentTile][currentVertex]->x = (currentVertex - 3) + 2 * (currentTile - 16);
                }
            }
            currentVertex++;
        }
        currentTile++;
    }
>>>>>>> origin/master
}
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

