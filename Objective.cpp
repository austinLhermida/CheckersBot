//
//  Objective.cpp
//  ECE141A_Assignment5
//
//  Created by Kyle Ng on 3/6/19.
//  Copyright © 2019 Kyle Ng. All rights reserved.
//

#include "Objective.hpp"
#include <stack>

namespace ECE141 {
    int Objective::rankMove(Move &aMove, Game &theGame) { //assign a score for each move
        if(aMove.moveLoc.row == aMove.piece->location.row && aMove.moveLoc.col == aMove.piece->location.col) {
            return -21;
        }
        
        int points = 0;
        
        points += canJumpEnemy(aMove);
        points += canDefendAlly(aMove,theGame);
        points += canAdvanceToKing(aMove,theGame);
        points += isSafeMove(aMove,theGame);
        points += isEdgeMove(aMove,theGame);
        points += allDirections(aMove,theGame);
        points += isEdgePiece(aMove,theGame);
        
        aMove.score = points;
        return points;
    }
    
    Move Objective::pickBestMove(std::map<direction,Move> &listOfMoves) { //Pick the highest scoring move
        auto currentMove = listOfMoves.begin();
        auto lastMove = listOfMoves.end();
        Move bestMove(currentMove->second.piece,currentMove->second.moveLoc);
        int bestScore = 0;
        
        while(currentMove!=lastMove) {
            if (currentMove->second.score > bestScore) {
                bestScore = currentMove->second.score;
                bestMove.piece = currentMove->second.piece;
                bestMove.moveLoc = currentMove->second.moveLoc;
                bestMove.score = currentMove->second.score;
                bestMove.jump = currentMove->second.jump;
            }
            currentMove++;
        }
        return bestMove;
    }
    
    int Objective::canJumpEnemy(Move &aMove) { //Piece is jumping an enemy
        if(aMove.jump) {
            return 10;
        }
        return 0;
    }
    
    int Objective::canDefendAlly(Move &aMove, Game &theGame) { //Piece is moving behind a friendly piece
        int points = 0;
        Piece tempPiece(aMove.piece->color, aMove.moveLoc, aMove.piece->kind); //simulate piece has moved to moveLoc
        std::map<direction, const Location> nearMove = Neighborhood::nearbyLocations(tempPiece, theGame); //nearby locations of moveLoc
        
        auto currLoc = nearMove.begin();
        auto lastLoc = nearMove.end();
        
        while(currLoc!=lastLoc) {
            if(currLoc->first==direction::fLeft || currLoc->first==direction::fRight) { //check if friendly piece is fLeft or fRight of moveLoc
                const Tile* currTile = theGame.getTileAt(currLoc->second);
                if(currTile->piece) {
                    if(currTile->piece->color==tempPiece.color) points+=4;
                }
            }
            currLoc++;
        }
        return points;
    }
    
    int Objective::isSafeMove(Move &aMove, Game &theGame) { //Piece is moving to a tile that does not make it vulnerable to an enemy
        //CHECK IF TILES ARE VALID LOCATIONS ON BOARD
        int points = 0;
        Piece tempPiece(aMove.piece->color, aMove.moveLoc, aMove.piece->kind); //simulate piece has moved to moveLoc
        std::map<direction,const Location> nearMove = Neighborhood::nearbyLocations(tempPiece, theGame); //locations around moveLoc
        auto currLoc = nearMove.begin(); //iterate through locations around moveLoc
        auto lastLoc = nearMove.end();
        
        while(currLoc!=lastLoc) {
            if(currLoc->first==direction::fLeft || currLoc->first==direction::fRight) { //check for fLeft and fRight of moveLoc
                const Tile* currTile = theGame.getTileAt(currLoc->second);
                if(currTile->piece) {
                    switch(currLoc->first) {
                        case direction::fLeft: {
                            if(currTile->piece->color!=tempPiece.color) {
                                try {
                                    const Tile* bRightTile = theGame.getTileAt(nearMove.at(direction::bRight));
                                    if(bRightTile->piece) {
                                        points+=1;
                                    } else {
                                        points-=10;
                                    }
                                }
                                catch(const std::out_of_range &oor) {
                                    points+=1;
                                }
                            }
                            break;
                        }
                        case direction::fRight: {
                            if(currTile->piece->color!=tempPiece.color) {
                                try {
                                    const Tile* bRightTile = theGame.getTileAt(nearMove.at(direction::bRight));
                                    if(bRightTile->piece) {
                                        points+=1;
                                    } else {
                                        points-=10;
                                    }
                                }
                                catch(const std::out_of_range &oor) {
                                    points+=1;
                                }
                            }
                            break;
                        }
                    }
                } else {
                    points +=1;
                }
            }
            currLoc++;
        }
        return points;
    }
    
    int Objective::canAdvanceToKing(Move &aMove, Game &theGame) { //Piece is beyond the middle of the map, per side
		int row = aMove.moveLoc.row;
        PieceColor pieceColor = aMove.piece->color;
        if(pieceColor == PieceColor::gold && row > 3) {
            return 1;
        } else if(row < 4) {
            return 1;
        }
        return 0;
    }
    
    int Objective::isEdgeMove(Move &aMove, Game &theGame) { //Piece is moving to an edge, safe spot
        if(aMove.moveLoc.col == (0|7) || aMove.moveLoc.row == (0|7)) {
            return 2;
        }
        return 0;
    }
    
    int Objective::allDirections(Move &aMove, Game &theGame) { //Piece can move in all directions
        int availableDirection = 1;
        Piece tempPiece(aMove.piece->color, aMove.moveLoc, aMove.piece->kind); //simulate piece has moved to moveLoc
        std::map<direction,const Location> nearMove = Neighborhood::nearbyLocations(tempPiece, theGame);
        auto currLoc = nearMove.begin();
        auto lastLoc = nearMove.end();
        
        while(currLoc!=lastLoc) {
            switch(aMove.piece->kind) {
                case PieceKind::pawn: {
                    if(currLoc->first==direction::fLeft || currLoc->first==direction::fRight) {
                        const Tile* currTile = theGame.getTileAt(nearMove.at(currLoc->first)); //ERROR HERE
                        if(currTile->piece) availableDirection = 0;
                    }
                    break;
                }
                case PieceKind::king: {
                    const Tile* currTile = theGame.getTileAt(nearMove.at(currLoc->first)); //ERROR HERE
                    if(currTile->piece) availableDirection = 0;
                }
            }
            currLoc++;
        }
        return availableDirection;
    }
    
    int Objective::isEdgePiece(Move &aMove, Game &theGame) { //Piece is on the edge of the board
        int row = aMove.moveLoc.row;
        int col = aMove.moveLoc.col;
        if(row==(0|7) || col==(0|7)) {
            return -1;
        }
        return 0;
    }
}
