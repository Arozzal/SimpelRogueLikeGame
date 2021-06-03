#pragma once
#include "Button.hpp"
#include "ListManager.hpp"
#include "Maploader.hpp"
#include <SFML\Graphics.hpp>

class GuiManager {
	int GuiNumber = 1;
	Button button4;
	Button button3;
	Button button2;
	Button button;

public:
	void update(sf::RenderWindow*);
	void draw(sf::RenderWindow*);

	int getGuiNumber() { return GuiNumber; };
	void setGuiNumber(int Guinumber) { this->GuiNumber = Guinumber; };
	GuiManager();
};