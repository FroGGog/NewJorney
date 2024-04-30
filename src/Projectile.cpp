#include "headers/Projectile.h"


void Projectile::updateBorderCollision()
{
	if (this->sprite.getPosition().x > 1400 || this->sprite.getPosition().x < 0) {
		this->state = projectile_state::OUT;
	}
	else if (this->sprite.getPosition().y > 1000 || this->sprite.getPosition().y < 0) {
		this->state = projectile_state::OUT;
	}
}

void Projectile::updateEnemyCollision(std::shared_ptr<army> checkArmy)
{
	if (this->sprite.getGlobalBounds().intersects(checkArmy->getGlobalBounds())) {
		checkArmy->gotHit(this->damage);
		this->state = projectile_state::HIT;
	}
}


Projectile::Projectile(float r_degrees, sf::Vector2f start_pos, std::shared_ptr<sf::Texture> _texture) : rotation(r_degrees)
{
	
	this->sprite.setTexture(*_texture);
	this->sprite.setPosition(start_pos);
	this->sprite.setRotation(this->rotation);

	this->sprite.setOrigin(_texture->getSize().x / static_cast<float>(2), _texture->getSize().y / static_cast<float>(2));

	this->speed = 20.f;
	this->state = projectile_state::NONE;
	this->damage = 1.f;

	this->velocity.x = std::cos(this->rotation * 3.14 / 180.0) * speed;
	this->velocity.y = std::sin(this->rotation * 3.14 / 180.0) * speed;

}

void Projectile::setScale(float x, float y)
{
	this->sprite.setScale(x / 5, y / 5);
}

void Projectile::setDamage(int _damage)
{
	this->damage = _damage;
}

projectile_state Projectile::getState() const
{
	return this->state;
}

void Projectile::update(std::shared_ptr<army> checkArmy)
{

	this->sprite.move(this->velocity);

	this->updateBorderCollision();

	//
	this->updateEnemyCollision(checkArmy);

}

void Projectile::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}

