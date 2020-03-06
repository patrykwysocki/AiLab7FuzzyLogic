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
	setupFontAndText(); // load font 
	setupSprite(); // load texture
	m_tiny = m_fuzzyLogic.FuzzyTriangle(8, -10, 0, 10);
	m_small = m_fuzzyLogic.FuzzyTrapezoid(8, 2.5, 10, 15,20);
	m_moderate = m_fuzzyLogic.FuzzyTrapezoid(8, 15, 20, 25,30);
	m_large = m_fuzzyLogic.FuzzyGrade(8, 25,30);
	m_close = m_fuzzyLogic.FuzzyTriangle(25,-30,0,30);
	m_medium = m_fuzzyLogic.FuzzyTrapezoid(25,10,30,50,70);
	m_far = m_fuzzyLogic.FuzzyGrade(25,50,70);
	std::cout << "Tiny " << m_tiny << std::endl;
	std::cout << "Small " << m_small << std::endl;
	std::cout << "Moderate " << m_moderate<< std::endl;
	std::cout << "Large" << m_large<< std::endl;
	std::cout << "Close " << m_close << std::endl;
	std::cout << "Medium " << m_medium<< std::endl;
	std::cout << "Far " << m_far<< std::endl;
	m_low = FuzzyOperations::FuzzyOR
	(FuzzyOperations::FuzzyAND(m_medium, m_tiny),
		FuzzyOperations::FuzzyAND(m_medium, m_small));
	m_mediumHigh = FuzzyOperations::FuzzyAND
	(m_close, m_tiny);
	m_high = FuzzyOperations::FuzzyAND
	(m_close, FuzzyOperations::FuzzyNOT(m_medium));
	std::cout << "Low " << m_low << std::endl;
	std::cout << "MediumHigh " << m_mediumHigh << std::endl;
	std::cout << "High " << m_high << std::endl;
	m_deploy = ((m_low * 10 + m_mediumHigh * 30 + m_high * 50) /
		(m_low + m_mediumHigh + m_high));
	std::cout << "Deploy " << m_deploy<< std::endl;
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
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
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
	m_window.draw(m_welcomeMessage);
	m_window.draw(m_logoSprite);
	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_welcomeMessage.setFont(m_ArialBlackfont);
	m_welcomeMessage.setString("SFML Game");
	m_welcomeMessage.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_welcomeMessage.setPosition(40.0f, 40.0f);
	m_welcomeMessage.setCharacterSize(80U);
	m_welcomeMessage.setOutlineColor(sf::Color::Red);
	m_welcomeMessage.setFillColor(sf::Color::Black);
	m_welcomeMessage.setOutlineThickness(3.0f);

}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{
	if (!m_logoTexture.loadFromFile("ASSETS\\IMAGES\\SFML-LOGO.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	m_logoSprite.setTexture(m_logoTexture);
	m_logoSprite.setPosition(300.0f, 180.0f);
}
