#ifndef GEOMOBJECT_H
#define GEOMOBJECT_H

#include <cmath>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Animation.h"

/**
 * @brief Classe abstraite représentant un objet géométrique avec animations.
 */
class GeomObject {
protected:
    std::vector<sf::Vector2f> points;
    sf::Color color;
    float thickness;
    sf::Vector2f center;
    float angle;
    Animation* animation;

public:
    GeomObject(const sf::Color &c = sf::Color::White, float t = 1.0f, Animation* anim = nullptr)
        : color(c), thickness(t), center(0.f, 0.f), angle(0.f), animation(anim) {}

    virtual ~GeomObject() {}

    void setAnimation(Animation* anim) {
        animation = anim;
    }

    virtual void draw(sf::RenderWindow &window) = 0;

    virtual void move(float dx, float dy) {
        center.x += dx;
        center.y += dy;
        for(auto &pt : points) {
            pt.x += dx;
            pt.y += dy;
        }
    }

    virtual void scale(float factor) {
        for(auto &pt : points) {
            pt.x = center.x + (pt.x - center.x) * factor;
            pt.y = center.y + (pt.y - center.y) * factor;
        }
    }

    virtual void rotate(float deltaAngle) {
        angle += deltaAngle;
        float rad = deltaAngle * 3.14159265f / 180.f;
        float cosA = std::cos(rad);
        float sinA = std::sin(rad);
        for(auto &pt : points) {
            float dx = pt.x - center.x;
            float dy = pt.y - center.y;
            pt.x = center.x + dx * cosA - dy * sinA;
            pt.y = center.y + dx * sinA + dy * cosA;
        }
    }

    virtual sf::Vector2f getCenter() const {
        return center;
    }

    virtual sf::FloatRect getBounds() const = 0;
    virtual bool contains(const sf::Vector2f &point) const = 0;
    virtual bool intersects(const GeomObject &other) const = 0;

    virtual void updateAnimation(sf::Shape &shape) {
        if (animation) {
            animation->apply(shape);
        }
    }
};

#endif // GEOMOBJECT_H
