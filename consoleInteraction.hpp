#ifndef CONSOLE_INTERACTION_HPP
#define CONSOLE_INTERACTION_HPP

#include <windows.h>
#include <iostream>
#include <string>
#include <algorithm>

#include "globals.hpp"
#include "definitions.hpp"

using std::to_string;

void setRGB(cGUI::RGB& obj, int r, int g, int b) {
	obj.r = r;
	obj.g = g;
	obj.b = b;
}

bool mouseDown() {
	if ((GetKeyState(VK_LBUTTON) & 0x8000) != 0) { return true; }
	return false;
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

void move(int x, int y, bool reset = false) {
	std::string s = ("\033[" + to_string(y) + ";" + to_string(x) + "H");
	fwrite(s.c_str(), sizeof(char), s.length(), stdout);
	if(reset) { 
		s = ("\033[" + to_string(y) + ";" + to_string(x) + "H");
		fwrite(s.c_str(), sizeof(char), s.length(), stdout);
	}
}

cGUI::Position handleMousePos(int width, int height) {
	POINT mousePos;
	cGUI::Position pos;

	GetCursorPos(&mousePos);
	ScreenToClient(GetConsoleWindow(), &mousePos);
	RECT screen = getScreenSize();

	pos.x = pixelToConsole((int)mousePos.x, 0, screen.right, 0, width);
	pos.y = pixelToConsole((int)mousePos.y, 0, screen.bottom, 0, height);

	return pos;
}

void setTextColor(cGUI::RGB color) {
	std::string s = ("\033[38;2;" + 
				  to_string(color.r) + ";" + 
				  to_string(color.g) + ";" +
				  to_string(color.b) + "m");
	fwrite(s.c_str(), sizeof(char), s.length(), stdout);
}

void setBackgroundColor(cGUI::RGB color) {
	std::string s = ("\033[48;2;" +
		to_string(color.r) + ";" +
		to_string(color.g) + ";" +
		to_string(color.b) + "m");
	fwrite(s.c_str(), sizeof(char), s.length(), stdout);
}

void clearColors() {
	setRGB(currTextCol, 255, 255, 255);
	setRGB(currBackCol, 0, 0, 0);
	std::string s = "\033[0m";
	fwrite(s.c_str(), sizeof(char), s.length(), stdout);
}

void repeatChar(char c, int num, bool newline) {
	char cArray[1000];
	std::fill_n(cArray, num, c);
	fwrite(cArray, sizeof(char), num, stdout);
	if (newline) { std::cout << "\n"; }
}

void repeatExtChar(int c, int num, bool newline) {
	char cArray[1000];
	char intChar = (char)c;
	std::fill_n(cArray, num, intChar);
	fwrite(cArray, sizeof(char), num, stdout);
	if (newline) { std::cout << "\n"; }
}

#endif