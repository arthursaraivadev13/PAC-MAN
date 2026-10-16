#include <SFML/Graphics.hpp>
#include <optional>
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <cmath>
#include <SFML/Audio.hpp>  //bbt do áudio
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
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

int mapaatual[33][28];

// --- NOVIDADE: MATRIZ DE SOMBRA ---
float shadowMatrix[33][28];
const float SHADOW_START = 245.0f; // Quase totalmente preto (0 a 255)

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

    for (int i = 0; i < 33; i++) {
        for (int j = 0; j < 28; j++) {
            mapaatual[i][j] = mapaoriginal[i][j];
            shadowMatrix[i][j] = SHADOW_START; // Reseta a sombra
        }
    }
    
    // Ilumina a posição inicial do jogador
    shadowMatrix[pacman.posy][pacman.posx] = 0.0f;
}

int main()
{
    // inicializa a sombra e mapa
    for (int i = 0; i < 33; i++) {
        for (int j = 0; j < 28; j++) {
            mapaatual[i][j] = mapaoriginal[i][j];
            shadowMatrix[i][j] = SHADOW_START;
        }
    }
    shadowMatrix[pacman.posy][pacman.posx] = 0.0f; // Acende o spawn point

    ESTADO estadoatual = MENU;        
    const float TAMANHO_BLOCO = 32.f; 
    const float OFFSET_Y = 64.f;      

    const unsigned int larguraJanela = static_cast<unsigned int>(28 * TAMANHO_BLOCO);           
    const unsigned int alturaJanela = static_cast<unsigned int>(33 * TAMANHO_BLOCO + OFFSET_Y); 

    sf::RenderWindow window(sf::VideoMode({larguraJanela, alturaJanela}), "Pac-Lumen (Light Runner)");

    sf::Music musicaFundo;
    if (!musicaFundo.openFromFile("moonlight.mp3")) {
        std::cout << "Erro ao carregar a moonlight.mp3\n";
    } else {
        musicaFundo.setLooping(true);   
        musicaFundo.setVolume(100.f); 
        musicaFundo.play();          
    }

    // Blocos do cenário
    sf::RectangleShape quad({32.f, 32.f});
    quad.setFillColor(sf::Color(0, 100, 200));
    quad.setOutlineThickness(-1.5f); 
    quad.setOutlineColor(sf::Color(0, 40, 120));

    // --- NOVIDADE: BLOCO ACESO E BLOCO DE SOMBRA ---
    sf::RectangleShape litFloorQuad({24.f, 24.f}); // Levemente menor para parecer uma luz no meio
    litFloorQuad.setFillColor(sf::Color(255, 255, 100)); // Uma cor amarela brilhante (neon)

    sf::RectangleShape shadowQuad({32.f, 32.f}); // Quadrado preto que fará a sombra

    // Texturas... (mantidas)
    sf::Texture texture;
    if (!texture.loadFromFile("pacman.png")) return 0;
    sf::Sprite spritedir{texture};

    sf::Texture texture2;
    if (!texture2.loadFromFile("pacman-esq.png")) return 0;
    sf::Sprite spriteesq(texture2);

    sf::Texture texture3;
    if (!texture3.loadFromFile("pacmanbaixo.png")) return 0;
    sf::Sprite spritebaixo(texture3);

    sf::Texture texture4;
    if (!texture4.loadFromFile("pacmancima.png")) return 0;
    sf::Sprite spritecima(texture4);

    sf::Texture Fantasma1;
    if (!Fantasma1.loadFromFile("fantasmalaranja.png")) return 0;
    sf::Sprite spritefantasma1(Fantasma1);

    sf::Texture Fantasma2;
    if (!Fantasma2.loadFromFile("fantasmavermelho.png")) return 0;
    sf::Sprite spritefantasma2(Fantasma2);

    spritedir.setScale({32.f / texture.getSize().x, 32.f / texture.getSize().y});
    spriteesq.setScale({32.f / texture2.getSize().x, 32.f / texture2.getSize().y});
    spritebaixo.setScale({32.f / texture3.getSize().x, 32.f / texture3.getSize().y});
    spritecima.setScale({32.f / texture4.getSize().x, 32.f / texture4.getSize().y});
    spritefantasma1.setScale({32.f / Fantasma1.getSize().x, 32.f / Fantasma1.getSize().y});
    spritefantasma2.setScale({32.f / Fantasma2.getSize().x, 32.f / Fantasma2.getSize().y});

    sf::Clock clock;

    sf::Font font;
    if (!font.openFromFile("arial.ttf")) return 0;

    sf::Text textscore(font);
    textscore.setCharacterSize(18);
    textscore.setFillColor(sf::Color::White);
    textscore.setPosition({20.f, 24.f + OFFSET_Y});

    sf::Text sadface(font);
    sadface.setCharacterSize(300);
    sadface.setFillColor(sf::Color::White);
    sadface.setPosition({450.f, 500.f + OFFSET_Y});

    sf::Text titulomenu(font);
    titulomenu.setCharacterSize(100);
    titulomenu.setFillColor(sf::Color::White);
    titulomenu.setPosition({350.f, 400.f });

    sf::Text titulofim(font);
    titulofim.setCharacterSize(100);
    titulofim.setFillColor(sf::Color::White);
    titulofim.setPosition({450.f, 500.f + OFFSET_Y});

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            else if (estadoatual == MENU)
            {
                if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
                {
                    if (keyPressed->scancode == sf::Keyboard::Scancode::Enter)
                    {
                        ResetarJogo();
                        estadoatual = JOGANDO;
                    }
                }
            }
            else if (estadoatual == GAMEOVER || estadoatual == VITORIA)
            {
                if (const auto *kp = event->getIf<sf::Event::KeyPressed>())
                {
                    if (kp->scancode == sf::Keyboard::Scancode::R)
                    {
                        ResetarJogo();
                        estadoatual = JOGANDO;
                    }
                    else if (kp->scancode == sf::Keyboard::Scancode::M)
                        estadoatual = MENU;
                }
            }
            else if (estadoatual == JOGANDO)
            {
                if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
                {
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
                }
            }
        }
        
        if(estadoatual == JOGANDO){
            if (clock.getElapsedTime() > sf::seconds(0.2))
            {
                clock.restart();

                // Lógica de Direção
                if (pacman.proximadirecao == CIMA && mapaatual[pacman.posy - 1][pacman.posx] != 2)
                    pacman.direcaoatual = CIMA;
                if (pacman.proximadirecao == BAIXO && mapaatual[pacman.posy + 1][pacman.posx] != 2)
                    pacman.direcaoatual = BAIXO;
                if (pacman.proximadirecao == ESQUERDA && mapaatual[pacman.posy][pacman.posx - 1] != 2)
                    pacman.direcaoatual = ESQUERDA;
                if (pacman.proximadirecao == DIREITA && mapaatual[pacman.posy][pacman.posx + 1] != 2)
                    pacman.direcaoatual = DIREITA;

                // Lógica de Movimento e Colisão Pac-Man x Fantasmas (otimizada)
                if (pacman.direcaoatual == CIMA && mapaatual[pacman.posy - 1][pacman.posx] != 2) pacman.posy--;
                else if (pacman.direcaoatual == BAIXO && mapaatual[pacman.posy + 1][pacman.posx] != 2) pacman.posy++;
                else if (pacman.direcaoatual == ESQUERDA) {
                    if (pacman.posx == 0) pacman.posx = 27;
                    else if (mapaatual[pacman.posy][pacman.posx - 1] != 2) pacman.posx--;
                }
                else if (pacman.direcaoatual == DIREITA) {
                    if (pacman.posx == 27) pacman.posx = 0;
                    else if (mapaatual[pacman.posy][pacman.posx + 1] != 2) pacman.posx++;
                }

                // Check de Morte Imediato
                if ((pacman.posy == aleatorio.posy && pacman.posx == aleatorio.posx) || 
                    (pacman.posx == cacador.posx && pacman.posy == cacador.posy)) 
                    estadoatual = GAMEOVER;

                // --- NOVIDADE: LÓGICA DE ILUMINAÇÃO ---
                if (mapaatual[pacman.posy][pacman.posx] == 1) { 
                    score += 10;
                    mapaatual[pacman.posy][pacman.posx] = 0; // Transforma em caminho visitado

                    // Clareia O MAPA INTEIRO DE FORMA SUTIL (Efeito Gradiente)
                    for (int i = 0; i < 33; i++) {
                        for (int j = 0; j < 28; j++) {
                            if (shadowMatrix[i][j] > 0.0f) {
                                shadowMatrix[i][j] -= 1.0f; // Reduz a escuridão do mundo
                                if (shadowMatrix[i][j] < 0.0f) shadowMatrix[i][j] = 0.0f;
                            }
                        }
                    }
                }
                // O BLOCO ONDE O PERSONAGEM ESTÁ FICA 100% ACESO
                shadowMatrix[pacman.posy][pacman.posx] = 0.0f;

                // ========================================================= //
                // MOVIMENTACAO FANTASMAS (Código original intacto)
                // (Aleatório)
                if (aleatorio.estadoatual == PRESO) {
                    if (aleatorio.relogio.getElapsedTime().asSeconds() >= 5.0f) aleatorio.estadoatual = SAINDO;
                    else aleatorio.posy = (aleatorio.posy == 14) ? 13 : 14;
                }
                else if (aleatorio.estadoatual == SAINDO) {
                    if (aleatorio.posx < 14) aleatorio.posx++;
                    else if (aleatorio.posx > 14) aleatorio.posx--;
                    else {
                        if (aleatorio.posy != 11) aleatorio.posy--;
                        else { aleatorio.estadoatual = LIVRE; aleatorio.direcaoatual = NENHUMA; }
                    }
                }
                else if (aleatorio.estadoatual == LIVRE) {
                    bool movimentovertical = (aleatorio.direcaoatual == CIMA || aleatorio.direcaoatual == BAIXO);
                    bool movimentohorizontal = (aleatorio.direcaoatual == ESQUERDA || aleatorio.direcaoatual == DIREITA);

                    int caminhoslivres = 0; 
                    if (mapaatual[aleatorio.posy - 1][aleatorio.posx] != 2) caminhoslivres++;
                    if (mapaatual[aleatorio.posy + 1][aleatorio.posx] != 2) caminhoslivres++;
                    if (mapaatual[aleatorio.posy][aleatorio.posx - 1] != 2) caminhoslivres++;
                    if (mapaatual[aleatorio.posy][aleatorio.posx + 1] != 2) caminhoslivres++;

                    bool mudadirecao = false;
                    bool cimadaporta = (aleatorio.posy == 11 && (aleatorio.posx == 13 || aleatorio.posx == 14)); 

                    if ((aleatorio.direcaoatual == NENHUMA) ||                                                                      
                        (aleatorio.direcaoatual == CIMA && mapaatual[aleatorio.posy - 1][aleatorio.posx] == 2) ||                   
                        (aleatorio.direcaoatual == BAIXO && (mapaatual[aleatorio.posy + 1][aleatorio.posx] == 2 || cimadaporta)) || 
                        (aleatorio.direcaoatual == ESQUERDA && aleatorio.posx > 0 && mapaatual[aleatorio.posy][aleatorio.posx - 1] == 2) ||
                        (aleatorio.direcaoatual == DIREITA && aleatorio.posx < 27 && mapaatual[aleatorio.posy][aleatorio.posx + 1] == 2) ||
                        (movimentohorizontal == true && (mapaatual[aleatorio.posy - 1][aleatorio.posx] != 2 || mapaatual[aleatorio.posy + 1][aleatorio.posx] != 2)) || 
                        (movimentovertical == true && (mapaatual[aleatorio.posy][aleatorio.posx - 1] != 2 || mapaatual[aleatorio.posy][aleatorio.posx + 1] != 2)))
                    {
                        mudadirecao = true; 
                    }

                    static random_device rd;
                    static mt19937 gerador(rd());
                    uniform_int_distribution<int> distribuicao(1, 4);

                    while (mudadirecao) {
                        int sorteio = distribuicao(gerador);
                        if (sorteio == 1 && mapaatual[aleatorio.posy - 1][aleatorio.posx] != 2) {
                            if (movimentohorizontal || aleatorio.direcaoatual == CIMA || caminhoslivres <= 1 || aleatorio.direcaoatual == NENHUMA) {
                                aleatorio.direcaoatual = CIMA; mudadirecao = false;
                            }
                        }
                        else if (sorteio == 2 && mapaatual[aleatorio.posy + 1][aleatorio.posx] != 2 && !cimadaporta) {
                            if (movimentohorizontal || aleatorio.direcaoatual == BAIXO || caminhoslivres <= 1 || aleatorio.direcaoatual == NENHUMA) {
                                aleatorio.direcaoatual = BAIXO; mudadirecao = false;
                            }
                        }
                        else if (sorteio == 3) {
                            if (aleatorio.posx == 0) { aleatorio.direcaoatual = ESQUERDA; mudadirecao = false; }
                            else if (mapaatual[aleatorio.posy][aleatorio.posx - 1] != 2) {
                                if (movimentovertical || aleatorio.direcaoatual == ESQUERDA || caminhoslivres <= 1 || aleatorio.direcaoatual == NENHUMA) {
                                    aleatorio.direcaoatual = ESQUERDA; mudadirecao = false;
                                }
                            }
                        }
                        else if (sorteio == 4) {
                            if (aleatorio.posx == 27) { aleatorio.direcaoatual = DIREITA; mudadirecao = false; }
                            else if (mapaatual[aleatorio.posy][aleatorio.posx + 1] != 2) {
                                if (movimentovertical || aleatorio.direcaoatual == DIREITA || caminhoslivres <= 1 || aleatorio.direcaoatual == NENHUMA) {
                                    aleatorio.direcaoatual = DIREITA; mudadirecao = false;
                                }
                            }
                        }
                    }

                    if (aleatorio.direcaoatual == CIMA && mapaatual[aleatorio.posy - 1][aleatorio.posx] != 2) aleatorio.posy--;
                    else if (aleatorio.direcaoatual == BAIXO && mapaatual[aleatorio.posy + 1][aleatorio.posx] != 2) aleatorio.posy++;
                    else if (aleatorio.direcaoatual == ESQUERDA) {
                        if (aleatorio.posx == 0) aleatorio.posx = 27;
                        else if (mapaatual[aleatorio.posy][aleatorio.posx - 1] != 2) aleatorio.posx--;
                    }
                    else if (aleatorio.direcaoatual == DIREITA) {
                        if (aleatorio.posx == 27) aleatorio.posx = 0;
                        else if (mapaatual[aleatorio.posy][aleatorio.posx + 1] != 2) aleatorio.posx++;
                    }
                }

                if (pacman.posy == aleatorio.posy && pacman.posx == aleatorio.posx) estadoatual = GAMEOVER;

                // (Caçador)
                std::vector<caminhos> caminhosvalidos; 
                if (cacador.estadoatual == PRESO) {
                    if (cacador.relogio.getElapsedTime().asSeconds() >= 10.0f) cacador.estadoatual = SAINDO;
                    else cacador.posy = (cacador.posy == 14) ? 13 : 14;
                }
                else if (cacador.estadoatual == SAINDO) {
                    if (cacador.posx < 13) cacador.posx++;
                    else if (cacador.posx > 13) cacador.posx--;
                    else {
                        if (cacador.posy != 11) cacador.posy--;
                        else { cacador.estadoatual = LIVRE; cacador.direcaoatual = NENHUMA; }
                    }
                }
                else if (cacador.estadoatual == LIVRE) {
                    bool cimadaporta = (cacador.posy == 11 && (cacador.posx == 13 || cacador.posx == 14)); 

                    if (mapaatual[cacador.posy - 1][cacador.posx] != 2 && cacador.direcaoatual != BAIXO) {
                        float distancia = pow(pacman.posx - cacador.posx, 2) + pow(pacman.posy - (cacador.posy - 1), 2);
                        caminhosvalidos.push_back({CIMA, distancia});
                    }
                    if (mapaatual[cacador.posy + 1][cacador.posx] != 2 && cacador.direcaoatual != CIMA && !cimadaporta) {
                        float distancia = pow(pacman.posx - cacador.posx, 2) + pow(pacman.posy - (cacador.posy + 1), 2);
                        caminhosvalidos.push_back({BAIXO, distancia});
                    }
                    if (cacador.posx == 0 || (mapaatual[cacador.posy][cacador.posx - 1] != 2 && cacador.direcaoatual != DIREITA)) {
                        float distancia = (cacador.posx == 0) ? pow(pacman.posx - 0, 2) + pow(pacman.posy - cacador.posy, 2)
                                                              : pow(pacman.posx - (cacador.posx - 1), 2) + pow(pacman.posy - cacador.posy, 2);
                        caminhosvalidos.push_back({ESQUERDA, distancia});
                    }
                    if (cacador.posx == 27 || (mapaatual[cacador.posy][cacador.posx + 1] != 2 && cacador.direcaoatual != ESQUERDA)) {
                        float distancia = (cacador.posx == 27) ? pow(pacman.posx - 27, 2) + pow(pacman.posy - cacador.posy, 2)
                                                               : pow(pacman.posx - (cacador.posx + 1), 2) + pow(pacman.posy - cacador.posy, 2);
                        caminhosvalidos.push_back({DIREITA, distancia});
                    }

                    sort(caminhosvalidos.begin(), caminhosvalidos.end(), comparadistancias);

                    if (caminhosvalidos.size() == 0) {
                        if (cacador.direcaoatual == CIMA) cacador.direcaoatual = BAIXO;
                        else if (cacador.direcaoatual == BAIXO) cacador.direcaoatual = CIMA;
                        else if (cacador.direcaoatual == ESQUERDA) cacador.direcaoatual = DIREITA;
                        else if (cacador.direcaoatual == DIREITA) cacador.direcaoatual = ESQUERDA;
                    }
                    else cacador.direcaoatual = caminhosvalidos[0].direcao; 

                    if (cacador.direcaoatual == CIMA && mapaatual[cacador.posy - 1][cacador.posx] != 2) cacador.posy--;
                    else if (cacador.direcaoatual == BAIXO && mapaatual[cacador.posy + 1][cacador.posx] != 2) cacador.posy++;
                    else if (cacador.direcaoatual == ESQUERDA) {
                        if (cacador.posx == 0) cacador.posx = 27;
                        else if (mapaatual[cacador.posy][cacador.posx - 1] != 2) cacador.posx--;
                    }
                    else if (cacador.direcaoatual == DIREITA) {
                        if (cacador.posx == 27) cacador.posx = 0;
                        else if (mapaatual[cacador.posy][cacador.posx + 1] != 2) cacador.posx++;
                    }

                    if (pacman.posy == cacador.posy && pacman.posx == cacador.posx) estadoatual = GAMEOVER;
                }
            }
        }
        
        window.clear(sf::Color::Black);

        if (estadoatual == MENU) {
            char s[3];
            snprintf(s, 20, ":(" ); 
            sadface.setString(s);
            sadface.setPosition({400.f, 500.f});
            window.draw(sadface);

            char t[20];
            snprintf(t, 20, "pacman" ); 
            titulomenu.setString(t);
            titulomenu.setPosition({200.f, 100.f});
            window.draw(titulomenu);
        }
       
        if(estadoatual == JOGANDO || estadoatual == GAMEOVER){
            
            // --- 1. DESENHA O MAPA BASE (Paredes e Piso iluminado) ---
            for (int i = 0; i < 33; i++) {
                for (int j = 0; j < 28; j++) {
                    if (mapaatual[i][j] == 2) { 
                        quad.setPosition({j * 32.f, i * 32.f + OFFSET_Y});
                        window.draw(quad);
                    }
                    else {
                        // Se estiver completamente iluminado, desenha o "piso de neon" (luzinha)
                        if (shadowMatrix[i][j] == 0.0f) {
                            litFloorQuad.setPosition({j * 32.f + 4.f, i * 32.f + 4.f + OFFSET_Y}); // centralizado no bloco
                            window.draw(litFloorQuad);
                        }
                    }
                }
            }
        
            // --- 2. DESENHA OQue base de código limpa e bem estruturada! Foi muito bacana trabalhar em cima dela. Como você já estava usando o esquema de matriz 33x28 (`mapaatual` e `mapaoriginal`), e implementando a manipulação de eventos padrão da SFML 3.0[cite: 1], a integração da mecânica de luz e sombra fluiu perfeitamente.

