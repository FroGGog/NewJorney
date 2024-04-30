#include "gameWorld.h"
#include "GameStats.h"
#include "army.h"
#include "Turret.h"

class Game
{

private:

	int screen_x, screen_y;

	sf::VideoMode vMode;
	std::shared_ptr<sf::RenderWindow> window;
	sf::Event GameEvents;

	std::vector<std::shared_ptr<army>> enemyArmy;

	std::unique_ptr<gameWorld> gWorld;

	GameStats gameStats;

	//gui
	sf::RectangleShape GUIback;
	sf::RectangleShape blackStroke;

	bool drawFirstTime;
	int enemyCount;

	void InitVars();
	void InitWindow();
	void InitGui();

	//TODO : for test - delete
	sf::Clock spawnerClock;
	sf::Time spawnerTime;
	void spawnArmy();

	void updateEnemiesList();

public:
	//constructor and dest
	Game();

	//accessors
	const bool windowOpen() const;

	void update();
	void updateEvents();

	void render();

};

