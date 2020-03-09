#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>
#include <iostream>
class Player
{
public:
	Player(sf::Vector2f t_position):
		m_position(t_position)
	{
		if (!m_texture.loadFromFile("ASSETS\\IMAGES\\player.png"))
		{
			// simple error message if previous call fails
			std::cout << "problem loading logo" << std::endl;
		}
		m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
		m_sprite.setTexture(m_texture);
		m_sprite.setPosition(t_position);
		
		m_sprite.setScale(0.1, 0.1);
	}
	void draw(sf::RenderWindow& window)
	{
		window.draw(m_sprite);
	}
private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Vector2f m_position;
};
#endif // !PLAYER_H
