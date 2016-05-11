#ifndef _CHECKERS_PLAYER_HPP_
#define _CHECKERS_PLAYER_HPP_

#include "constants.hpp"
#include "deadline.hpp"
#include "move.hpp"
#include "gamestate.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>



#define LOGLOC FILE_LOG(logDEBUG) << __FUNCTION__;


#define LOGDEB4 FILE_LOG(logDEBUG4) <<
#define LOGDEB3 FILE_LOG(logDEBUG3) <<
#define LOGDEB2 FILE_LOG(logDEBUG2) <<
#define LOGDEB1 FILE_LOG(logDEBUG1) <<
#define LOGDEB FILE_LOG(logDEBUG) <<
#define LOGINF FILE_LOG(logINFO) <<

namespace checkers
{

class Player
{
public:

//	typedef struct NodeValPair;
	typedef struct NodeValPair
	{
		NodeValPair(GameState* pGameState, int val){
			state  = pGameState;
			value  = val;
		}
		GameState* state;
		int value;
	}NodeValPair;


	enum PlayerType{
		min = 0,
		max = 1
	};
	int plyr;
    ///perform a move
    ///\param pState the current state of the board
    ///\param pDue time before which we must have returned
    ///\return the next state the board is in after our move


//	class StateWrap{
//		public:
//			GameState pState;
//			hashCache;
//			long hashValue();
//
//
//	};


    GameState play(const GameState &pState, const Deadline &pDue);

    bool TerminalNode(const GameState &pState);
//    float Utility(const GameState &pState, PlayerType playerType);
    int NumberOfCheckersScore(const GameState &pState, std::string board, bool bMaximizingPlayer);
    int NumberOfCheckersScoreWeighted(const GameState &pState, std::string board, bool bMaximizingPlayer);
    int NumberOfCheckersScore3(const GameState &pState, std::string board, int availableMoves, bool bMaximizingPlayer);
    int NumberOfCheckersScore4(const GameState &pState, std::string board, int availableMoves, bool bMaximizingPlayer);
    int PosValue(int pos, u_int8_t color);
    int scoreBoard(const GameState & pState, std::string board, int availableMoves, bool bMaximizingPlayer);
    int Utility(const GameState &pState, std::string board, int availableMoves, bool bMaximizingPlayer);

//    float MinValue(const GameState &pState, const Deadline &pDue, enum PlayerType playerType);

    //Depth-limited MiniMax
    int MinValue(const GameState &pState, const Deadline &pDue, bool bMaximizingPlayer, int depth);
    //float MaxValue(const GameState &pState, const Deadline &pDue, enum PlayerType playerType);
    int MaxValue(const GameState &pState, const Deadline &pDue, bool bMaximizingPlayer, int depth);
    //GameState* MiniMax_Search(const GameState &pState, const Deadline &pDue, enum PlayerType uint8_t playerType);
    GameState* MiniMax_Search(const GameState &pState, const Deadline &pDue, bool bMaximizingPlayere, int depth);

    //Depth-limited MiniMax
    GameState Invoke_MiniMax_DepthLimited_Search(const GameState &pState, const Deadline &pDue,  bool bMaximizingPlayer, int depth);
    int MiniMax_DepthLimited_Search(const GameState &pState, const Deadline &pDue,  bool bMaximizingPlayer, int depth);

    //Test Dummy Search
    GameState Invoke_Test_Search(const GameState &pState, const Deadline &pDue,  bool bMaximizingPlayer, int depth);
    int Test_Search(const GameState &pState, const Deadline &pDue,  bool bMaximizingPlayer, int depth);


    //Alpha-beta Prunning

    int TotalPiecesNum(const std::string checkerBoard);



    //AlphaBeta MiniMax
    GameState Invoke_MiniMax_AlphaBeta_Search(const GameState &pState, const Deadline &pDue,  bool bMaximizingPlayer, int depth, float alpha, float beta);
    int MiniMax_AlphaBeta_Search(const GameState &pState, const Deadline &pDue,  bool bMaximizingPlayer, int depth, float alpha, float beta);


    void LogNxtMovs(const GameState &pState);

    // NegaMax_AlphaBeta_Search
    NodeValPair* NegaMax_AlphaBeta_Search(const GameState &pState, const Deadline &pDue, int depth, int alpha, int beta);
    int  NegaMaxUtility(const GameState &pState, std::string board, int availableMoves, bool bMaximizingPlayer);
};

/*namespace checkers*/ }

#endif
