#include "Game.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


//This sets up the game in the same setup as the badly drawn map
//https://www.openlearning.com/courses/comp1917rag/ki/geographicmodel/badly-drawn-map.jpg?t=1460898406499&t=1460898589011


#define DEFAULT_DISCIPLINES {STUDENT_BQN, STUDENT_MMONEY, STUDENT_MJ, \ 
STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV, \
STUDENT_MTV, STUDENT_BPS, STUDENT_MTV, STUDENT_BQN, \
STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ, \
STUDENT_MMONEY, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS}

#define DEFAULT_DICE {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5}

typedef struct _vector {
	double x;
	double y;
}Vector2; //A Vector struct for storing coordinates

typedef struct _game {
	//Region information
	int regionD[NUM_REGIONS]; //Creates an int for every region that represents a discipline
	int regionDice[NUM_REGIONS]; //Creates an dice value for every region

	//Vertex information
	//vertex codenz here

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
	
	//Leaderboard information
	int topKPI; //Stores the top KPI value
	int topPublication; //Stores the top publication value
} game;

int main(int argc, char* argv[]) {

	printf("Beginning Testing\n\n");

	testGame();
	printf("All tests passed, you are Awesome!");

	return EXIT_SUCCESS;
}

void testGame() {

	int disciplines[NUM_REGIONS] = DEFAULT_DISCIPLINES;
	int dice[NUM_REGIONS] = DEFAULT_DICE;

	int counter = 0;
	printf("Here are the inputted disciplines:\n");

	while (counter < NUM_REGIONS){
		printf("%d ", disciplines[counter]);
		counter++;
	}
	counter = 0;

	printf("\nHere are the inputted dice values:\n");
	while (counter < NUM_REGIONS) {
		printf("%d ", dice[counter]);
		counter++;
	}
	counter = 0;

	printf("\n***Making a new game***\n");
	Game g = newGame(disciplines, dice);

	printf("Asserting getMostARCs is NO_ONE (0) \n");
	assert(getMostARCs(g) == NO_ONE);
	
	printf("Asserting getDiscipline is the right index\n");
	while (counter < NUM_REGIONS) {
		assert(getDiscipline(g, counter) == disciplines[counter]);
		counter++;
	}
	counter = 0;
	printf("Asserting getMostPublications is NO_ONE (0) \n");
	assert(getMostPublications(g) == NO_ONE);

	printf("Asserting the current turn == -1\n");
	assert(getTurnNumber(g) == -1);

	printf("Asserting getWhoseTurn is NO_ONE (0) \n");
	assert(getWhoseTurn(g) == NO_ONE);

	printf("Rolling the dice 10 times \n");
	printf("Asserting turnNumber is right\n");
	while (counter < 10) {
		throwDice(g, dice[i]);
		assert(getTurnNumber(g) == (i));
		assert((getWhoseTurn(g) >= UNI_A) && (getWhoseTurn(g) <= UNI_C)); //makes sure the turns are either of the 3 unis
		assert(getWhoseTurn(g) == ((i % NUM_UNIS)+1));
		counter++;
	}
	counter = 0;

	printf("Making a new action \n");
	action a = {
		PASS,
		NULL,
		NULL,
		NULL,
	};
	printf("Preforming the new action \n");
	makeAction(g, a);

	printf("Disposing the game\n");
	disposeGame(g);
	
}
