//
//  Neighborhood.hpp
//  ECE141A_Assignment5
//
//  Created by Kyle Ng on 3/6/19.
//  Copyright © 2019 Kyle Ng. All rights reserved.
//

#ifndef Neighborhood_hpp
#define Neighborhood_hpp

#include <stdio.h>
#include "Piece.hpp"
#include <map>
#include "Game.hpp"

namespace ECE141 {
    enum class direction    {fLeft, fRight, bLeft, bRight, nullMove};
    
    struct Move { //struct to track piece, location, score, jumping of move
        const Piece     *piece;
        Location        moveLoc;
        int             score;
        bool            jump;
        
        Move(const Piece *thePiece, const Location aLoc) : piece(thePiece), moveLoc(aLoc), score(0), jump(false) {}
        Move(const Move &aCopy) : piece(aCopy.piece), moveLoc(aCopy.moveLoc), score(aCopy.score), jump(aCopy.jump) {}

    };
    
    class Neighborhood {
    friend class Objective; // objective gains access to neighborhood's members
    public:
        static std::map <direction,const Location>      nearbyLocations(const Piece &aPiece, Game &theGame); //generate nearby locations
        static std::map<direction,Move>                 generateMoves(const Piece *aPiece, std::map<direction,const Location> &nearbyLocs, Game &theGame); //generate all possible moves of a piece
        
    private:
        static const Location                 fLeft(const Piece &aPiece); //unique per color, use validLocation for tile finding purposes in getTileAt
        static const Location                 fRight(const Piece &aPiece);
        static const Location                 bLeft(const Piece &aPiece);
        static const Location                 bRight(const Piece &aPiece);
    };
}

#endif /* Neighborhood_hpp */
