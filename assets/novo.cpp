#include <SFML/Graphics.hpp>
#include <optional>
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <cmath>
#include <SFML/Audio.hpp>
using namespace std;

// FANTASMA QUE TELEPORTA PELO mapaatual
// FANTASMA QUE SEGUE A FRUTA ESPECIAL LA
// FANTASMA CAMPER QUE ESPERA NO CANTINHO DA PILULA DE FORÇA
// FANTASMA QUE CONGUE ATRAVESSAR UMA PAREDE (FANTASMA DE VERDADE)

// mapaatual CORRIGIDO: 31 linhas por 28 colunas reais.
// com a casa dos fantasmas oca no centro e apenas um túnel central.
const int mapaoriginal[33][28] = { // essa é como se fosse o modelo do labirinto original
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

int score = 0;

enum ESTADO
{
    MENU,
    JOGANDO,
    GAMEOVER,
    VITORIA
};
enum DIRECAO
{
    NENHUMA,
    CIMA,
    BAIXO,
    ESQUERDA,
    DIREITA
};

struct Pacman
{
    int posx = 14;
    int posy = 21;
    DIRECAO direcaoatual = NENHUMA;
    DIRECAO proximadirecao = NENHUMA;
    bool abre = true;
    sf::Clock animacao;
    float posAnteriorX = 0;
    float posAnteriorY = 0;
};
Pacman pacman;

enum ESTADOFANTASMA
{
    PRESO,
    SAINDO,
    LIVRE
};

struct Fantasma
{
    int posx;
    int posy;
    DIRECAO direcaoatual = NENHUMA;
    DIRECAO proximadirecao = NENHUMA;
    ESTADOFANTASMA estadoatual = PRESO;
    sf::Clock relogio;
};

Fantasma aleatorio = {15, 14, NENHUMA, NENHUMA, PRESO};
Fantasma cacador = {13, 14, NENHUMA, NENHUMA, PRESO};

struct caminhos
{
    DIRECAO direcao;
    float distancia;
};

bool comparadistancias(caminhos a, caminhos b)
{
    return a.distancia < b.distancia;
}

void centralizarTexto(sf::Text& texto) {
    sf::FloatRect bounds = texto.getLocalBounds();
    texto.setOrigin({bounds.position.x + bounds.size.x / 2.0f, bounds.position.y + bounds.size.y / 2.0f});
}

void ResetarJogo()
{
    pacman.posx = 14;
    pacman.posy = 21;
    pacman.direcaoatual = NENHUMA;
    pacman.proximadirecao = NENHUMA;
    pacman.abre = true;

    aleatorio = {15, 14, NENHUMA, NENHUMA, PRESO};
    aleatorio.relogio.restart();
    cacador = {13, 14, NENHUMA, NENHUMA, PRESO};
    cacador.relogio.restart();

    score = 0;

    for (int i = 0; i < 33; i++)
        for (int j = 0; j < 28; j++)
            mapaatual[i][j] = mapaoriginal[i][j];
}

bool VerificarVitoria() {
    for (int i = 0; i < 33; i++)
        for (int j = 0; j < 28; j++)
            if (mapaatual[i][j] == 1 || mapaatual[i][j] == 3)
                return false;
    return true;
}

int main()
{
    for (int i = 0; i < 33; i++)
    {
        for (int j = 0; j < 28; j++)
            mapaatual[i][j] = mapaoriginal[i][j];
    }

    ESTADO estadoatual = MENU;
    const float TAMANHO_BLOCO = 32.f;
    const float OFFSET_Y = 64.f;

    const unsigned int larguraJanela = static_cast<unsigned int>(28 * TAMANHO_BLOCO);
    const unsigned int alturaJanela = static_cast<unsigned int>(33 * TAMANHO_BLOCO + OFFSET_Y);

    sf::RenderWindow window(sf::VideoMode({larguraJanela, alturaJanela}), "Pac-Man UFV");

    sf::Music musicaFundo;
    if (!musicaFundo.openFromFile("moonlight.mp3")) {
        std::cout << "Erro ao carregar a moonlight.mp3\n";
    } else {
        musicaFundo.setLooping(true);
        musicaFundo.setVolume(100.f);
        musicaFundo.play();
    }

    sf::RectangleShape quad({32.f, 32.f});
    quad.setFillColor(sf::Color(0, 100, 200));
    quad.setOutlineThickness(-1.5f);
    quad.setOutlineColor(sf::Color(0, 40, 120));

    sf::CircleShape pill({8.f});
    pill.setFillColor(sf::Color(200, 100, 0));

    sf::CircleShape powerPellet(12.f);
    powerPellet.setFillColor(sf::Color(200, 100, 0));

    sf::RectangleShape portaVisual({TAMANHO_BLOCO, TAMANHO_BLOCO / 4.f});
    portaVisual.setFillColor(sf::Color(255, 184, 222, 200));

    sf::RectangleShape painelGameOver({static_cast<float>(larguraJanela), static_cast<float>(alturaJanela)});
    painelGameOver.setFillColor(sf::Color(0, 0, 0, 180));

    sf::Texture texture, textureCima, textureBaixo, textureEsq;
    sf::Texture texFechadoDir, texFechadoCima, texFechadoBaixo, texFechadoEsq;

    if (!texture.loadFromFile("pacman.png") || !textureCima.loadFromFile("pacman-cima.png") ||
        !textureBaixo.loadFromFile("pacman-baixo.png") || !textureEsq.loadFromFile("pacman-esq.png") ||
        !texFechadoDir.loadFromFile("fechado-dir.png") || !texFechadoCima.loadFromFile("fechado-cima.png") ||
        !texFechadoBaixo.loadFromFile("fechado-baixo.png") || !texFechadoEsq.loadFromFile("fechado-esq.png"))
        std::cout << "Aviso: Imagens do Pac-Man ausentes.\n";

    sf::Sprite spritedir{texture}, spritecima{textureCima}, spritebaixo{textureBaixo}, spriteesq{textureEsq};
    sf::Sprite sFechadoDir{texFechadoDir}, sFechadoCima{texFechadoCima}, sFechadoBaixo{texFechadoBaixo}, sFechadoEsq{texFechadoEsq};

    spritedir.setScale({32.f / texture.getSize().x, 32.f / texture.getSize().y});
    spriteesq.setScale({32.f / textureEsq.getSize().x, 32.f / textureEsq.getSize().y});
    spritebaixo.setScale({32.f / textureBaixo.getSize().x, 32.f / textureBaixo.getSize().y});
    spritecima.setScale({32.f / textureCima.getSize().x, 32.f / textureCima.getSize().y});
    
    sFechadoDir.setScale({32.f / texFechadoDir.getSize().x, 32.f / texFechadoDir.getSize().y});
    sFechadoCima.setScale({32.f / texFechadoCima.getSize().x, 32.f / texFechadoCima.getSize().y});
    sFechadoBaixo.setScale({32.f / texFechadoBaixo.getSize().x, 32.f / texFechadoBaixo.getSize().y});
    sFechadoEsq.setScale({32.f / texFechadoEsq.getSize().x, 32.f / texFechadoEsq.getSize().y});

    sf::Texture Fantasma1;
    if (!Fantasma1.loadFromFile("fantasmalaranja.png"))
    {
        std::cout << "Erro lendo imagem fantasmalaranja.png\n";
        return 0;
    }
    sf::Sprite spritefantasma1(Fantasma1);
    spritefantasma1.setScale({32.f / Fantasma1.getSize().x, 32.f / Fantasma1.getSize().y});

    sf::Texture Fantasma2;
    if (!Fantasma2.loadFromFile("fantasmavermelho.png"))
    {
        std::cout << "Erro lendo imagem fantasmavermelho.png\n";
        return 0;
    }
    sf::Sprite spritefantasma2(Fantasma2);
    spritefantasma2.setScale({32.f / Fantasma2.getSize().x, 32.f / Fantasma2.getSize().y});

    sf::Clock clock;
    sf::Clock blinkClock;
    bool drawTextoIniciar = true;

    sf::Font font;
    if (!font.openFromFile("arial.ttf"))
    {
        std::cout << "Erro lendo fonte arial\n";
        return 0;
    }

    sf::Text textscore(font);
    textscore.setCharacterSize(18);
    textscore.setFillColor(sf::Color::White);
    textscore.setPosition({20.f, 24.f});

    sf::Text textoPacmanTopo(font);
    textoPacmanTopo.setString("PAC-MAN");
    textoPacmanTopo.setCharacterSize(30);
    textoPacmanTopo.setFillColor(sf::Color::Yellow);
    centralizarTexto(textoPacmanTopo);
    textoPacmanTopo.setPosition({larguraJanela / 2.f, 32.f});

    sf::Text textoHighScore(font);
    textoHighScore.setCharacterSize(18);
    textoHighScore.setFillColor(sf::Color::White);
    textoHighScore.setString("HI-SCORE\n0");
    sf::FloatRect boundsHS = textoHighScore.getLocalBounds();
    textoHighScore.setOrigin({boundsHS.position.x + boundsHS.size.x, boundsHS.position.y});
    textoHighScore.setPosition({larguraJanela - 20.f, 24.f});

    sf::Text textoTitulo(font);
    textoTitulo.setString("PAC-MAN");
    textoTitulo.setCharacterSize(80);
    textoTitulo.setFillColor(sf::Color::Yellow);
    centralizarTexto(textoTitulo);
    textoTitulo.setPosition({larguraJanela / 2.f, alturaJanela / 3.f});

    sf::Text textoIniciar(font);
    textoIniciar.setString("PRESS ENTER TO START");
    textoIniciar.setCharacterSize(20);
    textoIniciar.setFillColor(sf::Color::White);
    centralizarTexto(textoIniciar);
    textoIniciar.setPosition({larguraJanela / 2.f, alturaJanela / 1.5f});

    sf::Text textoGameOver(font);
    textoGameOver.setString("GAME OVER");
    textoGameOver.setCharacterSize(60);
    textoGameOver.setFillColor(sf::Color::Red);
    centralizarTexto(textoGameOver);
    textoGameOver.setPosition({larguraJanela / 2.f, alturaJanela / 3.f});

    sf::Text textoVitoria(font);
    textoVitoria.setString("YOU WIN!");
    textoVitoria.setCharacterSize(60);
    textoVitoria.setFillColor(sf::Color::Green);
    centralizarTexto(textoVitoria);
    textoVitoria.setPosition({larguraJanela / 2.f, alturaJanela / 3.f});

    sf::Text textoOpcoesGO(font);
    textoOpcoesGO.setString("PRESS 'R' TO RESTART\n\nPRESS 'M' FOR MENU");
    textoOpcoesGO.setCharacterSize(20);
    textoOpcoesGO.setFillColor(sf::Color::White);
    centralizarTexto(textoOpcoesGO);
    textoOpcoesGO.setPosition({larguraJanela / 2.f, alturaJanela / 1.5f});

    sf::Text textoFinalScore(font);
    textoFinalScore.setCharacterSize(25);
    textoFinalScore.setFillColor(sf::Color::Yellow);

    int highScore = 0;

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
                    {
                        pacman.proximadirecao = ESQUERDA;
                    }
                    else if (keyPressed->scancode == sf::Keyboard::Scancode::Right)
                    {
                        pacman.proximadirecao = DIREITA;
                    }
                    else if (keyPressed->scancode == sf::Keyboard::Scancode::Up)
                    {
                        pacman.proximadirecao = CIMA;
                    }
                    else if (keyPressed->scancode == sf::Keyboard::Scancode::Down)
                    {
                        pacman.proximadirecao = BAIXO;
                    }
                }
            }
        }
        
        if(estadoatual == JOGANDO){
            if (clock.getElapsedTime() > sf::seconds(0.2))
            {
                clock.restart();

                // Movimento Pac-Man
                if (pacman.proximadirecao == CIMA && mapaatual[pacman.posy - 1][pacman.posx] != 2 && mapaatual[pacman.posy - 1][pacman.posx] != 4)
                    pacman.direcaoatual = CIMA;
                else if (pacman.proximadirecao == BAIXO && mapaatual[pacman.posy + 1][pacman.posx] != 2 && mapaatual[pacman.posy + 1][pacman.posx] != 4)
                    pacman.direcaoatual = BAIXO;
                else if (pacman.proximadirecao == ESQUERDA && mapaatual[pacman.posy][pacman.posx - 1] != 2 && mapaatual[pacman.posy][pacman.posx - 1] != 4)
                    pacman.direcaoatual = ESQUERDA;
                else if (pacman.proximadirecao == DIREITA && mapaatual[pacman.posy][pacman.posx + 1] != 2 && mapaatual[pacman.posy][pacman.posx + 1] != 4)
                    pacman.direcaoatual = DIREITA;

                pacman.posAnteriorX = pacman.posx;
                pacman.posAnteriorY = pacman.posy;

                if (pacman.direcaoatual == CIMA)
                {
                    if (mapaatual[pacman.posy - 1][pacman.posx] != 2 && mapaatual[pacman.posy - 1][pacman.posx] != 4)
                    {
                        pacman.posy--;
                    }
                }
                else if (pacman.direcaoatual == BAIXO)
                {
                    if (mapaatual[pacman.posy + 1][pacman.posx] != 2 && mapaatual[pacman.posy + 1][pacman.posx] != 4)
                    {
                        pacman.posy++;
                    }
                }
                else if (pacman.direcaoatual == ESQUERDA)
                {
                    if (pacman.posx == 0) 
                        pacman.posx = 27;
                    else if (mapaatual[pacman.posy][pacman.posx - 1] != 2 && mapaatual[pacman.posy][pacman.posx - 1] != 4)
                    {
                        pacman.posx--;
                    }
                }
                else if (pacman.direcaoatual == DIREITA)
                {
                    if (pacman.posx == 27) 
                        pacman.posx = 0;
                    else if (mapaatual[pacman.posy][pacman.posx + 1] != 2 && mapaatual[pacman.posy][pacman.posx + 1] != 4)
                    {
                        pacman.posx++;
                    }
                }

                // Comer pílulas
                if (mapaatual[pacman.posy][pacman.posx] == 1)
                {
                    score += 10;
                    mapaatual[pacman.posy][pacman.posx] = 0;
                    if (VerificarVitoria()) estadoatual = VITORIA;
                }
                else if (mapaatual[pacman.posy][pacman.posx] == 3)
                {
                    score += 50;
                    mapaatual[pacman.posy][pacman.posx] = 0;
                    if (VerificarVitoria()) estadoatual = VITORIA;
                }

                if (score > highScore) highScore = score;
                textscore.setString("SCORE\n" + std::to_string(score));
                textoHighScore.setString("HI-SCORE\n" + std::to_string(highScore));
                sf::FloatRect boundsHS2 = textoHighScore.getLocalBounds();
                textoHighScore.setOrigin({boundsHS2.position.x + boundsHS2.size.x, boundsHS2.position.y});
                textoHighScore.setPosition({larguraJanela - 20.f, 24.f});

                // Fantasma Aleatório
                if (aleatorio.estadoatual == PRESO)
                {
                    if (aleatorio.relogio.getElapsedTime().asSeconds() >= 5.0f)
                    {
                        aleatorio.estadoatual = SAINDO;
                    }
                    else
                    {
                        if (aleatorio.posy == 14) 
                            aleatorio.posy = 13;
                        else
                            aleatorio.posy = 14;
                    }
                }
                else if (aleatorio.estadoatual == SAINDO)
                {
                    if (aleatorio.posx < 14)
                    {
                        aleatorio.posx++;
                    }
                    else if (aleatorio.posx > 14)
                    {
                        aleatorio.posx--;
                    }
                    else
                    {
                        if (aleatorio.posy != 11)
                        {
                            aleatorio.posy--;
                        }
                        else
                        {
                            aleatorio.estadoatual = LIVRE;
                            aleatorio.direcaoatual = NENHUMA;
                        }
                    }
                }
                else if (aleatorio.estadoatual == LIVRE)
                {
                    bool movimentovertical = (aleatorio.direcaoatual == CIMA || aleatorio.direcaoatual == BAIXO);
                    bool movimentohorizontal = (aleatorio.direcaoatual == ESQUERDA || aleatorio.direcaoatual == DIREITA);

                    int caminhoslivres = 0;
                    if (aleatorio.posy > 0 && mapaatual[aleatorio.posy - 1][aleatorio.posx] != 2) caminhoslivres++;
                    if (aleatorio.posy < 32 && mapaatual[aleatorio.posy + 1][aleatorio.posx] != 2 && mapaatual[aleatorio.posy + 1][aleatorio.posx] != 4) caminhoslivres++;
                    if (aleatorio.posx > 0 && mapaatual[aleatorio.posy][aleatorio.posx - 1] != 2) caminhoslivres++;
                    if (aleatorio.posx < 27 && mapaatual[aleatorio.posy][aleatorio.posx + 1] != 2) caminhoslivres++;

                    bool mudadirecao = false;

                    if ((aleatorio.direcaoatual == NENHUMA) ||
                        (aleatorio.direcaoatual == CIMA && (aleatorio.posy == 0 || mapaatual[aleatorio.posy - 1][aleatorio.posx] == 2)) ||
                        (aleatorio.direcaoatual == BAIXO && (aleatorio.posy == 32 || mapaatual[aleatorio.posy + 1][aleatorio.posx] == 2 || mapaatual[aleatorio.posy + 1][aleatorio.posx] == 4)) ||
                        (aleatorio.direcaoatual == ESQUERDA && (aleatorio.posx == 0 || mapaatual[aleatorio.posy][aleatorio.posx - 1] == 2)) ||
                        (aleatorio.direcaoatual == DIREITA && (aleatorio.posx == 27 || mapaatual[aleatorio.posy][aleatorio.posx + 1] == 2)) ||
                        (movimentohorizontal && (aleatorio.posy > 0 && mapaatual[aleatorio.posy - 1][aleatorio.posx] != 2 || aleatorio.posy < 32 && mapaatual[aleatorio.posy + 1][aleatorio.posx] != 2 && mapaatual[aleatorio.posy + 1][aleatorio.posx] != 4)) ||
                        (movimentovertical && (aleatorio.posx > 0 && mapaatual[aleatorio.posy][aleatorio.posx - 1] != 2 || aleatorio.posx < 27 && mapaatual[aleatorio.posy][aleatorio.posx + 1] != 2)))
                    {
                        mudadirecao = true;
                    }

                    static random_device rd;
                    static mt19937 gerador(rd());
                    uniform_int_distribution<int> distribuicao(1, 4);

                    while (mudadirecao)
                    {
                        int sorteio = distribuicao(gerador);

                        if (sorteio == 1 && aleatorio.posy > 0 && mapaatual[aleatorio.posy - 1][aleatorio.posx] != 2)
                        {
                            if (movimentohorizontal || aleatorio.direcaoatual == CIMA || caminhoslivres <= 1 || aleatorio.direcaoatual == NENHUMA)
                            {
                                aleatorio.direcaoatual = CIMA;
                                mudadirecao = false;
                            }
                        }
                        else if (sorteio == 2 && aleatorio.posy < 32 && mapaatual[aleatorio.posy + 1][aleatorio.posx] != 2 && mapaatual[aleatorio.posy + 1][aleatorio.posx] != 4)
                        {
                            if (movimentohorizontal || aleatorio.direcaoatual == BAIXO || caminhoslivres <= 1 || aleatorio.direcaoatual == NENHUMA)
                            {
                                aleatorio.direcaoatual = BAIXO;
                                mudadirecao = false;
                            }
                        }
                        else if (sorteio == 3)
                        {
                            if (aleatorio.posx == 0)
                            {
                                aleatorio.direcaoatual = ESQUERDA;
                                mudadirecao = false;
                            }
                            else if (mapaatual[aleatorio.posy][aleatorio.posx - 1] != 2)
                            {
                                if (movimentovertical || aleatorio.direcaoatual == ESQUERDA || caminhoslivres <= 1 || aleatorio.direcaoatual == NENHUMA)
                                {
                                    aleatorio.direcaoatual = ESQUERDA;
                                    mudadirecao = false;
                                }
                            }
                        }
                        else if (sorteio == 4)
                        {
                            if (aleatorio.posx == 27)
                            {
                                aleatorio.direcaoatual = DIREITA;
                                mudadirecao = false;
                            }
                            else if (mapaatual[aleatorio.posy][aleatorio.posx + 1] != 2)
                            {
                                if (movimentovertical || aleatorio.direcaoatual == DIREITA || caminhoslivres <= 1 || aleatorio.direcaoatual == NENHUMA)
                                {
                                    aleatorio.direcaoatual = DIREITA;
                                    mudadirecao = false;
                                }
                            }
                        }
                    }

                    if (aleatorio.direcaoatual == CIMA && aleatorio.posy > 0 && mapaatual[aleatorio.posy - 1][aleatorio.posx] != 2)
                    {
                        aleatorio.posy--;
                    }
                    else if (aleatorio.direcaoatual == BAIXO && aleatorio.posy < 32 && mapaatual[aleatorio.posy + 1][aleatorio.posx] != 2 && mapaatual[aleatorio.posy + 1][aleatorio.posx] != 4)
                    {
                        aleatorio.posy++;
                    }
                    else if (aleatorio.direcaoatual == ESQUERDA)
                    {
                        if (aleatorio.posx == 0) 
                            aleatorio.posx = 27;
                        else if (mapaatual[aleatorio.posy][aleatorio.posx - 1] != 2)
                        {
                            aleatorio.posx--;
                        }
                    }
                    else if (aleatorio.direcaoatual == DIREITA)
                    {
                        if (aleatorio.posx == 27) 
                            aleatorio.posx = 0;
                        else if (mapaatual[aleatorio.posy][aleatorio.posx + 1] != 2)
                        {
                            aleatorio.posx++;
                        }
                    }
                }

                // Fantasma Caçador
                std::vector<caminhos> caminhosvalidos;

                if (cacador.estadoatual == PRESO)
                {
                    if (cacador.relogio.getElapsedTime().asSeconds() >= 10.0f)
                    {
                        cacador.estadoatual = SAINDO;
                    }
                    else
                    {
                        if (cacador.posy == 14) 
                            cacador.posy = 13;
                        else
                            cacador.posy = 14;
                    }
                }
                else if (cacador.estadoatual == SAINDO)
                {
                    if (cacador.posx < 13)
                    {
                        cacador.posx++;
                    }
                    else if (cacador.posx > 13)
                    {
                        cacador.posx--;
                    }
                    else
                    {
                        if (cacador.posy != 11)
                        {
                            cacador.posy--;
                        }
                        else
                        {
                            cacador.estadoatual = LIVRE;
                            cacador.direcaoatual = NENHUMA;
                        }
                    }
                }
                else if (cacador.estadoatual == LIVRE)
                {
                    caminhosvalidos.clear();

                    if (cacador.posy > 0 && mapaatual[cacador.posy - 1][cacador.posx] != 2 && cacador.direcaoatual != BAIXO)
                    {
                        float distancia = pow(pacman.posx - cacador.posx, 2) + pow(pacman.posy - (cacador.posy - 1), 2);
                        caminhosvalidos.push_back({CIMA, distancia});
                    }
                    if (cacador.posy < 32 && mapaatual[cacador.posy + 1][cacador.posx] != 2 && mapaatual[cacador.posy + 1][cacador.posx] != 4 && cacador.direcaoatual != CIMA)
                    {
                        float distancia = pow(pacman.posx - cacador.posx, 2) + pow(pacman.posy - (cacador.posy + 1), 2);
                        caminhosvalidos.push_back({BAIXO, distancia});
                    }
                    if (cacador.posx > 0 && mapaatual[cacador.posy][cacador.posx - 1] != 2 && cacador.direcaoatual != DIREITA)
                    {
                        float distancia = pow(pacman.posx - (cacador.posx - 1), 2) + pow(pacman.posy - cacador.posy, 2);
                        caminhosvalidos.push_back({ESQUERDA, distancia});
                    }
                    if (cacador.posx < 27 && mapaatual[cacador.posy][cacador.posx + 1] != 2 && cacador.direcaoatual != ESQUERDA)
                    {
                        float distancia = pow(pacman.posx - (cacador.posx + 1), 2) + pow(pacman.posy - cacador.posy, 2);
                        caminhosvalidos.push_back({DIREITA, distancia});
                    }

                    sort(caminhosvalidos.begin(), caminhosvalidos.end(), comparadistancias);

                    if (caminhosvalidos.size() == 0)
                    {
                        if (cacador.direcaoatual == CIMA) cacador.direcaoatual = BAIXO;
                        else if (cacador.direcaoatual == BAIXO) cacador.direcaoatual = CIMA;
                        else if (cacador.direcaoatual == ESQUERDA) cacador.direcaoatual = DIREITA;
                        else if (cacador.direcaoatual == DIREITA) cacador.direcaoatual = ESQUERDA;
                    }
                    else
                    {
                        cacador.direcaoatual = caminhosvalidos[0].direcao;
                    }

                    if (cacador.direcaoatual == CIMA && cacador.posy > 0 && mapaatual[cacador.posy - 1][cacador.posx] != 2)
                    {
                        cacador.posy--;
                    }
                    else if (cacador.direcaoatual == BAIXO && cacador.posy < 32 && mapaatual[cacador.posy + 1][cacador.posx] != 2 && mapaatual[cacador.posy + 1][cacador.posx] != 4)
                    {
                        cacador.posy++;
                    }
                    else if (cacador.direcaoatual == ESQUERDA)
                    {
                        if (cacador.posx == 0) 
                            cacador.posx = 27;
                        else if (mapaatual[cacador.posy][cacador.posx - 1] != 2)
                        {
                            cacador.posx--;
                        }
                    }
                    else if (cacador.direcaoatual == DIREITA)
                    {
                        if (cacador.posx == 27) 
                            cacador.posx = 0;
                        else if (mapaatual[cacador.posy][cacador.posx + 1] != 2)
                        {
                            cacador.posx++;
                        }
                    }
                }

                // Verificar colisão com fantasmas
                if ((pacman.posy == aleatorio.posy && pacman.posx == aleatorio.posx) ||
                    (pacman.posy == cacador.posy && pacman.posx == cacador.posx))
                {
                    estadoatual = GAMEOVER;
                }
            }
        }

        window.clear(sf::Color::Black);

        if (estadoatual == MENU) {
            if (blinkClock.getElapsedTime() > sf::seconds(0.5f)) { drawTextoIniciar = !drawTextoIniciar; blinkClock.restart(); }
            window.draw(textoTitulo);
            if (drawTextoIniciar) window.draw(textoIniciar);
        }
        else if (estadoatual == JOGANDO || estadoatual == GAMEOVER || estadoatual == VITORIA) {
            window.draw(textscore);
            window.draw(textoPacmanTopo);
            window.draw(textoHighScore);

            for (int i = 0; i < 33; i++)
            {
                for (int j = 0; j < 28; j++)
                {
                    if (mapaatual[i][j] == 2)
                    {
                        quad.setPosition({j * 32.f, i * 32.f + OFFSET_Y});
                        window.draw(quad);
                    }
                    else if (mapaatual[i][j] == 4)
                    {
                        portaVisual.setPosition({j * TAMANHO_BLOCO, i * TAMANHO_BLOCO + OFFSET_Y + (TAMANHO_BLOCO / 4.f)});
                        window.draw(portaVisual);
                    }
                    else if (mapaatual[i][j] == 1)
                    {
                        pill.setPosition({j * 32.f + 8.f, i * 32.f + 8.f + OFFSET_Y});
                        window.draw(pill);
                    }
                    else if (mapaatual[i][j] == 3)
                    {
                        powerPellet.setPosition({j * 32.f + 4.f, i * 32.f + 4.f + OFFSET_Y});
                        window.draw(powerPellet);
                    }
                }
            }

            // Animação do Pac-Man
            if(pacman.posAnteriorX != pacman.posx || pacman.posAnteriorY != pacman.posy){
                if (pacman.animacao.getElapsedTime().asSeconds() > 0.1f) {
                    pacman.abre = !pacman.abre;
                    pacman.animacao.restart();
                }
            }
            else
                pacman.abre = true;

            if(pacman.abre){
                if (pacman.direcaoatual == DIREITA || pacman.direcaoatual == NENHUMA)
                {
                    spritedir.setPosition({pacman.posx * 32.f, pacman.posy * 32.f + OFFSET_Y});
                    window.draw(spritedir);
                }
                else if (pacman.direcaoatual == BAIXO)
                {
                    spritebaixo.setPosition({pacman.posx * 32.f, pacman.posy * 32.f + OFFSET_Y});
                    window.draw(spritebaixo);
                }
                else if (pacman.direcaoatual == ESQUERDA)
                {
                    spriteesq.setPosition({pacman.posx * 32.f, pacman.posy * 32.f + OFFSET_Y});
                    window.draw(spriteesq);
                }
                else if (pacman.direcaoatual == CIMA)
                {
                    spritecima.setPosition({pacman.posx * 32.f, pacman.posy * 32.f + OFFSET_Y});
                    window.draw(spritecima);
                }
            }
            else {
                if (pacman.direcaoatual == DIREITA || pacman.direcaoatual == NENHUMA) {
                    sFechadoDir.setPosition({pacman.posx * 32.f, pacman.posy * 32.f + OFFSET_Y});
                    window.draw(sFechadoDir);
                } else if (pacman.direcaoatual == BAIXO) {
                    sFechadoBaixo.setPosition({pacman.posx * 32.f, pacman.posy * 32.f + OFFSET_Y});
                    window.draw(sFechadoBaixo);
                } else if (pacman.direcaoatual == ESQUERDA) {
                    sFechadoEsq.setPosition({pacman.posx * 32.f, pacman.posy * 32.f + OFFSET_Y});
                    window.draw(sFechadoEsq);
                } else if (pacman.direcaoatual == CIMA) {
                    sFechadoCima.setPosition({pacman.posx * 32.f, pacman.posy * 32.f + OFFSET_Y});
                    window.draw(sFechadoCima);
                }
            }

            spritefantasma1.setPosition({aleatorio.posx * 32.f, aleatorio.posy * 32.f + OFFSET_Y});
            window.draw(spritefantasma1);

            spritefantasma2.setPosition({cacador.posx * 32.f, cacador.posy * 32.f + OFFSET_Y});
            window.draw(spritefantasma2);

            if (estadoatual == GAMEOVER || estadoatual == VITORIA) {
                window.draw(painelGameOver);
                textoFinalScore.setString("SCORE: " + std::to_string(score));
                centralizarTexto(textoFinalScore);
                textoFinalScore.setPosition({larguraJanela / 2.f, alturaJanela / 2.f});
                if (estadoatual == GAMEOVER) window.draw(textoGameOver);
                else window.draw(textoVitoria);
                window.draw(textoFinalScore);
                window.draw(textoOpcoesGO);
            }
        }

        window.display();
    }
    return 0;
}