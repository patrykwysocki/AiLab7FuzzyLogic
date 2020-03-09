#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	setUpText();
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
int Game::randomNum(int t_min, int t_max)
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(t_min, t_max);
	return dist(rng);
}

void Game::setUpText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_forceString.setFont(m_ArialBlackfont);
	m_distanceString.setFont(m_ArialBlackfont);
	m_deployedString.setFont(m_ArialBlackfont);
	m_forceString.setFillColor(sf::Color::Green);
	m_distanceString.setFillColor(sf::Color::Black);
	m_deployedString.setFillColor(sf::Color::Blue);
	m_forceString.setPosition(sf::Vector2f(0, 300));
	m_distanceString.setPosition(sf::Vector2f(300, 300));
	m_deployedString.setPosition(sf::Vector2f(590, 300));
}

void Game::fuzzyCreation()
{
	int distance = randomNum(1, 100);
	int force = randomNum(1, 46);
	std::cout << "Distance " << distance << std::endl;
	std::cout << "Force " << force << std::endl;

	m_tiny = FuzzyLogic::FuzzyGrade(force, 0, 10);
	m_small = FuzzyLogic::FuzzyTrapezoid(force, 2.5, 10, 15, 20);
	m_moderate = FuzzyLogic::FuzzyTrapezoid(force, 15, 20, 25, 30);
	m_large = FuzzyLogic::FuzzyGrade(force, 25, 30);

	m_close = FuzzyLogic::FuzzyGrade(distance, 0, 30);
	m_medium = FuzzyLogic::FuzzyTrapezoid(distance, 10, 30, 50, 70);
	m_far = FuzzyLogic::FuzzyGrade(distance, 50, 70);

	std::cout << "Tiny " << m_tiny << std::endl;
	std::cout << "Small " << m_small << std::endl;
	std::cout << "Moderate " << m_moderate << std::endl;
	std::cout << "Large" << m_large << std::endl;
	std::cout << "Close " << m_close << std::endl;
	std::cout << "Medium " << m_medium << std::endl;
	std::cout << "Far " << m_far << std::endl;

	//Low is
	//(Medium AND Tiny) OR(Medium AND Small) OR(Far AND NOT(Large))

	m_low = FuzzyOperations::FuzzyOR
	(FuzzyOperations::FuzzyAND(m_medium, m_tiny),
		FuzzyOperations::FuzzyAND(m_medium, m_small)
	);

	//Medium is
	//(Close AND Tiny) OR(Medium AND Moderate) OR(Far AND Large)

	m_mediumHigh = FuzzyOperations::FuzzyAND
	(m_close, m_tiny);

	//High is
	//(Close AND NOT(Tiny)) OR(Medium AND Large)

	m_high = FuzzyOperations::FuzzyAND
	(m_close, FuzzyOperations::FuzzyNOT(m_medium));


	std::cout << "Low " << m_low << std::endl;
	std::cout << "MediumHigh " << m_mediumHigh << std::endl;
	std::cout << "High " << m_high << std::endl;

	m_deploy = ((m_low * 10 + m_mediumHigh * 30 + m_high * 50) /
		(m_low + m_mediumHigh + m_high));

	std::cout << "Deploy " << m_deploy << std::endl;
	std::cout << "-------------------------------------------------------------------------------" << std::endl;
	m_aliens.clear();
	m_players.clear();
	int x = 0;
	int y = 0;
	int px = 0;
	int py = 400;
	for (int i = 0; i < force; ++i)
	{
		m_aliens.push_back(new Alien(sf::Vector2f(x, y)));
		x += 50;
		if (x > 750)
		{
			x = 0;
			y += 50;
		}
	}
	for (int i = 0; i < m_deploy; ++i)
	{
		m_players.push_back(new Player(sf::Vector2f(px, py)));
		px += 50;
		if (px > 750)
		{
			px = 0;
			py += 50;
		}
	}
	m_forceString.setString("Force: " + std::to_string(force));
	m_distanceString.setString("Distance: " + std::to_string(distance));
	m_deployedString.setString("Deployed: " + std::to_string(m_deploy));
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
	m_window.draw(m_forceString);
	m_window.draw(m_distanceString);
	m_window.draw(m_deployedString);
	m_window.display();
}
