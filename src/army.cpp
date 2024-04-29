#include "headers/army.h"

army::army(sf::Vector2f size, sf::Vector2f start_pos, sf::Color _color)
{

	this->shape = sf::RectangleShape(size);

	this->shape.setFillColor(_color);

	this->shape.setPosition(start_pos);

	this->speed = 2.f;

	this->moveDir = sf::Vector2f{ 0.f, this->speed };
	this->movingSide = m_side::DOWN;

	this->hp = 100;
	this->alive = true;

}


void army::setMoveDir(sf::Vector2f _moveDir)
{
	this->moveDir = _moveDir;
}

sf::Vector2f army::getPos()
{
	return this->shape.getPosition();
}

sf::FloatRect army::getGlobalBounds()
{
	return this->shape.getGlobalBounds();
}


void army::update(std::vector<std::shared_ptr<FieldRect>> _roads)
{
	this->shape.move(this->moveDir);

	this->updateTurnCollsion(_roads);


	// TODO : create death system
	if (this->shape.getPosition().x > 500.f) {
		this->alive = false;
	}
}

// if army is on turn point pos, turn army and move in different dir
void army::updateTurnCollsion(std::vector<std::shared_ptr<FieldRect>> _roads)
{
	sf::Vector2f floatRectPos{ 0,0 };
	for (auto& i : _roads) {
		//if we on the turn road set pos to this turn road and turn square
		switch (this->movingSide)
		{
		case m_side::DOWN:
			floatRectPos = sf::Vector2f{ i->getGBounds().getPosition().x + i->getGBounds().width / 2,
				i->getGBounds().getPosition().y + i->getGBounds().height - 2.f};
			break;
		case m_side::UP:
			floatRectPos = sf::Vector2f{ i->getGBounds().getPosition().x + i->getGBounds().width / 2,
				i->getGBounds().getPosition().y - 4.f};
			break;
		case m_side::LEFT:
			floatRectPos = sf::Vector2f{ i->getGBounds().getPosition().x - 4.f,
				i->getGBounds().getPosition().y + i->getGBounds().height / 2 };
			break;
		case m_side::RIGHT:
			floatRectPos = sf::Vector2f{ i->getGBounds().getPosition().x + i->getGBounds().width - 2.f,
				i->getGBounds().getPosition().y + i->getGBounds().height / 2};
			break;
		default:
			break;
		}

		sf::FloatRect collRect{ floatRectPos, sf::Vector2f{5.f,5.f} };

		if (this->shape.getGlobalBounds().intersects(collRect)) {

			switch (i->getTurn())
			{
			case FieldRect::turn_type::RIGHT:
				this->moveDir = sf::Vector2f{ this->speed, 0.f };
				this->movingSide = m_side::RIGHT;
				break;
			case FieldRect::turn_type::LEFT:
				this->moveDir = sf::Vector2f{ -this->speed, 0.f };
				this->movingSide = m_side::LEFT;
				break;
			case FieldRect::turn_type::UP:
				this->moveDir = sf::Vector2f{ 0.f, -this->speed };
				this->movingSide = m_side::UP;
				break;
			case FieldRect::turn_type::DOWN:
				this->moveDir = sf::Vector2f{ 0.f, this->speed };
				this->movingSide = m_side::DOWN;
				break;
			default:
				break;
			}
			
		}
	}
}


void army::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}


