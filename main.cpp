#include <iostream>

#include "definitions.hpp"
#include "consoleInteraction.hpp"
#include "consoleGUI.hpp"
#include "globals.hpp"

int main() {
	int width, height;
	terminalSize(width, height); 
	height += 3;

	cGUI::FancyRectangle titleBar = createFancyRectangle(
		1, 1, width, 5, 1, cGUI::doubleCorners, 205, 186
	);
	setRectText(titleBar, "< RPG Random Master >", cGUI::CENTER);
	setRectColor(titleBar, { 255, 0, 0 }, { 0, 255, 0 }, { 0, 0, 255 },
		{ 255, 0, 0 }, { 0, 0, 255 }
	);
	 
	while (true) {
		//Main event loop
	}

	exit(1);
}
