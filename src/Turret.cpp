#include "headers/Turret.h"


Turret::Turret(std::shared_ptr<sf::Texture> _texture, std::shared_ptr<sf::Texture> _projectileTexture , turret_type _type)
{

	this->sprite.setTexture(*_texture);
	this->projectileTexture = _projectileTexture;


	this->sprite.setOrigin(_texture->getSize().x / static_cast<float>(2), _texture->getSize().y / static_cast<float>(2));

	this->attackSpeed = 1.f;
	this->rotationSpeed = 0.89f;
	this->saved_x = 5.f;
	this->saved_y = 5.f;

	this->type = _type;
	this->radius = 0.f;

	switch (this->type)
	{
	case turret_type::ARROW:
		this->radius = 20.f;
		this->radiusShape = sf::CircleShape{ this->radius };
		break;
	default:
		break;
	}

}



sf::Sprite Turret::getSprite() const
{
	return this->sprite;
}

void Turret::setPos(sf::Vector2f _newPos)
{
	this->sprite.setPosition(_newPos);
	this->radiusShape.setOrigin(this->sprite.getOrigin());
	this->radiusShape.setPosition(this->sprite.getPosition());
}

void Turret::setScale(float x, float y)
{
	this->sprite.setScale(x, y);
	this->saved_x = x;
	this->saved_y = y;
}

sf::FloatRect Turret::getBounds()
{
	return this->sprite.getGlobalBounds();
}

void Turret::update(std::vector<std::shared_ptr<army>> enemy_armies)
{
	//pointer to closest enemy for turret
	std::shared_ptr<army> _enemyArmy = this->findClosestEnemy(enemy_armies);

	if (_enemyArmy != nullptr) {
		//rotation system
		float angle = atan2((_enemyArmy->getPos().y + 2.5f) - this->sprite.getPosition().y,
			(_enemyArmy->getPos().x + 2.5f) - this->sprite.getPosition().x) * 180 / 3.14;

		this->sprite.setRotation(angle);

		//shoot system
		this->shoot(_enemyArmy->getPos());
	}

	//update projectiles
	for (auto& i : this->projectiles) {
		i->update(_enemyArmy);
	}

	//check if projectile out of borders
	this->updateOutProjectiles();

	//check if projectiles hit enemy army
	this->updateHitProjectiles();

}

void Turret::render(sf::RenderTarget& target)
{	
	target.draw(this->sprite);

	for (auto& i : this->projectiles) {
		i->render(target);
	}

	target.draw(this->radiusShape);

}


void Turret::shoot(sf::Vector2f _enemyPos)
{
	
	this->reloadTime = this->reloadClock.getElapsedTime();

	if (this->reloadTime.asSeconds() > .5f) {

		float ProjectileAngle = atan2(_enemyPos.y - this->sprite.getPosition().y, _enemyPos.x - this->sprite.getPosition().x) * 180 / 3.14;

		sf::Vector2f projectile_stPos = {this->sprite.getPosition().x + this->sprite.getGlobalBounds().width / 4 - 1.f,
			this->sprite.getPosition().y + this->sprite.getGlobalBounds().height / 10 - 1.f};

		std::shared_ptr<Projectile> tempArrow = std::make_shared<Projectile>(ProjectileAngle, projectile_stPos , this->projectileTexture);

		switch (this->type)
		{
		case turret_type::ARROW:
			tempArrow->setDamage(25);
			break;
		default:
			break;
		}

		tempArrow->setScale(this->saved_x, this->saved_y);
		
		this->projectiles.push_back(tempArrow);

		this->reloadClock.restart();

	}

}

void Turret::updateOutProjectiles()
{
	//if projectile out of screen border - delete it
	for (int i{ 0 }; i < this->projectiles.size(); i++) {
		if (this->projectiles[i]->getState() == projectile_state::OUT) {
			this->projectiles.erase(this->projectiles.begin() + i);
		}
	}
}

void Turret::updateHitProjectiles()
{
	//if projectile hits enemy
	for (int i{ 0 }; i < this->projectiles.size(); i++) {
		if (this->projectiles[i]->getState() == projectile_state::HIT) {
			this->projectiles.erase(this->projectiles.begin() + i);
		}
	}

}

std::shared_ptr<army> Turret::findClosestEnemy(std::vector<std::shared_ptr<army>> enemy_armies)
{
	if (enemy_armies.size() == 0) {
		return nullptr;
	}

	float ShortestDistance = 10000;
	float tempDistance = 0;
	//if there are no closer enemy take first from list
	std::shared_ptr<army> tempArmy = nullptr;

	for (auto& i : enemy_armies) {
		
		tempDistance = this->calculateDistance(i->getPos());
		if (tempDistance < ShortestDistance) {
			tempArmy = i;
			ShortestDistance = tempDistance;
		}
	}
	return tempArmy;
	
}

float Turret::calculateDistance(sf::Vector2f enemyPos)
{
	float distance = sqrt(abs(pow(enemyPos.x - this->sprite.getPosition().x, 2) + pow(enemyPos.y - this->sprite.getPosition().y, 2)));

	return distance;
}

