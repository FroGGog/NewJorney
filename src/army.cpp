#include "headers/army.h"

army::army(sf::Vector2f size, sf::Vector2f start_pos, sf::Color _color)
{

	this->shape = new sf::RectangleShape(size);

	this->shape->setFillColor(_color);

	this->shape->setPosition(start_pos);

	this->speed = 4.f;

	this->moveDir = sf::Vector2f{ 0.f, this->speed };

}

army::~army()
{
	delete this->shape;

}

void army::setMoveDir(sf::Vector2f _moveDir)
{
	this->moveDir = _moveDir;
}


void army::update(std::vector<FieldRect*> _roads)
{
	this->shape->move(this->moveDir);

	this->updateTurnCollsion(_roads);
}



void army::updatePos(std::vector<FieldRect*> _roads)
{

	this->moveTime = this->armyMove.getElapsedTime();

	if (this->moveTime.asSeconds() > .5f) {
		

		this->armyMove.restart();

	}

}

void army::updateTurnCollsion(std::vector<FieldRect*> _roads)
{
	
	for (auto& i : _roads) {
		//if we on the turn road set pos to this turn road and turn square
		

		if (i->getShape().getPosition() == this->shape->getPosition()) {
			std::cout << "x " << i->getShape().getPosition().x << " y " << i->getShape().getPosition().y << '\n';
			std::cout << "x " << this->shape->getPosition().x << " y " << this->shape->getPosition().y << '\n';
			std::cout << "TURN\n";
			switch (i->getTurn())
			{
			case FieldRect::turn_type::RIGHT:
				this->speed = 2.5f;
				this->moveDir = sf::Vector2f{ this->speed, 0.f };
				break;
			case FieldRect::turn_type::LEFT:
				this->speed = 2.5f;
				this->moveDir = sf::Vector2f{ -this->speed, 0.f };
				break;
			case FieldRect::turn_type::UP:
				this->speed = 2.f;
				this->moveDir = sf::Vector2f{ 0.f, -this->speed };
				break;
			case FieldRect::turn_type::DOWN:
				this->speed = 2.f;
				this->moveDir = sf::Vector2f{ 0.f, this->speed };
				break;
			default:
				break;
			}
			
		}
	}
}




void army::render(sf::RenderTarget& target)
{
	target.draw(*this->shape);
}


