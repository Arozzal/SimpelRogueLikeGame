#include "Button.hpp"


void Button::update(){
	sprite.setPosition(pos);
	

	buttontext.setPosition(pos.x+(size.x/2 - buttontext.getLocalBounds().width / 2 ),
						   pos.y+(size.y/2 - buttontext.getLocalBounds().height / 1.4));

	if ((sf::Mouse::getPosition(*LM::getWindow()).x > getPos().x && sf::Mouse::getPosition(*LM::getWindow()).x < getPos().x + size.x)
	&&  (sf::Mouse::getPosition(*LM::getWindow()).y > getPos().y && sf::Mouse::getPosition(*LM::getWindow()).y < getPos().y + size.y)) {
		setMouseHover(true);
		sprite.setColor(sf::Color(sf::Color(100, 100, 100, 255)));
	}else {
		sprite.setColor(sf::Color(sf::Color(255, 255, 255, 255)));
		setMouseHover(false);
	}

	if (mouseHover == true && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		setClicked(true);
	}else {
		setClicked(false);
	}

}

void Button::setTexture(sf::String path) {
	texture.loadFromFile(path);
	sprite.setTexture(texture);
}

Button::Button(){
	font.loadFromFile("font.ttf");
	buttontext.setString("NULL");
	buttontext.setFont(font);
	buttontext.setColor(sf::Color(137, 137, 137, 255));
	buttontext.setCharacterSize(60);

}

void Button::setText(sf::String text){
	buttontext.setString(text);
	
}