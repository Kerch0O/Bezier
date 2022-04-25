#include <SFML/Graphics.hpp>
#include <iostream>
#include "point.h"
#include "functions.h"
#include "link.h"


int mousePointCol(std::vector<point>& p, sf::Vector2f mP) {

	for (int i = 0; i < p.size();  i++) {
		if (pythag(mP - p[i].rep.getPosition()) <= p[i].rep.getRadius()) {
			return i;
		}
	}

	return -1;
}

int main() {

	sf::RenderWindow window(sf::VideoMode(900, 900), "Bezier Curves", sf::Style::Default);

	std::vector<point> points;
	std::vector<link> links;


	bool clicking = false;
	int  currPressed = -1;

	bool stepping = false;

	sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

	sf::Clock dt;
	float deltaTime = 0.0001f;
	float totalTime = 0.0f;
	float movementTime = 1.0f;

	//Setting up points
	//Cubic bezier making U shape

	points.push_back(point(sf::Vector2f(400.0f, 700.0f), 0));
	points.push_back(point(sf::Vector2f(400.0f, 500.0f), 0));
	points.push_back(point(sf::Vector2f(600.0f, 500.0f), 0));
	points.push_back(point(sf::Vector2f(600.0f, 700.0f), 0));

	points.push_back(point(points[0].rep.getPosition(), 1));
	points.push_back(point(points[1].rep.getPosition(), 1));
	points.push_back(point(points[2].rep.getPosition(), 1));

	points.push_back(point(points[4].rep.getPosition(), 2));
	points.push_back(point(points[5].rep.getPosition(), 2));

	points.push_back(point(points[7].rep.getPosition(), 3));

	//Links
	links.push_back(link(points[0], points[1], 0, 1));
	links.push_back(link(points[1], points[2], 1, 2));
	links.push_back(link(points[2], points[3], 2, 3));

	links.push_back(link(points[4], points[5], 4, 5));
	links.push_back(link(points[5], points[6], 5, 6));

	links.push_back(link(points[7], points[8], 7, 8));

	for (int i = 0; i < links.size(); i++) {
		links[i].p3 = i + 4;
	}

	/*Same function as above^
	links[0].p3 = 4;
	links[1].p3 = 5;
	links[2].p3 = 6;
	links[3].p3 = 7;
	links[4].p3 = 8;
	links[5].p3 = 9;
	*/

	bool type1traceD = false;
	bool type2traceD = false;
	bool type3traceD = false;



	while (window.isOpen()) {
		sf::Event evnt;
		while (window.pollEvent(evnt)) {
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				currPressed = mousePointCol(points, mousePos);
				clicking = true;
				
				break;
			case sf::Event::MouseButtonReleased:
				currPressed = -1;
				clicking = false;
				break;
			case sf::Event::TextEntered:
				if (evnt.text.unicode == 's') {
					for (auto& x : points) {
						x.trace.clear();
					}

					stepping = !stepping;
					totalTime = 0.0f;
					std::cout << "Stepping flipped" << std::endl;
				}
				else if (evnt.text.unicode == '1') {
					type1traceD = !type1traceD;
				}
				else if (evnt.text.unicode == '2') {
					type2traceD = !type2traceD;
				}
				else if (evnt.text.unicode == '3') {
					type3traceD = !type3traceD;
				}
				
				break;
			}
		}
		mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

		//get dt
		deltaTime = dt.getElapsedTime().asSeconds();
		dt.restart();

		deltaTime /= movementTime; //when movementTime = 1.0f, then the full movement will take exactly 1 second as it is using deltaTime, dividing lets you change the full movement time
		totalTime += deltaTime * stepping; //if stepping is true then update totalTime(unbranched)
		stepping *= totalTime < 1.0f; //if totaltime has exceeded one then stop stepping

		if (clicking) {
		
			if (currPressed != -1) {
				points[currPressed].rep.setPosition(mousePos);
				for (auto &x: links) {
					if (points[x.p1].type == 0) {
						x.updateRect(points);
					}
				}
			}
		}

		if (stepping) {
			std::cout << "Stepping" << std::endl;
			for (auto& x : links) {
				x.update(totalTime, points);
			}
		}

		window.clear(sf::Color::Black);

		for (auto& x : links) {
			if (points[x.p1].type == 0) {
				window.draw(x.rep);
			}
		}
		for (auto& x : points) {
			window.draw(x.rep);
			if (x.type == 1 && type1traceD || x.type == 2 && type2traceD || x.type == 3 && type3traceD) {
				for (auto& y : x.trace) {
					window.draw(y);
				}
			}
		}


		window.display();
	}

	return 0;
}