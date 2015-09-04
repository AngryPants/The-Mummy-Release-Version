#ifndef _COLLISIONDETECTION_H
#define _COLLISIONDETECTION_H

//General Collision Detection. Since our boxes and player is sized 3 by 3, it checks for 3 coordinates at a go.
bool collisionDetection(int a, int b, int c);

//Collision detection for player for all 4 directions.
bool playerCollisionDetectionUp();
bool playerCollisionDetectionDown();
bool playerCollisionDetectionLeft();
bool playerCollisionDetectionRight();

//Detect if the player has collided with items on the map.
void detectItemsCollision();

//Detect if the player has reached the portal to move on to the next level.
void detectGoToNextLevel();

//Detect if the player has either chosen to reset the level or has been killed, causing the level to restart.
void detectRestartLevel();
void detectRestartLevel(int X , int Y);

#endif