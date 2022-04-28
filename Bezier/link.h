#pragma once
#include <SFML/Graphics.hpp>
#include "point.h"
#include "functions.h"

class link {
public:

	sf::RectangleShape rep;
	int p1;//Index positions of the points in the points[] array
	int p2;
	int p3;

	link() :p1(-1), p2(-1), p3(-1) {}

	link(point& p, point &P, int i1, int i2) 
	:  p1(i1), p2(i2), p3(-1){

		sf::Vector2f d = P.rep.getPosition() - p.rep.getPosition();
		rep.setFillColor(sf::Color(255, 255, 255, 20));
		rep.setOutlineColor(sf::Color(255, 255, 255, 50));
		rep.setOutlineThickness(3.0f);
		createRect(rep, p.rep.getPosition(), P.rep.getPosition());
	}

	void updateRect(std::vector<point> &points) {

		createRect(rep, points[p1].rep.getPosition(), points[p2].rep.getPosition());
	}

	void update(float t, std::vector<point> &points) {
		//lerp() = a + k(b - a)
		if (p3 != -1) {
			sf::Vector2f pastPos = points[p3].rep.getPosition();

			points[p3].rep.setPosition(points[p1].rep.getPosition() + t * (points[p2].rep.getPosition() - points[p1].rep.getPosition()));
			if (pythag(points[p3].rep.getPosition() - pastPos) <= 50.0f) {

				sf::RectangleShape r;
				createRect(r, pastPos, points[p3].rep.getPosition());
				switch (points[p3].type) {
				case 1:

					r.setFillColor(sf::Color(0, 255, 0, 150));
					break;
				case 2:

					r.setFillColor(sf::Color(255, 0, 0, 150));
					break;
				case 3:

					r.setFillColor(sf::Color(255, 0, 255, 150));
					break;
				}

				points[p3].trace.push_back(r);
			}
		}
	}

};
