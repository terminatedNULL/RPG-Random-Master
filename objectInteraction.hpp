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
		if (
			boundsCheck(mousePos, rect->x, rect->y, rect->width, rect->height)
		) {
			if (rect->state == cGUI::DISABLED || rect->state == cGUI::RECT) { continue; }
			if (mouseDown()) {
				setRectState(*rect, cGUI::CLICK);
				if (rect->radio) {
					rect->radioSelect = !rect->radioSelect;
				}
			}
			else {
				setRectState(*rect, cGUI::HOVER);
			}
		}
		else {
			if (rect->state == cGUI::DISABLED || rect->state == cGUI::RECT) { continue; }
			if (rect->radio && rect->radioSelect) {
				setRectState(*rect, cGUI::HOVER);
			}
			else {
				setRectState(*rect, cGUI::IDLE);
			}
		}
	}

	for (cGUI::FancyRectangle* rect : fancyRectObjects) {
		if (
			boundsCheck(mousePos, rect->x, rect->y, rect->width, rect->height)
			) {
			if (rect->state == cGUI::DISABLED || rect->state == cGUI::RECT) { continue; }
			if (mouseDown()) {
				setRectState(*rect, cGUI::CLICK);
				if (rect->radio) {
					rect->radioSelect = !rect->radioSelect;
				}
			}
			else {
				setRectState(*rect, cGUI::HOVER);
			}
		}
		else {
			if (rect->state == cGUI::DISABLED || rect->state == cGUI::RECT) { continue; }
			if (rect->radio && rect->radioSelect) {
				setRectState(*rect, cGUI::HOVER);
			}
			else {
				setRectState(*rect, cGUI::IDLE);
			}
		}
	}
}

#endif
