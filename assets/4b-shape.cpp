sf::Event event;
while (window.pollEvent(event)) {
    
    // Verifica se o evento é de fechar a janela
    if (event.is<sf::Event::Closed>()) {
        window.close();
    }
    
    // Verifica se uma tecla foi pressionada
    if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
        if (keyPressed->code == sf::Keyboard::Key::Escape) {
            window.close();
        }
        else if (keyPressed->code == sf::Keyboard::Key::Left) {
            posx -= 10; // Esquerda
        }
        else if (keyPressed->code == sf::Keyboard::Key::Right) {
            posx += 10; // Direita
        }
    }
}