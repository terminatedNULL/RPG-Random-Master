#include <iostream>

#define extern_
#include "definitions.hpp"
#undef extern_

#include "consoleInteraction.hpp"
#include "consoleGUI.hpp"

int main() {
	int width, height;
	terminalSize(width, height);

	cGUI::Rectangle titleBar = rectangle(0, 0, width, 5);

	while (true) {
		//Main event loop
	}

	exit(1);
}
