#ifndef _GAME_H
#define _GAME_H

//Custom Variables
#define worldSizeX 601
#define worldSizeY 201
#define cameraCollisionX 150
#define cameraCollisionY 50

#include "Framework\timer.h"
#include <string>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::string;

extern StopWatch g_timer;
extern bool g_quitGame;

enum Keys
{
    K_UP,
    K_DOWN,
    K_LEFT,
    K_RIGHT,
    K_ESCAPE,
	K_PAUSE,
	K_ENTER,
	K_GRAB,
	K_RESTART,
    K_COUNT
};

enum State {
	Menu,
	Play,
	Pause,
	Exit,
	MAX_STATE
};

enum collisionDirection {
	Up,
	Down,
	Left,
	Right,
	MAX_COLLISIONDIRECTION
};

void init();              // initialize your variables, allocate memory, etc
void getInput();          // get input from player
void update(double dt);   // update the game and the state of the game
void render();            // renders the current state of the game to the console
void shutdown();		  // do clean up, free memory
void updateMenu();
void processUserInput();  // checks if you should change states or do something else with the game, e.g. pause, exit
void clearScreen();       // clears the current screen and draw from scratch 
void renderMap();         // renders the map to the buffer first
void renderFramerate();   // renders debug information, frame rate, elapsed time, etc
void renderToScreen();// dump the contents of the buffer to the screen, one frame worth of game
void mainLoop();

#endif // _GAME_H