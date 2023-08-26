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

bool boundsCheck(cGUI::Position pos, int x, int y, int width, int height) {
	if (
		(pos.x >= x && pos.x <= x - 2 + width)
		&& (pos.y >= y && pos.y <= y - 2 + height)
	) {
		return true;
	} else {
		return false;
	}
}

void terminalSize(int& width, int& height) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	width = (int)(csbi.srWindow.Right - csbi.srWindow.Left + 1);
	height = (int)(csbi.srWindow.Bottom - csbi.srWindow.Top + 2);
}

int pixelToConsole(int num, int oldMin, int oldMax, int newMin, int newMax) {
	return newMin + (num - oldMin) * (newMax - newMin) / (oldMax - oldMin);
}

RECT getScreenSize() {
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	return desktop;
}

struct cGUI::Position getMousePos(int width, int height) {
	POINT mousePos;
	cGUI::Position pos;

	GetCursorPos(&mousePos);
	ScreenToClient(GetConsoleWindow(), &mousePos);
	RECT screen = getScreenSize();

	pos.x = pixelToConsole((int)mousePos.x, 0, screen.right, 0, width);
	pos.y = pixelToConsole((int)mousePos.y, 0, screen.bottom, 0, height);

	return pos;
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