
#ifndef _PHYSICAL_OBJECT_
#define _PHYSICAL_OBJECT_

#include "GeomUtils.h"
#include <vector>

class PhysicalObject {
public:
    virtual ~PhysicalObject() = default;

    virtual PhysicalObject* clone() const = 0;
    virtual bool intersectLine(Line line) const = 0;
    virtual bool intersectLine(Line line, sf::Vector2f& intersectionPoint) const = 0;
    virtual bool intersectLine(Line line, sf::Vector2f& intersectionPoint,
                               sf::Vector2f& intersectionNormal) const = 0;
    virtual bool intersectLineSegment(LineSegment lineSegment) const = 0;
    virtual bool intersectLineSegment(LineSegment lineSegment,
                                      sf::Vector2f& intersectionPoint) const = 0;
    virtual bool intersectLineSegment(LineSegment lineSegment, sf::Vector2f& intersectionPoint,
                                      sf::Vector2f& intersectionNormal) const = 0;
    virtual bool intersectRay(Ray ray) const = 0;
    virtual bool intersectRay(Ray ray, sf::Vector2f& intersectionPoint) const = 0;
    virtual bool intersectRay(Ray ray, sf::Vector2f& intersectionPoint,
                              sf::Vector2f& intersectionNormal) const = 0;
    virtual bool intersectCircle(float radius, LineSegment displacement) const = 0;
    virtual bool intersectCircle(float radius, LineSegment displacement,
                                 sf::Vector2f& centerAfterCollision) const = 0;
    virtual bool intersectCircle(float radius, LineSegment displacement,
                                 sf::Vector2f& centerAfterCollision,
                                 sf::Vector2f& intersectionPoint) const = 0;
    virtual bool intersectCircle(float radius, LineSegment displacement,
                                 sf::Vector2f& centerAfterCollision,
                                 sf::Vector2f& intersectionPoint,
                                 sf::Vector2f& intersectionNormal) const = 0;

protected:
    PhysicalObject() = default;

private:
    PhysicalObject& operator=(const PhysicalObject& rhs) = delete;
};

class PhysicalCircle : public PhysicalObject {
public:
    ~PhysicalCircle() noexcept {}
    PhysicalCircle() = delete;
    PhysicalCircle(sf::Vector2f center, float radius) :
        PhysicalObject(), center_(center), radius_(radius) {}

    PhysicalCircle* clone() const override;
    bool intersectLine(Line line) const override;
    bool intersectLine(Line line, sf::Vector2f& intersectionPoint) const override;
    bool intersectLine(Line line, sf::Vector2f& intersectionPoint,
                       sf::Vector2f& intersectionNormal) const override;
    bool intersectLineSegment(LineSegment lineSegment) const override;
    bool intersectLineSegment(LineSegment lineSegment,
                              sf::Vector2f& intersectionPoint) const override;
    bool intersectLineSegment(LineSegment lineSegment,
                              sf::Vector2f& intersectionPoint,
                              sf::Vector2f& intersectionNormal) const override;
    bool intersectRay(Ray ray) const override;
    bool intersectRay(Ray ray, sf::Vector2f& intersectionPoint) const override;
    bool intersectRay(Ray ray, sf::Vector2f& intersectionPoint,
                      sf::Vector2f& intersectionNormal) const override;
    bool intersectCircle(float radius, LineSegment displacement) const override;
    bool intersectCircle(float radius, LineSegment displacement,
                         sf::Vector2f& centerAfterCollision) const override;
    bool intersectCircle(float radius, LineSegment displacement,
                         sf::Vector2f& centerAfterCollision,
                         sf::Vector2f& intersectionPoint) const override;
    bool intersectCircle(float radius, LineSegment displacement,
                         sf::Vector2f& centerAfterCollision,
                         sf::Vector2f& intersectionPoint,
                         sf::Vector2f& intersectionNormal) const override;
    float getRadius() const;
    void setCenter(sf::Vector2f center);

private:
    PhysicalCircle(const PhysicalCircle& other) = default;
    PhysicalCircle& operator=(const PhysicalCircle& rhs) = delete;

    bool lineIntersect(Line line, float& t1, float& t2) const;

    sf::Vector2f center_;
    float radius_;
};

class PhysicalPolygon : public PhysicalObject {
public:
    ~PhysicalPolygon() noexcept {};
    PhysicalPolygon() = delete;
    explicit PhysicalPolygon(std::vector<sf::Vector2f> vertices) :
        PhysicalObject(), vertices_(vertices) {}

    PhysicalPolygon* clone() const;
    bool intersectLine(Line line) const override;
    bool intersectLine(Line line, sf::Vector2f& intersectionPoint) const override;
    bool intersectLine(Line line, sf::Vector2f& intersectionPoint,
                       sf::Vector2f& intersectionNormal) const override;
    bool intersectLineSegment(LineSegment lineSegment) const override;
    bool intersectLineSegment(LineSegment lineSegment, sf::Vector2f& intersectionPoint) const override;
    bool intersectLineSegment(LineSegment lineSegment, sf::Vector2f& intersectionPoint,
                              sf::Vector2f& intersectionNormal) const override;
    bool intersectRay(Ray ray) const override;
    bool intersectRay(Ray ray, sf::Vector2f& intersectionPoint) const override;
    bool intersectRay(Ray ray, sf::Vector2f& intersectionPoint,
                      sf::Vector2f& intersectionNormal) const override;
    bool intersectCircle(float radius, LineSegment displacement) const override;
    bool intersectCircle(float radius, LineSegment displacement,
                         sf::Vector2f& centerAfterCollision) const override;
    bool intersectCircle(float radius, LineSegment displacement,
                         sf::Vector2f& centerAfterCollision,
                         sf::Vector2f& intersectionPoint) const override;
    bool intersectCircle(float radius, LineSegment displacement,
                         sf::Vector2f& centerAfterCollision,
                         sf::Vector2f& intersectionPoint,
                         sf::Vector2f& intersectionNormal) const override;

private:
    PhysicalPolygon(const PhysicalPolygon& other) = default;
    PhysicalPolygon& operator=(const PhysicalPolygon& rhs) = delete;

    bool lineIntersect(Line line, LineSegment lineSegment, float& t, float& u) const;

    std::vector<sf::Vector2f> vertices_;
};

class PhysicalAABox : public PhysicalObject {
public:
    ~PhysicalAABox() noexcept {};
    PhysicalAABox() = delete;
    PhysicalAABox(sf::Vector2f origin, float width, float height) :
        PhysicalObject(), origin_(origin), width_(width), height_(height) {}

    PhysicalAABox* clone() const;
    bool intersectLine(Line line) const override;
    bool intersectLine(Line line, sf::Vector2f& intersectionPoint) const override;
    bool intersectLine(Line line, sf::Vector2f& intersectionPoint,
                       sf::Vector2f& intersectionNormal) const override;
    bool intersectLineSegment(LineSegment lineSegment) const override;
    bool intersectLineSegment(LineSegment lineSegment, sf::Vector2f& intersectionPoint) const override;
    bool intersectLineSegment(LineSegment lineSegment, sf::Vector2f& intersectionPoint,
                              sf::Vector2f& intersectionNormal) const override;
    bool intersectRay(Ray ray) const override;
    bool intersectRay(Ray ray, sf::Vector2f& intersectionPoint) const override;
    bool intersectRay(Ray ray, sf::Vector2f& intersectionPoint,
                      sf::Vector2f& intersectionNormal) const override;
    bool intersectCircle(float radius, LineSegment displacement) const override;
    bool intersectCircle(float radius, LineSegment displacement,
                         sf::Vector2f& centerAfterCollision) const override;
    bool intersectCircle(float radius, LineSegment displacement,
                         sf::Vector2f& centerAfterCollision,
                         sf::Vector2f& intersectionPoint) const override;
    bool intersectCircle(float radius, LineSegment displacement,
                         sf::Vector2f& centerAfterCollision,
                         sf::Vector2f& intersectionPoint,
                         sf::Vector2f& intersectionNormal) const override;

private:
    PhysicalAABox(const PhysicalAABox& other) = default;
    PhysicalAABox& operator=(const PhysicalAABox& rhs) = delete;

    sf::Vector2f origin_;
    float width_;
    float height_;
};

#endif // _PHYSICAL_OBJECT_
