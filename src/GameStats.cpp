#include "headers/GameStats.h"


GameStats::GameStats() : wood(500), gold(500), food(500), woodIncome(1), goldIncome(1), foodIncome(1)
{
	this->initFont();
	this->initTextures();
}

std::map<std::string, int> GameStats::getResources() const
{
	return std::map<std::string, int> {{"gold", this->gold}, { "wood",this->wood }, { "food", this->food }};
}

void GameStats::setResources(std::map <std::string, int> _res)
{
	this->gold = _res["gold"];
	this->wood = _res["wood"];
	this->food = _res["food"];
}

void GameStats::getIncome(std::vector<int> income)
{
	this->goldIncome = income[0];
	this->woodIncome = income[1];
	this->foodIncome = income[2];
}

void GameStats::update()
{
	this->updateT(this->wood_t, this->wood, this->woodIncome);
	this->updateT(this->gold_t, this->gold, this->goldIncome);
	this->updateT(this->food_t, this->food, this->foodIncome);

	this->updateResources();

}

void GameStats::render(sf::RenderTarget& target)
{
	target.draw(this->food_t);
	target.draw(this->wood_t);
	target.draw(this->gold_t);

	target.draw(this->food_S);
	target.draw(this->wood_S);
	target.draw(this->gold_S);
}

void GameStats::initFont()
{
	if (!this->mainFont.loadFromFile("fonts/Anta-Regular.ttf")) {
		std::cout << "ERROR::LOADFROMFILE::FONTS:Anta-Regular.ttf\n";
	}
	this->food_t.setFont(this->mainFont);
	this->wood_t.setFont(this->mainFont);
	this->gold_t.setFont(this->mainFont);

	this->food_t.setPosition(1100.f, 50.f);
	this->wood_t.setPosition(1100.f, 100.f);
	this->gold_t.setPosition(1100.f, 150.f);

}

void GameStats::initTextures()
{
	if (!this->food_icT.loadFromFile("src/pics/foodIcon.png")) {
		std::cout << "ERROR::LOADFROMFILE::PICS::foodIcon.png\n";
	}
	this->food_S.setTexture(this->food_icT);
	this->food_S.setPosition(1050.f, 50.f);
	this->food_S.setScale(0.5f, 0.5f);

	if (!this->wood_icT.loadFromFile("src/pics/woodIcon.png")) {
		std::cout << "ERROR::LOADFROMFILE::PICS::woodIcon.png\n";
	}
	this->wood_S.setTexture(this->wood_icT);
	this->wood_S.setPosition(1050.f, 100.f);
	this->wood_S.setScale(0.25f, 0.25f);

	if (!this->gold_icT.loadFromFile("src/pics/goldIcon.png")) {
		std::cout << "ERROR::LOADFROMFILE::PICS::goldIcon.png\n";
	}
	this->gold_S.setTexture(this->gold_icT);
	this->gold_S.setPosition(1050.f, 150.f);
	this->gold_S.setScale(0.5f, 0.5f);

}

void GameStats::updateT(sf::Text& _text ,int _resource, int _income)
{
	std::stringstream ss;

	ss << _resource << " (+" << _income << ")";

	_text.setString(ss.str());

}

void GameStats::updateResources()
{
	this->timeToAdd = this->incomeClock.getElapsedTime();

	if (this->timeToAdd.asSeconds() > 0.1f) {

		this->incomeClock.restart();

		this->food += this->foodIncome;
		this->wood += this->woodIncome;
		this->gold += this->goldIncome;
	}
	else {
		return;
	}


}


