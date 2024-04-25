#include "headers/army.h"

army::army(sf::Vector2f size, sf::Vector2f start_pos, sf::Color _color, sf::Vector2f _dest) : pos(start_pos), dest(_dest)
{

	this->shape = new sf::RectangleShape(size);

	this->shape->setFillColor(_color);

	this->shape->setPosition(this->pos);

	this->state = ATTACK;

	this->distance = sqrt(pow(int(this->dest.x - start_pos.x), 2) - pow(int(this->dest.y - start_pos.y), 2));

}

army::~army()
{
	delete this->shape;

}



void army::update(std::vector<FieldRect*> _roads)
{

	if (this->state == status::ATTACK) {
		this->updatePos(_roads);
	}

}

int army::getDistance(sf::Vector2f _newPos)
{
	int tempDist = sqrt(pow(abs(int(this->shape->getPosition().x - _newPos.x)), 2) - pow(abs(int(this->shape->getPosition().y - _newPos.y)), 2));
	return tempDist;
}

bool army::updateDistance(sf::Vector2f _newPos)
{
	int tempDist = sqrt(pow(int(this->dest.x - _newPos.x), 2) - pow(int(this->dest.y - _newPos.y), 2));
	if (tempDist <= this->distance - 1) {
		this->distance = tempDist;
		return true;
	}
	return false;
}

void army::updatePos(std::vector<FieldRect*> _roads)
{
	this->savedDistance = this->distance;
	if (this->shape->getPosition() == this->dest) {
		this->shape->setPosition(this->dest);
		this->state = status::IDLE;
		std::cout << "ONPLACE\n";
		return;
	}

	std::vector<FieldRect*> s_roads;
	FieldRect* shortesDist = nullptr;
	this->moveTime = this->armyMove.getElapsedTime();
	int counter = 0;

	if (this->moveTime.asSeconds() > 0.5f) {
		for (auto& i : _roads) {
			if (this->shape->getPosition() == i->getShape().getPosition()) {
				s_roads.push_back(i);
				continue;
			}
			int tempDist = getDistance(i->getShape().getPosition());
			if (tempDist <= 25 && tempDist > 0) {
				s_roads.push_back(i);
			}
		}

		for (int i{ 0 }; i < s_roads.size(); i++) {

			if (this->shape->getPosition() == s_roads[i]->getShape().getPosition()) {
				if (i == s_roads.size() - 1) {
					this->shape->setPosition(s_roads[i - 1]->getShape().getPosition());
					break;
				}
				std::cout << "GOT\n";
				this->shape->setPosition(s_roads[i + 1]->getShape().getPosition());
				break;
			}

		}

		this->armyMove.restart();
	}


	for (auto& i : s_roads) {
		i = nullptr;
	}
	
	
}

void army::moveUp()
{
	this->shape->setPosition(this->shape->getPosition().x, this->shape->getPosition().y - this->shape->getGlobalBounds().height);
}



void army::render(sf::RenderTarget& target)
{
	target.draw(*this->shape);
}


