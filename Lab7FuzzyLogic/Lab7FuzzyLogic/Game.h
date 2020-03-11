#ifndef GAME_HPP
#define GAME_HPP
#include <SFML/Graphics.hpp>
#include "FuzzyLogic.h"
#include "FuzzyOperations.h"
#include "Alien.h"
#include "Player.h"
#include <random>
class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_forceString;
	sf::Text m_rangeString;
	sf::Text m_deployedString;
	sf::Text m_startString;
	bool m_exitGame; // control exiting game
	double m_tiny=0.0;
	double m_small = 0.0;
	double m_moderate = 0.0;
	double m_large = 0.0;
	double m_close = 0.0;
	double m_medium = 0.0;
	double m_far = 0.0;
	double m_low = 0.0;
	double m_mediumHigh = 0.0;
	double m_high = 0.0;
	int m_deploy = 0;
	FuzzyLogic m_fuzzyLogic;
	std::vector<Alien*> m_aliens;
	std::vector<Player*>m_players;
	int randomNum(int t_min, int t_max);
	void setUpText();
	void fuzzyCreation();
};

#endif // !GAME_HPP

