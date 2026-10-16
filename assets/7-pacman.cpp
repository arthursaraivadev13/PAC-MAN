#include <SFML/Graphics.hpp>
#include <iostream>

char mapa[9][17] = {    // Mapa do jogo
  "1111111111111111",
  "1000010000100001",
  "1011000110001101",
  "1011010110101101",
  "1000010000100001",
  "1011010110101101",
  "1011000000001101",
  "1000011111100001",
  "1111111111111111"
};

int posx = 7; // posicao do PacMan
int posy = 6;

bool direita = true;
int main() {
    // cria a janela
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Minha janela");

    // cria um círculo de raio 50
    sf::CircleShape circ(50.f);
    // define a posição absoluta do círculo
    circ.setPosition({10.f, 50.f});
    // define a cor do círculo (verde)
    circ.setFillColor(sf::Color(100, 250, 50));

    // cria um quadrado de tamanho 50 (a parede)
    sf::RectangleShape quad({50.f, 50.f});
    quad.setFillColor(sf::Color(0, 100, 200));

    // sprites do PacMan
    sf::Texture texture;
    if (!texture.loadFromFile("pacman.png")) {
        std::cout << "Erro lendo imagem pacman.png\n";
        return 0;
    }
    sf::Sprite sprite{texture};

    sf::Texture texture2;
    if (!texture2.loadFromFile("pacman-esq.png")) {
        std::cout << "Erro lendo imagem pacman-esq.png\n";
        return 0;
    }
    sf::Sprite sprite2{texture2};


    // executa o programa enquanto a janela está aberta
    while (window.isOpen()) {

        // verifica todos os eventos que foram acionados na janela desde a última iteração do loop
        while (const std::optional event = window.pollEvent()) {
            // evento "fechar" acionado: fecha a janela
            if (event->is<sf::Event::Closed>())
                window.close();
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                  if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                      window.close();
                  else if (keyPressed->scancode == sf::Keyboard::Scancode::Left){
                    if(mapa[posy][posx-1]!='1')
                      posx--;   // left key: move o PacMan para esquerda
                    direita = false;
                  }
                  else if (keyPressed->scancode == sf::Keyboard::Scancode::Right){
                    if(mapa[posy][posx+1]!='1')
                      posx++;   // right key: move o PacMan para direita
                      direita = true;
                  }
                  else if (keyPressed->scancode == sf::Keyboard::Scancode::Up){
                    if(mapa[posy-1][posx]!='1')
                      posy--;   // up key: move o PacMan para cima
                  }
                  else if (keyPressed->scancode == sf::Keyboard::Scancode::Down){
                    if(mapa[posy+1][posx]!='1')
                      posy++;   // down key: move o PacMan para baixo
                  }
            }
        }

        // limpa a janela com a cor preta
        window.clear(sf::Color::Black);

        // desenhar tudo aqui...

        // desenha paredes
        for(int i=0;i<9;i++)
            for(int j=0;j<17;j++)
                if (mapa[i][j]=='1') {
                    quad.setPosition({j*50.f, i*50.f});
                    window.draw(quad);
                }

        // desenha PacMan

        if(direita){
        sprite.setPosition({posx*50.f,posy*50.f});     //olhando para direita
        window.draw(sprite);
        }
        else{
        sprite2.setPosition({posx*50.f,posy*50.f});   //olhando para esquerda
        window.draw(sprite2);        
        }
        // termina e desenha o frame corrente
        window.display();
    }

    return 0;
}
