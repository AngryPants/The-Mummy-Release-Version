#include "game.h"
#include "MoveCharacter.h"
#include "collisionDetection.h"
#include "boxes.h"
#include "Music.h"

//External Variables
extern COORD charLocation;
extern bool keyPressed[K_COUNT];
extern Boxes *g_heldBox;
extern unsigned int timeStoodStill;

bool keyDownedJump = false;

//Local Variables
Mummy mummy;

void moveCharacter()
{
	if (!keyPressed[K_UP]) {
		keyDownedJump = false;
	}

    // Updating the location of the character based on the key press
	collisionDirection up = Up;
	collisionDirection down = Down;
	collisionDirection left = Left;
	collisionDirection right = Right;

	//Able to jump up.
	if (mummy.onGround && charLocation.Y > 0 && keyPressed[K_UP] && playerCollisionDetectionUp() && !keyDownedJump) {
		playMusic(1);
		keyDownedJump = true;
        mummy.jumpHeight = 5;
    }

	//In the process of jumping.
	if (mummy.jumpHeight > 0 && charLocation.Y > 0 && playerCollisionDetectionUp()) {
		--charLocation.Y;
		--mummy.jumpHeight;

	//Falling
	} else if (playerCollisionDetectionDown()) {
		mummy.jumpHeight = 0;
		++charLocation.Y;
	}

	//Is the Mummy still in mid-air?
	if (playerCollisionDetectionDown()) {
		mummy.onGround = false;
	} else {
		mummy.onGround = true;
	}

	//Moving left when NOT holding box.
	if (!mummy.isGrabbing) {

		if (charLocation.X > 0 && keyPressed[K_LEFT] && playerCollisionDetectionLeft()) {
			timeStoodStill = 60;
			--charLocation.X;
			mummy.charDirection = 1;
		} else if (charLocation.X > 0 && keyPressed[K_LEFT] && keyPressed[K_GRAB]) {
			grabBox(left);
		}

	} else {

		if (g_heldBox->beingHeldLeft) {
			if (charLocation.X > 0 && keyPressed[K_LEFT] && boxesCollisionLeft(*g_heldBox)) {
				timeStoodStill = 60;
				--charLocation.X;
				mummy.charDirection = 1;
			}
		} else if (g_heldBox->beingHeldRight) {
			if (charLocation.X > 0 && keyPressed[K_LEFT] && playerCollisionDetectionLeft()) {
				timeStoodStill = 60;
				--charLocation.X;
				mummy.charDirection = 1;
			}
		}

		if (keyPressed[K_DOWN]) {
			releaseBox();
		}

	}

	//Moving right when NOT holding box.
	if (!mummy.isGrabbing) {

		if (charLocation.X < worldSizeX && keyPressed[K_RIGHT] && playerCollisionDetectionRight()) {
			timeStoodStill = 60;
			++charLocation.X;
			mummy.charDirection = 2;
		} else if (charLocation.X < worldSizeX && keyPressed[K_RIGHT] && keyPressed[K_GRAB]) {
			grabBox(right);
		}

	} else { //Moving Right When Holding Box

		if (g_heldBox->beingHeldLeft) {
			if (charLocation.X < worldSizeX && keyPressed[K_RIGHT] && playerCollisionDetectionRight()) {
				timeStoodStill = 60;
				++charLocation.X;
				mummy.charDirection = 2;
			}
		} else if (g_heldBox->beingHeldRight) {
			if (charLocation.X < worldSizeX && keyPressed[K_RIGHT] && boxesCollisionRight(*g_heldBox)) {
				timeStoodStill = 60;
				++charLocation.X;
				mummy.charDirection = 2;
			}
		}

		if (keyPressed[K_DOWN]) {
			releaseBox();
		}

	}

	//Not moving (No detection needed)
	if (keyPressed[K_RIGHT] == false && keyPressed[K_LEFT] == false) {
		mummy.charDirection = 0;
	}

}