#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 400}), "SFML 3: Bolas con Zoom Suave");
    const float radioBase = 40.f;
    const float radioMax = 60.f;
    const float velocidadCrecimiento = 0.15f;

    struct Bola {
        sf::CircleShape shape;
        float radioObjetivo;
        float radioActual;
    };

    std::vector<Bola> bolas;
    std::vector<sf::Color> colores = {sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Yellow, sf::Color::Magenta};
    Bola miBolita;
    miBolita.radioActual = radioBase;
    std::cout << "Hola mundo: " <<  (float)colores[0].r << std::endl;

    return 0;
}