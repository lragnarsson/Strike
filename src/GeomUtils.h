/***************************************
GeomUtils.h

Linear algebra utils.

Written by
Jesper Otterholm
***************************************/

#ifndef _GEOM_UTILS_
#define _GEOM_UTILS_

#include <stdlib.h>
#include <cmath>
#include <limits>

#include <SFML/System.hpp>

#define MIN_FLOAT std::numeric_limits<float>::min()
#define MAX_FLOAT std::numeric_limits<float>::max()
#define EPSILON std::numeric_limits<float>::epsilon()


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

inline bool equalf(float a, float b) {
	return fabs(a - b) < EPSILON;
}

inline int sgn(float x) {
    return (x > 0) - (x < 0);
}

inline float smoothstep(float a, float b, float f) {
    return ( f < a ? 0 : ( f > b ? 1 : f/(b-a) ) );
}

inline float lengthsq(sf::Vector2f v) {
    return dot(v, v);
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
