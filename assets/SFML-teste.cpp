#include <SFML/Graphics.hpp>

int main()
{
    // A sintaxe do VideoMode no SFML 2 é sem as chaves {}
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        // O pollEvent no SFML 2 funciona passando a variável "event" dentro dos parênteses
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}