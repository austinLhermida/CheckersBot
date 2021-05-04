//
//  KyleAustinPlayer.cpp
//  ECE141A_Assignment5
//
//  Created by Kyle Ng on 3/6/19.
//  Copyright © 2019 Kyle Ng. All rights reserved.
//


#include "KyleAustinPlayer.hpp"

namespace ECE141 {
    int KyleAustinPlayer::pcount = 0; //init our static member to track # of players...
    
    static PieceColor autoColor() { //auto assigns a color
        return (++KyleAustinPlayer::pcount % 2) ? PieceColor::blue : PieceColor::gold;
    }
    
   KyleAustinPlayer::KyleAustinPlayer() : color(autoColor()) {}
    
    bool KyleAustinPlayer::takeTurn(Game &aGame) { //still need to rank moves
        size_t theCount=aGame.countAvailablePieces(color);
        //std::cout << "Number of pieces available: " << theCount <<std::endl;
        std::map<direction,Move> allMoves;
        //std::cout << "allMoves map generated" << std::endl;
        for(int pos=0;pos<theCount;pos++) {
            //std::cout << "Piece number: " << pos <<std::endl;
            if(const Piece *thePiece = aGame.getAvailablePiece(this->color, pos)) {
                //  std::cout << "Piece found" << std::endl;
                std::map<direction,const Location> nearbyLocs = Neighborhood::nearbyLocations(*thePiece, aGame);
                // std::cout << "Nearby locations generated" << std::endl;
                std::map<direction,Move> pieceMoves = Neighborhood::generateMoves(thePiece, nearbyLocs, aGame);
                //std::cout << "Map for piece's moves generated" << std::endl;
                auto currMove = pieceMoves.begin();
                auto lastMove = pieceMoves.end();
                
                while(currMove!=lastMove) {
                    //std::cout << "Iterating through moves" << std::endl;
                    currMove->second.score = Objective::rankMove(currMove->second, aGame);
                    allMoves.insert({currMove->first,currMove->second});
                    
                    /*
                     std::cout << "Move: " << "(" << currMove->second.moveLoc.row << ", " << currMove->second.moveLoc.col << "), " << "Move score: " << currMove->second.score;
                     switch(currMove->first) {
                     case direction::fLeft:
                     std::cout << ", Direction: fLeft" << std::endl;
                     break;
                     case direction::fRight:
                     std::cout << ", Direction: fRight" << std::endl;
                     break;
                     case direction::bLeft:
                     std::cout << ", Direction: bLeft" << std::endl;
                     break;
                     case direction::bRight:
                     std::cout << ", Direction: bRight" << std::endl;
                     break;
                     case direction::nullMove:
                     std::cout << ", Direction: nullMove" << std::endl;
                     break;
                     }
                     */
                    
                    currMove++;
                }
            }
        }
        // std::cout << "total moves: " << allMoves.size() << std::endl;
        Move bestMove = Objective::pickBestMove(allMoves);
        /*
         std::cout << "Best move picked" << std::endl;
         std::cout << "Moving PieceKind: " << ((bestMove.piece->kind==PieceKind::pawn) ? "pawn" : "king") << std::endl;
         std::cout << "Piece was moved from (" << bestMove.piece->location.row << ", " << bestMove.piece->location.col << ") " << "to: (" << bestMove.moveLoc.row << ", " << bestMove.moveLoc.col << ") with score " << bestMove.score << std::endl;
         */
        aGame.movePieceTo(*bestMove.piece, bestMove.moveLoc);
        return true; //if you return false, you forfeit!
    }
}
