#include "chess.h"

/* Auxiliary functions ****************************************************/

/**************************************************************************/
tPlayer *find_player (tChessTournament c, int idPlayer)
/**************************************************************************/
{
	tPlayer *res;
	int  i;

	i = 0;
	res = NULL;
	while ((i < c.numPlayers) && (res == NULL)) {
		if (c.players[i].idPlayer == idPlayer){
			res = &(c.players[i]);
		}
		else {
			i++;
		}
	}
	return res;
}

/**************************************************************************/
int num_order_pairing (tChessTournament c, int idRound, int idPairing)
/**************************************************************************/
{
	int  i;
	bool found = false;

	i = 0;
	while ((i < c.rounds[idRound].numPairings) && (!found)) {
		if (c.rounds[idRound].pairings[i].idPairing == idPairing){
			found = true;
		}
		else {
			i++;
		}
	}
	if (found) {
		return i;
	}
	else{
		return -1;
	}
}

/**************************************************************************/
void set_level (tChessTournament *c)
/**************************************************************************/
{
	string level;
	int elo = c->players[c->numPlayers].elo;
	
	if (elo <= 1800) {
		strcpy(level,"novice");
	} else if (elo <= 2000){
		strcpy(level,"medium");
	} else if (elo <= 2400){
		strcpy(level,"advanced");
	} else {
		strcpy(level,"master");
	}
	
	strcpy(c->players[c->numPlayers].level,level);
}

/**************************************************************************/
tResult calculate_results (tChessTournament *c, int idRound,int idPairing)
/**************************************************************************/
{
	int aux = rand()%3+1;
	tResult res;
		
	if (aux == 1) {
		res = whiteWins;
		c->rounds[idRound].numWhiteWins++;
	} else if (aux == 2){
		res = blackWins;
		c->rounds[idRound].numBlackWins++;
	} else if (aux == 3){
		res = draw;
		c->rounds[idRound].numDraws++;
	}
	return res;
}

/**************************************************************************/
void check_pairing (tChessTournament c, int idRound, int idPairing, int idPlayer, bool *checked)
/**************************************************************************/
{
	int  i;
	*checked = true;
	i = 0;
	if (find_player(c,idPlayer) == NULL) {
		printf("ERROR while pairing player %i. He/she does not appear in the list of players\n",idPlayer);
		*checked = false;
	}
	else {
		while ((i < c.rounds[idRound].numPairings) && (*checked)) {
			if ((c.rounds[idRound].pairings[i].idBlackPlayer == idPlayer) ||
				(c.rounds[idRound].pairings[i].idWhitePlayer == idPlayer)) {
				*checked = false;
			}
			else {
				i++;
			}
		}
		if (!*checked) {
			printf("ERROR while pairing player %i. He/she is already paired in round %i\n",idPlayer,idRound);
		}
		else {
			if (c.rounds[idRound].numPairings == 5) {
				printf("ERROR while adding the pairing %i to round %i. It is already full of pairings\n",idPairing,idRound);
				*checked = false;
			}
			else{
				if (idRound > 9) {
					printf("ERROR while adding the pairing %i to round %i. Maximum number of rounds reached\n",idPairing,idRound);
					*checked = false;
				
				}
			}
		}
	}
}

/**************************************************************************/
void copy_info_player (tPlayer srcPlayer, tPlayer *dstPlayer)
/**************************************************************************/
{
	dstPlayer->idPlayer = srcPlayer.idPlayer;
	strcpy(dstPlayer->name,srcPlayer.name);
	dstPlayer->age = srcPlayer.age;
	strcpy(dstPlayer->nationality,srcPlayer.nationality);
	dstPlayer->elo = srcPlayer.elo;
	strcpy(dstPlayer->level,srcPlayer.level);
}

/**************************************************************************/
tResult get_result (tChessTournament c, int idRound, int idPairing)
/**************************************************************************/
{
	return c.rounds[idRound].pairings[num_order_pairing(c,idRound,idPairing)].result;
}

/* Demanded functions ****************************************************/

/**************************************************************************/
void init_chess_tournament (tChessTournament *c)
/**************************************************************************/
{
	/* Check PRE conditions */
	assert(c != NULL);

	/* Name of the tournament */
	strcpy(c->name,"OPEN CHESS 2020");
	strcpy(c->location,"SPAIN");
	c->date.day = 30;
	c->date.month = 1;
	c->date.year = 2020;
	
	/* Empty structures */
	c->numPlayers = 0;
	c->numRounds = 0;
	
	/* Random seed for rand() function */
	srand(time(NULL));
}

/**************************************************************************/
void new_player (tChessTournament *c, int idPlayer, string name,
				 int age, string nationality, int elo)
/**************************************************************************/
{
	/* Check PRE conditions */
	assert(c != NULL);
	assert(idPlayer > 0);
	assert(elo > 0);

	/* Search the medicine */
	if (find_player (*c, idPlayer) != NULL) {
		printf("ERROR: Player %i is already in the list of players\n", idPlayer);
	}
	else {
		/* It does not exist, allocate space */
		if (c->numPlayers == 0){
			c->players = (tPlayer *) malloc(sizeof(tPlayer));
		}
		else { 
			c->players = (tPlayer *) realloc(c->players, (c->numPlayers+1)*sizeof(tPlayer));
		}

		/* If it is ok, then add the player to the tournament */
		if (c->players == NULL)
			printf("ERROR: Memory error\n");
		else {
			c->players[c->numPlayers].idPlayer = idPlayer;
			strcpy(c->players[c->numPlayers].name,name);
			c->players[c->numPlayers].age = age;
			strcpy(c->players[c->numPlayers].nationality,nationality);
			c->players[c->numPlayers].elo = elo;
			set_level(c);
			c->numPlayers++;
		}
	}
}



/**************************************************************************/
void new_round (tChessTournament *c, int idRound)
/**************************************************************************/
{
	/* Initialize round related parameters and add 1 to the current round */
	c->rounds[idRound+1].idRound = idRound+1;
	c->rounds[idRound+1].numPairings = 0;
	c->rounds[idRound+1].numWhiteWins = 0;
	c->rounds[idRound+1].numBlackWins = 0;
	c->rounds[idRound+1].numDraws = 0;
	c->numRounds++;
}

/**************************************************************************/
void add_pairing (tChessTournament *c, int idPairing, int idPlayer1,
				 int idPlayer2, int idRound)
/**************************************************************************/
{
	bool checked;
	
	/* Checks validity of the player 1 */
	check_pairing(*c,idRound,idPairing,idPlayer1,&checked);
	
	if (checked){
		/* Checks validity of the player 2 */
		check_pairing(*c,idRound,idPairing,idPlayer2,&checked);
		
		if(checked){
			/* If everything is checked, the pairing is added with a random result */
			c->rounds[idRound].pairings[c->rounds[idRound].numPairings].idPairing = idPairing;
			c->rounds[idRound].pairings[c->rounds[idRound].numPairings].idWhitePlayer = idPlayer1;
			c->rounds[idRound].pairings[c->rounds[idRound].numPairings].idBlackPlayer = idPlayer2;
			c->rounds[idRound].pairings[c->rounds[idRound].numPairings].result = calculate_results(c,idRound,idPairing);
			c->rounds[idRound].numPairings++;
		}
	}
}

/**************************************************************************/
void print_round_pairings (tChessTournament c, int idRound)
/**************************************************************************/
{
	tPlayer auxPlayer;
	tResult auxRes;
	
	/* Title of the tournament */
	printf("\n******************************************************************\n");
	printf("%s %s %i/%i/%i (%i players in the tournament)\n",c.name,c.location,
			c.date.day,c.date.month,c.date.year,c.numPlayers);
	printf("******************************************************************\n");
	printf("ROUND %i\n",idRound);
	printf("------------------------------------------------------------------\n");
	printf("Number of pairings: %i\n",c.rounds[idRound].numPairings);
	printf("Number of wins with white pieces: %i\n",c.rounds[idRound].numWhiteWins);
	printf("Number of wins with black pieces: %i\n",c.rounds[idRound].numBlackWins);
	printf("Number of draws: %i\n",c.rounds[idRound].numDraws);
	printf("\n");
	
	/* Information of all the pairing in a given round */
	for(int i=0;i<c.rounds[idRound].numPairings;i++){
		printf("Pairing id: %i\n",c.rounds[idRound].pairings[i].idPairing);
		copy_info_player(*find_player(c,c.rounds[idRound].pairings[i].idWhitePlayer),&auxPlayer);
		printf("White: %s, %i years old, from %s, %i elo\n",auxPlayer.name,auxPlayer.age,
				auxPlayer.nationality,auxPlayer.elo);
		copy_info_player(*find_player(c,c.rounds[idRound].pairings[i].idBlackPlayer),&auxPlayer);
		printf("Black: %s, %i years old, from %s, %i elo\n",auxPlayer.name,auxPlayer.age,
				auxPlayer.nationality,auxPlayer.elo);		
		printf("Result: ");
		
		auxRes = get_result(c,idRound,c.rounds[idRound].pairings[i].idPairing);

		if (auxRes == whiteWins){
			printf("White wins\n\n");
		}
		else if (auxRes == blackWins){
			printf("Black wins\n\n");
		}
		else if (auxRes == draw){
			printf("Draw\n\n");
		}
	}
}