#include "gameWorld.h"
#include "GameStats.h"
#include "army.h"
#include "Turret.h"

class Game
{

private:

	int screen_x, screen_y;

	sf::VideoMode vMode;
	sf::RenderWindow* window;
	sf::Event GameEvents;

	std::map<std::string, sf::Texture*> textures;

	gameWorld gWorld;

	GameStats gameStats;

	army* tempArmy;
	Turret* tempTurret;

	//gui
	sf::RectangleShape GUIback;
	sf::RectangleShape blackStroke;

	bool drawFirstTime;

	void InitVars();
	void InitWindow();
	void InitGui();
	void InitTextures();


public:
	//constructor and dest
	Game();
	virtual ~Game();

	//accessors
	const bool windowOpen() const;

	void update();
	void updateEvents();

	void render();

};

