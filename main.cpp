#include <SFML/Graphics.hpp>
#include <iostream>
#include "CircleObject.h"
#include "Animation.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Déplacement et Redimensionnement");

    // Animations
    AnimationFadeIn fadeInAnimation(2.0f);
    AnimationFadeOut fadeOutAnimation(2.0f);
    AnimationModification zoomAnimation(1.01f);

    // Création du cercle avec animation de fade-in
    CircleObject circle(sf::Vector2f(400.f, 300.f), 50.f, sf::Color::Green, 2.f, &fadeInAnimation);

    bool fadeInComplete = false;
    bool fadeOutComplete = false;
    bool zoomActive = false;

    // Variables de déplacement et de redimensionnement
    float speed = 2.0f;
    float dx = speed; // Direction horizontale
    float scaleFactor = 1.005f; // Facteur de croissance
    bool growing = true; // Indique si le cercle grandit ou rétrécit

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        // Déplacement du cercle
        circle.move(dx, 0);

        // Vérification des bords pour rebondir
        sf::FloatRect bounds = circle.getBounds();
        if (bounds.left <= 0 || bounds.left + bounds.width >= window.getSize().x) {
            dx = -dx; // Inversion de la direction
        }

        // Modification progressive de la taille du cercle
        if (growing) {
            circle.scale(scaleFactor);
            if (circle.getBounds().width > 120) { // Taille max
                growing = false;
            }
        } else {
            circle.scale(1.0f / scaleFactor);
            if (circle.getBounds().width < 50) { // Taille min
                growing = true;
            }
        }

        // Gestion des animations
        if (!fadeInComplete) {
            circle.draw(window);
            if (circle.getBounds().width > 100) {
                fadeInComplete = true;
                circle.setAnimation(&fadeOutAnimation);
            }
        } 
        else if (!fadeOutComplete) {
            circle.draw(window);
            if (circle.getBounds().width < 20) {
                fadeOutComplete = true;
                zoomActive = true;
                circle.setAnimation(&zoomAnimation);
            }
        } 
        else if (zoomActive) {
            circle.draw(window);
        }

        window.display();
    }

    return 0;
}
