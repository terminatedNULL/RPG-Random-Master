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
		1, 1, width, 5, 1, cGUI::doubleCorners, 205, 186, 32, cGUI::RECT
	);
	setRectText(titleBar, "< RPG Random Master >", cGUI::LEFT_CENTER, 1);

	cGUI::FancyRectangle sideBar = createFancyRectangle(
		1, 5, width * .2, height - 6, 1, cGUI::doubleCorners, 205, 186, 32,
		cGUI::RECT
	);
	setRectSide(sideBar, cGUI::TOP, false);
	addRect(&sideBar);

	cGUI::FancyRectangle editorWind = createFancyRectangle(
		width * .2 + 1, 5, ceil(width * .5), height - 6, 1, cGUI::doubleCorners,
		205, 186, 32, cGUI::RECT
	);
	setRectSide(editorWind, cGUI::TOP, false);
	addRect(&editorWind);

	cGUI::FancyRectangle visualWind = createFancyRectangle(
		ceil(width * .7) + 1, 5, width * .3, height - 6, 1, cGUI::doubleCorners,
		205, 186, 32, cGUI::RECT
	);
	setRectSide(visualWind, cGUI::TOP, false);
	addRect(&visualWind);

	//Add here to draw on top
	addRect(&titleBar);
	 
	while (true) {
		cGUI::Position mousePos = handleMousePos(width, height);
		handleRectMouse(mousePos);

		if (!_kbhit()) { continue; }
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
