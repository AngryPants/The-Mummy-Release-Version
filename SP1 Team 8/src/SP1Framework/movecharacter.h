#ifndef _MOVECHARACTER_H
#define _MOVECHARACTER_H

//Moves the character.
void moveCharacter();

//The struct storing the traits of the player.
struct Mummy {
	//Direction the player is walking towards.
	char charDirection;
	//Jumping and Gravity
	char jumpHeight;
	bool onGround;
	//Is the player already holding a box?
	bool isGrabbing;
};

#endif