#include <iostream>

#include "definitions.hpp"
#include "consoleInteraction.hpp"
#include "consoleGUI.hpp"
#include "globals.hpp"

int main() {
	int width, height;
	terminalSize(width, height);

	cGUI::Rectangle titleBar = createRectangle(0, 0, width, 5);
	setRectColor(titleBar, { 255, 0, 0 }, {0, 255, 0}, {0, 0, 255});
	setRectText(titleBar, "<RPG Random Master >", cGUI::CENTER);

	cGUI::FancyRectangle footerBar = createFancyRectangle(
										0, height - 5, width, 5
									 );
	 
	while (true) {
		//Main event loop
	}

	exit(1);
}
