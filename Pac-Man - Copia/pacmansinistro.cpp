#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <optional>

// --- CONFIGURAÇÕES GLOBAIS ---
const float TAMANHO_BLOCO = 24.f; 
const float VELOCIDADE_BASE = 2.0f; // Ajustado para bater certinho com o grid de 24
const unsigned int LARGURA_MAPA = 28;
const unsigned int ALTURA_MAPA = 36;

enum EstadoJogo { MENU, JOGANDO, GAME_OVER, VITORIA };
enum Direcao { NENHUMA = 0, CIMA, BAIXO, ESQUERDA, DIREITA };
enum ModoIA { CHASE, SCATTER, FRIGHTENED, EATEN };

const int mapaOriginal[ALTURA_MAPA][LARGURA_MAPA] = {
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,1,1,1,1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,1,1,1,1,1,1,2},
    {2,1,2,2,2,2,1,2,2,2,2,2,1,2,2,1,2,2,2,2,2,1,2,2,2,2,1,2},
    {2,3,2,2,2,2,1,2,2,2,2,2,1,2,2,1,2,2,2,2,2,1,2,2,2,2,3,2},
    {2,1,2,2,2,2,1,2,2,2,2,2,1,2,2,1,2,2,2,2,2,1,2,2,2,2,1,2},
    {2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
    {2,1,2,2,2,2,1,2,2,1,2,2,2,2,2,2,2,2,1,2,2,1,2,2,2,2,1,2},
    {2,1,2,2,2,2,1,2,2,1,2,2,2,2,2,2,2,2,1,2,2,1,2,2,2,2,1,2},
    {2,1,1,1,1,1,1,2,2,1,1,1,1,2,2,1,1,1,1,2,2,1,1,1,1,1,1,2},
    {2,2,2,2,2,2,1,2,2,2,2,2,0,2,2,0,2,2,2,2,2,1,2,2,2,2,2,2},
    {0,0,0,0,0,2,1,2,2,2,2,2,0,2,2,0,2,2,2,2,2,1,2,0,0,0,0,0},
    {0,0,0,0,0,2,1,2,2,0,0,0,0,0,0,0,0,0,0,2,2,1,2,0,0,0,0,0},
    {0,0,0,0,0,2,1,2,2,0,2,2,2,4,4,2,2,2,0,2,2,1,2,0,0,0,0,0},
    {2,2,2,2,2,2,1,2,2,0,2,0,0,0,0,0,0,2,0,2,2,1,2,2,2,2,2,2},
    {0,0,0,0,0,0,1,0,0,0,2,0,0,0,0,0,0,2,0,0,0,1,0,0,0,0,0,0}, 
    {2,2,2,2,2,2,1,2,2,0,2,0,0,0,0,0,0,2,0,2,2,1,2,2,2,2,2,2},
    {0,0,0,0,0,2,1,2,2,0,2,2,2,2,2,2,2,2,0,2,2,1,2,0,0,0,0,0},
    {0,0,0,0,0,2,1,2,2,0,0,0,0,0,0,0,0,0,0,2,2,1,2,0,0,0,0,0},
    {0,0,0,0,0,2,1,2,2,0,2,2,2,2,2,2,2,2,0,2,2,1,2,0,0,0,0,0},
    {2,2,2,2,2,2,1,2,2,0,2,2,2,2,2,2,2,2,0,2,2,1,2,2,2,2,2,2},
    {2,1,1,1,1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,1,1,1,1,1,1,2},
    {2,1,2,2,2,2,1,2,2,2,2,2,1,2,2,1,2,2,2,2,2,1,2,2,2,2,1,2},
    {2,1,2,2,2,2,1,2,2,2,2,2,1,2,2,1,2,2,2,2,2,1,2,2,2,2,1,2},
    {2,3,1,1,2,2,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,2,2,1,1,3,2},
    {2,2,2,1,2,2,1,2,2,1,2,2,2,2,2,2,2,2,1,2,2,1,2,2,1,2,2,2},
    {2,2,2,1,2,2,1,2,2,1,2,2,2,2,2,2,2,2,1,2,2,1,2,2,1,2,2,2},
    {2,1,1,1,1,1,1,2,2,1,1,1,1,2,2,1,1,1,1,2,2,1,1,1,1,1,1,2},
    {2,1,2,2,2,2,2,2,2,2,2,2,1,2,2,1,2,2,2,2,2,2,2,2,2,2,1,2},
    {2,1,2,2,2,2,2,2,2,2,2,2,1,2,2,1,2,2,2,2,2,2,2,2,2,2,1,2},
    {2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
};

int mapa[ALTURA_MAPA][LARGURA_MAPA];

struct Pacman {
    sf::Vector2f pos;
    Direcao dir;
    Direcao proximaDir;
    float frameAtual;
};

struct Fantasma {
    sf::Vector2f pos;
    Direcao dir;
    int tipo; 
    ModoIA modo;
    sf::Vector2i alvoScatter;
    bool ativo;
    bool naCasa; 
};

Pacman pacman;
std::vector<Fantasma> fantasmas(4);
EstadoJogo estadoAtual = MENU;
ModoIA modoGlobalFantasmas = SCATTER;
sf::Clock clockGlobalModos;
sf::Clock clockFrightened;
sf::Clock clockDelta; // Relógio unificado para animação estável

int score = 0;
int pastilhasRestantes = 0;

float obterDistancia(sf::Vector2f p1, sf::Vector2f p2) {
    return std::sqrt((p2.x - p1.x)*(p2.x - p1.x) + (p2.y - p1.y)*(p2.y - p1.y));
}

Direcao obterInverso(Direcao d) {
    if (d == CIMA) return BAIXO;
    if (d == BAIXO) return CIMA;
    if (d == ESQUERDA) return DIREITA;
    if (d == DIREITA) return ESQUERDA;
    return NENHUMA;
}

bool celulaViavel(int gx, int gy, bool paraFantasma = false) {
    if (gx < 0 || gx >= (int)LARGURA_MAPA || gy < 0 || gy >= (int)ALTURA_MAPA) {
        if (gy == 17 && (gx < 0 || gx >= (int)LARGURA_MAPA)) return true;
        return false;
    }
    int val = mapa[gy][gx];
    if (val == 2) return false;
    if (val == 4 && !paraFantasma) return false; 
    return true;
}

void resetMecanicoGeral() {
    pastilhasRestantes = 0;
    for (int y = 0; y < (int)ALTURA_MAPA; y++) {
        for (int x = 0; x < (int)LARGURA_MAPA; x++) {
            mapa[y][x] = mapaOriginal[y][x];
            if (mapa[y][x] == 1 || mapa[y][x] == 3) pastilhasRestantes++;
        }
    }

    // Alinhado perfeitamente com inteiros múltiplos do TAMANHO_BLOCO (24)
    pacman.pos = { 14.f * TAMANHO_BLOCO, 26.f * TAMANHO_BLOCO };
    pacman.dir = NENHUMA;
    pacman.proximaDir = NENHUMA;
    pacman.frameAtual = 0.f;

    fantasmas[0] = { {13.f * TAMANHO_BLOCO, 14.f * TAMANHO_BLOCO}, NENHUMA, 0, SCATTER, {27, 0}, false, true };
    fantasmas[1] = { {13.f * TAMANHO_BLOCO, 16.f * TAMANHO_BLOCO}, NENHUMA, 1, SCATTER, {0, 0}, false, true };
    fantasmas[2] = { {11.f * TAMANHO_BLOCO, 16.f * TAMANHO_BLOCO}, NENHUMA, 2, SCATTER, {27, 35}, false, true };
    fantasmas[3] = { {15.f * TAMANHO_BLOCO, 16.f * TAMANHO_BLOCO}, NENHUMA, 3, SCATTER, {0, 35}, false, true };

    modoGlobalFantasmas = SCATTER;
    clockGlobalModos.restart();
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    resetMecanicoGeral();

    sf::RenderWindow window(sf::VideoMode({LARGURA_MAPA * (unsigned int)TAMANHO_BLOCO, ALTURA_MAPA * (unsigned int)TAMANHO_BLOCO}), "Pac-Man Sinistro");
    window.setFramerateLimit(60);

    // --- CARREGAMENTO DA SPRITE SHEET ---
    sf::Texture texPacman;
    bool usarSpriteSheet = texPacman.loadFromFile("five-pacmans.png");
    sf::Sprite spritePacman(texPacman);
    
    float frameWidth = 0.f;
    float frameHeight = 0.f;

    if (usarSpriteSheet) {
        frameWidth = static_cast<float>(texPacman.getSize().x) / 5.f;
        frameHeight = static_cast<float>(texPacman.getSize().y);
        spritePacman.setOrigin({frameWidth / 2.f, frameHeight / 2.f});
        spritePacman.setScale({TAMANHO_BLOCO / frameWidth, TAMANHO_BLOCO / frameHeight});
    }

    sf::RectangleShape wallBlock({TAMANHO_BLOCO - 2.f, TAMANHO_BLOCO - 2.f});
    wallBlock.setFillColor(sf::Color(33, 33, 255));

    sf::CircleShape dot(3.f);
    dot.setFillColor(sf::Color(255, 184, 174));
    dot.setOrigin({3.f, 3.f});

    sf::CircleShape powerDot(7.f);
    powerDot.setFillColor(sf::Color(255, 184, 174));
    powerDot.setOrigin({7.f, 7.f});

    sf::CircleShape ghostVisual(TAMANHO_BLOCO / 2.f - 1.f);
    ghostVisual.setOrigin({(TAMANHO_BLOCO / 2.f - 1.f), (TAMANHO_BLOCO / 2.f - 1.f)});

    sf::Font font;
    font.openFromFile("retrofonte.ttf");

    sf::Text uiText(font, "", 20);
    uiText.setFillColor(sf::Color::White);

    while (window.isOpen()) {
        float dt = clockDelta.restart().asSeconds(); // Resgata o tempo global por frame

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();

            if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
                if (estadoAtual == JOGANDO) {
                    if (key->scancode == sf::Keyboard::Scancode::Up) pacman.proximaDir = CIMA;
                    if (key->scancode == sf::Keyboard::Scancode::Down) pacman.proximaDir = BAIXO;
                    if (key->scancode == sf::Keyboard::Scancode::Left) pacman.proximaDir = ESQUERDA;
                    if (key->scancode == sf::Keyboard::Scancode::Right) pacman.proximaDir = DIREITA;
                }
            }

            if (event->is<sf::Event::MouseButtonPressed>()) {
                if (estadoAtual == MENU || estadoAtual == GAME_OVER || estadoAtual == VITORIA) {
                    resetMecanicoGeral();
                    score = 0;
                    estadoAtual = JOGANDO;
                }
            }
        }

        if (estadoAtual == JOGANDO) {
            // Controle de Ondas da IA
            if (modoGlobalFantasmas != FRIGHTENED) {
                float tempoDecorrido = clockGlobalModos.getElapsedTime().asSeconds();
                if (modoGlobalFantasmas == SCATTER && tempoDecorrido > 7.0f) {
                    modoGlobalFantasmas = CHASE;
                    clockGlobalModos.restart();
                } else if (modoGlobalFantasmas == CHASE && tempoDecorrido > 20.0f) {
                    modoGlobalFantasmas = SCATTER;
                    clockGlobalModos.restart();
                }
            } else {
                if (clockFrightened.getElapsedTime().asSeconds() > 7.0f) {
                    modoGlobalFantasmas = CHASE;
                    clockGlobalModos.restart();
                }
            }

            // Animação calculada com o Delta Time global
            if (pacman.dir != NENHUMA) {
                pacman.frameAtual += dt * 12.f; 
                if (pacman.frameAtual >= 5.f) pacman.frameAtual = 0.f;
            } else {
                pacman.frameAtual = 0.f; 
            }

            // Movimento baseado no Resto do Grid
            float restoX = std::fmod(pacman.pos.x, TAMANHO_BLOCO);
            float restoY = std::fmod(pacman.pos.y, TAMANHO_BLOCO);

            if (std::abs(restoX) < 0.01f && std::abs(restoY) < 0.01f) {
                pacman.pos.x = std::round(pacman.pos.x);
                pacman.pos.y = std::round(pacman.pos.y);
                
                int currGridX = static_cast<int>(pacman.pos.x / TAMANHO_BLOCO);
                int currGridY = static_cast<int>(pacman.pos.y / TAMANHO_BLOCO);

                if (currGridX == 0 && pacman.dir == ESQUERDA) { pacman.pos.x = 27.f * TAMANHO_BLOCO; }
                else if (currGridX == 27 && pacman.dir == DIREITA) { pacman.pos.x = 0.f * TAMANHO_BLOCO; }

                currGridX = static_cast<int>(pacman.pos.x / TAMANHO_BLOCO);

                if (pacman.proximaDir == CIMA && celulaViavel(currGridX, currGridY - 1)) pacman.dir = CIMA;
                if (pacman.proximaDir == BAIXO && celulaViavel(currGridX, currGridY + 1)) pacman.dir = BAIXO;
                if (pacman.proximaDir == ESQUERDA && celulaViavel(currGridX - 1, currGridY)) pacman.dir = ESQUERDA;
                if (pacman.proximaDir == DIREITA && celulaViavel(currGridX + 1, currGridY)) pacman.dir = DIREITA;

                if (pacman.dir == CIMA && !celulaViavel(currGridX, currGridY - 1)) pacman.dir = NENHUMA;
                if (pacman.dir == BAIXO && !celulaViavel(currGridX, currGridY + 1)) pacman.dir = NENHUMA;
                if (pacman.dir == ESQUERDA && !celulaViavel(currGridX - 1, currGridY)) pacman.dir = NENHUMA;
                if (pacman.dir == DIREITA && !celulaViavel(currGridX + 1, currGridY)) pacman.dir = NENHUMA;
            }

            if (pacman.dir == CIMA) pacman.pos.y -= VELOCIDADE_BASE;
            if (pacman.dir == BAIXO) pacman.pos.y += VELOCIDADE_BASE;
            if (pacman.dir == ESQUERDA) pacman.pos.x -= VELOCIDADE_BASE;
            if (pacman.dir == DIREITA) pacman.pos.x += VELOCIDADE_BASE;

            // Comer Pastilhas
            int centerGridX = static_cast<int>((pacman.pos.x + TAMANHO_BLOCO / 2.f) / TAMANHO_BLOCO);
            int centerGridY = static_cast<int>((pacman.pos.y + TAMANHO_BLOCO / 2.f) / TAMANHO_BLOCO);

            if (centerGridX >= 0 && centerGridX < (int)LARGURA_MAPA && centerGridY >= 0 && centerGridY < (int)ALTURA_MAPA) {
                if (mapa[centerGridY][centerGridX] == 1) {
                    mapa[centerGridY][centerGridX] = 0;
                    score += 10;
                    pastilhasRestantes--;
                } else if (mapa[centerGridY][centerGridX] == 3) {
                    mapa[centerGridY][centerGridX] = 0;
                    score += 50;
                    pastilhasRestantes--;
                    modoGlobalFantasmas = FRIGHTENED;
                    clockFrightened.restart();
                    for (auto& f : fantasmas) {
                        if (f.modo != EATEN) f.modo = FRIGHTENED;
                    }
                }
            }

            if (pastilhasRestantes <= 0) {
                estadoAtual = VITORIA;
            }

            // Movimentação dos Fantasmas
            int pacX = static_cast<int>(pacman.pos.x / TAMANHO_BLOCO);
            int pacY = static_cast<int>(pacman.pos.y / TAMANHO_BLOCO);

            for (size_t i = 0; i < fantasmas.size(); ++i) {
                Fantasma& f = fantasmas[i];
                
                if (f.modo != EATEN && f.modo != FRIGHTENED) {
                    f.modo = modoGlobalFantasmas;
                }

                // Fantasmas parados na casa começam a se mover imediatamente ao iniciar o round
                if (f.dir == NENHUMA) f.dir = CIMA;

                float fRestoX = std::fmod(f.pos.x, TAMANHO_BLOCO);
                float fRestoY = std::fmod(f.pos.y, TAMANHO_BLOCO);

                if (std::abs(fRestoX) < 0.01f && std::abs(fRestoY) < 0.01f) {
                    f.pos.x = std::round(f.pos.x);
                    f.pos.y = std::round(f.pos.y);

                    int fGridX = static_cast<int>(f.pos.x / TAMANHO_BLOCO);
                    int fGridY = static_cast<int>(f.pos.y / TAMANHO_BLOCO);

                    if (fGridX == 0 && f.dir == ESQUERDA) { f.pos.x = 27.f * TAMANHO_BLOCO; fGridX = 27; }
                    else if (fGridX == 27 && f.dir == DIREITA) { f.pos.x = 0.f * TAMANHO_BLOCO; fGridX = 0; }

                    if (f.modo == EATEN && fGridX == 14 && fGridY == 14) {
                        f.modo = modoGlobalFantasmas;
                    }

                    sf::Vector2i alvoCoordenada = f.alvoScatter;

                    if (f.modo == CHASE) {
                        if (f.tipo == 0) alvoCoordenada = { pacX, pacY };
                        else if (f.tipo == 1) { 
                            if (pacman.dir == CIMA) alvoCoordenada = { pacX - 4, pacY - 4 }; 
                            else if (pacman.dir == BAIXO) alvoCoordenada = { pacX, pacY + 4 };
                            else if (pacman.dir == ESQUERDA) alvoCoordenada = { pacX - 4, pacY };
                            else alvoCoordenada = { pacX + 4, pacY };
                        }
                        else if (f.tipo == 2) { 
                            int bX = static_cast<int>(fantasmas[0].pos.x / TAMANHO_BLOCO);
                            int bY = static_cast<int>(fantasmas[0].pos.y / TAMANHO_BLOCO);
                            int pX = pacX; int pY = pacY;
                            if (pacman.dir == CIMA) { pX -= 2; pY -= 2; }
                            else if (pacman.dir == BAIXO) pY += 2;
                            else if (pacman.dir == ESQUERDA) pX -= 2;
                            else pX += 2;
                            alvoCoordenada = { pX + (pX - bX), pY + (pY - bY) };
                        }
                        else if (f.tipo == 3) { 
                            if (obterDistancia(f.pos, pacman.pos) > 8.f * TAMANHO_BLOCO) alvoCoordenada = { pacX, pacY };
                            else alvoCoordenada = f.alvoScatter;
                        }
                    }
                    else if (f.modo == EATEN) {
                        alvoCoordenada = { 14, 14 }; 
                    }

                    Direcao direcoesPossiveis[4] = { CIMA, ESQUERDA, BAIXO, DIREITA }; 
                    Direcao direcaoEscolhida = f.dir;
                    float menorDistanciaCalculada = 99999999.f;
                    Direcao proibida = obterInverso(f.dir);

                    for (Direcao d : direcoesPossiveis) {
                        if (d == proibida) continue;

                        int testX = fGridX + (d == DIREITA) - (d == ESQUERDA);
                        int testY = fGridY + (d == BAIXO) - (d == CIMA);

                        if (celulaViavel(testX, testY, true)) {
                            float dist = obterDistancia(sf::Vector2f(testX * TAMANHO_BLOCO, testY * TAMANHO_BLOCO),
                                                        sf::Vector2f(alvoCoordenada.x * TAMANHO_BLOCO, alvoCoordenada.y * TAMANHO_BLOCO));
                            
                            if (f.modo == FRIGHTENED) {
                                direcaoEscolhida = d;
                                break; 
                            }

                            if (dist < menorDistanciaCalculada) {
                                menorDistanciaCalculada = dist;
                                direcaoEscolhida = d;
                            }
                        }
                    }
                    f.dir = direcaoEscolhida;
                }

                float velFantasma = VELOCIDADE_BASE;
                if (f.modo == FRIGHTENED) velFantasma = VELOCIDADE_BASE * 0.5f;
                if (f.modo == EATEN) velFantasma = VELOCIDADE_BASE * 2.0f;

                if (f.dir == CIMA) f.pos.y -= velFantasma;
                if (f.dir == BAIXO) f.pos.y += velFantasma;
                if (f.dir == ESQUERDA) f.pos.x -= velFantasma;
                if (f.dir == DIREITA) f.pos.x += velFantasma;

                if (obterDistancia(pacman.pos, f.pos) < TAMANHO_BLOCO * 0.65f) {
                    if (f.modo == FRIGHTENED) {
                        f.modo = EATEN;
                        score += 200;
                    } else if (f.modo != EATEN) {
                        estadoAtual = GAME_OVER;
                    }
                }
            }
        }

        // --- RENDERIZAÇÃO ---
        window.clear(sf::Color::Black);
  
        if (estadoAtual == MENU) {
            uiText.setCharacterSize(35);
            uiText.setString("PAC-MAN SINISTRO");
            uiText.setFillColor(sf::Color::Yellow);
            uiText.setPosition({ (LARGURA_MAPA * TAMANHO_BLOCO) / 2.f - 180.f, 300.f });
            window.draw(uiText);

            uiText.setCharacterSize(18);
            uiText.setString("Clique em qualquer lugar para Iniciar");
            uiText.setFillColor(sf::Color::White);
            uiText.setPosition({ (LARGURA_MAPA * TAMANHO_BLOCO) / 2.f - 160.f, 400.f });
            window.draw(uiText);
        }
        else if (estadoAtual == JOGANDO || estadoAtual == GAME_OVER || estadoAtual == VITORIA) {
            for (int y = 0; y < (int)ALTURA_MAPA; y++) {
                for (int x = 0; x < (int)LARGURA_MAPA; x++) {
                    if (mapa[y][x] == 2) {
                        wallBlock.setPosition({x * TAMANHO_BLOCO + 1.f, y * TAMANHO_BLOCO + 1.f});
                        window.draw(wallBlock);
                    } else if (mapa[y][x] == 1) {
                        dot.setPosition({x * TAMANHO_BLOCO + TAMANHO_BLOCO / 2.f, y * TAMANHO_BLOCO + TAMANHO_BLOCO / 2.f});
                        window.draw(dot);
                    } else if (mapa[y][x] == 3) {
                        powerDot.setPosition({x * TAMANHO_BLOCO + TAMANHO_BLOCO / 2.f, y * TAMANHO_BLOCO + TAMANHO_BLOCO / 2.f});
                        window.draw(powerDot);
                    }
                }
            }

            if (usarSpriteSheet) {
                int frameIdx = static_cast<int>(pacman.frameAtual);
                spritePacman.setTextureRect(sf::IntRect({static_cast<int>(frameIdx * frameWidth), 0}, {static_cast<int>(frameWidth), static_cast<int>(frameHeight)}));
                spritePacman.setPosition({pacman.pos.x + TAMANHO_BLOCO / 2.f, pacman.pos.y + TAMANHO_BLOCO / 2.f});

                if (pacman.dir == ESQUERDA) spritePacman.setRotation(sf::degrees(180.f));
                else if (pacman.dir == CIMA) spritePacman.setRotation(sf::degrees(270.f));
                else if (pacman.dir == BAIXO) spritePacman.setRotation(sf::degrees(90.f));
                else if (pacman.dir == DIREITA || pacman.dir == NENHUMA) spritePacman.setRotation(sf::degrees(0.f));

                window.draw(spritePacman);
            } else {
                sf::CircleShape fallbackPac(TAMANHO_BLOCO / 2.f - 1.f);
                fallbackPac.setFillColor(sf::Color::Yellow);
                fallbackPac.setPosition(pacman.pos);
                window.draw(fallbackPac);
            }

            sf::Color coresFantasmas[4] = {
                sf::Color::Red,               
                sf::Color(255, 182, 193),     
                sf::Color(0, 255, 255),       
                sf::Color(255, 165, 0)        
            };

            for (size_t i = 0; i < fantasmas.size(); ++i) {
                ghostVisual.setPosition({fantasmas[i].pos.x + TAMANHO_BLOCO / 2.f, fantasmas[i].pos.y + TAMANHO_BLOCO / 2.f});
                
                if (fantasmas[i].modo == FRIGHTENED) {
                    ghostVisual.setFillColor(sf::Color::Blue);
                } else if (fantasmas[i].modo == EATEN) {
                    ghostVisual.setFillColor(sf::Color(255, 255, 255, 60)); 
                } else {
                    ghostVisual.setFillColor(coresFantasmas[i]);
                }
                window.draw(ghostVisual);
            }

            uiText.setCharacterSize(20);
            uiText.setFillColor(sf::Color::White);
            uiText.setString("SCORE: " + std::to_string(score) + "   RESTANTES: " + std::to_string(pastilhasRestantes));
            uiText.setPosition({ 20.f, 25.f });
            window.draw(uiText);

            if (estadoAtual == GAME_OVER || estadoAtual == VITORIA) {
                sf::RectangleShape overlay(window.getView().getSize());
                overlay.setFillColor(sf::Color(0, 0, 0, 210));
                window.draw(overlay);

                uiText.setCharacterSize(40);
                if (estadoAtual == GAME_OVER) {
                    uiText.setString("GAME OVER");
                    uiText.setFillColor(sf::Color::Red);
                } else {
                    uiText.setString("VITORIA!");
                    uiText.setFillColor(sf::Color::Green);
                }
                uiText.setPosition({ (LARGURA_MAPA * TAMANHO_BLOCO) / 2.f - 120.f, 350.f });
                window.draw(uiText);

                uiText.setCharacterSize(18);
                uiText.setString("Clique para Reiniciar");
                uiText.setFillColor(sf::Color::White);
                uiText.setPosition({ (LARGURA_MAPA * TAMANHO_BLOCO) / 2.f - 95.f, 440.f });
                window.draw(uiText);
            }
        }

        window.display();
    }

    return 0;
}