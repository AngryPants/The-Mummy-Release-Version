// This is the main file for the game logic and function

#include "setlevelitems.h"
#include "game.h"
#include "monster.h"
#include "shooter.h"
#include "Framework\console.h"
#include "loadlevel.h"
#include "teleporters.h"
#include "boxes.h"
#include "menu.h"
#include "collisionDetection.h"
#include "keys.h"
#include "loadlevel.h"
#include "inventory.h"
#include "camera.h"
#include "movecharacter.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include "doors.h"
#include "LevelMenu.h"
#include "printMessages.h"
#include "Music.h"

// Console object
Console console(180, 50, "The Mummy");

double elapsedTime;
double deltaTime;
bool keyPressed[K_COUNT];

//Checks if the game state is Pause, Play etc.
extern State g_gameState;

//Makes sure the key is lifted before allowing the player to press again to prevent the game from double sensing key presses.
bool keyIsLifted = true;

//Character;
extern Mummy mummy;

//Location of player.
COORD charLocation;

//Find the distance of the Mummy from the camera start points to know where exactly to render the Mummy.
extern int distanceFromCamX;
extern int distanceFromCamY;

//Boxes
extern Boxes *g_heldBox;

//Decide whether to load map or not
bool bupdateWorldGrid = true;

//Which level map to load.
unsigned int g_levelNumber = 0;

/*2D array to store the position of the walls and items etc.
This is like a grid. (0, 0) here is the same as (0, 0) on the "world".
Use this together with charLocation.X & charLocation.Y to manipulate the Mummy.
For example, a teleporter could teleport our dear Mummy to (80, 90) by doing charLocation.X = 80 and charLocation.Y = 90.*/
unsigned int g_worldGrid[worldSizeX][worldSizeY] = {0};

// Initialize variables, allocate memory, load data from file, etc. 
// This is called once before entering into your main loop
void init()
{
    //Set precision for floating point output
    elapsedTime = 0.0;

    //Sets the width, height and the font name to use in the console
    console.setConsoleFont(0, 16, L"Arial");
}

// Do your clean up of memory here
// This is called once just before the game exits
void shutdown()
{
    // Reset to white text on black background
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

    console.clearBuffer();
}

/*This function checks if any key had been pressed since the last time we checked
If a key is pressed, the value for that particular key will be true
Add more keys to the enum in game.h if you need to detect more keys
To get other VK key defines, right click on the VK define (e.g. VK_UP) and choose "Go To Definition" 
For Alphanumeric keys, the values are their ascii values (uppercase).*/
void getInput()
{    
    keyPressed[K_UP] = isKeyPressed(VK_UP);
    keyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
    keyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
    keyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
	keyPressed[K_PAUSE] = isKeyPressed(0x50);
    keyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
	keyPressed[K_ENTER] = isKeyPressed(VK_RETURN);
	keyPressed[K_GRAB] = isKeyPressed(0x43);
	keyPressed[K_RESTART] = isKeyPressed(0x52);
}

/*This is the update function
double dt - This is the amount of time in seconds since the previous call was made

Game logic should be done here.
Such as collision checks, determining the position of your game characters, status updates, etc
If there are any calls to write to the console here, then you are doing it wrong.
If your game has multiple states, you should determine the current state, and call the relevant function here.*/
void update(double dt)
{
    //Gets the delta time
    elapsedTime += dt;
    deltaTime = dt;
	
	//Updates the world grid. Only do it once per level. Set bupdateWorldGrid to true whenever you load a new level.
	//It will turn itself off after it update once.
	if (bupdateWorldGrid == true) {
		updateWorldGrid(g_levelNumber);
		bupdateWorldGrid = false;
	}

	//Updates the position of the camera.
	moveCameraTo();

	//Checks if you should change states or do something else with the game, e.g. pause, exit.
    processUserInput(); 
    
	//Sets the position of the teleporters in the level and check if the player can teleport through them in this frame.
	setItemsInLevel();

	//Updates the position of the monsters and if the player is killed by them.
	monsterUpdate();

	//Moves the character, collision detection, physics, etc
	moveCharacter();

	//Updates the position of the box. Ensure that this is called AFTER moveCharacter to prevent glitches.
	boxesUpdate();

	//Checks if the player has walked over an item.
	detectItemsCollision();
	
	//Update the bullet(?)
	bulletUpdate();

}

/*This is the render loop
At this point, you should know exactly what to draw onto the screen, so just draw it!
To get an idea of the values for colours, look at console.h and the URL listed there*/
void render() {
    
	//Clears the current screen and draw from scratch.
	clearScreen();
    renderMap();
	renderShooter();
	renderCharacter(mummy.charDirection);
	renderBoxes();
	renderMonsters();
	renderMessages();

	//Dump the contents of the buffer to the screen. One frame worth of the game.
    renderToScreen();

}

void processUserInput()
{
	/*Pause game when P is pressed.
	Or quit to main menu when ESC is pressed.
	Or restart the level when r is pressed.*/
	if (keyPressed[K_PAUSE] && g_gameState == Play && keyIsLifted) {
		g_gameState = Pause;
		keyIsLifted = false;
	} else if (g_gameState == Pause && keyPressed[K_PAUSE] && keyIsLifted) {
		g_gameState = Play;
		keyIsLifted = false;
	} else if (g_gameState == Pause && keyPressed[K_ESCAPE] && keyIsLifted) {
		g_gameState = Menu;
		clearScreen();
		keyIsLifted = false;
	} else if (g_gameState == Play && keyPressed[K_RESTART] && keyIsLifted) {
		g_gameState = Play;
		updateWorldGrid(g_levelNumber);
		clearInventory();
		keyIsLifted = false;
	}
	
	//Checks if the Escape and P key is not being pressed.
	if (!keyPressed[K_PAUSE] && !keyPressed[K_ESCAPE]) {
		keyIsLifted = true;
	}

}

void clearScreen() {
    // Clears the buffer with this colour attribute
    console.clearBuffer(0x0F);
}

void renderMap() {
    
	//Set up sample colours, and output shadings
    const WORD colors[] = {
        0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
        0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
    };

	//Render what the parts of the map the camera can see.
	renderView();

}

void renderFramerate() {
    COORD c;
    //Displays the framerate of the game.
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(3);
    ss << 1.0 / deltaTime << "FPS";
    c.X = console.getConsoleSize().X - 9;
    c.Y = 0;
    console.writeToBuffer(c, ss.str());
}

void renderToScreen() {
    //Writes the buffer to the console, hence you will see what you have written.
    console.flushBufferToConsole();
}