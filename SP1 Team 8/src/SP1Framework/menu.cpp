#include "Framework\timer.h"
#include "game.h"
#include "Framework\console.h"
#include "loadlevel.h"
#include "teleporters.h"
#include "collisionDetection.h"
#include "LevelMenu.h"
#include "loadlevel.h"
#include "inventory.h"
#include "camera.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <fstream>
#include "menu.h"
#include "Music.h"

//External Variables
extern bool keyPressed[K_COUNT];
extern bool bupdateWorldGrid;
extern Console console;
extern State g_gameState;
extern unsigned int g_levelNumber;

//Local Variables
bool keyDownedDown = false;
bool keyDownedUp = false;
bool keyDownedEnter = false;
bool keyDownedEscape = false;
//Change this value according to the number of levels in the folder.
unsigned int numberOfLevels = 9;
unsigned int selectedLevel = 0;
unsigned int textXCoords = 42;

const unsigned int numberOfMenuOptions = 3;
MenuOptions options[numberOfMenuOptions];
MenuStates menuStates = Start;

//Fills up the options array with options like Start, Level Selection and Quit.
void populateOptionsArray() {

	for (int i = 0; i < numberOfMenuOptions; ++i) {
		if (i > 0) {
			options[i].isSelected = false;
		} else {
			options[i].isSelected = true;
		}

		options[i].optionColour = 0x0F;
	}

	options[0].displayName = "     Start     ";
	options[1].displayName = "Level Selection";
	options[2].displayName = "     Quit      ";

}

//Update the menu every frame.
void updateMenu() {

	for (unsigned int u = 0; u < numberOfMenuOptions; ++u) {
		if (u != static_cast<int>(menuStates)) {
			options[u].isSelected = false;
		} else {
			options[u].isSelected = true;
		}
	}
	menuUserInput();
	renderMainMenu();

}

//Gets the user input of the up and down arrow keys and change which option is being currently selected.
void menuUserInput() {

	if (!keyPressed[K_DOWN]) {
		keyDownedDown = false;
	}

	if (!keyPressed[K_UP]) {
		keyDownedUp = false;
	}

	if (!keyPressed[K_ENTER]) {
		keyDownedEnter = false;
	}
	
	if (!keyPressed[K_ESCAPE]) {
		keyDownedEscape = false;
	}

	if (menuStates != Level_Selection) {

		if (keyPressed[K_DOWN] && menuStates != Quit && !keyDownedDown) {

			menuStates = static_cast<MenuStates>(menuStates + 1);
			keyDownedDown = true;
	
		} else if (keyPressed[K_UP] && menuStates != Start && !keyDownedUp) {

			menuStates = static_cast<MenuStates>(menuStates - 1);
			keyDownedUp = true;

		} else if (keyPressed[K_ENTER] && !keyDownedEnter) {

			keyDownedEnter = true;

			if (menuStates == Start) {

				g_gameState = Play;
				g_levelNumber = 0;
				updateWorldGrid(g_levelNumber);
				clearInventory();
				keyDownedEnter = true;

			} else if (menuStates == Levels) {

				menuStates = Level_Selection;

			} else if (menuStates == Quit) {

				g_gameState = Exit;

			}

		}

	} else if (menuStates == Level_Selection) {

		if (selectedLevel < numberOfLevels - 1 && keyPressed[K_DOWN] && !keyDownedDown) {
			keyDownedDown = true;
			++selectedLevel;
		} else if (selectedLevel > 0 && keyPressed[K_UP] && !keyDownedUp) {
			keyDownedUp = true;
			--selectedLevel;
		} else if (keyPressed[K_ESCAPE] && !keyDownedEscape) {
			keyDownedEscape = true;
			menuStates = Levels;
		} else if (keyPressed[K_ENTER] && !keyDownedEnter) {
			keyDownedEnter = true;
			g_levelNumber = selectedLevel;
			bupdateWorldGrid = true;
			g_gameState = Play;
		}

	}

}

void renderMainMenu() {

	clearScreen();

	string str;
	unsigned int lineNumber = 0;

	std::ifstream file("menu.txt");
	{
		while(getline(file, str))
		{
			console.writeToBuffer(0, lineNumber, str, 0x0F);
			++lineNumber;
		}
	}

	if (menuStates != Level_Selection) {
	
		unsigned int yCoords = 10;

		for (unsigned int c = 0; c < numberOfMenuOptions; ++c) {

			if (options[c].isSelected) {
				options[c].optionColour = 0xF0;
			} else {
				options[c].optionColour = 0x0F;
			}

			console.writeToBuffer(textXCoords, yCoords + 6, options[c].displayName, options[c].optionColour);
			++yCoords;
		}

	} else {

		renderLevelSelection();

	}
	
	renderToScreen();

}

void renderLevelSelection() {

	unsigned int yCoords = 15;

	console.writeToBuffer(textXCoords - 3, yCoords, "Press Escape To Return", 0x0F);

	yCoords += 2;

	for (unsigned int h = 0; h < numberOfLevels; ++h) {

		string level = "Level ";
		char levelNumberString[999];
		int colour = 0x0F;

		itoa(h, levelNumberString, 10);

		level += levelNumberString;

		if (h == selectedLevel) {
			colour = 0xF0;
		} else {
			colour = 0x0F;
		}

		console.writeToBuffer(textXCoords + 4, yCoords, level, colour);

		++yCoords;

	}

}