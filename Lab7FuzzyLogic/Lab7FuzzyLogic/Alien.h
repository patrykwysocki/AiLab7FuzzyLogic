#ifndef ALIEN_H
#define ALIEN_H
#include <SFML/Graphics.hpp>
#include <iostream>
class Alien
{
public:
	Alien(sf::Vector2f t_position) :
		m_position(t_position)
	{
		if (!m_texture.loadFromFile("ASSETS\\IMAGES\\apes.png"))
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
	void setScale(sf::Vector2f t_scalar)
	{
		m_sprite.scale(t_scalar);
	}
private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Vector2f m_position;
};
#endif // !ALIEN_H
