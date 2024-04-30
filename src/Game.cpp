#include "headers/Game.h"

//private 

void Game::InitVars()
{
	this->window = nullptr;

	this->drawFirstTime = true;

	this->enemyCount = 0;

}

void Game::InitWindow()
{
	this->screen_x = 1280;//1280 720
	this->screen_y = 720;

	this->vMode.width = this->screen_x;
	this->vMode.height = this->screen_y;

	this->window = std::make_shared<sf::RenderWindow>(this->vMode, "New Jorney", sf::Style::Resize | sf::Style::Close);
	this->window->setFramerateLimit(60);

	//game world stuff
	this->gWorld.getScreenSize(sf::Vector2i(this->screen_x, this->screen_y));
	this->gWorld.initGameField();
	

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

void Game::spawnArmy()
{
	this->spawnerTime = this->spawnerClock.getElapsedTime();

	if (this->spawnerTime.asSeconds() > 0.1f) {

		this->enemyCount++;

		army tempArm{ sf::Vector2f{25.f,25.f}, sf::Vector2f{50,364}, sf::Color::Green };

		this->enemyArmy.push_back(std::make_shared<army>(tempArm));

		this->spawnerClock.restart();
	}

}

void Game::updateEnemiesList()
{
	for (int i{ 0 }; i < this->enemyArmy.size(); i++) {
		if (!this->enemyArmy[i]->isAlive()) {
			this->enemyArmy.erase(this->enemyArmy.begin() + i);
			this->enemyCount--;
		}
	}

}

//public staff
Game::Game()
{

	this->InitVars();
	this->InitWindow();
	this->InitGui();
	
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

	//set recources from gameStats to gameWorld class
	this->gWorld.setResources(this->gameStats.getResources());

	//update gameWorld
	this->gWorld.update(*this->window);
	
	//set resources to game stats
	this->gameStats.setResources(this->gWorld.getResources());

	//recieve income from buildings from gameWorld class
	this->gameStats.getIncome(this->gWorld.getIncome());

	//update turrets (update only when enemies on field)
	if (this->enemyCount > 0) {
		this->gWorld.updateTurrets(this->enemyArmy);
	}

	for (auto& i : this->enemyArmy) {
		i->update(this->gWorld.roadRects());
	}

	if (this->enemyCount < 10) {
		this->spawnArmy();
	}
	

	//check if any enemies died
	this->updateEnemiesList();

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

	//game world
	this->gWorld.render(*this->window);

	//armies
	for (auto& i : this->enemyArmy) {
		i->render(*this->window);
	}

	//gui stuff
	this->window->draw(this->GUIback);
	this->window->draw(this->blackStroke);

	//buttons
	this->gWorld.renderButtons(*this->window);  

	//other stuff
	this->gameStats.render(*this->window);
	
	this->window->display();

}