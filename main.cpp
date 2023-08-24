#include <iostream>

#define extern_
#include "consoleInteraction.hpp"
#undef extern_

#include "consoleGUI.hpp"

int main() {

	setTextColor(255, 0, 0);
	rectangle(0, 0, 10, 10);
	clearColors();
	std::cout << "test";

	exit(1);
}
