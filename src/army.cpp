#include "headers/army.h"

army::army(sf::Vector2f size, sf::Vector2f start_pos, sf::Color _color)
{

	this->shape = new sf::RectangleShape(size);

	this->shape->setFillColor(_color);

	this->shape->setPosition(start_pos);

	this->speed = 4.f;

	this->moveDir = sf::Vector2f{ 0.f, this->speed };

	this->hp = 100;
	this->alive = true;

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


	// TODO : create death system
	if (this->shape->getPosition().x > 500.f) {
		this->alive = false;
	}
}

// if army is on turn point pos, turn army and move in different dir
void army::updateTurnCollsion(std::vector<FieldRect*> _roads)
{
	
	for (auto& i : _roads) {
		//if we on the turn road set pos to this turn road and turn square
	
		if (i->getShape().getPosition() == this->shape->getPosition()) {

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


