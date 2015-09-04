#ifndef _BOXES_H
#define _BOXES_H

#include <vector>

using std::vector;

struct Boxes {

	unsigned int gravityDirection;
	unsigned int boxColour;
	bool isMovable;
	unsigned int boxLocationX;
	unsigned int boxLocationY;
	bool beingHeldRight;
	bool beingHeldLeft;

};

//Spawns the boxes every level.
void spawnBoxes(unsigned int boxSpawnX, unsigned int boxSpawnY, string boxColour);

//Updates every single box every frame.
void boxesUpdate();

//Handles the gravity for the boxes. Grey and Yellow boxes will fall downwards, while Purple boxes float upwards.
void boxesGravity(Boxes & box);

//Finds the box that is being grabbed(if any) when the player presses C.
void grabBox(collisionDirection direction);

//Move the boxes if they are being held by the player.
void moveBox(Boxes &box);

//Releases the box that is being held in the player's hands.
void releaseBox(); //This releases a specific box.
void releaseBox(Boxes &box); //This checks through every single box to make sure every one is being released. releaseBox() works but this is just to make sure.

//Helps with checking what the box can destroy and what it cannot.
bool canDestroy(unsigned int &j);

//Collision detection for boxes for all for all 4 directions.
bool boxesCollisionUp(Boxes &box);
bool boxesCollisionDown(Boxes &box);
bool boxesCollisionRight(Boxes &box);
bool boxesCollisionLeft(Boxes &box);

#endif