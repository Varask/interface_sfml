#ifndef CIRCLEOBJECT_H
#define CIRCLEOBJECT_H

#include "GeomObject.h"

/**
 * @brief Classe représentant un cercle.
 */
class CircleObject : public GeomObject {
private:
    float radius;

public:
    CircleObject(const sf::Vector2f &c, float r, const sf::Color &col = sf::Color::White, float t = 1.0f, Animation* anim = nullptr)
        : radius(r), GeomObject(col, t, anim) {
        center = c;
    }

    virtual void draw(sf::RenderWindow &window) override {
        sf::CircleShape circle(radius);
        circle.setFillColor(sf::Color::Transparent);
        circle.setOutlineColor(color);
        circle.setOutlineThickness(thickness);
        circle.setOrigin(radius, radius);
        circle.setPosition(center);
        circle.setRotation(angle);
        
        // Appliquer l'animation si elle existe
        updateAnimation(circle);

        window.draw(circle);
    }

    virtual void scale(float factor) override {
        radius *= factor;
    }

    virtual void rotate(float deltaAngle) override {
        angle += deltaAngle;
    }

    virtual sf::FloatRect getBounds() const override {
        return sf::FloatRect(center.x - radius, center.y - radius, 2 * radius, 2 * radius);
    }

    virtual bool contains(const sf::Vector2f &point) const override {
        float dx = point.x - center.x;
        float dy = point.y - center.y;
        return (dx * dx + dy * dy) <= (radius * radius);
    }

    virtual bool intersects(const GeomObject &other) const override {
        return getBounds().intersects(other.getBounds());
    }
};

#endif // CIRCLEOBJECT_H
