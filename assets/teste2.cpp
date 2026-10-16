#include <SFML/Graphics.hpp>
#include <optional>
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

// mapaatual CORRIGIDO: 31 linhas por 28 colunas reais.
const int mapaoriginal[33][28] = { 
    {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
    {2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2},
    {2, 1, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1, 2, 2, 1, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 1, 2},
    {2, 3, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1, 2, 2, 1, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 3, 2},
    {2, 1, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1, 2, 2, 1, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 1, 2},
    {2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2},
    {2, 1, 2, 2, 2, 2, 1, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 1, 2, 2, 2, 2, 1, 2},
    {2, 1, 2, 2, 2, 2, 1, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 1, 2, 2, 2, 2, 1, 2},
    {2, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 2},
    {2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 0, 2, 2, 0, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2},
    {0, 0, 0, 0, 0, 2, 1, 2, 2, 2, 2, 2, 0, 2, 2, 0, 2, 2, 2, 2, 2, 1, 2, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 2, 1, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 1, 2, 0, 0, 0, 0, 0},
    {2, 2, 2, 2, 2, 2, 1, 2, 2, 0, 2, 2, 2, 4, 4, 2, 2, 2, 0, 2, 2, 1, 2, 2, 2, 2, 2, 2},
    {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
    {2, 2, 2, 2, 2, 2, 1, 2, 2, 0, 2, 0, 0, 0, 0, 0, 0, 2, 0, 2, 2, 1, 2, 2, 2, 2, 2, 2},
    {0, 0, 0, 0, 0, 2, 1, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 2, 0, 2, 2, 1, 2, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 2, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 2, 0, 0, 0, 0, 0},
    {2, 2, 2, 2, 2, 2, 1, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 1, 2, 2, 2, 2, 2, 2},
    {2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2},
    {2, 1, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1, 2, 2, 1, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 1, 2},
    {2, 1, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1, 2, 2, 1, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 1, 2},
    {2, 3, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 3, 2},
    {2, 2, 2, 1, 2, 2, 1, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 1, 2, 2, 1, 2, 2, 2},
    {2, 2, 2, 1, 2, 2, 1, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 1, 2, 2, 1, 2, 2, 2},
    {2, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 2},
    {2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2},
    {2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2},
    {2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2},
    {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};

int mapaatual[33][28]; 
int score = 0;

enum ESTADO { MENU, JOGANDO, GAMEOVER, VITORIA };
enum DIRECAO { NENHUMA, CIMA, BAIXO, ESQUERDA, DIREITA };

struct Pacman {                  
    int posx = 14;
    int posy = 21;
    DIRECAO direcaoatual = NENHUMA;
    DIRECAO proximadirecao = NENHUMA;
};
Pacman pacman;

enum ESTADOFANTASMA { PRESO, SAINDO, LIVRE };

struct Fantasma { 
    int posx;
    int posy;
    DIRECAO direcaoatual = NENHUMA; 
    DIRECAO proximadirecao = NENHUMA;
    ESTADOFANTASMA estadoatual = PRESO; 
    sf::Clock relogio;
};

Fantasma aleatorio = {15, 14, NENHUMA, NENHUMA, PRESO};
Fantasma cacador = {13, 14, NENHUMA, NENHUMA, PRESO};

struct caminhos { 
    DIRECAO direcao;
    float distancia;
};

bool comparadistancias(caminhos a, caminhos b) { 
    return a.distancia < b.distancia;
}

void ResetarJogo() {
    pacman.posx = 14;
    pacman.posy = 21;
    pacman.direcaoatual = NENHUMA;
    pacman.proximadirecao = NENHUMA;
    aleatorio = {15, 14, NENHUMA, NENHUMA, PRESO};
    cacador = {13, 14, NENHUMA, NENHUMA, PRESO};
    score = 0;
    for (int i = 0; i < 33; i++)
        for (int j = 0; j < 28; j++)
            mapaatual[i][j] = mapaoriginal[i][j];
}

int main() {
    for (int i = 0; i < 33; i++) {
        for (int j = 0; j < 28; j++)
            mapaatual[i][j] = mapaoriginal[i][j];
    }

    ESTADO estadoatual = MENU;        
    const float TAMANHO_BLOCO = 32.f;
    const float OFFSET_Y = 64.f;

    const unsigned int larguraJanela = static_cast<unsigned int>(28 * TAMANHO_BLOCO);
    const unsigned int alturaJanela = static_cast<unsigned int>(33 * TAMANHO_BLOCO + OFFSET_Y);

    sf::RenderWindow window(sf::VideoMode({larguraJanela, alturaJanela}), "Pac-Man UFV");
    sf::RectangleShape quad({32.f, 32.f});
    quad.setFillColor(sf::Color(0, 100, 200));
    quad.setOutlineThickness(-1.5f);
    quad.setOutlineColor(sf::Color(0, 40, 120));

    sf::CircleShape pill({8.f});
    pill.setFillColor(sf::Color(200, 100, 0));

    sf::Texture texture;
    if (!texture.loadFromFile("pacman.png")) {
        std::cout << "Erro lendo imagem pacman.png\n";
        return 0;
    }
    sf::Sprite spritedir{texture};

    sf::Texture texture2;
    if (!texture2.loadFromFile("pacman-esq.png")) {
        std::cout << "Erro lendo imagem pacman-esq.png\n";
        return 0;
    }
    sf::Sprite spriteesq(texture2);

    sf::Texture texture3;
    if (!texture3.loadFromFile("pacmanbaixo.png")) {
        std::cout << "Erro lendo imagem pacmanbaixo.png\n";
        return 0;
    }
    sf::Sprite spritebaixo(texture3);

    sf::Texture texture4;
    if (!texture4.loadFromFile("pacmancima.png")) {
        std::cout << "Erro lendo imagem pacmancima.png\n";
        return 0;
    }
    sf::Sprite spritecima(texture4);

    sf::Texture Fantasma1;
    if (!Fantasma1.loadFromFile("fantasmalaranja.png")) {
        std::cout << "Erro lendo imagem fantasmalaranja.png\n";
        return 0;
    }
    sf::Sprite spritefantasma1(Fantasma1);

    sf::Texture Fantasma2;
    if (!Fantasma2.loadFromFile("fantasmavermelho.png")) {
        std::cout << "Erro lendo imagem fantasmavermelho.png\n";
        return 0;
    }
    sf::Sprite spritefantasma2(Fantasma2);

    spritedir.setScale({32.f / texture.getSize().x, 32.f / texture.getSize().y});
    spriteesq.setScale({32.f / texture2.getSize().x, 32.f / texture2.getSize().y});
    spritebaixo.setScale({32.f / texture3.getSize().x, 32.f / texture3.getSize().y});
    spritecima.setScale({32.f / texture4.getSize().x, 32.f / texture4.getSize().y});
    spritefantasma1.setScale({32.f / Fantasma1.getSize().x, 32.f / Fantasma1.getSize().y});
    spritefantasma2.setScale({32.f / Fantasma2.getSize().x, 32.f / Fantasma2.getSize().y});

    sf::Clock clock;
    sf::Font font;
    if (!font.openFromFile("arial.ttf")) {
        std::cout << "Erro lendo fonte arial\n";
        return 0;
    }

    sf::Text textscore(font);
    textscore.setCharacterSize(18);
    textscore.setFillColor(sf::Color::White);
    textscore.setPosition({20.f, 24.f + OFFSET_Y});

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
            else if (estadoatual == MENU) {
                if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                    if (keyPressed->scancode == sf::Keyboard::Scancode::Enter) {
                        ResetarJogo();
                        estadoatual = JOGANDO;
                    }
                }
            }
            else if (estadoatual == GAMEOVER || estadoatual == VITORIA) {
                if (const auto *kp = event->getIf<sf::Event::KeyPressed>()) {
                    if (kp->scancode == sf::Keyboard::Scancode::R) {
                        ResetarJogo();
                        estadoatual = JOGANDO;
                    }
                    else if (kp->scancode == sf::Keyboard::Scancode::M)
                        estadoatual = MENU;
                }
            }
            else if (estadoatual == JOGANDO) {
                if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                    if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                        window.close();
                    else if (keyPressed->scancode == sf::Keyboard::Scancode::Left)
                        pacman.proximadirecao = ESQUERDA;
                    else if (keyPressed->scancode == sf::Keyboard::Scancode::Right)
                        pacman.proximadirecao = DIREITA;
                    else if (keyPressed->scancode == sf::Keyboard::Scancode::Up)
                        pacman.proximadirecao = CIMA;
                    else if (keyPressed->scancode == sf::Keyboard::Scancode::Down)
                        pacman.proximadirecao = BAIXO;
                    else if (keyPressed->scancode == sf::Keyboard::Scancode::R) {
                        pacman.posx = 1;
                        pacman.posy = 1;
                        pacman.proximadirecao = NENHUMA;
                        pacman.direcaoatual = DIREITA;
                    }
                }
            }
        } // Fim do loop de eventos (pollEvent)

        if (estadoatual == JOGANDO) {
            if (clock.getElapsedTime() > sf::seconds(0.2)) {
                clock.restart();

                // 1°- Verifica intenção do jogador
                if (pacman.proximadirecao == CIMA && mapaatual[pacman.posy - 1][pacman.posx] != 2)
                    pacman.direcaoatual = CIMA;
                if (pacman.proximadirecao == BAIXO && mapaatual[pacman.posy + 1][pacman.posx] != 2)
                    pacman.direcaoatual = BAIXO;
                if (pacman.proximadirecao == ESQUERDA && mapaatual[pacman.posy][pacman.posx - 1] != 2)
                    pacman.direcaoatual = ESQUERDA;
                if (pacman.proximadirecao == DIREITA && mapaatual[pacman.posy][pacman.posx + 1] != 2)
                    pacman.direcaoatual = DIREITA;

                // 2°- Realiza movimentação do Pacman e checa colisão
                if (pacman.direcaoatual == CIMA) {
                    if (mapaatual[pacman.posy - 1][pacman.posx] != 2) {
                        pacman.posy--;
                        if ((pacman.posy == aleatorio.posy && pacman.posx == aleatorio.posx) || (pacman.posx == cacador.posx && pacman.posy == cacador.posy)) {
                            estadoatual = GAMEOVER;
                        }
                        if (mapaatual[pacman.posy][pacman.posx] == 1) {
                            score += 10;
                            mapaatual[pacman.posy][pacman.posx] = 0;
                        }
                    }
                }
                if (pacman.direcaoatual == BAIXO) {
                    if (mapaatual[pacman.posy + 1][pacman.posx] != 2) {
                        pacman.posy++;
                        if ((pacman.posy == aleatorio.posy && pacman.posx == aleatorio.posx) || (pacman.posx == cacador.posx && pacman.posy == cacador.posy)) {
                            estadoatual = GAMEOVER;
                        }
                        if (mapaatual[pacman.posy][pacman.posx] == 1) {
                            score += 10;
                            mapaatual[pacman.posy][pacman.posx] = 0;
                        }
                    }
                }
                if (pacman.direcaoatual == ESQUERDA) {
                    if (pacman.posx == 0)
                        pacman.posx = 27;
                    else if (mapaatual[pacman.posy][pacman.posx - 1] != 2) {
                        pacman.posx--;
                        if ((pacman.posy == aleatorio.posy && pacman.posx == aleatorio.posx) || (pacman.posx == cacador.posx && pacman.posy == cacador.posy)) {
                            estadoatual = GAMEOVER;
                        }
                        if (mapaatual[pacman.posy][pacman.posx] == 1) {
                            score += 10;
                            mapaatual[pacman.posy][pacman.posx] = 0;
                        }
                    }
                }
                if (pacman.direcaoatual == DIREITA) {
                    if (pacman.posx == 27)
                        pacman.posx = 0;
                    else if (mapaatual[pacman.posy][pacman.posx + 1] != 2) {
                        pacman.posx++;
                        if ((pacman.posy == aleatorio.posy && pacman.posx == aleatorio.posx) || (pacman.posx == cacador.posx && pacman.posy == cacador.posy)) {
                            estadoatual = GAMEOVER;
                        }
                        if (mapaatual[pacman.posy][pacman.posx] == 1) {
                            score += 10;
                            mapaatual[pacman.posy][pacman.posx] = 0;
                        }
                    }
                }

                // Lógica simplificada/protegida do fantasma aleatório
                if (aleatorio.estadoatual == PRESO) {
                    if (aleatorio.relogio.getElapsedTime().asSeconds() >= 5.0f) {
                        aleatorio.estadoatual = SAINDO;
                    } else {
                        aleatorio.posy = (aleatorio.posy == 14) ? 13 : 14;
                    }
                } 
                else if (aleatorio.estadoatual == SAINDO) {
                    if (aleatorio.posx < 14) aleatorio.posx++;
                    else if (aleatorio.posx > 14) aleatorio.posx--;
                    else {
                        if (aleatorio.posy != 11) aleatorio.posy--;
                        else {
                            aleatorio.estadoatual = LIVRE;
                            aleatorio.direcaoatual = NENHUMA;
                        }
                    }
                } 
                else if (aleatorio.estadoatual == LIVRE) {
                    // Movimento fantasma livre (Apenas avança se a direção for válida)
                    if (aleatorio.direcaoatual == CIMA && mapaatual[aleatorio.posy - 1][aleatorio.posx] != 2) aleatorio.posy--;
                    else if (aleatorio.direcaoatual == BAIXO && mapaatual[aleatorio.posy + 1][aleatorio.posx] != 2) aleatorio.posy++;
                    else if (aleatorio.direcaoatual == ESQUERDA && mapaatual[aleatorio.posy][aleatorio.posx - 1] != 2) aleatorio.posx--;
                    else if (aleatorio.direcaoatual == DIREITA && mapaatual[aleatorio.posy][aleatorio.posx + 1] != 2) aleatorio.posx++;
                    else aleatorio.direcaoatual = CIMA; // Direção padrão de escape caso trave
                }

                // Checa colisão novamente após mover os fantasmas
                if ((pacman.posy == aleatorio.posy && pacman.posx == aleatorio.posx) || (pacman.posx == cacador.posx && pacman.posy == cacador.posy)) {
                    estadoatual = GAMEOVER;
                }
            }
        }

        // --- Seção de Desenho (Render) ---
        window.clear();

        // Desenha o Labirinto e Itens
        for (int i = 0; i < 33; i++) {
            for (int j = 0; j < 28; j++) {
                if (mapaatual[i][j] == 2) {
                    quad.setPosition({j * TAMANHO_BLOCO, i * TAMANHO_BLOCO + OFFSET_Y});
                    window.draw(quad);
                } else if (mapaatual[i][j] == 1) {
                    pill.setPosition({j * TAMANHO_BLOCO + 12.f, i * TAMANHO_BLOCO + 12.f + OFFSET_Y});
                    window.draw(pill);
                }
            }
        }

        // Desenha o Pacman baseado na direção atual
        if (pacman.direcaoatual == DIREITA || pacman.direcaoatual == NENHUMA) {
            spritedir.setPosition({pacman.posx * TAMANHO_BLOCO, pacman.posy * TAMANHO_BLOCO + OFFSET_Y});
            window.draw(spritedir);
        } else if (pacman.direcaoatual == ESQUERDA) {
            spriteesq.setPosition({pacman.posx * TAMANHO_BLOCO, pacman.posy * TAMANHO_BLOCO + OFFSET_Y});
            window.draw(spriteesq);
        } else if (pacman.direcaoatual == CIMA) {
            spritecima.setPosition({pacman.posx * TAMANHO_BLOCO, pacman.posy * TAMANHO_BLOCO + OFFSET_Y});
            window.draw(spritecima);
        } else if (pacman.direcaoatual == BAIXO) {
            spritebaixo.setPosition({pacman.posx * TAMANHO_BLOCO, pacman.posy * TAMANHO_BLOCO + OFFSET_Y});
            window.draw(spritebaixo);
        }

        // Desenha Fantasmas
        spritefantasma1.setPosition({aleatorio.posx * TAMANHO_BLOCO, aleatorio.posy * TAMANHO_BLOCO + OFFSET_Y});
        window.draw(spritefantasma1);
        spritefantasma2.setPosition({cacador.posx * TAMANHO_BLOCO, cacador.posy * TAMANHO_BLOCO + OFFSET_Y});
        window.draw(spritefantasma2);

        // Texto de Score
        char s[20];
        snprintf(s, sizeof(s), "Score: %d", score);
        textscore.setString(s);
        window.draw(textscore);

        window.display();
    } // Fim do loop principal (window.isOpen)

    return 0;
}