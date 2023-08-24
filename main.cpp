#include <iostream>

#include "definitions.hpp"
#include "consoleInteraction.hpp"
#include "consoleGUI.hpp"
#include "globals.hpp"

int main() {
	int width, height;
	terminalSize(width, height);

	cGUI::Rectangle titleBar = rectangle(0, 0, width, 5);
	setRectText(titleBar, "Test Text", cGUI::LEFT_CENTER);

	while (true) {
		//Main event loop
	}

	exit(1);
}
