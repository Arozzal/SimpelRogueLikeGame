#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include "ListManager.hpp"

class GuiObj {
protected:
	bool clicked = false;
	bool mouseHover = false;
	

	sf::Texture texture;
	sf::Sprite sprite;

	sf::Vector2f size;
	sf::Vector2f pos;
	sf::Vector2f scale;
public:


	const sf::Vector2f &getSize() { return size; };
	const sf::Vector2f &getPos() { return pos; };
	const sf::Vector2f &getScale() { return scale; };
	const bool &isMouseHover() { return mouseHover; };
	const bool &isClicked() { return clicked; };

	virtual void update() = 0;
	virtual void setTexture(sf::String) = 0;

	void setSize(sf::Vector2f size) { this->size = size; };
	void setPos(sf::Vector2f pos) { this->pos = pos; };
	void setScale(sf::Vector2f scale) { this->scale = scale; };
	
	void setMouseHover(bool mouseHover) { this->mouseHover = mouseHover; };
	void setClicked(bool clicked) { this->clicked = clicked; };

	sf::Sprite getSprite() { return sprite; }
	const virtual sf::Text& getDrawText() = 0;
	sf::Texture getTexture() { return texture; };
};