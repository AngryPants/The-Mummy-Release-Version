// This is the main file to hold everthing together

#include "Framework\timer.h"
#include "Framework\console.h"
#include "game.h"
#include "menu.h"
#include "Music.h"

StopWatch g_timer;            // Timer function to keep track of time and the frame rate
bool g_quitGame = false;      // Set to true if you want to quit the game
const unsigned char FPS = 20; // FPS of this game
const unsigned int frameTime = 1000 / FPS; // time for each frame in milliseconds
extern Console console;
State g_gameState = Menu;

// TODO:
// Bug in waitUntil. it waits for the time from getElapsedTime to waitUntil, but should be insignificant.

void main()
{
	
	while (g_gameState != Exit) { //This runs as long as the player does not quit.

		if (g_gameState == Menu) {
			playMusic(0);
			menu();
		} else if (g_gameState == Play) {
			PlaySound(NULL, 0, 0);
			init();      // initialize your variables
			mainLoop();  // main loop
		}

	}
		
	if (g_gameState == Exit) {
		shutdown();  // do clean up, if any. free memory.
	}

}

// This main loop calls functions to get input, update and render the game
// at a specific frame rate
void mainLoop()
{

    g_timer.startTimer(); // Start timer to calculate how long it takes to render this frame

    while (g_gameState == Play) { //This loop runs while the game is being played. But not when in the Main Menu or when the game is paused. 

        getInput();                         // get keyboard input
        update(g_timer.getElapsedTime());   // update the game
        render();                           // render the graphics output to screen
        g_timer.waitUntil(frameTime);       // Frame rate limiter. Limits each frame to a specified time in ms.      
	}

	while(g_gameState == Pause) { //This loop runs when the game is being paused mid-game.

		getInput();
		processUserInput();
		clearScreen();
		console.writeToBuffer(50, 15, "Game Paused", 0x0F);
		console.writeToBuffer(45, 17, "Press P to continue.", 0x0F);
		console.writeToBuffer(39, 19, "Press ESC to return to Main Menu.", 0x0F);
		for (int x = 0; x < 100 + 2; ++x) {
			console.writeToBuffer(x, 30 + 1, '-', 0x08);
			console.writeToBuffer(x, 30 + 8, '-', 0x08);
			console.writeToBuffer(x, 30, '-', 0x08);
			console.writeToBuffer(x, 0, '-', 0x08);
		}
		for (int i = 0; i <= 30; ++i) {
			console.writeToBuffer(100 + 1, i, '|', 0x08);
			console.writeToBuffer(0, i, '|', 0x08);
		}
		for (int y = 0; y < 6; ++y) {
			console.writeToBuffer(0, 30 + y + 2, 186, 0x08);
			console.writeToBuffer(18, 30  + y + 2, 186, 0x08);
			console.writeToBuffer(0, 30  + y + 2, 186, 0x08);
			console.writeToBuffer(101, 30 + y + 2, 186, 0x08);
		}
		renderToScreen();

	}
}

void menu() {

	populateOptionsArray();

	while (g_gameState == Menu) { //This loop runs when the game is in the Main Menu.

		getInput();
		updateMenu();

	}

}