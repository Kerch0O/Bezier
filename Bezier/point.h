#pragma once
#include <SFML/Graphics.hpp>

class point {
public:

	int type;
	sf::CircleShape rep;
	std::vector<sf::RectangleShape> trace;

	point(sf::Vector2f p, int t)
	: type(t){
		rep.setOrigin(5.0f, 5.0f);
		rep.setPointCount(100);
		rep.setPosition(p);
		rep.setRadius(5.0f);
		
		sf::Color col;

		switch (t)
		{
		case 0:
			col = sf::Color::Blue;
			break;
		case 1:
			col = sf::Color::Green;
			break;
		case 2:
			col = sf::Color::Red;
			break;
		case 3:
			col = sf::Color::Magenta;
			rep.setRadius(10.0f);
			rep.setOrigin(10.0f, 10.0f);
			rep.setPosition(p);
			break;
		}

		rep.setFillColor(col);
	
	}
};
