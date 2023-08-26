#include <iostream>

#include "definitions.hpp"
#include "consoleInteraction.hpp"
#include "objectInteraction.hpp"
#include "consoleGUI.hpp"
#include "globals.hpp"

#define ARROW_UP	72
#define ARROW_DOWN	80
#define ARROW_RIGHT	75
#define ARROW_LEFT	77

int main() {
	int width, height;
	terminalSize(width, height); 

	cGUI::FancyRectangle titleBar = createFancyRectangle(
		1, 1, width, 5, 1, cGUI::doubleCorners, 205, 186
	);
	setRectText(titleBar, "< RPG Random Master >", cGUI::CENTER);
	addRect(&titleBar);
	 
	while (true) {
		cGUI::Position mousePos = getMousePos(width, height);
		handleRectMouse(mousePos);

		char input = _getch();

		switch (input) {
		case ARROW_UP:
			break;
		case ARROW_DOWN:
			break;
		case ARROW_RIGHT:
			break;
		case ARROW_LEFT:
			break;
		}
	}

	exit(1);
}
