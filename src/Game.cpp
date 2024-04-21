#include "headers/Game.h"

//private 

void Game::InitVars()
{
	this->window = nullptr;

	this->drawFirstTime = true;

	this->tempArmy = new army{ sf::Vector2f{28,28}, sf::Vector2f{100,100}, sf::Color::Blue };

}

void Game::InitWindow()
{
	this->screen_x = 1280;//1280 720
	this->screen_y = 720;

	this->vMode.width = this->screen_x;
	this->vMode.height = this->screen_y;

	this->window = new sf::RenderWindow(this->vMode, "New Jorney", sf::Style::Resize | sf::Style::Close);
	this->window->setFramerateLimit(60);

	this->gWorld.getScreenSize(sf::Vector2i(this->screen_x, this->screen_y));

}

void Game::InitGui()
{

	this->GUIback = sf::RectangleShape{ sf::Vector2f{float(this->screen_x - this->gWorld.getWorldEnd()), float(this->screen_y)} };
	this->blackStroke = sf::RectangleShape{ sf::Vector2f{5.f, float(this->screen_y)} };

	this->GUIback.setFillColor(sf::Color{ 135,130,111,255 });
	this->GUIback.setPosition(this->gWorld.getWorldEnd(), 0);

	this->blackStroke.setFillColor(sf::Color::Black);
	this->blackStroke.setPosition(this->gWorld.getWorldEnd(), 0);
}




//public staff
Game::Game()
{
	this->InitVars();
	this->InitWindow();
	
}

Game::~Game()
{
	delete this->window;

}

const bool Game::windowOpen() const
{
	return this->window->isOpen();
}


//update functions
void Game::update()
{
	this->updateEvents();

	this->gameStats.update();

	this->gWorld.setResources(this->gameStats.getResources());

	this->gWorld.update(*this->window);
	
	this->gameStats.setResources(this->gWorld.getResources());

	this->gameStats.getIncome(this->gWorld.getIncome());

	if (drawFirstTime) {
		this->InitGui();
		drawFirstTime = false;
	}

}

void Game::updateEvents()
{
	while (this->window->pollEvent(this->GameEvents)) {
		switch (this->GameEvents.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		default:
			break;
		}
	}
}

//render functions
void Game::render()
{
	this->window->clear();

	//gui stuff

	this->window->draw(this->GUIback);
	this->window->draw(this->blackStroke);

	//other stuff
	this->gWorld.render(*this->window);

	this->gameStats.render(*this->window);
	
	this->window->display();

}