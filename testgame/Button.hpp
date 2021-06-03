#pragma once
#include "GuiObj.hpp"


class Button : public GuiObj {
public:
	sf::String text;
	sf::Text buttontext;
	sf::Font font;
	void setTexture(sf::String path) override;

	Button();

	

	void update() override;
	void setText(sf::String text);
	const sf::Text& getDrawText() override { return buttontext; };
};