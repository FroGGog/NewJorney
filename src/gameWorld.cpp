#include "headers/gameWorld.h"


void gameWorld::fillRectsV()
{
	int temp_x = 0, temp_y = 0;

	this->worldRects.clear();

	this->cal_x = (this->screen_size.x - 250) / this->worldMap[0].size();
	this->cal_y = this->screen_size.y / this->worldMap.size() + 1;

	for (auto& i : this->worldMap) {
		for (auto& j : i) {
			//init rectangle
			sf::RectangleShape temp_shape{ sf::Vector2f(cal_x, cal_y) };
			temp_shape.setPosition(temp_x, temp_y);

			FieldRect* temp = new FieldRect{ temp_shape, FieldRect::NONE };

			//check if player clicked on any rect in game
			
			//if rect is ground
			if (j == "G") {
				temp->setColor(sf::Color(153, 255, 153, 255));
				temp->setType(FieldRect::f_type::GROUND);
			}
			//if rect is water
			else if (j == "W") {
				temp->setColor(sf::Color(50, 50, 255, 255));
				temp->setType(FieldRect::f_type::WATER);
			}
			//if rect is road part
			else if (j == "R") {
				temp->setColor(sf::Color(152, 126, 96, 255));
				temp->setType(FieldRect::f_type::ROAD);
			}
			//if rect is city
			else if (j == "C") {
				temp->setColor(sf::Color(255, 255, 102, 255));
				temp->setType(FieldRect::f_type::CITY);
			}
			//forest
			else if(j == "F"){
				temp->setColor(sf::Color(0, 51, 25, 255));
				temp->setType(FieldRect::f_type::FOREST);
			}
			//mountain
			else if (j == "M") {
				temp->setColor(sf::Color(128, 128, 128, 255));
				temp->setType(FieldRect::f_type::MOUNTAIN);
			}
			//right turn road
			else if (j == "RTR") {
				temp->setColor(sf::Color(152, 126, 96, 255));
				temp->setType(FieldRect::f_type::ROAD);
				temp->setTurnType(FieldRect::turn_type::RIGHT);
			}
			//left turn road
			else if (j == "RTL") {
				temp->setColor(sf::Color(152, 126, 96, 255));
				temp->setType(FieldRect::f_type::ROAD);
				temp->setTurnType(FieldRect::turn_type::LEFT);
			}
			//up turn road
			else if (j == "RTD") {
				temp->setColor(sf::Color(152, 126, 96, 255));
				temp->setType(FieldRect::f_type::ROAD);
				temp->setTurnType(FieldRect::turn_type::DOWN);
			}
			//down turn road
			else if (j == "RTU") {
				temp->setColor(sf::Color(152, 126, 96, 255));
				temp->setType(FieldRect::f_type::ROAD);
				temp->setTurnType(FieldRect::turn_type::UP);
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

	this->resources = {

		{"gold",500},
		{"wood",500},
		{"food",500}
	};
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
	this->textures["gold_mine"] = new sf::Texture{};
	if (!this->textures["gold_mine"]->loadFromFile("src/pics/goldMinePlace.png")) {
		std::cout << "ERROR:LOADFROMFILE::goldMinePlace.png\n";
		return;
	}
	

	//sawmill button
	if (!this->sawmillT.loadFromFile("src/pics/sawmill.png")) {
		std::cout << "ERROR:LOADFROMFILE::sawmill.png\n";
		return;
	}

	//building
	this->textures["sawmill"] = new sf::Texture{};
	if (!this->textures["sawmill"]->loadFromFile("src/pics/sawmillPlace.png")) {
		std::cout << "ERROR:LOADFROMFILE::sawmillPlace.png\n";
		return;
	}


	//turrets textures
	this->textures["bowTurret"] = new sf::Texture{};
	if (!this->textures["bowTurret"]->loadFromFile("src/pics/turrets/bow.png")) {
		std::cout << "ERROR:LOADFROMFILE:PICTURE:bow.png\n";
	}
	this->textures["bowProjectile"] = new sf::Texture{};
	if (!this->textures["bowProjectile"]->loadFromFile("src/pics/turrets/bowArrow.png")) {
		std::cout << "ERROR:LOADFROMFILE:PICTURE:bowArrow.png\n";
	}

	//armies textures


	this->button2.setTexture(this->sawmillT);
	this->button2.setPosition(1150.f, 500.f);

}

void gameWorld::checkButtonCollision()
{
	//gold mine button
	if (this->Tshape.getGlobalBounds().intersects(this->button1.getGlobalBounds()) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		GMine temp;
		//check if enought res to build and space is't occupied
		if (temp.checkEnoughtRes(this->resources["wood"], this->resources["gold"], this->resources["food"]) && this->build(*this->textures["gold_mine"])) {
			temp.MinusCost(this->resources["gold"], this->resources["wood"], this->resources["food"]);
			this->buildings.push_back(temp);
			this->CalculateIncome();
		}
	}
	//sawmil button
	else if (this->Tshape.getGlobalBounds().intersects(this->button2.getGlobalBounds()) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		SawMill temp;

		if (temp.checkEnoughtRes(this->resources["wood"], this->resources["gold"], this->resources["food"]) && this->build(*this->textures["sawmill"])) {
			temp.MinusCost(this->resources["gold"], this->resources["wood"], this->resources["food"]);
			this->buildings.push_back(temp);
			this->CalculateIncome();
		}
	}
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
		this->build(*this->textures["bowTurret"], true);
	}
}

bool gameWorld::build(sf::Texture& _toBuild, bool turret)
{
	bool canBuild = true;
	sf::Sprite newBuilding{ _toBuild };
	newBuilding.setPosition(this->saved_x, this->saved_y);
	//if player tryies to build on same spot multiple time
	for (auto& sprite : this->worldSprites) {
		if (sprite.getGlobalBounds().contains(newBuilding.getPosition())) {
			return false;
		}
	}
	//if player tryies to place more than one turret on same rect
	for (auto& i : this->turrets) {
		if (i.getBounds().contains(newBuilding.getPosition())) {
			return false;
		}
	}

	//if player tryies to build on road or on city 
	for (auto& i : this->worldRects) {
		FieldRect::f_type tempType = i->getType();
		if (tempType == FieldRect::f_type::CITY || tempType == FieldRect::f_type::ROAD || tempType == FieldRect::f_type::WATER) {
			if (this->saved_x == i->getShape().getPosition().x && this->saved_y == i->getShape().getPosition().y) {
				return false;
			}
		}
	}
	//if all is ok build structure
	newBuilding.setScale(this->cal_x / this->goldMineT.getSize().x, this->cal_y / this->goldMineT.getSize().y);
	if (turret) {
		Turret temp{ this->textures["bowTurret"], this->textures["bowProjectile"], turret_type::ARROW};
		temp.setPos(sf::Vector2f{ this->saved_x + temp.getSprite().getGlobalBounds().width / 7, this->saved_y + temp.getSprite().getGlobalBounds().height / 7});
		temp.setScale(this->cal_x / this->goldMineT.getSize().x, this->cal_y / this->goldMineT.getSize().y);

		this->turrets.push_back(temp);
		return true;
	}

	this->worldSprites.push_back(newBuilding);
	return true;
}

void gameWorld::CalculateIncome()
{
	this->temp_incomeFood = 1;
	this->temp_incomeGold = 1;
	this->temp_incomeWood = 1;

	for (auto& i : this->buildings) {
		if (i.getType() == "g_mine") {
			this->temp_incomeGold += 10;
		}
		else if (i.getType() == "w_mine") {
			this->temp_incomeWood += 10;
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

gameWorld::~gameWorld()
{
	for (auto& i : this->worldRects) {
		delete i;
		i = nullptr;
	}

	for (auto& i : this->textures) {
		delete i.second;
	}

}

void gameWorld::getScreenSize(sf::Vector2i _screen_size)
{
	this->screen_size = _screen_size;
}


int gameWorld::getWorldEnd() const
{
	return this->cal_x * this->worldMap[0].size();
}

void gameWorld::setResources(std::map<std::string, int> _res)
{
	this->resources = _res;
}

std::map <std::string, int> gameWorld::getResources() const
{
	return this->resources;
}

std::vector<int> gameWorld::getIncome() const
{
	return std::vector<int>{this->temp_incomeGold, this->temp_incomeWood, this->temp_incomeFood};
}

std::vector<FieldRect*> gameWorld::roadRects() const
{
	std::vector<FieldRect* > roadRects;
	for (auto& i : this->worldRects) {
		//if it's turn road add it to vector
		if (i->getTurn() == FieldRect::turn_type::NONETURN) {
			continue;
		}
		else {
			roadRects.push_back(i);
		}
	}
	return roadRects;
}

void gameWorld::update(sf::Window& window)
{
	this->updateTshape();

	this->getOnRectClick(window);

	this->checkButtonCollision();
	
	//turrets and other


}

void gameWorld::updateTurrets(std::vector<army*>& enemy_armies)
{
	for (auto& i : this->turrets) {
		i.update(enemy_armies[0]->getPos());
	}
	return;
}


void gameWorld::updateTshape()
{
	for (auto i : this->worldRects) {
		if (this->Tshape.getGlobalBounds().intersects(i->getShape().getGlobalBounds())) {
			//std::cout << this->choosedSprite.getPosition().x << ' ' << this->choosedSprite.getPosition().y << '\n';
			this->saved_x = i->getShape().getGlobalBounds().getPosition().x;
			this->saved_y = i->getShape().getGlobalBounds().getPosition().y;
			this->choosedSprite.setPosition(sf::Vector2f{ this->saved_x, this->saved_y });
			//supprots window change
			this->choosedSprite.setScale(this->cal_x / this->choosedTexture.getSize().x, this->cal_y / this->choosedTexture.getSize().y);
		}
	}
	
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
		target.draw(i->getShape());
		
	}	

	for (auto& i : this->worldSprites) {
		target.draw(i);
	}

	for (auto& i : this->turrets) {
		i.render(target);
	}


	if (clicked) {
		target.draw(this->choosedSprite);
	}
	
}

void gameWorld::renderButtons(sf::RenderTarget& target)
{
	target.draw(this->button1);
	target.draw(this->button2);
}

void gameWorld::initGameField()
{
	this->fillRectsV();
}


void gameWorld::initWorldMap()
{
	//G - ground
	this->worldMap = {

		{"G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","M","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G",},
		{"G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","M","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G",},
		{"G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","M","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G",},
		{"G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","M","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G",},
		{"G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","M","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G",},
		{"G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","M","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G",},
		{"G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","M","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G",},
		{"G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","M","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G",},
		{"G","G","G","G","RTR","R","R","R","R","R","R","R","R","R","R","R","R","R","RTD","M","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G",},
		{"G","G","G","G","R","G","G","G","G","G","G","G","G","G","G","G","G","G","R","M","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G",},
		{"G","G","G","G","RTU","R","RTL","G","G","G","G","G","G","G","G","G","G","G","R","M","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G",},
		{"G","G","G","G","G","G","R","G","G","G","G","G","G","G","G","G","G","G","R","M","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G",},
		{"G","G","G","G","G","G","R","G","G","G","G","G","G","G","G","G","G","G","R","M","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G",},
		{"G","G","G","G","G","RTR","RTU","G","G","G","G","G","G","G","G","G","G","G","R","M","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G",},
		{"G","C","R","G","G","R","G","G","G","G","G","G","G","G","G","G","G","G","RTR","R","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","C","G",},
		{"G","G","R","G","G","R","G","G","G","G","G","G","G","G","G","G","G","G","G","M","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G",},
		{"G","G","RTR","R","R","RTU","G","G","G","G","G","G","G","G","G","G","G","G","G","M","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G",},
		{"G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","M","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G",},
		{"G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","M","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G",},
		{"G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","M","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G",},
		{"G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","M","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G",},
		{"G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","M","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G",},
		{"G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","M","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G",},
		{"G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","M","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G",},
		{"G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","M","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G",},
		{"G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","M","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G",},
		{"G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","M","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G",},
		{"G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","M","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G","G",}
	};
}