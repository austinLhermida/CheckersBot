//
//  Objective.hpp
//  ECE141A_Assignment5
//
//  Created by Kyle Ng on 3/6/19.
//  Copyright © 2019 Kyle Ng. All rights reserved.
//

#ifndef Objective_hpp
#define Objective_hpp

#include <stdio.h>
#include "Neighborhood.hpp"
#include "Player.hpp"

namespace ECE141 {
    
    class Objective {
    public:
        static int rankMove(Move &aMove, Game &theGame); //assign point value to a move
        static Move pickBestMove(std::map<direction,Move> &listOfMoves); //pick move with highest point value
    private:
        static int canJumpEnemy(Move &aMove);                       //jump enemy piece
        static int canDefendAlly(Move &aMove, Game &theGame);       //move closest back row pawn to vulnerable tile of another ally piece
        static int canAdvanceToKing(Move &aMove, Game &theGame);    //move most-forward pawn forward to safe tile
        static int isSafeMove(Move &aMove, Game &theGame);          //move piece to tile that is non-adjacent to enemy
        static int isEdgeMove(Move &aMove, Game &theGame);          //move piece to available edge tile
        static int allDirections(Move &aMove, Game &theGame);       //piece able to move left or right (forward and back for king)
        static int isEdgePiece(Move &aMove, Game &theGame);         //maintain edge position (assign negative points if leaving edge)
    };
}

#endif /* Objective_hpp */
