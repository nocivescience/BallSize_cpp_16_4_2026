#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

int main() {
    // 1. Configuración de la ventana (SFML 3 usa sf::VideoMode)
    sf::RenderWindow window(sf::VideoMode({800, 400}), "SFML 3: Bolas con Zoom Suave");
    window.setFramerateLimit(60);

    // 2. Definición de propiedades
    const float radioBase = 40.f;
    const float radioMax = 60.f;
    const float velocidadCrecimiento = 0.15f; // Factor de suavizado (lerp)

    struct Bola {
        sf::CircleShape shape;
        float radioObjetivo;
        float radioActual;
    };

    std::vector<Bola> bolas;
    std::vector<sf::Color> colores = {sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Yellow, sf::Color::Magenta};

    // 3. Inicialización de las 5 bolas
    for (int i = 0; i < 5; ++i) {
        Bola b;
        b.radioActual = radioBase;
        b.radioObjetivo = radioBase;
        
        b.shape.setRadius(radioBase);
        b.shape.setFillColor(colores[i]);
        b.shape.setOrigin({radioBase, radioBase}); // Origen al centro para que crezca parejo
        b.shape.setPosition({150.f + i * 120.f, 200.f});
        
        bolas.push_back(b);
    }

    // 4. Bucle principal
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // Obtener posición del mouse
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosF = window.mapPixelToCoords(mousePos);

        // 5. Lógica de actualización
        for (auto& b : bolas) {
            // Detectar si el mouse está dentro del círculo
            sf::Vector2f diff = b.shape.getPosition() - mousePosF;
            float distancia = std::sqrt(diff.x * diff.x + diff.y * diff.y);

            if (distancia < b.radioActual) {
                b.radioObjetivo = radioMax;
            } else {
                b.radioObjetivo = radioBase;
            }

            // Interpolación Lineal Suave (Lerp)
            // radioActual = radioActual + (objetivo - actual) * velocidad
            b.radioActual += (b.radioObjetivo - b.radioActual) * velocidadCrecimiento;

            // Aplicar cambios visuales
            b.shape.setRadius(b.radioActual);
            b.shape.setOrigin({b.radioActual, b.radioActual}); // Reajustar origen
        }

        // 6. Renderizado
        window.clear(sf::Color(30, 30, 30));
        for (const auto& b : bolas) {
            window.draw(b.shape);
        }
        window.display();
    }

    return 0;
}