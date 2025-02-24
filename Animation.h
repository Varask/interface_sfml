#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>

/**
 * @brief Classe de base pour les animations.
 */
class Animation {
public:
    virtual ~Animation() {}
    virtual void apply(sf::Shape &shape) = 0;
};

/**
 * @brief Animation d'apparition progressive.
 */
class AnimationFadeIn : public Animation {
private:
    float speed;
    float opacity;
public:
    AnimationFadeIn(float s = 5.0f) : speed(s), opacity(0.0f) {}
    void apply(sf::Shape &shape) override {
        if (opacity < 255) {
            opacity += speed;
            if (opacity > 255) opacity = 255;
            shape.setFillColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(opacity)));
        }
    }
};

/**
 * @brief Animation de disparition progressive.
 */
class AnimationFadeOut : public Animation {
private:
    float speed;
    float opacity;
public:
    AnimationFadeOut(float s = 5.0f) : speed(s), opacity(255.0f) {}
    void apply(sf::Shape &shape) override {
        if (opacity > 0) {
            opacity -= speed;
            if (opacity < 0) opacity = 0;
            shape.setFillColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(opacity)));
        }
    }
};

/**
 * @brief Animation de modification d'attributs.
 */
class AnimationModification : public Animation {
private:
    float scaleFactor;
public:
    AnimationModification(float factor = 1.1f) : scaleFactor(factor) {}
    void apply(sf::Shape &shape) override {
        shape.setScale(scaleFactor, scaleFactor);
    }
};

#endif // ANIMATION_H
