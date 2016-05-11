#include <cstdlib>
#include <iostream>
#include <string>
#include <limits>

#include "player.hpp"
#include "log.h"
#include "constants.hpp"
#include <random>
#include "iso646.h"
using namespace std;

//Last work 10-5-2016

namespace checkers
{

/////////////////////////////////////////////////////////////////////////////////////////////////
//Constants and globals
typedef enum SearchChoice{
	MiniMax =1,
	DL_MiniMax = 2,
	AB_MiniMax = 3,
	Ne_MiniMax = 4,
	Testing = 100,
	Random = 101,
	First = 102,
	Last = 103,
	Midpoint = 104,
};


SearchChoice searchChoice = AB_MiniMax;
static const bool MINPLAYER = false, MAXPLAYER = true;
static int turn=0;
const int MinInt = std::numeric_limits<int>::min(); // minimum integer value
const int MaxInt = std::numeric_limits<int>::max(); // maximum integer value
const float MinFloat = std::numeric_limits<float>::min(); // minimum integer value
const float MaxFloat = std::numeric_limits<float>::max(); // maximum integer value
const int HighestScore = 1000;
const int LowestScore = -1000;
int player;

static const int PosWeight[] =
		{ 4, 4, 4, 4,
		4, 3, 3, 3,
		3, 2, 2, 4,
		4, 2, 2, 3,
		3, 2, 2, 4,
		4, 2, 2, 3,
		3, 3, 3, 4,
		4, 4, 4, 4};

//Constants and globals
/////////////////////////////////////////////////////////////////////////////////////////////////


int Player::PosValue(int pos, u_int8_t color)
{
	int value;

	if(color == CELL_WHITE)
	{
		if (pos >= 4 && pos <=7)
			value = 7;
		else
			value = 5;
	}else
	{
		if (pos >= 24 && pos <= 27)
			value = 7;
		else
			value = 5;
	}
	return value * PosWeight[pos];
}

int Player::NumberOfCheckersScoreWeighted2(const GameState &pState, std::string board, int availableMoves, bool bMaximizingPlayer, int checkersLeft)
{
	if (pState.isEOG() && pState.getNextPlayer() == player)
		return HighestScore;

	int score = 0;

	for(int i = 0; i < board.length(); i++)
	{
		if (player == CELL_RED && board[i] == 'r')
			score += (2 * PosValue(i, CELL_RED));
		else if (player == CELL_WHITE && board[i] == 'w')
			score += (2 * PosValue(i, CELL_WHITE));
		else if (player == CELL_RED && board[i] == 'R')
			score += ((checkersLeft <= 5 ? 7 : 6) * PosValue(i, CELL_RED));
		else if ( player == CELL_WHITE && board[i] == 'W')
			score += ((checkersLeft <= 5 ? 7 : 6) * PosValue(i, CELL_WHITE));
	}

	if(pState.getMove().isJump())
		score += 4;


	score += 2 * availableMoves;
	return score;

    
}


int Player::scoreBoard(const GameState & pState, string board, int availableMoves, bool bMaximizingPlayer, int checkersLeft){
//    int checkersLeft = TotalPiecesNum(pState.toMessage().substr(0,32));
	return NumberOfCheckersScoreWeighted2(pState, board, availableMoves, bMaximizingPlayer, checkersLeft);
}

bool Player::TerminalNode(const GameState &pState)
{
	return pState.isEOG();
}


int  Player::Utility(const GameState &pState, string board, int availableMoves, bool bMaximizingPlayer, int checkersLeft)
{
	if (TerminalNode(pState)){
		return (bMaximizingPlayer? HighestScore : LowestScore);
	}
	return scoreBoard(pState, board, availableMoves, bMaximizingPlayer, checkersLeft);
}

int Player::TotalPiecesNum(const std::string checkerBoard)
{
	int count  = 0;
	for(int i = 0; i<checkerBoard.length() ; i++)
	{
		if(checkerBoard[i]== 'W' | checkerBoard[i]== 'w' | checkerBoard[i]== 'R' | checkerBoard[i]== 'r' )
		{
			count++;
		}
	}
	return count;
}

// AlpaBeta Prunning //////////////////////////////////////////////////////
//
//
GameState Player::Invoke_MiniMax_AlphaBeta_Search(const GameState &pState, const Deadline &pDue,  bool bMaximizingPlayer, int maxDepth){
	std::vector<GameState> lNextStates;
	pState.findPossibleMoves(lNextStates);
	GameState* bestState = &lNextStates[0];
    GameState state = GameState(pState, Move());
//    GameState* bestState = &state;
	int bestValue = MinInt;

	int value;
	for(int i=0;  i<lNextStates.size(); i++)
	{
		value = MiniMax_AlphaBeta_Search2(lNextStates[i], pDue, MINPLAYER, maxDepth, 1, MinInt, MaxInt);
		if( bestValue < value ){
			bestValue = value;
			bestState = &lNextStates[i];
		}

	}
	return *bestState;
}

//int Player::MiniMax_AlphaBeta_Search(const GameState &pState, const Deadline &pDue,  bool bMaximizingPlayer, int depth, float alpha, float beta)
//{
//	std::vector<GameState> lNextStates;
//	pState.findPossibleMoves(lNextStates);
//    int checkersLeft = TotalPiecesNum(pState.toMessage().substr(0,32));
//
//    if(checkersLeft <= 2)
//        depth += 3;
////    LOGINF "board: " << pState.toMessage().substr(0,32) << " checkersLeft# " << checkersLeft << " maxDepth: " << depth;
//        
//	if ((depth <= 0) || (TerminalNode(pState))){
//		return Utility(pState, pState.toMessage().substr(0,32), lNextStates.size(), bMaximizingPlayer, checkersLeft);
//	}
////	GameState* bestState = &lNextStates[0];
//	
//	GameState bestState = pState;
//	int value;
//	
//	if (bMaximizingPlayer==MAXPLAYER){
//		for(int i=0;  i<lNextStates.size(); i++)
//		{
//			value = MiniMax_AlphaBeta_Search(lNextStates[i], pDue, MINPLAYER, depth-1, alpha, beta);
//			if(alpha < value)
//			{
//				alpha =  value;
//			}
//			if(alpha >= beta)
//						break;
//			return alpha;
//		}
//	}
//	else if (bMaximizingPlayer==MINPLAYER){
//		for(int i=0;  i<lNextStates.size(); i++)
//		{
//			value = MiniMax_AlphaBeta_Search(lNextStates[i], pDue, MAXPLAYER, depth-1, alpha, beta);
//			if(beta > value)
//			{
//				beta = value;
//			}
//			if(alpha >= beta)
//						break;
//			return beta;
//		}
//	}
//}

int Player::MiniMax_AlphaBeta_Search2(const GameState &pState, const Deadline &pDue,  bool bMaximizingPlayer, int maxDepth, int depth, float alpha, float beta)
{		
	std::vector<GameState> lNextStates;
	pState.findPossibleMoves(lNextStates);
	
	int checkersLeft = TotalPiecesNum(pState.toMessage().substr(0,32));
	
	if (checkersLeft <= 2)
		maxDepth = 12;

    if ((depth == maxDepth) || pState.isEOG()){ //.(TerminalNode(pState))){
		return Utility(pState, pState.toMessage().substr(0,32), lNextStates.size(), bMaximizingPlayer, checkersLeft);
	}
	
	int score;
	if (bMaximizingPlayer==MAXPLAYER)
	{
		score = MinInt;
		for(int i=0;  i<lNextStates.size(); i++)
		{
			score = std::max<int>(score, MiniMax_AlphaBeta_Search2(lNextStates[i], pDue, MINPLAYER, maxDepth, depth+1, alpha, beta));
			if (score >= beta)
				return score;

			alpha = std::max<int>(score, alpha);
		}
	} else
	{ //MINPLAYER
		score = MaxInt;
		for(int i=0;  i<lNextStates.size(); i++)
		{
			score = std::min<int>(score, MiniMax_AlphaBeta_Search2(lNextStates[i], pDue, MAXPLAYER, maxDepth, depth+1, alpha, beta));
			if (score <= alpha)
				return score;
			
			beta = std::min<int>(score, beta);
		}
	}
	return score;

}

//
//
//
// AlpaBeta Prunning //////////////////////////////////////////////////////


void Player::LogNxtMovs(const GameState &pState){
    std::vector<GameState> lNextStates;
    pState.findPossibleMoves(lNextStates);
    int size = lNextStates.size();
    uint8_t player = pState.getNextPlayer();

    LOGDEB1 "########## START TURN ##########";
    LOGDEB1 "Next Player: "<< player;
    LOGDEB1 "lNextStates Size "<< size;
	for(int i = 0; i< size; i++){
		FILE_LOG(logDEBUG1)<< "\n" << lNextStates[i].toString(player);
	}
	LOGDEB1 "##########  END TURN  ##########";
}





GameState Player::play(const GameState &pState,const Deadline &pDue)
{
//	FILELog::ReportingLevel() = FILELog::FromString("INFO");
//	FILE* pFile = fopen("./debug.log", "a");
//	Output2FILE::Stream() = pFile;

	player = pState.getNextPlayer();
    std::vector<GameState> lNextStates;
    pState.findPossibleMoves(lNextStates);

    if (lNextStates.size() == 0) return GameState(pState, Move());
    /*
     * Here you should write your clever algorithms to get the best next move, ie the best
     * next state. This skeleton returns a random move instead.
     */
//    GameState* result;
    GameState resultTemp;
//    NodeValPair* resultNodevalPair;
    int maxDepth = 9;
    resultTemp  = Invoke_MiniMax_AlphaBeta_Search(pState, pDue, MAXPLAYER, maxDepth);
//    resultTemp = lNextStates[rand() % lNextStates.size()];
    return resultTemp;
}

/*namespace checkers*/ }
