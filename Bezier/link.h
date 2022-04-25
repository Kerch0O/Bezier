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

		std::cout << "2: " << p1 << " " << p2 << std::endl;
		sf::Vector2f d = P.rep.getPosition() - p.rep.getPosition();
		rep.setSize(sf::Vector2f(3.0f, pythag(d)));
		rep.setOrigin(1.5f, 0.0f);
		rep.setPosition(p.rep.getPosition());
		rep.setFillColor(sf::Color(255, 255, 255, 20));
		rep.setOutlineColor(sf::Color(255, 255, 255, 50));
		rep.setOutlineThickness(3.0f);
		rep.setRotation(180.0f);

		sf::Vector2f dNorm = d / pythag(d);
		float deg = atan(dNorm.x / dNorm.y) * 180.0f / 3.1415926535f;//Degrees
		deg = deg < 0.0f ? deg * -1.0f : deg;//Absolute

		if (dNorm.x > 0 && dNorm.y > 0) {
			rep.rotate(90.0f);
			deg = 90.0f - deg;
		}
		else if (dNorm.x < 0 && dNorm.y > 0) {
			rep.rotate(180.0f);
		}
		else if (dNorm.x < 0 && dNorm.y < 0) {
			rep.rotate(270.0f);
			deg = 90.0f - deg;
		}
	
		rep.rotate(deg);
		

	}

	void updateRect(std::vector<point> &points) {

		createRect(rep, points[p1].rep.getPosition(), points[p2].rep.getPosition());
	}

	void update(float t, std::vector<point> &points) {
		//lerp() = a + k(b - a)
		if (p3 != -1) {
			sf::Vector2f pastPos = points[p3].rep.getPosition();

			points[p3].rep.setPosition(points[p1].rep.getPosition() + t * (points[p2].rep.getPosition() - points[p1].rep.getPosition()));
			if (pythag(points[p3].rep.getPosition() - pastPos) <= 10.0f) {

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
