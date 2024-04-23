#include "headers/army.h"

army::army(sf::Vector2f size, sf::Vector2f start_pos, sf::Color _color, sf::Vector2f _dest) : pos(start_pos), dest(_dest)
{

	this->shape = new sf::RectangleShape(size);

	this->shape->setFillColor(_color);

	this->shape->setPosition(this->pos);

	this->state = ATTACK;

	this->lastElem = false;
	this->counter = 0;

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
	if (this->shape->getPosition() == this->dest) {
		return;
	}
	this->moveTime = this->armyMove.getElapsedTime();

	if (this->moveTime.asSeconds() > .5f) {
		std::cout << this->distance << '\n';
		for (auto& i : _roads) {
			if (i->getShape().getPosition() != this->shape->getPosition()) {
				if (this->shape->getGlobalBounds().intersects(i->getShape().getGlobalBounds())) {
					if (this->updateDistance(i->getShape().getPosition())) {
						this->shape->setPosition(i->getShape().getPosition());
						break;
					}
					else {
						this->shape->setPosition(sf::Vector2f{ i->getShape().getPosition().x, i->getShape().getPosition().y - 25 });
					}
				}	
			}
		}
		this->armyMove.restart();

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


