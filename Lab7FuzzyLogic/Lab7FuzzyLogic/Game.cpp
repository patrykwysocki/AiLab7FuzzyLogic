#include "Game.h"
#include <iostream>

static const unsigned int S_WINDOW_H = 600U;
static const unsigned int S_WINDOW_W = 1000U;
/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ S_WINDOW_W, S_WINDOW_H, 32U }, "Fuzzy Logic Lab" },
	m_exitGame{false} //when true game will exit
{	//setUpText();
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_startString.setFillColor(sf::Color::Black);
	m_startString.setCharacterSize(60);
	m_startString.setFont(m_ArialBlackfont);
	m_startString.setString("Press Space to Fuzzify");
	m_startString.setOrigin(sf::Vector2f(m_startString.getGlobalBounds().width / 2, m_startString.getGlobalBounds().height / 2));
	m_startString.setPosition(m_window.getSize().x / 2.0f, m_window.getSize().y / 2.0f);
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}
/// <summary>
/// random number generator in a range
/// </summary>
int Game::randomNum(int t_min, int t_max)
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(t_min, t_max);
	return dist(rng);
}

/// <summary>
/// position,color,character size ,origin of text for the force,range,deployed numbers
/// </summary>
void Game::setUpText()
{
	m_forceString.setFont(m_ArialBlackfont);
	m_rangeString.setFont(m_ArialBlackfont);
	m_deployedString.setFont(m_ArialBlackfont);

	m_forceString.setFillColor(sf::Color::Green);
	m_rangeString.setFillColor(sf::Color::Black);
	m_deployedString.setFillColor(sf::Color::Blue);

	m_forceString.setCharacterSize(35);
	m_rangeString.setCharacterSize(35);
	m_deployedString.setCharacterSize(35);

	m_forceString.setOrigin(sf::Vector2f(m_forceString.getGlobalBounds().width / 2, m_forceString.getGlobalBounds().height / 2));
	m_rangeString.setOrigin(sf::Vector2f(m_rangeString.getGlobalBounds().width / 2, m_rangeString.getGlobalBounds().height / 2));
	m_deployedString.setOrigin(sf::Vector2f(m_deployedString.getGlobalBounds().width / 2, m_deployedString.getGlobalBounds().height / 2));

	m_forceString.setPosition(m_window.getSize().x / 8.0f, m_window.getSize().y / 2.0f);
	m_rangeString.setPosition(m_window.getSize().x / 2.0f, m_window.getSize().y / 2.0f);
	m_deployedString.setPosition(m_window.getSize().x / 1.2f, m_window.getSize().y / 2.0f);
}

/// <summary>
/// where we do the fuzzy stuff
///random generate the range and force, use the fuzzy logic operations
/// fuzzify, defuzzify, set up the aliens and players,
/// draw the texts for the fuzzy variables.
/// </summary>
void Game::fuzzyCreation()
{
	m_startString.setString("");

	//range and force for fuzzy logic
	int range = randomNum(1, 100);
	int force = randomNum(1, 100);
	std::cout << "Range : " << range << std::endl;
	std::cout << "Force : " << force << std::endl;

	//fuzzifiy for size
	m_tiny = FuzzyLogic::FuzzyTriangle(force, -10,0, 10);
	m_small = FuzzyLogic::FuzzyTrapezoid(force, 2.5, 10, 15, 20);
	m_moderate = FuzzyLogic::FuzzyTrapezoid(force, 15, 20, 25, 30);
	m_large = FuzzyLogic::FuzzyGrade(force, 25, 30);

	//fuzzifiy for range
	m_close = FuzzyLogic::FuzzyTriangle(range, -30,0, 30);
	m_medium = FuzzyLogic::FuzzyTrapezoid(range, 10, 30, 50, 70);
	m_far = FuzzyLogic::FuzzyGrade(range, 50, 70);

	//output the results
	std::cout << "Tiny : " << m_tiny << std::endl;
	std::cout << "Small : " << m_small << std::endl;
	std::cout << "Moderate : " << m_moderate << std::endl;
	std::cout << "Large : " << m_large << std::endl;
	std::cout << "Close : " << m_close << std::endl;
	std::cout << "Medium : " << m_medium << std::endl;
	std::cout << "Far : " << m_far << std::endl;

	//rule matrix

	//Low is
	//(Medium AND Tiny) OR(Medium AND Small) OR(Far AND NOT(Large))
	m_low = FuzzyOperations::FuzzyOR
	(FuzzyOperations::FuzzyAND(m_medium, m_tiny),
		FuzzyOperations::FuzzyAND(m_medium, m_small)
	);
	m_low = FuzzyOperations::FuzzyOR(m_low, 
		FuzzyOperations::FuzzyAND(m_far, 
			FuzzyOperations::FuzzyNOT(m_large)));

	//Medium is
	//(Close AND Tiny) OR(Medium AND Moderate) OR(Far AND Large)
	m_mediumHigh = FuzzyOperations::FuzzyOR(
		FuzzyOperations::FuzzyAND(m_close, m_tiny), 
		FuzzyOperations::FuzzyAND(m_medium, m_moderate));

	m_mediumHigh = FuzzyOperations::FuzzyOR(m_mediumHigh, 
		FuzzyOperations::FuzzyAND(m_far, m_large));

	//High is
	//(Close AND NOT(Tiny)) OR(Medium AND Large)
	m_high = FuzzyOperations::FuzzyOR(
		FuzzyOperations::FuzzyAND(m_close, FuzzyOperations::FuzzyNOT(m_tiny)),
		FuzzyOperations::FuzzyAND(m_medium, m_large));

	std::cout << "Low : " << m_low << std::endl;
	std::cout << "MediumHigh : " << m_mediumHigh << std::endl;
	std::cout << "High : " << m_high << std::endl;

	//defuzzify
	m_deploy = ((m_low * 10 + m_mediumHigh * 30 + m_high * 50) /
		(m_low + m_mediumHigh + m_high));
	std::cout << "Deploy : " << m_deploy << std::endl;
	std::cout << "-------------------------------------------------------------------------------" << std::endl;

	//set up the players and aliens in regards of the deploy number and force number
	m_aliens.clear();
	m_players.clear();
	int x = 0;
	int y = 0;
	int px = 0;
	int py = 400;
	for (int i = 0; i < force; ++i)
	{
		//scale the sprite based on the range(how far/close alien is)
		sf::Vector2f tempScale = sf::Vector2f(1.0f - (static_cast<float>(range) / 100.0f),
			(1.0f - (static_cast<float>(range) / 100.0f)));
		m_aliens.push_back(new Alien(sf::Vector2f(x, y)));
		m_aliens.at(i)->setScale(tempScale);

		x += 50;
		if (x > S_WINDOW_W-50)
		{
			x = 0;
			y += 50;
		}
	}
	for (int i = 0; i < m_deploy; ++i)
	{
		m_players.push_back(new Player(sf::Vector2f(px, py)));
		px += 50;
		if (px > S_WINDOW_W-50)
		{
			px = 0;
			py += 50;
		}
	}

	m_forceString.setString("Force : " + std::to_string(force));
	m_rangeString.setString("Range : " + std::to_string(range));
	m_deployedString.setString("Deployed : " + std::to_string(m_deploy));
	setUpText();
}



/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
	if (sf::Keyboard::Space == t_event.key.code)
	{
		fuzzyCreation();
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);

	for (auto& alien : m_aliens)
	{
		alien->draw(m_window);
	}
	for (auto& player : m_players)
	{
		player->draw(m_window);
	}
	m_window.draw(m_startString);
	m_window.draw(m_forceString);
	m_window.draw(m_rangeString);
	m_window.draw(m_deployedString);
	m_window.display();
}
