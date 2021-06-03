#include "GuiManager.hpp"

void GuiManager::update(sf::RenderWindow* window){
	if (window->hasFocus() == false) {
		return;
	}


	switch (GuiNumber) {
	case 1:
		button.update();
		button2.update();
		button3.update();
		button4.update();


		if (button.isClicked()) {
			GuiNumber = 0;
		}

		if (button2.isClicked()) {
			Maploader::reset();
			Maploader::destroy();
			LM::setRunning(false);
		}

		if (button3.isClicked()) {
			exit(0);
		}

		if (button4.isClicked()) {
			Maploader::destroy();
			*LM::getMapNumber() = 2;
			std::string mapstr = "map" + std::to_string(*LM::getMapNumber()) + "/map." + std::to_string(LM::getGlobalMapCords()->x) + "." + std::to_string(LM::getGlobalMapCords()->y) + ".sean";
			Maploader::load(mapstr);
			Maploader::create(up);
		}
	}
}

void GuiManager::draw(sf::RenderWindow* window){
	switch (GuiNumber) {
	case 1:
		window->draw(button.getSprite());
		window->draw(button.getDrawText());
		window->draw(button2.getSprite());
		window->draw(button2.getDrawText());
		window->draw(button3.getSprite());
		window->draw(button3.getDrawText());
		window->draw(button4.getSprite());
		window->draw(button4.getDrawText());
	}
}

GuiManager::GuiManager(){
	GuiNumber = 1;

	button.setTexture("images/button1.png");
	button.setSize(sf::Vector2f(200.f, 100.f));
	button.setText("Start");
	button.setPos(sf::Vector2f(100.f, 100.f));

	button2.setTexture("images/button1.png");
	button2.setSize(sf::Vector2f(200.f, 100.f));
	button2.setText("Restart");
	button2.setPos(sf::Vector2f(100.f, 300.f));

	button3.setTexture("images/button1.png");
	button3.setSize(sf::Vector2f(200.f, 100.f));
	button3.setText("End");
	button3.setPos(sf::Vector2f(100.f, 500.f));

	button4.setTexture("images/button1.png");
	button4.setSize(sf::Vector2f(200.f, 100.f));
	button4.setText("NextLevel");
	button4.setPos(sf::Vector2f(500.f, 100.f));
}
