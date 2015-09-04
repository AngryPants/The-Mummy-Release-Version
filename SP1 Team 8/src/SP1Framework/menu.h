#ifndef _MENU_H
#define _MENU_H

using std::ifstream;

struct MenuOptions {
	int optionColour;
	bool isSelected;
	string displayName;
};

enum MenuStates {
	Start,
	Levels,
	Quit,
	Level_Selection,
	LAST_STATE
};

void populateOptionsArray();
void menu();
void renderMainMenu();
void updateMenu();
void menuUserInput();
void renderLevelSelection();

#endif