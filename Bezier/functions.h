#pragma once

float pythag(sf::Vector2f a) {
	return sqrt(a.x * a.x + a.y * a.y);
}

void createRect(sf::RectangleShape &r, sf::Vector2f p1, sf::Vector2f p2) {
	sf::Vector2f d = p2 - p1;
	r.setSize(sf::Vector2f(3.0f, pythag(d)));
	r.setOrigin(1.5f, 0.0f);
	r.setPosition(p1);
	r.setRotation(180.0f);

	d /= pythag(d);

	float deg = atan(d.x / d.y) * 180.0f / 3.14159265358979f;
	deg = deg < 0.0f ? deg * -1.0f : deg;

	if (d.x > 0 && d.y > 0) {
		r.rotate(90.0f);
		deg = 90.0f - deg;
	}
	else if (d.x < 0 && d.y > 0) {
		r.rotate(180.0f);
	}
	else if (d.x < 0 && d.y < 0) {
		r.rotate(270.0f);
		deg = 90.0f - deg;
	}

	r.rotate(deg);

}

