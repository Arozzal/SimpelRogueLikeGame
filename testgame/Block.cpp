#include "Block.hpp"
#include "Maploader.hpp"
#include "ListManager.hpp"
#include <SFML\Graphics.hpp>
void Block::setDirection(Direction dir) {
	this->dir = dir;
}

	void Block::create(float sizex, float sizey){
		image.create(sizex, sizey, sf::Color(255, 255, 255, 255));
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setPosition(posx, posy);
		beginypos = sprite.getPosition().y;
		sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
		
	}
	void Block::create(sf::String path) {
		
		image.loadFromFile(path);
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setPosition(posx, posy);
		beginypos = sprite.getPosition().y;
		sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
		
	}

	void Block::setColor(Color col){
		switch (col) {
		case BLACK:
			sprite.setColor(sf::Color(0, 0, 0, 255));
			break;
		case WHITE:
			sprite.setColor(sf::Color(255, 255, 255, 255));
			break;
		case RED:
			sprite.setColor(sf::Color(255, 0, 0, 255));
			break;
		case BLUE:
			sprite.setColor(sf::Color(0, 0, 255, 255));
			break;
		case LIME:
			sprite.setColor(sf::Color(0, 255, 0, 255));
			break;
		case YELLOW:
			sprite.setColor(sf::Color(255, 255, 0, 255));
			break;
		case CYAN:
			sprite.setColor(sf::Color(0, 255, 255, 255));
			break;
		case MAGNETA:
			sprite.setColor(sf::Color(255, 0, 255, 255));
			break;
		case SILVER:
			sprite.setColor(sf::Color(192, 192, 192, 255));
			break;
		case GRAY:
			sprite.setColor(sf::Color(128, 128, 128, 255));
			break;
		case MARRON:
			sprite.setColor(sf::Color(128, 0, 0, 255));
			break;
		case OLIVE:
			sprite.setColor(sf::Color(128, 128, 0, 255));
			break;
		case GREEN:
			sprite.setColor(sf::Color(0, 128, 0, 255));
			break;
		case PURPLE:
			sprite.setColor(sf::Color(128, 0, 128, 255));
			break;
		case TEAL:
			sprite.setColor(sf::Color(0, 128, 128, 255));
			break;
		case NAVY:
			sprite.setColor(sf::Color(0, 0, 128, 255));
			break;
		case INVISIBLE:
			sprite.setColor(sf::Color(0, 0, 0, 1));
			break;
		default:
			sprite.setColor(sf::Color(0, 0, 0, 0));
		}
	}

	

	sf::Sprite *Block::getImage(){
		sf::Sprite* pSprite = &sprite;
		return pSprite;
	}

	void Block::update(float){}

	void Block::setPosition(float posx, float posy) {
		this->posx = posx;
		this->posy = posy;
		sprite.setPosition(this->posx,this->posy);
	}

	float Block::getX(){
		return this->posx;
	}

	float Block::getY(){
		return this->posy;
	}


	void Block::setSize(float sizex, float sizey) {
		
		this->sizex = sizex;
		this->sizey = sizey;
	}
	
	float Block::getSize() {
		return image.getSize().x;
	}

	Block::Block()
	{
		
	}

	void Block::addItemPickupContainer(sf::Vector2i cords) {
		Maploader::getItemDataMap()->insert(std::pair<sf::String, bool>(std::to_string(cords.x) + "." + std::to_string(cords.y)
			+ "." + std::to_string(LM::getGlobalMapCords()->x) + "." + std::to_string(LM::getGlobalMapCords()->y), true));
	}