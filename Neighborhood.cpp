//
//  Neighborhood.cpp
//  ECE141A_Assignment5
//
//  Created by Kyle Ng on 3/6/19.
//  Copyright © 2019 Kyle Ng. All rights reserved.
//

#include "Neighborhood.hpp"
#include <iostream>

namespace ECE141 {

    std::map<direction,const Location> Neighborhood::nearbyLocations(const Piece &aPiece, Game &theGame) { //Obtain all valid nearby locations
        std::map<direction,const Location> allLocs;
        
        if(theGame.validLocation(fLeft(aPiece))) { //if locations are valid places on the board
            allLocs.insert({direction::fLeft,fLeft(aPiece)}); //generate a Location object for that location
            //std::cout << "fLeft nearby location found" << std::endl;
        }
        if(theGame.validLocation(fRight(aPiece))) {
            allLocs.insert({direction::fRight,fRight(aPiece)});
            //std::cout << "fRight nearby location found" << std::endl;
        }
        if(theGame.validLocation(bLeft(aPiece))) {
            allLocs.insert({direction::bLeft,bLeft(aPiece)});
            //std::cout << "bLeft nearby location found" << std::endl;
        }
        if(theGame.validLocation(bRight(aPiece))) {
            allLocs.insert({direction::bRight,bRight(aPiece)});
            //std::cout << "bRight nearby location found" << std::endl;
        }
        
    
        return allLocs;
    }
    
    std::map<direction,Move> Neighborhood::generateMoves(const Piece *aPiece, std::map<direction,const Location> &nearbyLocs, Game &theGame) { //Generate all possible moves for a given piece
        std::map<direction,Move> moveList;
        
        auto currLoc = nearbyLocs.begin();
        auto lastLoc = nearbyLocs.end();
        while(currLoc!=lastLoc) {
            const Tile* currTile = theGame.getTileAt(currLoc->second); //get tile at potential moveLoc
                switch(currLoc->first) {
                    case direction::fLeft: {//if moving fLeft
                        if(currTile->piece) {
                            if(currTile->piece->color!=aPiece->color) {
                                const Tile* otherSide = theGame.getTileAt(bRight(*(currTile)->piece)); //get second fLeft tile
                                if(otherSide!=NULL && (! otherSide->piece)) { //if tile is empty, jump
                                    moveList.insert({currLoc->first,Move(aPiece,otherSide->location)}); //generate jump move
                                    moveList.at(currLoc->first).jump = true; //indicate jump move
                                } else { //if enemy piece is on otherSide
                                    moveList.insert({direction::nullMove,Move(aPiece,aPiece->location)}); //nullMove if piece on other side
                                }
                            } else { //if piece is our color
                                moveList.insert({direction::nullMove,Move(aPiece,aPiece->location)}); ///nullMove since we can't jump our own piece
                            }
                        } else { //if no piece there
                            moveList.insert({currLoc->first,Move(aPiece,currLoc->second)}); //standard, non-jump move
                        }
                        break;
                    }
                    case direction::fRight: {
                        if(currTile->piece) {
                            if(currTile->piece->color!=aPiece->color) {
                                const Tile* otherSide = theGame.getTileAt(bLeft(*(currTile)->piece)); //get second fLeft tile
                                if(otherSide!=NULL && (! otherSide->piece)) { //if tile is empty, jump
                                    moveList.insert({currLoc->first,Move(aPiece,otherSide->location)});
                                    moveList.at(currLoc->first).jump = true;
                                } else { //if enemy piece is on otherSide
                                    moveList.insert({direction::nullMove,Move(aPiece,aPiece->location)});
                                }
                                
                            } else { //if piece is our color
                                moveList.insert({direction::nullMove,Move(aPiece,aPiece->location)});
                            }
                        } else { //if no piece there
                            moveList.insert({currLoc->first,Move(aPiece,currLoc->second)});
                        }
                        break;
                    }
                    case direction::bLeft: {
                        if(aPiece->kind == PieceKind::pawn) { //bLeft move only for King
                            moveList.insert({direction::nullMove,Move(aPiece,aPiece->location)});
                            break;
                        } else {
                            if(currTile->piece) {
                                if(currTile->piece->color!=aPiece->color) {
                                    const Tile* otherSide = theGame.getTileAt(fRight(*(currTile)->piece)); //get tile on opposite side of opponent's piece
                                    if(otherSide!=NULL && (! otherSide->piece)) { //if tile is empty, jump
                                        moveList.insert({currLoc->first,Move(aPiece,otherSide->location)});
                                        moveList.at(currLoc->first).jump = true;
                                    } else { //if enemy piece is on otherSide
                                        moveList.insert({direction::nullMove,Move(aPiece,aPiece->location)});
                                    }
                                    
                                } else { //if piece is our color
                                    moveList.insert({direction::nullMove,Move(aPiece,aPiece->location)});
                                }
                            } else { //if no piece there
                                moveList.insert({currLoc->first,Move(aPiece,currLoc->second)});
                            }
                            break;
                        }
                    }
                    case direction::bRight: {
                        if(aPiece->kind == PieceKind::pawn) { //bRight move only for King
                            moveList.insert({direction::nullMove,Move(aPiece,aPiece->location)});
                            break;
                        } else {
                            if(currTile->piece) {
                                if(currTile->piece->color!=aPiece->color) {
                                    const Tile* otherSide = theGame.getTileAt(fLeft(*(currTile)->piece)); //get tile on opposite side of opponent's piece
                                    if(otherSide!=NULL && (! otherSide->piece)) { //if tile is empty, jump
                                        moveList.insert({currLoc->first,Move(aPiece,otherSide->location)});
                                        moveList.at(currLoc->first).jump = true;
                                    } else { //if enemy piece is on otherSide
                                        moveList.insert({direction::nullMove,Move(aPiece,aPiece->location)});
                                    }
                                } else { //if piece is our color
                                    moveList.insert({direction::nullMove,Move(aPiece,aPiece->location)});
                                }
                            } else { //if no piece there
                                moveList.insert({currLoc->first,Move(aPiece,currLoc->second)});
                            }
                            break;
                            }
                    }
                    case direction::nullMove: {
                        moveList.insert({direction::nullMove,Move(aPiece,aPiece->location)});
                        break;
                    }
                }
            currLoc++;
            }
        return moveList;
        }
    

    
    const Location Neighborhood::fLeft(const Piece &aPiece) { //create location for front left of piece
        int pieceRow = aPiece.location.row;
        int pieceCol = aPiece.location.col;
        PieceColor pieceColor = aPiece.color;
        if(pieceColor == PieceColor::gold) { //front is different depending on color
            return Location(pieceRow+1,pieceCol+1);
        } else {
            return Location(pieceRow-1,pieceCol-1);
        }
    }
    
    const Location Neighborhood::fRight(const Piece &aPiece) { //create location for front right of piece
        int pieceRow = aPiece.location.row;
        int pieceCol = aPiece.location.col;
        PieceColor pieceColor = aPiece.color;
        if(pieceColor == PieceColor::gold) { //front is different depending on color
            return Location(pieceRow+1,pieceCol-1);
        } else {
            return Location(pieceRow-1,pieceCol+1);
        }
    }
    
   const Location Neighborhood::bLeft(const Piece &aPiece) { //create location for back left of piece
        int pieceRow = aPiece.location.row;
        int pieceCol = aPiece.location.col;
        PieceColor pieceColor = aPiece.color;
        if(pieceColor == PieceColor::gold) { //back is different depending on color
            return Location(pieceRow-1,pieceCol+1);
        } else {
            return Location(pieceRow+1,pieceCol-1);
        }
    }
    
    const Location Neighborhood::bRight(const Piece &aPiece) { //create location for back right of piece
        int pieceRow = aPiece.location.row;
        int pieceCol = aPiece.location.col;
        PieceColor pieceColor = aPiece.color;
        if(pieceColor == PieceColor::gold) { //back is different depending on color
            return Location(pieceRow-1,pieceCol-1);
        } else {
            return Location(pieceRow+1,pieceCol+1);
        }
    }
    
}
