#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include "definitions.hpp"

int cursorRetX;
int cursorRetY;
struct cGUI::RGB currTextCol = { 255, 255, 255 };
struct cGUI::RGB currBackCol = { 0, 0, 0 };
const struct cGUI::RGB BLANK_RGB = { -1, -1, -1 };
int cursorPosX;
int cursorPosY;

std::vector<struct cGUI::Rectangle*> rectObjects;
std::vector<struct cGUI::FancyRectangle*> fancyRectObjects;

#endif