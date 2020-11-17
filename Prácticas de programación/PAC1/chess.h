#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

/* Constants *********************************************************/

#define MAX_PAIRINGS  20
#define MAX_PLAYERS   200
#define MAX_ROUNDS    100
#define MAX_CHAR      100

/* Types *************************************************************/

typedef enum {false, true} bool;

typedef char string[MAX_CHAR+1];

typedef struct {
	int idPlayer;
	string name;
	int age;
	string nationality;
	int elo;
	string level;
} tPlayer;

typedef enum {draw, whiteWins, blackWins} tResult;

typedef struct {
	int idPairing;
	int idWhitePlayer;
	int idBlackPlayer;
	tResult result;
} tPairing;

typedef struct {
	int idRound;
	tPairing pairings[MAX_PAIRINGS];
	int numPairings;
	int numWhiteWins;
	int numBlackWins;
	int numDraws;
} tRound;

typedef struct {
	int day;
	int month;
	int year;
} tDate;

typedef struct {
	string name;
	string location;
	tDate date;
	tPlayer *players;
	int numPlayers;
	tRound rounds[MAX_ROUNDS];
	int numRounds;
} tChessTournament;

/* Functions *********************************************************/
void init_chess_tournament (tChessTournament *c);
void new_player (tChessTournament *c, int idPlayer, string name,
				 int age, string nationality, int elo);
void new_round (tChessTournament *c, int idRound);
void add_pairing (tChessTournament *c, int idPairing, int idPlayer1,
				 int idPlayer2, int idRound);
void print_round_pairings (tChessTournament c, int idRound);

/* Auxiliary functions ***********************************************/

/* Given a ID player, returns a player in the chess tournament */
tPlayer *find_player (tChessTournament c, int idPlayer);

/* Given a round and a ID pairing, returns the position 'i' in the vector pairings[i] */
int num_order_pairing (tChessTournament c, int idRound, int idPairing);

/* Calculate level from elo parameter */
void set_level (tChessTournament *c);

/* Generate random results for a given pairing in a given round */
tResult calculate_results (tChessTournament *c, int idRound,int idPairing);

/* Given a player, a pairing and a round, it checks if the player is in the tournament, if the player 
is already paired, if the round is already full of pairings and if there are no more round left to add*/
void check_pairing (tChessTournament c, int idRound, int idPairing, int idPlayer, bool *checked);

/* Move information of a player from the source to the destination */
void copy_info_player (tPlayer srcPlayer, tPlayer *dstPlayer);

/* It returns the result of a pairing in a given round */
tResult get_result (tChessTournament c, int idRound, int idPairing);