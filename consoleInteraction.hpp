#ifndef CONSOLE_INTERACTION_HPP
#define CONSOLE_INTERACTION_HPP

#include <windows.h>
#include <iostream>
#include <string>

#include "globals.hpp"
#include "definitions.hpp"

using std::to_string;

void setRGB(cGUI::RGB& obj, int r, int g, int b) {
	obj.r = r;
	obj.g = g;
	obj.b = b;
}

void terminalSize(int& width, int& height) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	width = (int)(csbi.srWindow.Right - csbi.srWindow.Left + 1);
	height = (int)(csbi.srWindow.Bottom - csbi.srWindow.Top - 1);
}

void move(int x, int y, bool reset = false) {
	std::cout << ("\033[" + to_string(y) + ";" + to_string(x) + "H");
	if(reset) { 
		std::cout << ("\033[" + to_string(y) + ";" + to_string(x) + "H");
	}
}

void setTextColor(cGUI::RGB color) {
	std::cout << ("\033[38;2;" + 
				  to_string(color.r) + ";" + 
				  to_string(color.g) + ";" +
				  to_string(color.b) + "m");
}

void setBackgroundColor(cGUI::RGB color) {
	std::cout << ("\033[48;2;" +
		to_string(color.r) + ";" +
		to_string(color.g) + ";" +
		to_string(color.b) + "m");
}

void clearColors() {
	setRGB(currTextCol, 255, 255, 255);
	setRGB(currBackCol, 0, 0, 0);
	std::cout << "\033[0m";
}

void repeatChar(char c, int num, bool newline) {
	for (int i = 0; i < num; i++) { std::cout << c; }
	if (newline) { std::cout << "\n"; }
}

void repeatExtChar(int c, int num, bool newline) {
	for (int i = 0; i < num; i++) { std::cout << (char)c; }
	if (newline) { std::cout << "\n"; }
}

#endif