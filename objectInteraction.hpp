#ifndef OBJECT_INTERACTION_HPP
#define OBJECT_INTERACTION_HPP

#include "definitions.hpp"
#include "consoleGUI.hpp"
#include "globals.hpp"

void addRect(cGUI::Rectangle *rect) {
	rectObjects.push_back(rect);
}

void addRect(cGUI::FancyRectangle* rect) {
	fancyRectObjects.push_back(rect);
}

void handleRectMouse(cGUI::Position mousePos) {
	for (cGUI::Rectangle* rect : rectObjects) {
		
	}
	for (cGUI::FancyRectangle* rect : fancyRectObjects) {
		if (
			boundsCheck(mousePos, rect->x, rect->y, rect->width, rect->height)
		) {
			setRectState(*rect, cGUI::HOVER);
			move(50, 50);
			std::cout << rect->colorMod;
		} else {
			setRectState(*rect, cGUI::IDLE);
			move(50, 50);
			std::cout << rect->colorMod;
		}
	}
}

#endif
