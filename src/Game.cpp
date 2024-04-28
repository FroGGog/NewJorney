#include "headers/Game.h"

//private 

void Game::InitVars()
{
	this->window = nullptr;

	this->drawFirstTime = true;

	//775 y 50 city dest pos
	// road start pos 225 50
	this->tempArmy = new army{ sf::Vector2f{25.f,26.f}, sf::Vector2f{50,364}, sf::Color::Blue };

	this->tempTurret = new Turret{ this->textures["bowTurret"] };

}

void Game::InitWindow()
{
	this->screen_x = 1280;//1280 720
	this->screen_y = 720;

	this->vMode.width = this->screen_x;
	this->vMode.height = this->screen_y;

	this->window = new sf::RenderWindow(this->vMode, "New Jorney", sf::Style::Resize | sf::Style::Close);
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

void Game::InitTextures()
{
	//turrets textures
	this->textures["bowTurret"] = new sf::Texture{};
	if (!this->textures["bowTurret"]->loadFromFile("src/pics/turrets/bow.png")) {
		std::cout << "ERROR:LOADFROMFILE:PICTURE:bow.png\n";
	}

	//armies textures

}


//public staff
Game::Game()
{
	this->InitTextures();

	this->InitVars();
	this->InitWindow();
	this->InitGui();
	
}

Game::~Game()
{
	delete this->window;

	delete this->tempArmy;

	delete this->tempTurret;

	//delete all textures
	for (auto& i : this->textures) {
		delete i.second;
	}

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

	this->tempArmy->update(this->gWorld.roadRects());

	this->tempTurret->update();

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
	this->tempArmy->render(*this->window);
	this->tempTurret->render(*this->window);

	//gui stuff
	this->window->draw(this->GUIback);
	this->window->draw(this->blackStroke);

	//buttons
	this->gWorld.renderButtons(*this->window);  

	//other stuff
	this->gameStats.render(*this->window);
	
	this->window->display();

}