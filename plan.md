# ECE141 Winter 2019 -- Group Assignment #5
## Austin Hermida
## Kyle Ng
## PART 1 

# IMPLEMENTING PLAYER CLASS
##IMPLEMENTING NEIGHBORHOOD METHOD (return the game state of the adjacent pieces/squares)
1. Mark all pieces that can legally move
2. See if forward diagonals are occupied by a friendly piece 
3. See if forward diagonals are blocked by the board's edges 
4. Mark any tiles that are volatile: tiles that are a diagonal away from an enemy piece, resulting in losing that piece 
5. Mark any vulernable (i.e. friendly pieces that can be jumped) pieces and their vulernable tiles 
6. Mark any enemy pieces that are in "our" territory (in order to try to prevent kinging)
	- "our" territory is defined as the first three rows  


##IMPLEMENTING OBJECTIVE METHOD AS A PAWN (how close a given option is to the optimal option)
1. Jumping/eating an enemy piece takes the highest priority since it is a game rule 
2. Move the closest back row pawn to a vulernable tile marked by the Neighborhood Method 
3. If an unoccupied side tile is detected, the furthest pawn will move towards it 
4. Move the furthest pawn forward if there are no vulernable positions (in order to become a king)
5. If enemy can move to a edge tile, then try to move closest friendly pawn to the edge tile 
6. If a pawn has a valid bidirectional option (i.e. forward left and forward right), then randomly move in either direction 
7. If all moves are equally viable, then randomly move a back row piece forward 

##IMPLEMENTING OBJECTIVE METHOD AS A KING (how close a given option is to the optimal option)
1. Jumping/eating an enemy piece takes the highest priority since it is a game rule 
2. If enemy can move to a edge tile, then try to move closest friendly king to the edge tile 
3. If a king has all quad-directional options (i.e. forward left and forward right), then randomly move in a direction towards our side 
4. If all moves are equally viable, then randomly move a random King in a direction towards our side 
