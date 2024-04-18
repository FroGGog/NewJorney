#include "headers/gameWorld.h"


void gameWorld::fillRectsV()
{
	int temp_x = 0, temp_y = 0;
	this->worldRects.clear();
	this->cal_x = (this->scree_size.x - 250) / this->worldMap[0].size();
	this->cal_y = this->scree_size.y / this->worldMap.size() + 1;

	for (auto& i : this->worldMap) {
		for (auto& j : i) {
			sf::RectangleShape temp{ sf::Vector2f(cal_x, cal_y)};
			temp.setPosition(temp_x, temp_y);

			//check if player clicked on any rect in game
			if (this->Tshape.getGlobalBounds().intersects(temp.getGlobalBounds())) {
				this->saved_type = j;
				this->saved_x = temp.getGlobalBounds().getPosition().x;
				this->saved_y = temp.getGlobalBounds().getPosition().y;
				this->choosedSprite.setPosition(sf::Vector2f{ this->saved_x, this->saved_y });
				//supprots window change
				this->choosedSprite.setScale(cal_x / this->choosedTexture.getSize().x, cal_y / this->choosedTexture.getSize().y);
			}
			//check if player clicked on button goldmine
			else if (this->Tshape.getGlobalBounds().intersects(this->button1.getGlobalBounds())) {
				GMine temp;
				//check if enought res to build and space is't occupied
				if (temp.checkEnoughtRes(this->res[0], this->res[1], this->res[2]) && this->build(this->goldMineTplace)) {
					temp.MinusCost(this->res[0], this->res[1], this->res[2]);
					this->buildings.push_back(temp);
					std::cout << "Build!";
					this->CalculateIncome();
				}
			}
			//sawmil button
			else if (this->Tshape.getGlobalBounds().intersects(this->button2.getGlobalBounds())) {
				this->build(this->sawmillTplace);
			}
			//if rect is groudn
			if (j == "G") {
				temp.setFillColor(sf::Color(153,255,153,255));
			}
			//if rect is water
			else if (j == "W") {
				temp.setFillColor(sf::Color(50,50, 255, 255));
			}
			//if rect is road part
			else if (j == "R") {
				temp.setFillColor(sf::Color(152, 126, 96, 255));
			}
			//if rect is city
			else if (j == "C") {
				temp.setFillColor(sf::Color(255, 255, 102, 255));
			}
			//forest
			else if(j == "F"){
				temp.setFillColor(sf::Color(0, 51, 25, 255));
			}
			//mountain
			else if (j == "M") {
				temp.setFillColor(sf::Color(128, 128, 128, 255));
			}
			this->worldRects.push_back(temp);
			temp_x += this->cal_x;
		}
		temp_x = 0;
		temp_y += this->cal_y;
	}
	
	
}

void gameWorld::initVars()
{
	this->clicked = false;

	this->temp_incomeFood = 1;
	this->temp_incomeGold = 1;
	this->temp_incomeWood = 1;

}

void gameWorld::initTextures()
{
	//rect 
	if (!this->choosedTexture.loadFromFile("src/pics/choosedRect.png")) {
		std::cout << "ERROR::LOADFROMFILE::choosedRect.png\n";
		return;
	}
	this->choosedSprite.setTexture(this->choosedTexture);

	//mines button
	if (!this->goldMineT.loadFromFile("src/pics/goldMine.png")) {
		std::cout << "ERROR:LOADFROMFILE::goldMine.png\n";
		return;
	}
	this->button1.setTexture(this->goldMineT);
	this->button1.setPosition(1050.f, 500.f);

	//mine placeholder
	if (!this->goldMineTplace.loadFromFile("src/pics/goldMinePlace.png")) {
		std::cout << "ERROR:LOADFROMFILE::goldMinePlace.png\n";
		return;
	}

	//sawmill
	if (!this->sawmillT.loadFromFile("src/pics/sawmill.png")) {
		std::cout << "ERROR:LOADFROMFILE::sawmill.png\n";
		return;
	}

	if (!this->sawmillTplace.loadFromFile("src/pics/sawmillPlace.png")) {
		std::cout << "ERROR:LOADFROMFILE::sawmillPlace.png\n";
		return;
	}

	this->button2.setTexture(this->sawmillT);
	this->button2.setPosition(1150.f, 500.f);

}

bool gameWorld::build(sf::Texture& _toBuild)
{
	bool canBuild = true;
	sf::Sprite newBuilding{ _toBuild };
	newBuilding.setPosition(this->saved_x, this->saved_y);
	for (auto& sprite : this->worldSprites) {
		if (sprite.getGlobalBounds().contains(newBuilding.getPosition())) {
			canBuild = false;
			break;
		}
	}
	if (canBuild) {
		newBuilding.setScale(this->cal_x / this->goldMineT.getSize().x, this->cal_y / this->goldMineT.getSize().y);
		this->worldSprites.push_back(newBuilding);
	}
	return canBuild;
}

void gameWorld::CalculateIncome()
{
	for (auto& i : this->buildings) {
		if (i.getType() == "g_mine") {
			this->temp_incomeGold += 10;
		}
	}

}

gameWorld::gameWorld()
{
	this->initTextures();

	this->initWorldMap();

	this->initVars();

	this->fillRectsV();

}

void gameWorld::getScreenSize(sf::Vector2i _screen_size)
{
	this->scree_size = _screen_size;
}

int gameWorld::getWorldEnd() const
{
	return this->cal_x * this->worldMap[0].size();
}

void gameWorld::setResources(std::vector<int> _res)
{
	this->res = _res;
}

std::vector<int> gameWorld::getResources() const
{
	return this->res;
}

std::vector<int> gameWorld::getIncome() const
{
	return std::vector<int>{this->temp_incomeGold, this->temp_incomeWood, this->temp_incomeFood};
}

void gameWorld::update(sf::Window& window)
{
	this->updateRects();

	this->getOnRectClick(window);

}

void gameWorld::updateRects()
{
	this->fillRectsV();
}

void gameWorld::getOnRectClick(sf::Window& window)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		this->clicked = true;
		this->Tshape = sf::RectangleShape{ sf::Vector2f{1.f,1.f} };
		this->Tshape.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
	}
}


void gameWorld::render(sf::RenderTarget& target)
{

	for (auto& i : this->worldRects) {
		target.draw(i);
	}	

	for (auto& i : this->worldSprites) {
		target.draw(i);
	}

	if (clicked) {
		target.draw(this->choosedSprite);
	}
	target.draw(this->button1);
	target.draw(this->button2);
}


void gameWorld::initWorldMap()
{
	//G - ground
	this->worldMap = {

		{"G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","W","W","W","W","W",},
		{"G","G","G","G","G","G","G","G","F","F","F","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","W","W","W","W","W","W",},
		{"G","G","G","G","F","F","F","F","F","R","R","R","G","G","G","G","G","G","G","G","G","G","G","G","R","R","R","R","R","G","G","C","G","G","G","W","W","W","W","W",},
		{"G","G","G","C","R","R","R","R","R","R","F","R","G","G","G","G","G","G","G","G","G","G","R","R","R","G","G","G","R","G","G","R","G","G","G","G","W","W","W","W",},
		{"G","G","G","R","G","F","F","F","F","F","F","R","R","R","R","R","R","R","R","R","R","R","R","G","G","G","G","G","R","G","R","R","G","G","G","G","W","W","W","W",},
		{"G","G","R","R","G","F","F","F","F","F","F","R","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","R","R","R","R","R","G","G","G","G","W","W","W",},
		{"G","G","R","G","G","F","F","F","F","F","F","R","R","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","R","G","G","G","W","W","W","W",},
		{"G","G","R","G","G","F","F","F","G","G","G","G","R","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","R","G","G","G","W","W","W","W",},
		{"G","G","R","G","G","G","F","F","G","G","G","G","R","R","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","R","R","G","W","W","G","W","W",},
		{"F","G","R","R","G","G","G","G","G","G","G","G","G","R","R","R","R","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","W","R","W","W","G","G","G","G",},
		{"F","F","G","R","G","G","G","G","G","G","G","G","G","G","G","G","R","R","G","G","G","G","G","G","G","G","G","G","G","W","W","W","W","R","R","W","G","G","G","G",},
		{"F","F","G","R","G","G","G","G","G","G","G","G","G","G","G","G","G","R","R","G","G","G","G","G","G","G","G","G","W","W","W","W","G","G","R","G","G","G","G","G",},
		{"F","F","G","R","R","G","G","G","G","G","G","G","G","G","G","G","G","G","R","R","C","G","F","F","G","G","G","G","W","W","G","G","G","G","R","R","G","G","G","G",},
		{"F","F","F","G","R","G","G","G","G","G","G","G","G","G","G","F","G","G","G","G","G","G","F","F","G","G","G","W","W","G","G","G","G","G","G","R","R","G","G","G",},
		{"F","F","F","G","R","G","G","G","G","G","G","G","G","G","F","F","F","G","F","F","F","F","F","F","G","G","W","W","W","G","G","G","G","G","G","G","R","G","G","G",},
		{"F","F","F","G","R","G","G","G","G","G","G","G","G","G","F","F","F","G","F","F","F","F","F","F","G","G","W","W","G","G","G","G","G","G","G","G","R","G","G","M",},
		{"F","F","F","G","R","R","G","G","G","G","G","G","G","F","F","F","F","G","F","F","F","F","F","G","G","W","W","G","G","G","G","G","G","G","G","G","R","G","M","M",},
		{"F","F","F","G","G","R","G","G","G","G","G","G","G","F","F","F","F","F","F","F","F","F","F","W","W","W","W","G","G","G","G","G","G","G","G","G","R","G","M","M",},
		{"F","F","F","F","G","R","R","G","G","G","G","G","G","F","F","F","F","F","F","F","F","G","W","W","W","G","G","G","M","G","G","G","G","G","G","G","R","G","M","M",},
		{"F","F","F","F","G","G","R","G","G","G","G","G","G","F","F","F","F","F","F","F","F","G","W","W","G","G","G","M","M","M","G","G","G","G","G","G","R","G","M","M",},
		{"F","F","F","F","F","G","R","G","G","G","G","G","G","F","F","F","F","F","F","G","W","W","W","G","G","G","G","M","M","M","G","G","G","G","G","G","R","M","M","M",},
		{"F","F","F","F","F","G","R","R","G","G","G","G","G","G","F","F","F","F","G","G","W","W","W","G","G","G","G","M","M","M","G","G","G","G","G","G","R","M","M","M",},
		{"F","F","F","F","F","G","G","R","W","W","W","G","G","G","G","G","G","G","G","W","W","G","G","G","G","G","M","M","M","M","M","G","G","G","G","G","R","M","M","M",},
		{"F","F","F","F","F","F","G","C","W","W","W","W","G","G","G","G","G","G","W","W","W","G","G","G","G","M","M","G","M","M","M","G","G","G","M","M","R","M","M","M",},
		{"F","F","F","F","F","F","G","W","W","W","W","W","W","G","G","G","W","W","W","W","G","G","G","G","G","M","M","G","G","G","M","M","G","G","M","M","R","M","M","M",},
		{"F","F","F","F","F","G","G","W","W","W","W","W","W","W","G","W","W","W","G","G","G","G","G","G","M","M","G","G","G","G","G","M","G","M","M","M","C","M","M","M",},
		{"F","F","F","F","G","G","W","W","W","W","W","W","W","W","W","W","G","G","G","G","G","G","G","M","M","M","G","G","G","G","G","M","M","M","M","M","M","M","M","M",},
		{"F","F","F","F","G","W","W","W","W","W","W","W","W","W","W","W","G","G","G","G","G","G","G","M","M","M","G","G","M","M","M","M","M","M","M","M","M","M","M","M",},
		{"F","F","F","F","G","W","W","W","W","W","W","W","W","W","W","W","W","W","G","G","G","G","G","G","G","G","G","M","M","M","M","M","M","M","M","M","M","M","M","M",}
	};
}