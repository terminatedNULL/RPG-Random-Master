#ifndef CONSOLE_INTERACTION_HPP
#define CONSOLE_INTERACTION_HPP

#include <iostream>
#include <string>

#define extern_ extern

using std::to_string;

extern_ int cursorRetX = 0;
extern_ int cursorRetY = 0;

void move(int x, int y, bool reset = false) {
	std::cout << ("\033[" + to_string(x) + ";" + to_string(y) + "H");
	if(reset) { 
		std::cout << ("\033[" + to_string(x) + ";" + to_string(y) + "H");
	}
}

void setTextColor(int r, int g, int b) {
	std::cout << ("\033[38;2;" + 
				  to_string(r) + ";" + 
				  to_string(g) + ";" + 
				  to_string(b) + "m");
}

void setBackgroundColor(int r, int g, int b) {
	std::cout << ("\033[38;2;" +
		to_string(r) + ";" +
		to_string(g) + ";" +
		to_string(b) + "m");
}

void clearColors() {
	std::cout << "\033[0m";
}

#endif