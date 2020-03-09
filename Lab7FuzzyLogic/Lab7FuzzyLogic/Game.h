#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
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
	sf::Text m_distanceString;
	sf::Text m_deployedString;
	bool m_exitGame; // control exiting game
	double m_tiny;
	double m_small;
	double m_moderate;
	double m_large;
	double m_close;
	double m_medium;
	double m_far;
	double m_low;
	double m_mediumHigh;
	double m_high;
	int m_deploy;
	FuzzyLogic m_fuzzyLogic;
	std::vector<Alien*> m_aliens;
	std::vector<Player*>m_players;
	int randomNum(int t_min, int t_max);
	void setUpText();
	void fuzzyCreation();
};

#endif // !GAME_HPP

