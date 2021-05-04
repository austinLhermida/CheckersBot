//
//  KyleAustinPlayer.hpp
//  ECE141A_Assignment5
//
//  Created by Kyle Ng on 3/6/19.
//  Copyright © 2019 Kyle Ng. All rights reserved.
//

#ifndef KyleAustinPlayer_hpp
#define KyleAustinPlayer_hpp

#include <stdio.h>
#include "Neighborhood.hpp"
#include "Objective.hpp"

namespace ECE141 {
    class KyleAustinPlayer : public Player {
    public:
        KyleAustinPlayer();
        bool        takeTurn(Game &aGame); //OVERRIDE THIS...
        const       PieceColor  color;
        static int  pcount; //how many created so far?
    };
}

#endif /* KyleAustinPlayer_hpp */
