#ifndef _GEOM_UTILS_
#define _GEOM_UTILS_

#include <SFML/System/vector2.hpp>
#include <stdlib.h>
#include <cmath>

#define MIN_FLOAT std::numeric_limits<float>::min()
#define MAX_FLOAT std::numeric_limits<float>::max()


inline float dot(sf::Vector2f v1, sf::Vector2f v2) {
	return v1.x * v2.x + v1.y * v2.y;
}

inline float cross(sf::Vector2f v1, sf::Vector2f v2) {
	return v1.x * v2.y - v1.y * v2.x;
}

inline float length(sf::Vector2f v) {
	return sqrtf(dot(v, v));
}

inline sf::Vector2f normalize(sf::Vector2f v) {
	return v/length(v);
}

struct Line {
	Line(sf::Vector2f _origin, sf::Vector2f _direction) {
		origin = _origin;
		direction = _direction;
	}
	sf::Vector2f origin, direction;
};

struct Ray {
	Ray(sf::Vector2f _origin, sf::Vector2f _direction) {
		origin = _origin;
		direction = _direction;
	}
	sf::Vector2f origin, direction;
};

struct LineSegment {
	LineSegment(sf::Vector2f _start, sf::Vector2f _end) {
		start = _start;
		end = _end;
	}
	sf::Vector2f start, end;
};

#endif // _GEOM_UTILS_
