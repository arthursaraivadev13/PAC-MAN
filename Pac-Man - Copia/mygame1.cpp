#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <optional>
#include <cmath> // Necessário para fmod e sqrt

enum EstadoJogo { MENU, JOGANDO, GAME_OVER };
enum Direcao { NENHUMA, CIMA, BAIXO, ESQUERDA, DIREITA };

// 0 = Vazio, 1 = Pastilha, 2 = Parede, 3 = Pastilha do Poder
int mapaOriginal[33][28] = {
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
    {2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2},
    {2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,3,2}, 
    {2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2},
    {2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
    {2,1,2,2,2,2,1,2,2,1,2,2,2,2,2,2,2,2,1,2,2,1,2,2,2,2,1,2},
    {2,1,2,2,2,2,1,2,2,1,2,2,2,2,2,2,2,2,1,2,2,1,2,2,2,2,1,2},
    {2,1,1,1,1,1,1,2,2,1,1,1,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,2},
    {2,2,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,2,2},
    {2,2,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,2,2},
    {2,2,2,2,2,2,1,2,2,1,1,1,1,1,1,1,1,1,1,2,2,1,2,2,2,2,2,2},
    {2,2,2,2,2,2,1,2,2,1,2,2,2,0,0,2,2,2,1,2,2,1,2,2,2,2,2,2},
    {2,2,2,2,2,2,1,2,2,1,2,0,0,0,0,0,0,2,1,2,2,1,2,2,2,2,2,2},
    {0,0,0,0,0,0,1,1,1,1,2,0,0,0,0,0,0,2,1,1,1,1,1,0,0,0,0,0}, // Linha do Túnel aberta nas pontas (Esquerda/Direita)
    {2,2,2,2,2,2,1,2,2,1,2,0,0,0,0,0,0,2,1,2,2,1,2,2,2,2,2,2},
    {2,2,2,2,2,2,1,2,2,1,2,2,2,2,2,2,2,2,1,2,2,1,2,2,2,2,2,2},
    {2,2,2,2,2,2,1,2,2,1,1,1,1,1,1,1,1,1,1,2,2,1,2,2,2,2,2,2},
    {2,2,2,2,2,2,1,2,2,1,2,2,2,2,2,2,2,2,1,2,2,1,2,2,2,2,2,2},
    {2,2,2,2,2,2,1,2,2,1,2,2,2,2,2,2,2,2,1,2,2,1,2,2,2,2,2,2},
    {2,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,2},
    {2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2},
    {2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2},
    {2,3,1,1,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,1,1,3,2}, 
    {2,2,2,1,2,2,1,2,2,1,2,2,2,2,2,2,2,2,1,2,2,1,2,2,1,2,2,2},
    {2,2,2,1,2,2,1,2,2,1,2,2,2,2,2,2,2,2,1,2,2,1,2,2,1,2,2,2},
    {2,1,1,1,1,1,1,2,2,1,1,1,1,2,2,1,1,1,1,2,2,1,1,1,1,1,1,2},
    {2,1,2,2,2,2,2,2,2,2,2,2,1,2,2,1,2,2,2,2,2,2,2,2,2,2,1,2},
    {2,1,2,2,2,2,2,2,2,2,2,2,1,2,2,1,2,2,2,2,2,2,2,2,2,2,1,2},
    {2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
    {2,1,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,1,2},
    {2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
};

int mapa[33][28];

struct Pacman {
    float x; 
    float y; 
    Direcao direcao;
    Direcao proxima_direcao;
};

struct Fantasma {
    float x;
    float y;
    Direcao direcao;
    int tipo; 
    bool morto;
    bool saiuDaCasa; // Nova flag para gerenciar a saída controlada da base
};

Pacman pacman;
Fantasma fantasmas[4];
EstadoJogo estadoAtual = MENU;

bool olhadireita = true, olhaesquerda = false, olhacima = false, olhabaixo = false;
int score = 0;
bool modoAssustado = false;
sf::Clock relogioPoder;
const float DURACAO_PODER = 7.0f; 

void reiniciarJogo() {
    for (int i = 0; i < 33; i++) {
        for (int j = 0; j < 28; j++) {
            mapa[i][j] = mapaOriginal[i][j];
        }
    }
    pacman.x = 14.f * 32.f; pacman.y = 23.f * 32.f; // Posição correta padrão do Pacman clássico
    pacman.direcao = NENHUMA; pacman.proxima_direcao = NENHUMA;
    olhadireita = true; olhaesquerda = false; olhacima = false; olhabaixo = false;
    
    // Fantasmas começam na casinha com a flag saiuDaCasa = false
    fantasmas[0] = {13.f * 32.f, 14.f * 32.f, NENHUMA, 0, false, false}; // Blinky
    fantasmas[1] = {14.f * 32.f, 14.f * 32.f, NENHUMA, 1, false, false}; // Pinky
    fantasmas[2] = {13.f * 32.f, 14.f * 32.f, NENHUMA, 2, false, false}; // Inky
    fantasmas[3] = {14.f * 32.f, 14.f * 32.f, NENHUMA, 3, false, false}; // Clyde

    score = 0;
    modoAssustado = false;
}

float calcularDistancia(float x1, float y1, float x2, float y2) {
    return std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

Direcao obterOposto(Direcao d) {
    if (d == CIMA) return BAIXO;
    if (d == BAIXO) return CIMA;
    if (d == ESQUERDA) return DIREITA;
    if (d == DIREITA) return ESQUERDA;
    return NENHUMA;
}

int main() {
    const float TAMANHO_BLOCO = 32.f; 
    const float VELOCIDADE = 4.f; 

    reiniciarJogo();

    const unsigned int larguraJanela = static_cast<unsigned int>(28 * TAMANHO_BLOCO);
    const unsigned int alturaJanela = static_cast<unsigned int>(33 * TAMANHO_BLOCO);

    sf::RenderWindow window(sf::VideoMode({larguraJanela, alturaJanela}), "Pac-Man Pro");
    window.setFramerateLimit(60); 

    sf::RectangleShape quad({TAMANHO_BLOCO, TAMANHO_BLOCO});
    quad.setFillColor(sf::Color(0, 100, 200));

    sf::CircleShape circle(4.f); 
    circle.setFillColor(sf::Color(255, 184, 151)); 

    sf::CircleShape bigCircle(8.f); 
    bigCircle.setFillColor(sf::Color(255, 184, 151));

    sf::Font fonte;
    if (!fonte.openFromFile("retrofonte.ttf")) { 
        std::cout << "Erro ao carregar a fonte com openFromFile!\n";
        return 0; 
    }
    
    sf::Text texto(fonte); 
    texto.setCharacterSize(20); 
    texto.setFillColor(sf::Color::White);
    texto.setPosition({10.f, 5.f});

    // --- INTERFACES DE TEXTO (BOTÕES) ---
    sf::Text txtTitulo(fonte, "PAC-MAN", 50);
    txtTitulo.setFillColor(sf::Color::Yellow);
    txtTitulo.setPosition({(larguraJanela / 2.f) - 120.f, 250.f});

    sf::RectangleShape btnIniciar({200.f, 60.f});
    btnIniciar.setFillColor(sf::Color(0, 150, 0));
    btnIniciar.setPosition({(larguraJanela / 2.f) - 100.f, 400.f});

    sf::Text txtIniciar(fonte, "JOGAR", 24);
    txtIniciar.setFillColor(sf::Color::White);
    txtIniciar.setPosition({btnIniciar.getPosition().x + 50.f, btnIniciar.getPosition().y + 15.f});

    sf::Text txtGameOver(fonte, "GAME OVER", 50);
    txtGameOver.setFillColor(sf::Color::Red);
    txtGameOver.setPosition({(larguraJanela / 2.f) - 150.f, 250.f});

    sf::RectangleShape btnReiniciar({220.f, 60.f});
    btnReiniciar.setFillColor(sf::Color(150, 0, 0));
    btnReiniciar.setPosition({(larguraJanela / 2.f) - 110.f, 400.f});

    sf::Text txtReiniciar(fonte, "REINICIAR", 24);
    txtReiniciar.setFillColor(sf::Color::White);
    txtReiniciar.setPosition({btnReiniciar.getPosition().x + 35.f, btnReiniciar.getPosition().y + 15.f});


    // --- CARREGAR SPRITE SHEET DO PAC-MAN ---
    sf::Texture textureSheet;
    if (!textureSheet.loadFromFile("five-pacmans.png")) return 0;

    float larguraFrameOriginal = static_cast<float>(textureSheet.getSize().x) / 5.f;
    float alturaFrameOriginal = static_cast<float>(textureSheet.getSize().y);

    sf::Sprite spritedir{textureSheet}, spritecima{textureSheet}, spritebaixo{textureSheet}, spriteesq{textureSheet};

    spritedir.setScale({TAMANHO_BLOCO / larguraFrameOriginal, TAMANHO_BLOCO / alturaFrameOriginal});
    spritecima.setScale({TAMANHO_BLOCO / larguraFrameOriginal, TAMANHO_BLOCO / alturaFrameOriginal});
    spritebaixo.setScale({TAMANHO_BLOCO / larguraFrameOriginal, TAMANHO_BLOCO / alturaFrameOriginal});
    spriteesq.setScale({TAMANHO_BLOCO / larguraFrameOriginal, TAMANHO_BLOCO / alturaFrameOriginal});

    spritedir.setOrigin({larguraFrameOriginal / 2.f, alturaFrameOriginal / 2.f});
    spritecima.setOrigin({larguraFrameOriginal / 2.f, alturaFrameOriginal / 2.f});
    spritebaixo.setOrigin({larguraFrameOriginal / 2.f, alturaFrameOriginal / 2.f});
    spriteesq.setOrigin({larguraFrameOriginal / 2.f, alturaFrameOriginal / 2.f});

    spritecima.setRotation(sf::degrees(270.f)); 
    spritebaixo.setRotation(sf::degrees(90.f));  
    spriteesq.setRotation(sf::degrees(180.f));  

    int sequenciaFrames[8] = {0, 1, 2, 3, 4, 3, 2, 1};
    int indiceAnimacao = 0;
    sf::Clock relogioAnimacao;

    // --- TEXTURAS DOS FANTASMAS ---
    sf::Texture texF1, texF2, texF3, texF4;
    if (!texF1.loadFromFile("fantasma-vermelho.png") || !texF2.loadFromFile("fantasma-rosa.png") ||
        !texF3.loadFromFile("fantasma-azul.png") || !texF4.loadFromFile("fantasma-laranja.png")) {
        std::cout << "Erro ao carregar fantasmas\n";
        return 0;
    }

    sf::Sprite spritesFantasmas[4] = { sf::Sprite{texF1}, sf::Sprite{texF2}, sf::Sprite{texF3}, sf::Sprite{texF4} };
    for(int i=0; i<4; i++) {
        spritesFantasmas[i].setScale({TAMANHO_BLOCO / texF1.getSize().x, TAMANHO_BLOCO / texF1.getSize().y});
    }

    while (window.isOpen()) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();
            
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) window.close();
                
                if (estadoAtual == JOGANDO) {
                    if (keyPressed->scancode == sf::Keyboard::Scancode::Left) pacman.proxima_direcao = ESQUERDA;
                    if (keyPressed->scancode == sf::Keyboard::Scancode::Right) pacman.proxima_direcao = DIREITA;
                    if (keyPressed->scancode == sf::Keyboard::Scancode::Up) pacman.proxima_direcao = CIMA;
                    if (keyPressed->scancode == sf::Keyboard::Scancode::Down) pacman.proxima_direcao = BAIXO;
                }
            }

            if (event->is<sf::Event::MouseButtonPressed>()) {
                if (estadoAtual == MENU) {
                    if (btnIniciar.getGlobalBounds().contains({static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
                        reiniciarJogo();
                        estadoAtual = JOGANDO;
                    }
                }
                else if (estadoAtual == GAME_OVER) {
                    if (btnReiniciar.getGlobalBounds().contains({static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
                        reiniciarJogo();
                        estadoAtual = JOGANDO;
                    }
                }
            }
        }

        if (estadoAtual == JOGANDO) {
            if (modoAssustado && relogioPoder.getElapsedTime().asSeconds() > DURACAO_PODER) {
                modoAssustado = false;
            }

            if (pacman.direcao == NENHUMA) { indiceAnimacao = 0; } 
            else {
                if (relogioAnimacao.getElapsedTime().asSeconds() > 0.04f) {
                    indiceAnimacao = (indiceAnimacao + 1) % 8;
                    relogioAnimacao.restart();
                }
            }

            int frameParaCortar = sequenciaFrames[indiceAnimacao];
            sf::Vector2i posicaoCorte{ static_cast<int>(frameParaCortar * larguraFrameOriginal), 0 };
            sf::Vector2i tamanhoCorte{ static_cast<int>(larguraFrameOriginal), static_cast<int>(alturaFrameOriginal) };
            sf::IntRect retanguloCorte{posicaoCorte, tamanhoCorte};

            spritedir.setTextureRect(retanguloCorte); spritecima.setTextureRect(retanguloCorte);
            spritebaixo.setTextureRect(retanguloCorte); spriteesq.setTextureRect(retanguloCorte);

            // --- MOVIMENTO PAC-MAN & TÚNEL DE TELETRANSPORTE ---
            int gridX = static_cast<int>(pacman.x / TAMANHO_BLOCO);
            int gridY = static_cast<int>(pacman.y / TAMANHO_BLOCO);

            if (std::fmod(pacman.x, TAMANHO_BLOCO) == 0 && std::fmod(pacman.y, TAMANHO_BLOCO) == 0) {
                // Teletransporte do Túnel das Laterais
                if (gridX < 0) { pacman.x = 27.f * TAMANHO_BLOCO; gridX = 27; }
                else if (gridX > 27) { pacman.x = 0.f; gridX = 0; }

                if (pacman.proxima_direcao == CIMA && gridY > 0 && mapa[gridY - 1][gridX] != 2) pacman.direcao = CIMA;
                else if (pacman.proxima_direcao == BAIXO && gridY < 32 && mapa[gridY + 1][gridX] != 2) pacman.direcao = BAIXO;
                else if (pacman.proxima_direcao == ESQUERDA && (gridX == 0 || mapa[gridY][gridX - 1] != 2)) pacman.direcao = ESQUERDA;
                else if (pacman.proxima_direcao == DIREITA && (gridX == 27 || mapa[gridY][gridX + 1] != 2)) pacman.direcao = DIREITA;

                if (pacman.direcao == CIMA && gridY > 0 && mapa[gridY - 1][gridX] == 2) pacman.direcao = NENHUMA;
                if (pacman.direcao == BAIXO && gridY < 32 && mapa[gridY + 1][gridX] == 2) pacman.direcao = NENHUMA;
                if (pacman.direcao == ESQUERDA && gridX > 0 && mapa[gridY][gridX - 1] == 2) pacman.direcao = NENHUMA;
                if (pacman.direcao == DIREITA && gridX < 27 && mapa[gridY][gridX + 1] == 2) pacman.direcao = NENHUMA;
            }

            if (pacman.direcao == CIMA) { pacman.y -= VELOCIDADE; olhacima = true; olhabaixo = false; olhadireita = false; olhaesquerda = false; }
            else if (pacman.direcao == BAIXO) { pacman.y += VELOCIDADE; olhabaixo = true; olhacima = false; olhadireita = false; olhaesquerda = false; }
            else if (pacman.direcao == ESQUERDA) { pacman.x -= VELOCIDADE; olhaesquerda = true; olhadireita = false; olhacima = false; olhabaixo = false; }
            else if (pacman.direcao == DIREITA) { pacman.x += VELOCIDADE; olhadireita = true; olhacima = false; olhabaixo = false; olhaesquerda = false; }

            gridX = static_cast<int>((pacman.x + 16.f) / TAMANHO_BLOCO);
            gridY = static_cast<int>((pacman.y + 16.f) / TAMANHO_BLOCO);

            // Garante que o índice fique dentro do mapa dinâmico para pontuação
            if (gridX >= 0 && gridX < 28 && gridY >= 0 && gridY < 33) {
                if (mapa[gridY][gridX] == 1) { 
                    score += 10; mapa[gridY][gridX] = 0;
                } else if (mapa[gridY][gridX] == 3) { 
                    score += 50; mapa[gridY][gridX] = 0;
                    modoAssustado = true; relogioPoder.restart();
                }
            }

            // --- IA DOS FANTASMAS AJUSTADA ---
            int pGridX = static_cast<int>(pacman.x / TAMANHO_BLOCO);
            int pGridY = static_cast<int>(pacman.y / TAMANHO_BLOCO);

            for (int i = 0; i < 4; i++) {
                float velocidadeAtual = modoAssustado ? (VELOCIDADE * 0.4f) : (VELOCIDADE * 0.75f);
                if (fantasmas[i].morto) velocidadeAtual = VELOCIDADE * 1.5f;

                float restoX = std::fmod(fantasmas[i].x, TAMANHO_BLOCO);
                float restoY = std::fmod(fantasmas[i].y, TAMANHO_BLOCO);

                if (restoX < velocidadeAtual && restoY < velocidadeAtual) {
                    fantasmas[i].x -= restoX; fantasmas[i].y -= restoY;
                    int fGridX = static_cast<int>(fantasmas[i].x / TAMANHO_BLOCO);
                    int fGridY = static_cast<int>(fantasmas[i].y / TAMANHO_BLOCO);

                    // Teletransporte do fantasma no túnel lateral
                    if (fGridX < 0) { fantasmas[i].x = 27.f * TAMANHO_BLOCO; fGridX = 27; }
                    else if (fGridX > 27) { fantasmas[i].x = 0.f; fGridX = 0; }

                    // Se ele acabou de voltar morto para a base, revive
                    if (fantasmas[i].morto && fGridX >= 13 && fGridX <= 14 && fGridY == 14) {
                        fantasmas[i].morto = false;
                        fantasmas[i].saiuDaCasa = false; // Precisa realizar o processo de saída novamente
                    }

                    float alvoX = pGridX; float alvoY = pGridY;

                    // LOGICA DE SAÍDA DA CASINHA: Se não saiu ainda, o alvo vira a porta da casa (Linha 11, Coluna 14)
                    if (!fantasmas[i].saiuDaCasa && !fantasmas[i].morto) {
                        alvoX = 14; alvoY = 11;
                        if (fGridY == 11) {
                            fantasmas[i].saiuDaCasa = true; // Saiu oficialmente para o labirinto!
                        }
                    } 
                    else if (fantasmas[i].morto) { 
                        alvoX = 14; alvoY = 14; // Alvo é o interior da casinha
                    } 
                    else if (modoAssustado) { 
                        alvoX = rand() % 28; alvoY = rand() % 33;
                    } 
                    else { 
                        // Personalidades Normais fora da casinha
                        if (fantasmas[i].tipo == 1) { 
                            if (pacman.direcao == CIMA) alvoY -= 4; else if (pacman.direcao == BAIXO) alvoY += 4;
                            else if (pacman.direcao == ESQUERDA) alvoX -= 4; else if (pacman.direcao == DIREITA) alvoX += 4;
                        } else if (fantasmas[i].tipo == 2) { 
                            int bGridX = static_cast<int>(fantasmas[0].x / TAMANHO_BLOCO);
                            int bGridY = static_cast<int>(fantasmas[0].y / TAMANHO_BLOCO);
                            alvoX = bGridX + 2 * (pGridX - bGridX); alvoY = bGridY + 2 * (pGridY - bGridY);
                        } else if (fantasmas[i].tipo == 3) { 
                            if (calcularDistancia(fGridX, fGridY, pGridX, pGridY) < 8.f) { alvoX = 0; alvoY = 32; }
                        }
                    }

                    Direcao direcoesPossiveis[4] = {CIMA, BAIXO, ESQUERDA, DIREITA};
                    Direcao melhorDirecao = fantasmas[i].direcao;
                    float menorDistancia = 999999.f;
                    Direcao proibida = obterOposto(fantasmas[i].direcao);

                    for (Direcao d : direcoesPossiveis) {
                        if (d == proibida && fantasmas[i].direcao != NENHUMA) continue;
                        int pX = fGridX + (d == DIREITA) - (d == ESQUERDA);
                        int pY = fGridY + (d == BAIXO) - (d == CIMA);

                        // Impede falhas de limites fora do labirinto (como dentro dos túneis)
                        if (pY >= 0 && pY < 33) {
                            if (pX < 0 || pX >= 28 || mapa[pY][pX] != 2) { 
                                float d_centro = calcularDistancia(pX, pY, alvoX, alvoY);
                                if (d_centro < menorDistancia) { menorDistancia = d_centro; melhorDirecao = d; }
                            }
                        }
                    }
                    fantasmas[i].direcao = melhorDirecao;
                }

                if (fantasmas[i].direcao == CIMA) fantasmas[i].y -= velocidadeAtual;
                else if (fantasmas[i].direcao == BAIXO) fantasmas[i].y += velocidadeAtual;
                else if (fantasmas[i].direcao == ESQUERDA) fantasmas[i].x -= velocidadeAtual;
                else if (fantasmas[i].direcao == DIREITA) fantasmas[i].x += velocidadeAtual;

                // --- SISTEMA DE DANO & COLISÕES ---
                if (calcularDistancia(pacman.x, pacman.y, fantasmas[i].x, fantasmas[i].y) < 20.f) {
                    if (modoAssustado && !fantasmas[i].morto) {
                        fantasmas[i].morto = true;
                        score += 200;
                    } else if (!modoAssustado && !fantasmas[i].morto) {
                        estadoAtual = GAME_OVER;
                    }
                }
            }
        }

        // --- RENDERIZAÇÃO ---
        window.clear(sf::Color::Black);

        if (estadoAtual == MENU) {
            window.draw(txtTitulo);
            window.draw(btnIniciar);
            window.draw(txtIniciar);
        } 
        else if (estadoAtual == JOGANDO || estadoAtual == GAME_OVER) {
            for (int i = 0; i < 33; i++) {
                for (int j = 0; j < 28; j++) {
                    if (mapa[i][j] == 2) {
                        quad.setPosition({j * TAMANHO_BLOCO, i * TAMANHO_BLOCO});
                        window.draw(quad);
                    } else if (mapa[i][j] == 1) {
                        circle.setPosition({j * TAMANHO_BLOCO + 12.f, i * TAMANHO_BLOCO + 12.f});
                        window.draw(circle);
                    } else if (mapa[i][j] == 3) {
                        bigCircle.setPosition({j * TAMANHO_BLOCO + 8.f, i * TAMANHO_BLOCO + 8.f});
                        window.draw(bigCircle);
                    }
                }
            }

            float compX = pacman.x + 16.f; float compY = pacman.y + 16.f;
            if (olhadireita) { spritedir.setPosition({compX, compY}); window.draw(spritedir); }
            else if (olhabaixo) { spritebaixo.setPosition({compX, compY}); window.draw(spritebaixo); }
            else if (olhaesquerda) { spriteesq.setPosition({compX, compY}); window.draw(spriteesq); }
            else if (olhacima) { spritecima.setPosition({compX, compY}); window.draw(spritecima); }

            for (int i = 0; i < 4; i++) {
                spritesFantasmas[i].setPosition({fantasmas[i].x, fantasmas[i].y});
                if (fantasmas[i].morto) {
                    spritesFantasmas[i].setColor(sf::Color(255, 255, 255, 80)); 
                } else if (modoAssustado) {
                    spritesFantasmas[i].setColor(sf::Color::Blue); 
                } else {
                    spritesFantasmas[i].setColor(sf::Color::White); 
                }
                window.draw(spritesFantasmas[i]);
            }

            texto.setString("Score: " + std::to_string(score));
            window.draw(texto);

            if (estadoAtual == GAME_OVER) {
                sf::RectangleShape overlay({static_cast<float>(larguraJanela), static_cast<float>(alturaJanela)});
                overlay.setFillColor(sf::Color(0, 0, 0, 200)); 
                window.draw(overlay);

                window.draw(txtGameOver);
                window.draw(btnReiniciar);
                window.draw(txtReiniciar);
            }
        }

        window.display();
    }

    return 0;
}