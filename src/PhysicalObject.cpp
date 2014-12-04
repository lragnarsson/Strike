#include "PhysicalObject.h"
#include "GeomUtils.h"
#include <limits>
#include <SFML/System.hpp>
#include <stdlib.h>
#include <cmath>
#include <iostream>

/*
 * PHYSICAL_CIRCLE
 */

bool PhysicalCircle::lineIntersect(Line line, float& t1, float& t2) const {
	sf::Vector2f f = line.origin - center_;
	float a = dot(line.direction, line.direction);
	float b = 2*dot(f, line.direction);
	float c = dot(f, f) - radius_*radius_;

	float discriminant = b*b - 4*a*c;

	if (discriminant < 0) {
		return false;
	}
	else {
		discriminant = sqrtf(discriminant);
		t1 = (-b - discriminant)/(2*a);
		t2 = (-b + discriminant)/(2*a);
	}

	return true;
}

PhysicalCircle* PhysicalCircle::clone() const {
	return new PhysicalCircle{*this};
}

bool PhysicalCircle::intersectLine(Line line) const {
	sf::Vector2f dummy1;
	sf::Vector2f dummy2;

	return intersectLine(line, dummy1, dummy2);
}

bool PhysicalCircle::intersectLine(Line line, sf::Vector2f& intersectionPoint) const {
	sf::Vector2f dummy;

	return intersectLine(line, intersectionPoint, dummy);
}

bool PhysicalCircle::intersectLine(Line line, sf::Vector2f& intersectionPoint, sf::Vector2f& intersectionNormal) const {
	float t1, t2;
	if (lineIntersect(line, t1, t2)) {
		float t = (abs(t1) < abs(t2)) ? t1 : t2;
		intersectionPoint = sf::Vector2f(line.origin + t*line.direction);
		intersectionNormal = sf::Vector2f(normalize(intersectionPoint - center_));
	}
	else
		return false;

	return true;
}

bool PhysicalCircle::intersectLineSegment(LineSegment lineSegment) const {
	sf::Vector2f dummy1;
	sf::Vector2f dummy2;

	return intersectLineSegment(lineSegment, dummy1, dummy2);
}

bool PhysicalCircle::intersectLineSegment(LineSegment lineSegment, sf::Vector2f& intersectionPoint) const {
	sf::Vector2f dummy;

	return intersectLineSegment(lineSegment, intersectionPoint, dummy);
}

bool PhysicalCircle::intersectLineSegment(LineSegment lineSegment, sf::Vector2f& intersectionPoint, sf::Vector2f& intersectionNormal) const {
	float t1, t2;
	//std::cout << "lineSegment: " << lineSegment.start.x << " " << lineSegment.start.y << " " << lineSegment.end.x << " " << lineSegment.end.y << std::endl;
	if (lineIntersect(Line(lineSegment.start, lineSegment.end - lineSegment.start), t1, t2)) {
		float t;
		if (t1 >= 0.0f && t1 <= 1.0f)
			if (t2 >= 0.0f && t1 <= 1.0f)
				t = (t1 < t2) ? t1 : t2;
			else
				t = t1;
		else if (t2 >= 0.0f && t2 <= 1.0f)
			t = t2;
		else
			return false;

 		intersectionPoint = lineSegment.start + t*(lineSegment.end - lineSegment.start);
		intersectionNormal = sf::Vector2f(normalize(intersectionPoint - center_));
	}
	else
		return false;

	return true;
}

bool PhysicalCircle::intersectRay(Ray ray) const {
	sf::Vector2f dummy1;
	sf::Vector2f dummy2;

	return intersectRay(ray, dummy1, dummy2);
}

bool PhysicalCircle::intersectRay(Ray ray, sf::Vector2f& intersectionPoint) const {
	sf::Vector2f dummy;

	return intersectRay(ray, intersectionPoint, dummy);
}

bool PhysicalCircle::intersectRay(Ray ray, sf::Vector2f& intersectionPoint, sf::Vector2f& intersectionNormal) const {
	float t1, t2;
	if (lineIntersect(Line(ray.origin, ray.direction), t1, t2)) {
		float t;
		if (t1 >= 0.0f)
			if (t2 >= 0.0f)
				t = (t1 < t2) ? t1 : t2;
			else
				t = t1;
		else if (t2 >= 0.0f)
			t = t2;
		else
			return false;

 		intersectionPoint = sf::Vector2f(ray.origin + t*ray.direction);
		intersectionNormal = sf::Vector2f(normalize(intersectionPoint - center_));
	}
	else
		return false;

	return true;
}

bool PhysicalCircle::intersectCircle(float radius, LineSegment displacement) const {
	sf::Vector2f dummy1;
	sf::Vector2f dummy2;
	sf::Vector2f dummy3;

	return intersectCircle(radius, displacement, dummy1, dummy2, dummy3);
}

bool PhysicalCircle::intersectCircle(float radius, LineSegment displacement, sf::Vector2f& centerAfterCollision) const {
	sf::Vector2f dummy1;
	sf::Vector2f dummy2;

	return intersectCircle(radius, displacement, centerAfterCollision, dummy1, dummy2);
}

bool PhysicalCircle::intersectCircle(float radius, LineSegment displacement, sf::Vector2f& centerAfterCollision, sf::Vector2f& intersectionPoint) const {
	sf::Vector2f dummy;

	return intersectCircle(radius, displacement, centerAfterCollision, intersectionPoint, dummy);
}

bool PhysicalCircle::intersectCircle(float radius, LineSegment displacement, sf::Vector2f& centerAfterCollision, sf::Vector2f& intersectionPoint, sf::Vector2f& intersectionNormal) const {
	sf::Vector2f v = displacement.end - displacement.start;
	sf::Vector2f p = center_;
	sf::Vector2f w = p - displacement.start;
	float a = dot(w, v)/dot(v, v);
	float b = (radius+radius_) * (radius+radius_) - dot(w - a*v, w - a*v);

	if (b >= 0) {
		float d = a - sqrtf(b/dot(v, v));
		if (d > 0.0f && d < 1.0f) {
                  centerAfterCollision = displacement.start + (d - 0.1f)*v;
			intersectionPoint = centerAfterCollision + radius*normalize(p - centerAfterCollision);
			intersectionNormal = normalize(intersectionPoint - center_);

			return true;
		}
	}

	return false;
}

float PhysicalCircle::getRadius() const {
    return radius_;
}

void PhysicalCircle::setCenter(sf::Vector2f center) {
    center_ = center;
}

/*
 * PHYSICAL_POLYGON
+ */

bool PhysicalPolygon::lineIntersect(Line line, LineSegment lineSegment, float& t, float& u) const {
	sf::Vector2f r = line.direction;
	sf::Vector2f s = lineSegment.end - lineSegment.start;
	sf::Vector2f CmP = lineSegment.start - line.origin;

	float rxs = cross(r, s);

	if (rxs == 0.0f)
		return false;

	float CmPxr = cross(CmP, r);
	float CmPxs = cross(CmP, s);

	float rxsr = 1.0f / rxs;
	t = CmPxs * rxsr;
	u = CmPxr * rxsr;

	return true;
}

PhysicalPolygon* PhysicalPolygon::clone() const {
	return new PhysicalPolygon{*this};
}

bool PhysicalPolygon::intersectLine(Line line) const {
	sf::Vector2f dummy1;
	sf::Vector2f dummy2;

	return intersectLine(line, dummy1, dummy2);
}

bool PhysicalPolygon::intersectLine(Line line, sf::Vector2f& intersectionPoint) const {
	sf::Vector2f dummy;

	return intersectLine(line, intersectionPoint, dummy);
}

bool PhysicalPolygon::intersectLine(Line line, sf::Vector2f& intersectionPoint, sf::Vector2f& intersectionNormal) const {
	float minD{MAX_FLOAT};
	sf::Vector2f closestIntersectionPoint;
	sf::Vector2f closestIntersectionNormal;

	for (auto pVertex = vertices_.begin() + 1; pVertex != vertices_.end(); pVertex++) {
		float t, u;
		if (lineIntersect(line, LineSegment(*pVertex, *(pVertex-1)), t, u)) {
			if (u >= 0.0f && u <= 1.0f) {
				float d = length(t*line.direction);
				if (d < minD) {
					minD = d;
					closestIntersectionPoint = line.origin + t*line.direction;
					closestIntersectionNormal = normalize(sf::Vector2f(-(*(pVertex-1)-*pVertex).x, (*(pVertex-1)-*pVertex).y));
				}
			}
		}
	}

	if (minD == MAX_FLOAT)
		return false;
	else {
		intersectionPoint = closestIntersectionPoint;
		intersectionNormal = closestIntersectionNormal;
	}

	return true;
}

bool PhysicalPolygon::intersectLineSegment(LineSegment lineSegment) const {
	sf::Vector2f dummy1;
	sf::Vector2f dummy2;

	return intersectLineSegment(lineSegment, dummy1, dummy2);
}

bool PhysicalPolygon::intersectLineSegment(LineSegment lineSegment, sf::Vector2f& intersectionPoint) const {
	sf::Vector2f dummy;

	return intersectLineSegment(lineSegment, intersectionPoint, dummy);
}

bool PhysicalPolygon::intersectLineSegment(LineSegment lineSegment, sf::Vector2f& intersectionPoint, sf::Vector2f& intersectionNormal) const {
	float minD{MAX_FLOAT};
	sf::Vector2f closestIntersectionPoint;
	sf::Vector2f closestIntersectionNormal;

	Line line(lineSegment.start, lineSegment.end - lineSegment.start);

	for (auto pVertex = vertices_.begin() + 1; pVertex != vertices_.end(); pVertex++) {
		float t, u;
		if (lineIntersect(line, LineSegment(*(pVertex - 1), *pVertex), t, u)) {
			if (t >= 0.0f && t <= 1.0f && u >= 0.0f && u <= 1.0f) {
				float d = length(t*line.direction);
				if (d < minD) {
					minD = d;
					closestIntersectionPoint = line.origin + t*line.direction;
					closestIntersectionNormal = normalize(sf::Vector2f(-(*(pVertex-1)-*pVertex).x, (*(pVertex-1)-*pVertex).y));
				}
			}
		}
	}

	if (minD == MAX_FLOAT)
		return false;
	else {
		intersectionPoint = closestIntersectionPoint;
		intersectionNormal = closestIntersectionNormal;
	}

	return true;
}

bool PhysicalPolygon::intersectRay(Ray ray) const {
	sf::Vector2f dummy1;
	sf::Vector2f dummy2;

	return intersectRay(ray, dummy1, dummy2);
}

bool PhysicalPolygon::intersectRay(Ray ray, sf::Vector2f& intersectionPoint) const {
	sf::Vector2f dummy;

	return intersectRay(ray, intersectionPoint, dummy);
}

bool PhysicalPolygon::intersectRay(Ray ray, sf::Vector2f& intersectionPoint, sf::Vector2f& intersectionNormal) const {
	float minD{MAX_FLOAT};
	sf::Vector2f closestIntersectionPoint;
	sf::Vector2f closestIntersectionNormal;

	for (auto pVertex = vertices_.begin() + 1; pVertex != vertices_.end(); pVertex++) {
		float t, u;
		if (lineIntersect(Line(ray.origin, ray.direction), LineSegment(*pVertex, *(pVertex-1)), t, u)) {
			if (t >= 0.0f && u >= 0.0f && u <= 1.0f) {
				float d = length(t*ray.direction);
				if (d < minD) {
					minD = d;
					closestIntersectionPoint = ray.origin + t*ray.direction;
					closestIntersectionNormal = normalize(sf::Vector2f(-(*(pVertex-1)-*pVertex).x, (*(pVertex-1)-*pVertex).y));
				}
			}
		}
	}

	if (minD == MAX_FLOAT)
		return false;
	else {
		intersectionPoint = closestIntersectionPoint;
		intersectionNormal = closestIntersectionNormal;
	}

	return true;
}

bool PhysicalPolygon::intersectCircle(float radius, LineSegment displacement) const {
	sf::Vector2f dummy1;
	sf::Vector2f dummy2;
	sf::Vector2f dummy3;

	return intersectCircle(radius, displacement, dummy1, dummy2, dummy3);
}

bool PhysicalPolygon::intersectCircle(float radius, LineSegment displacement, sf::Vector2f& centerAfterCollision) const {
	sf::Vector2f dummy1;
	sf::Vector2f dummy2;

	return intersectCircle(radius, displacement, centerAfterCollision, dummy1, dummy2);
}

bool PhysicalPolygon::intersectCircle(float radius, LineSegment displacement, sf::Vector2f& centerAfterCollision, sf::Vector2f& intersectionPoint) const {
	sf::Vector2f dummy1;

	return intersectCircle(radius, displacement, centerAfterCollision, intersectionPoint, dummy1);
}

bool PhysicalPolygon::intersectCircle(float radius, LineSegment displacement, sf::Vector2f& centerAfterCollision, sf::Vector2f& intersectionPoint, sf::Vector2f& intersectionNormal) const {
	float minD{MAX_FLOAT};
	sf::Vector2f closestCenterAfterCollision;
	sf::Vector2f closestIntersectionPoint;
	sf::Vector2f closestIntersectionNormal;

	for (auto pVertex = vertices_.begin() + 1; pVertex != vertices_.end(); pVertex++) {
		sf::Vector2f normal(-(*(pVertex-1)-*pVertex).x, (*(pVertex-1)-*pVertex).y);
		normal = normalize( (dot(displacement.start - *pVertex, normal) > 0) ? normal : -normal );
		Line shiftedLine(displacement.start - normal * radius, displacement.end - displacement.start);

		bool segmentIntersected = false;
		float t, u;
		if (lineIntersect(shiftedLine, LineSegment(*(pVertex - 1), *pVertex), t, u)) {
			if (t >= 0.0f && t <= 1.0f && u >= 0.0f && u <= 1.0f) {
				segmentIntersected = true;
				float d = length(t*shiftedLine.direction);
				if (d < minD) {
					minD = d;
					closestCenterAfterCollision = displacement.start + (t-0.1f)*shiftedLine.direction;
					closestIntersectionPoint = shiftedLine.origin + t*shiftedLine.direction;
					closestIntersectionNormal = normal;
				}
			}
		}
		if (!segmentIntersected) {
			sf::Vector2f v = displacement.end - displacement.start;

			sf::Vector2f p = *(pVertex-1);
			sf::Vector2f w = p - displacement.start;
			float a = dot(w, v)/dot(v, v);
			float b = radius * radius - dot(w - a*v, w - a*v);
			if (b >= 0) {
				float d = a - sqrtf(b/dot(v, v));
				if (d > 0.0f && d < 1.0f && d < minD) {
					minD = d;
					closestCenterAfterCollision = displacement.start + (d-0.1f)*v;
					closestIntersectionPoint = p;
					closestIntersectionNormal = closestCenterAfterCollision - p;
				}
			}

			p = *pVertex;
			w = p - displacement.start;
			a = dot(w, v)/dot(v, v);
			b = radius * radius - dot(w - a*v, w - a*v);
			if (b >= 0) {
				float d = a - sqrtf(b/dot(v, v));
				if (d > 0.0f && d < 1.0f && d < minD) {
					minD = d;
					closestCenterAfterCollision = displacement.start + (d-0.1f)*v;
					closestIntersectionPoint = p;
					closestIntersectionNormal = closestCenterAfterCollision - p;
				}
			}
		}
	}

	if (minD == MAX_FLOAT)
		return false;
	else {
		centerAfterCollision = closestCenterAfterCollision;
		intersectionPoint = closestIntersectionPoint;
		intersectionNormal = normalize(closestIntersectionNormal);
	}

	return true;
}


/*
 * PHYSICAL_AABOX
 */

PhysicalAABox* PhysicalAABox::clone() const {
	return new PhysicalAABox{*this};
}

bool PhysicalAABox::intersectLine(Line line) const {
	sf::Vector2f dummy1;
	sf::Vector2f dummy2;

	return intersectLine(line, dummy1, dummy2);
}

bool PhysicalAABox::intersectLine(Line line, sf::Vector2f& intersectionPoint) const {
	sf::Vector2f dummy;

	return intersectLine(line, intersectionPoint, dummy);
}

bool PhysicalAABox::intersectLine(Line line, sf::Vector2f& intersectionPoint, sf::Vector2f& intersectionNormal) const {
	// fulhaxx för jeppan vet inte hur u:sarna ska kollas
	return intersectLineSegment(LineSegment(line.origin - 10000.0f*line.direction, line.origin + 10000.0f*line.direction), intersectionPoint, intersectionNormal);

	/*
	float p[4] = { -line.direction.x, line.direction.x, -line.direction.y, line.direction.y };
	float q[4] = { (line.origin.x - origin_.x), (origin_.x + width_ - line.origin.x), (line.origin.y - origin_.y), (origin_.y + height_ - line.origin.y) };
	float u1 = MIN_FLOAT;
	float u2 = MAX_FLOAT;

	for (int i = 0; i < 4; i++) {
		if (p[i] == 0.0f) {
			if (q[i] < 0.0f)
				return false;
		}
		else {
			float t = q[i] / p[i];
			if (p[i] < 0.0f && u1 < t)
				u1 = t;
			else if (p[i] > 0.0f && u2 > t)
				u2 = t;
		}
	}

	std::cout << "u1: " << u1 << " u2: " << u2 << std::endl;

	if (u1 < -10000000.0f && u2 > 10000000.0f)
		return false;

	intersectionPoint = line.origin + u1*line.direction;

	return true;
	*/
}

bool PhysicalAABox::intersectLineSegment(LineSegment lineSegment) const {
	sf::Vector2f dummy1;
	sf::Vector2f dummy2;

	return intersectLineSegment(lineSegment, dummy1, dummy2);
}

bool PhysicalAABox::intersectLineSegment(LineSegment lineSegment, sf::Vector2f& intersectionPoint) const {
	sf::Vector2f dummy;

	return intersectLineSegment(lineSegment, intersectionPoint, dummy);
}

bool PhysicalAABox::intersectLineSegment(LineSegment lineSegment, sf::Vector2f& intersectionPoint, sf::Vector2f& intersectionNormal) const {
	sf::Vector2f direction = lineSegment.end - lineSegment.start;
	float p[4] = { -direction.x, direction.x, -direction.y, direction.y };
	float q[4] = { (lineSegment.start.x - origin_.x), (origin_.x + width_ - lineSegment.start.x), (lineSegment.start.y - origin_.y), (origin_.y + height_ - lineSegment.start.y) };
	float u1{MIN_FLOAT};
	float u2{MAX_FLOAT};

	for (int i = 0; i < 4; i++) {
		if (p[i] == 0.0f) {
			if (q[i] < 0.0f)
				return false;
		}
		else {
			float t = q[i] / p[i];
			if (p[i] < 0.0f && u1 < t)
				u1 = t;
			else if (p[i] > 0.0f && u2 > t)
				u2 = t;
		}
	}

	if (u1 > u2 || u1 > 1.0f || u1 < 0.0f)
		return false;

	intersectionPoint = lineSegment.start + u1*direction;
	if ( equalf(intersectionPoint.x, origin_.x) )
		intersectionNormal = sf::Vector2f(-1, 0);
	else if ( equalf(intersectionPoint.x, origin_.x + width_) )
		intersectionNormal = sf::Vector2f(1, 0);
	else if ( equalf(intersectionPoint.y, origin_.y) )
		intersectionNormal = sf::Vector2f(0, -1);
	else if ( equalf(intersectionPoint.y, origin_.y + height_) )
		intersectionNormal = sf::Vector2f(0, 1);

	return true;
}

bool PhysicalAABox::intersectRay(Ray ray) const {
	sf::Vector2f dummy1;
	sf::Vector2f dummy2;

	return intersectRay(ray, dummy1, dummy2);
}

bool PhysicalAABox::intersectRay(Ray ray, sf::Vector2f& intersectionPoint) const {
	sf::Vector2f dummy;

	return intersectRay(ray, intersectionPoint, dummy);
}

bool PhysicalAABox::intersectRay(Ray ray, sf::Vector2f& intersectionPoint, sf::Vector2f& intersectionNormal) const {
	// fulhaxx för jeppan vet inte hur u:sarna ska kollas
	return intersectLineSegment(LineSegment(ray.origin, ray.origin + 10000.0f*ray.direction), intersectionPoint, intersectionNormal);

	/*
	float p[4] = { -ray.direction.x, ray.direction.x, -ray.direction.y, ray.direction.y };
	float q[4] = { (ray.origin.x - origin_.x), (origin_.x + width_ - ray.origin.x), (ray.origin.y - origin_.y), (origin_.y + height_ - ray.origin.y) };
	float u1 = MIN_FLOAT;
	float u2 = MAX_FLOAT;

	for (int i = 0; i < 4; i++) {
		if (p[i] == 0.0f) {
			if (q[i] < 0.0f)
				return false;
		}
		else {
			float t = q[i] / p[i];
			if (p[i] < 0.0f && u1 < t)
				u1 = t;
			else if (p[i] > 0.0f && u2 > t)
				u2 = t;
		}
	}

	std::cout << "u1: " << u1 << " u2: " << u2 << std::endl;

	if (u1 < 0.0f)
		return false;

	intersectionPoint = ray.origin + u1*ray.direction;

	return true;
	*/
}

bool PhysicalAABox::intersectCircle(float radius, LineSegment displacement) const {
	sf::Vector2f dummy1;
	sf::Vector2f dummy2;
	sf::Vector2f dummy3;

	return intersectCircle(radius, displacement, dummy1, dummy2, dummy3);
}

bool PhysicalAABox::intersectCircle(float radius, LineSegment displacement, sf::Vector2f& centerAfterCollision) const {
	sf::Vector2f dummy1;
	sf::Vector2f dummy2;

	return intersectCircle(radius, displacement, centerAfterCollision, dummy1, dummy2);
}

bool PhysicalAABox::intersectCircle(float radius, LineSegment displacement, sf::Vector2f& centerAfterCollision, sf::Vector2f& intersectionPoint) const {
	sf::Vector2f dummy;

	return intersectCircle(radius, displacement, centerAfterCollision, intersectionPoint, dummy);
}

bool PhysicalAABox::intersectCircle(float radius, LineSegment displacement, sf::Vector2f& centerAfterCollision, sf::Vector2f& intersectionPoint, sf::Vector2f& intersectionNormal) const {
	sf::Vector2f direction = displacement.end - displacement.start;
	sf::Vector2f origin = origin_ - sf::Vector2f(radius, radius);
	float width = width_ + radius + radius;
	float height = height_ + radius + radius;

	float p[4] = { -direction.x, direction.x, -direction.y, direction.y };
	float q[4] = { (displacement.start.x - origin.x), (origin.x + width - displacement.start.x), (displacement.start.y - origin.y), (origin.y + height - displacement.start.y) };
	float u1{MIN_FLOAT};
	float u2{MAX_FLOAT};

	for (int i = 0; i < 4; i++) {
		if (p[i] == 0.0f) {
			if (q[i] < 0.0f)
				return false;
		}
		else {
			float t = q[i] / p[i];
			if (p[i] < 0.0f && u1 < t)
				u1 = t;
			else if (p[i] > 0.0f && u2 > t)
				u2 = t;
		}
	}

	if (u1 > u2 || u1 > 1.0f || u1 < 0.0f)
		return false;

	centerAfterCollision = displacement.start + u1*direction;
	if ( equalf(centerAfterCollision.x, origin.x) )
          intersectionNormal = sf::Vector2f(-1, 0);
	else if ( equalf(centerAfterCollision.x, origin.x + width) )
          intersectionNormal = sf::Vector2f(1, 0);
	else if ( equalf(centerAfterCollision.y, origin.y) )
          intersectionNormal = sf::Vector2f(0, -1);
	else if ( equalf(centerAfterCollision.y, origin.y + height) )
          intersectionNormal = sf::Vector2f(0, 1);
	intersectionPoint = centerAfterCollision - radius*intersectionNormal;

	return true;
}
