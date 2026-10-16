#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <optional>
#include <cmath>
#include <fstream>
#include <string>
#include <queue>
#include <array>
#include <algorithm>

// g++ mygame.cpp -o pacman -std=c++20 -lsfml-graphics -lsfml-window -lsfml-system && ./pacman

int mapa[33][28] = {
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
    {2,2,2,2,2,2,1,2,2,2,2,2,0,2,2,0,2,2,2,2,2,1,2,2,2,2,2,2},
    {2,2,2,2,2,2,1,2,2,1,1,1,1,1,1,1,1,1,1,2,2,1,2,2,2,2,2,2},
    {2,2,2,2,2,2,1,2,2,1,2,2,2,0,0,2,2,2,1,2,2,1,2,2,2,2,2,2},
    {2,2,2,2,2,2,1,2,2,1,2,0,0,0,0,0,0,2,1,2,2,1,2,2,2,2,2,2},
    {0,0,0,0,0,0,1,1,1,1,2,0,0,0,0,0,0,2,1,1,1,1,1,0,0,0,0,0},
    {2,2,2,2,2,2,1,2,2,1,2,0,0,0,0,0,0,2,1,2,2,1,2,2,2,2,2,2},
    {2,2,2,2,2,2,1,2,2,1,2,2,2,2,2,2,2,2,1,2,2,1,2,2,2,2,2,2},
    {2,2,2,2,2,2,1,2,2,1,1,1,1,1,1,1,1,1,1,2,2,1,2,2,2,2,2,2},
    {2,2,2,2,2,2,1,2,2,1,2,2,2,2,2,2,2,2,1,2,2,1,2,2,2,2,2,2},
    {2,2,2,2,2,2,1,2,2,1,2,2,2,2,2,2,2,2,1,2,2,1,2,2,2,2,2,2},
    {2,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,2},
    {2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2},
    {2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2},
    {2,3,1,1,2,2,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,2,2,1,1,3,2},
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
int mapaOriginal[33][28];

enum Direcao { NENHUMA, CIMA, BAIXO, ESQUERDA, DIREITA };
enum ESTADO  { MENU, JOGANDO, GAMEOVER };

struct Pacman {
    int x = 13, y = 23;
    Direcao direcao = NENHUMA, proxima_direcao = NENHUMA;
};

struct Fantasma {
    int x, y;
    Direcao direcao = NENHUMA;
    bool assustado = false;
    int cor = 0; // 0=Blinky(Vermelho), 1=Pinky(Rosa), 2=Inky(Ciano), 3=Clyde(Laranja)
};

Pacman pacman;
Fantasma fantasmas[4] = {
    {13, 11, NENHUMA, false, 0},
    {14, 11, NENHUMA, false, 1},
    {13, 13, NENHUMA, false, 2},
    {14, 13, NENHUMA, false, 3}
};

int carregarRecorde() {
    std::ifstream f("recorde.txt"); int r = 0;
    if (f.is_open()) f >> r; return r;
}
void salvarRecorde(int r) {
    std::ofstream f("recorde.txt");
    if (f.is_open()) f << r;
}

// Retorna a direção ideal para alcançar o Alvo (tx, ty) sem poder voltar para trás
Direcao obterMelhorDirecao(int sx, int sy, int tx, int ty, Direcao dirAtual) {
    Direcao oposta = NENHUMA;
    if (dirAtual == CIMA) oposta = BAIXO;
    if (dirAtual == BAIXO) oposta = CIMA;
    if (dirAtual == ESQUERDA) oposta = DIREITA;
    if (dirAtual == DIREITA) oposta = ESQUERDA;

    Direcao melhorDir = NENHUMA;
    double menorDistancia = 1e9;

    std::pair<Direcao, std::pair<int, int>> movimentos[4] = {
        {CIMA, {0, -1}}, {ESQUERDA, {-1, 0}}, {BAIXO, {0, 1}}, {DIREITA, {1, 0}}
    };

    for (const auto& mov : movimentos) {
        if (mov.first == oposta) continue; // Proibido dar meia-volta no clássico

        int nx = sx + mov.second.first;
        int ny = sy + mov.second.second;

        if (nx >= 0 && nx < 28 && ny >= 0 && ny < 33) {
            if (mapa[ny][nx] != 2) { // Não é parede
                double dx = nx - tx;
                double dy = ny - ty;
                double dist = dx * dx + dy * dy; // Distância euclidiana ao quadrado
                if (dist < menorDistancia) {
                    menorDistancia = dist;
                    melhorDir = mov.first;
                }
            }
        }
    }
    return melhorDir;
}

void centralizarTexto(sf::Text& t, float cx, float y) {
    sf::FloatRect b = t.getLocalBounds();
    t.setPosition({cx - b.size.x / 2.f - b.position.x, y});
}

void desenharBotao(sf::RenderWindow& w, sf::RectangleShape& btn, sf::Text& txt) {
    w.draw(btn);
    sf::FloatRect b = txt.getLocalBounds();
    txt.setPosition({
        btn.getPosition().x + (btn.getSize().x - b.size.x) / 2.f - b.position.x,
        btn.getPosition().y + (btn.getSize().y - b.size.y) / 2.f - b.position.y
    });
    w.draw(txt);
}

void desenharPacman(sf::RenderWindow& win, float px, float py, Direcao dir, float bocaAngle) {
    const float R = 14.f;
    const float CX = px + 16.f, CY = py + 16.f;
    const int SEG = 30;

    float rot = 0.f;
    if (dir == CIMA)      rot = -90.f;
    if (dir == BAIXO)     rot =  90.f;
    if (dir == ESQUERDA) rot = 180.f;

    float bocaRad = bocaAngle * 3.14159f / 180.f;

    sf::ConvexShape fatia;
    fatia.setPointCount(SEG + 2);
    fatia.setFillColor(sf::Color(255, 235, 0));

    fatia.setPoint(0, {0, 0});
    for (int i = 0; i <= SEG; i++) {
        float ang = (bocaRad + (2.f * 3.14159f - 2.f * bocaRad) * i / SEG);
        float rotRad = rot * 3.14159f / 180.f;
        float rx = std::cos(ang) * std::cos(rotRad) - std::sin(ang) * std::sin(rotRad);
        float ry = std::cos(ang) * std::sin(rotRad) + std::sin(ang) * std::cos(rotRad);
        fatia.setPoint(i + 1, {rx * R, ry * R});
    }
    fatia.setPosition({CX, CY});
    win.draw(fatia);

    sf::CircleShape olho(2.5f);
    olho.setFillColor(sf::Color::Black);
    float olhoAng = (rot - 70.f) * 3.14159f / 180.f;
    olho.setPosition({CX + std::cos(olhoAng) * 8.f - 2.5f, CY + std::sin(olhoAng) * 8.f - 2.5f});
    win.draw(olho);
}

void desenharFantasma(sf::RenderWindow& win, float px, float py, int cor, bool assustado, float t) {
    const float CX = px + 16.f, CY = py + 14.f, R = 14.f;
    const int SEG = 20;

    sf::Color bodyColor;
    if (assustado) {
        bool pisca = (static_cast<int>(t * 5) % 2 == 0);
        bodyColor = pisca ? sf::Color(0, 90, 255) : sf::Color(180, 210, 255);
    } else {
        sf::Color cores[4] = {
            sf::Color(255, 0, 60),     // Blinky - Vermelho
            sf::Color(255, 100, 180),   // Pinky - Rosa
            sf::Color(0, 240, 255),     // Inky - Ciano
            sf::Color(255, 150, 0)      // Clyde - Laranja
        };
        bodyColor = cores[cor % 4];
    }

    sf::ConvexShape topo; topo.setPointCount(SEG + 2);
    topo.setFillColor(bodyColor);
    for (int i = 0; i <= SEG; i++) {
        float a = 3.14159f + 3.14159f * i / SEG;
        topo.setPoint(i, {CX + std::cos(a) * R, CY + std::sin(a) * R});
    }
    topo.setPoint(SEG + 1, {CX + R, CY});
    win.draw(topo);

    sf::RectangleShape corpo({R * 2.f, 12.f});
    corpo.setFillColor(bodyColor);
    corpo.setPosition({CX - R, CY});
    win.draw(corpo);

    const int DENTES = 4;
    float base = CY + 12.f;
    sf::ConvexShape saia; saia.setPointCount(DENTES * 2 + 2);
    saia.setFillColor(bodyColor);
    saia.setPoint(0, {CX - R, base});
    float passo = R * 2.f / DENTES;
    for (int i = 0; i < DENTES; i++) {
        float xL = CX - R + passo * i;
        float xR = CX - R + passo * (i + 0.5f);
        saia.setPoint(i * 2 + 1, {xL, base});
        saia.setPoint(i * 2 + 2, {xR, base + 5.f});
    }
    saia.setPoint(DENTES * 2 + 1, {CX + R, base});
    win.draw(saia);

    auto desenhaOlho = [&](float ox, float oy) {
        sf::CircleShape branco(4.5f); branco.setFillColor(sf::Color::White);
        branco.setPosition({ox - 4.5f, oy - 4.5f}); win.draw(branco);
        if (!assustado) {
            sf::CircleShape pupila(2.f); pupila.setFillColor(sf::Color(0, 0, 200));
            pupila.setPosition({ox - 2.f, oy - 2.f}); win.draw(pupila);
        } else {
            for (int s = -1; s <= 1; s += 2) {
                sf::RectangleShape rx({6.f, 1.5f});
                rx.setFillColor(sf::Color(255, 50, 50));
                rx.setRotation(sf::degrees(45.f * s));
                rx.setOrigin({3.0f, 0.75f});
                rx.setPosition({ox, oy}); win.draw(rx);
            }
        }
    };
    desenhaOlho(CX - 5.f, CY - 4.f);
    desenhaOlho(CX+5.f, CY-4.f);
}

void resetarJogo(int& score, bool& novoRecorde, sf::Text& textoScore) {
    pacman = {13, 23, NENHUMA, NENHUMA};
    fantasmas[0] = {13, 11, NENHUMA, false, 0};
    fantasmas[1] = {14, 11, NENHUMA, false, 1};
    fantasmas[2] = {13, 13, NENHUMA, false, 2};
    fantasmas[3] = {14, 13, NENHUMA, false, 3};
    for (int i = 0; i < 33; i++) for (int j = 0; j < 28; j++) mapa[i][j] = mapaOriginal[i][j];
    score = 0; novoRecorde = false;
    textoScore.setString("Score: 0");
}

int main() {
    for (int i = 0; i < 33; i++) for (int j = 0; j < 28; j++) mapaOriginal[i][j] = mapa[i][j];

    const float TB = 32.f;
    const unsigned int LJ = static_cast<unsigned int>(28 * TB);
    const unsigned int AJ = static_cast<unsigned int>(33 * TB);
    const float CX = LJ / 2.f;

    ESTADO estado = MENU;

    sf::RenderWindow window(sf::VideoMode({LJ, AJ}), "Pac-Man Neon Arcade");
    window.setFramerateLimit(60);

    sf::Font fonte;
    if (!fonte.openFromFile("retrofonte.ttf")) { std::cout << "Sem fonte retrofonte.ttf!\n"; return 0; }

    sf::RectangleShape quad({TB - 4.f, TB - 4.f});
    quad.setOutlineThickness(2.f);
    quad.setOutlineColor(sf::Color(0, 120, 255));
    quad.setFillColor(sf::Color(0, 15, 45));

    sf::CircleShape pastilha(3.f);
    pastilha.setFillColor(sf::Color(255, 185, 120));

    sf::CircleShape pPoder(7.f);
    pPoder.setFillColor(sf::Color(0, 255, 160));

    sf::Text textoScore(fonte);
    textoScore.setCharacterSize(20);
    textoScore.setFillColor(sf::Color::White);
    textoScore.setPosition({10.f, 5.f});
    textoScore.setString("Score: 0");

    const float PW = LJ - 80.f;
    sf::RectangleShape painelMenu({PW, 430.f});
    painelMenu.setFillColor(sf::Color(3, 5, 20, 230));
    painelMenu.setOutlineThickness(3.f);
    painelMenu.setOutlineColor(sf::Color(0, 255, 255));
    painelMenu.setPosition({40.f, AJ / 2.f - 215.f});

    sf::Text titMenu(fonte); titMenu.setCharacterSize(64);
    titMenu.setFillColor(sf::Color(255, 235, 0)); titMenu.setString("PAC-MAN");

    sf::Text subMenu(fonte); subMenu.setCharacterSize(16);
    subMenu.setFillColor(sf::Color(140, 160, 190));
    subMenu.setString("Setas: mover    ESC: sair    R: menu");

    sf::Text recMenu(fonte); recMenu.setCharacterSize(22);
    recMenu.setFillColor(sf::Color(0, 255, 150));

    sf::RectangleShape btnIniciar({240.f, 55.f});
    btnIniciar.setFillColor(sf::Color(0, 255, 255));
    sf::Text txtIniciar(fonte); txtIniciar.setCharacterSize(22);
    txtIniciar.setFillColor(sf::Color::Black); txtIniciar.setString("INICIAR JOGO");

    sf::RectangleShape painelGO({PW, 420.f});
    painelGO.setFillColor(sf::Color(20, 5, 10, 230));
    painelGO.setOutlineThickness(3.f);
    painelGO.setOutlineColor(sf::Color(255, 0, 60));
    painelGO.setPosition({40.f, AJ / 2.f - 210.f});

    sf::Text titGO(fonte); titGO.setCharacterSize(58);
    titGO.setFillColor(sf::Color(255, 0, 60)); titGO.setString("GAME OVER");

    sf::Text txtPontFinal(fonte); txtPontFinal.setCharacterSize(26);
    txtPontFinal.setFillColor(sf::Color::White);

    sf::Text txtRecGO(fonte); txtRecGO.setCharacterSize(24);
    txtRecGO.setFillColor(sf::Color(0, 255, 150));

    sf::Text txtNovRec(fonte); txtNovRec.setCharacterSize(26);
    txtNovRec.setFillColor(sf::Color(255, 235, 0));
    txtNovRec.setString("*** NOVO RECORDE! ***");

    sf::RectangleShape btnReiniciar({260.f, 55.f});
    btnReiniciar.setFillColor(sf::Color(0, 255, 255));
    sf::Text txtReiniciar(fonte); txtReiniciar.setCharacterSize(22);
    txtReiniciar.setFillColor(sf::Color::Black); txtReiniciar.setString("JOGAR DE NOVO");

    sf::RectangleShape btnMenuGO({260.f, 55.f});
    btnMenuGO.setFillColor(sf::Color(50, 50, 60));
    sf::Text txtMenuGO(fonte); txtMenuGO.setCharacterSize(22);
    txtMenuGO.setFillColor(sf::Color::White); txtMenuGO.setString("MENU PRINCIPAL");

    int score = 0, recorde = carregarRecorde();
    bool novoRecorde = false;

    sf::Clock clockJogo;    
    sf::Clock clockAnim;    
    sf::Clock clockPoder;   
    bool poderAtivo = false;
    float bocaAngle = 0.f, bocaDir = 1.f;

    while (window.isOpen()) {
        float t = clockAnim.getElapsedTime().asSeconds();

        while (const std::optional ev = window.pollEvent()) {
            if (ev->is<sf::Event::Closed>()) window.close();

            else if (estado == MENU) {
                if (const auto* mp = ev->getIf<sf::Event::MouseButtonPressed>()) {
                    if (mp->button == sf::Mouse::Button::Left) {
                        sf::Vector2f pos = sf::Vector2f(mp->position);
                        if (btnIniciar.getGlobalBounds().contains(pos)) estado = JOGANDO;
                    }
                }
                if (const auto* kp = ev->getIf<sf::Event::KeyPressed>()) {
                    if (kp->scancode == sf::Keyboard::Scancode::Enter) estado = JOGANDO;
                }
            }

            else if (estado == GAMEOVER) {
                if (const auto* mp = ev->getIf<sf::Event::MouseButtonPressed>()) {
                    if (mp->button == sf::Mouse::Button::Left) {
                        sf::Vector2f pos = sf::Vector2f(mp->position);
                        if (btnReiniciar.getGlobalBounds().contains(pos)) {
                            resetarJogo(score, novoRecorde, textoScore);
                            poderAtivo = false; estado = JOGANDO;
                        } else if (btnMenuGO.getGlobalBounds().contains(pos)) {
                            resetarJogo(score, novoRecorde, textoScore);
                            poderAtivo = false; estado = MENU;
                        }
                    }
                }
            }

            else if (estado == JOGANDO) {
                if (const auto* kp = ev->getIf<sf::Event::KeyPressed>()) {
                    if (kp->scancode == sf::Keyboard::Scancode::Escape) window.close();
                    else if (kp->scancode == sf::Keyboard::Scancode::Left)  pacman.proxima_direcao = ESQUERDA;
                    else if (kp->scancode == sf::Keyboard::Scancode::Right) pacman.proxima_direcao = DIREITA;
                    else if (kp->scancode == sf::Keyboard::Scancode::Up)    pacman.proxima_direcao = CIMA;
                    else if (kp->scancode == sf::Keyboard::Scancode::Down)  pacman.proxima_direcao = BAIXO;
                    else if (kp->scancode == sf::Keyboard::Scancode::R)     estado = MENU;
                }
            }
        }

        if (estado == JOGANDO && clockJogo.getElapsedTime() > sf::seconds(0.15f)) {
            clockJogo.restart();

            bocaAngle += bocaDir * 15.f;
            if (bocaAngle >= 40.f) { bocaAngle = 40.f; bocaDir = -1.f; }
            if (bocaAngle <= 2.f) { bocaAngle = 2.f; bocaDir = 1.f; }

            if (poderAtivo && clockPoder.getElapsedTime() > sf::seconds(8.f)) {
                poderAtivo = false;
                for (auto& f : fantasmas) f.assustado = false;
            }

            auto podeIr = [](int nx, int ny) -> bool {
                if (ny < 0 || ny > 32 || nx < 0 || nx > 27) return false;
                return mapa[ny][nx] != 2;
            };

            // Processa a intenção de curva imediatamente
            if (pacman.proxima_direcao == CIMA && podeIr(pacman.x, pacman.y - 1)) pacman.direcao = CIMA;
            if (pacman.proxima_direcao == BAIXO && podeIr(pacman.x, pacman.y + 1)) pacman.direcao = BAIXO;
            if (pacman.proxima_direcao == ESQUERDA && podeIr(pacman.x - 1 < 0 ? 27 : pacman.x - 1, pacman.y)) pacman.direcao = ESQUERDA;
            if (pacman.proxima_direcao == DIREITA && podeIr(pacman.x + 1 > 27 ? 0 : pacman.x + 1, pacman.y)) pacman.direcao = DIREITA;

            // Movimentação mecânica contínua
            if (pacman.direcao == CIMA) {
                if (podeIr(pacman.x, pacman.y - 1)) pacman.y--; else pacman.direcao = NENHUMA;
            } else if (pacman.direcao == BAIXO) {
                if (podeIr(pacman.x, pacman.y + 1)) pacman.y++; else pacman.direcao = NENHUMA;
            } else if (pacman.direcao == ESQUERDA) {
                if (pacman.x == 0) pacman.x = 27;
                else if (podeIr(pacman.x - 1, pacman.y)) pacman.x--; else pacman.direcao = NENHUMA;
            } else if (pacman.direcao == DIREITA) {
                if (pacman.x == 27) pacman.x = 0;
                else if (podeIr(pacman.x + 1, pacman.y)) pacman.x++; else pacman.direcao = NENHUMA;
            }

            // CRÍTICO: Detecção e consumo imediato de pastilhas
            if (mapa[pacman.y][pacman.x] == 1) {
                score += 10; mapa[pacman.y][pacman.x] = 0;
                textoScore.setString("Score: " + std::to_string(score));
            } else if (mapa[pacman.y][pacman.x] == 3) {
                score += 50; mapa[pacman.y][pacman.x] = 0;
                textoScore.setString("Score: " + std::to_string(score));
                poderAtivo = true; clockPoder.restart();
                for (auto& f : fantasmas) f.assustado = true;
            }

            // --- INTELIGÊNCIA ARTIFICIAL INDIVIDUAL DOS FANTASMAS (ARCADE LÓGICA) ---
            for (int i = 0; i < 4; i++) {
                auto& f = fantasmas[i];
                int targetX = pacman.x;
                int targetY = pacman.y;

                if (f.assustado) {
                    // Modo assustado: escolhem direções aleatórias nas bifurcações
                    Direcao validas[4]; int qtd = 0;
                    if (podeIr(f.x, f.y - 1) && f.direcao != BAIXO) validas[qtd++] = CIMA;
                    if (podeIr(f.x, f.y + 1) && f.direcao != CIMA) validas[qtd++] = BAIXO;
                    if (podeIr(f.x - 1, f.y) && f.direcao != DIREITA) validas[qtd++] = ESQUERDA;
                    if (podeIr(f.x + 1, f.y) && f.direcao != ESQUERDA) validas[qtd++] = DIREITA;
                    
                    if (qtd > 0) f.direcao = validas[rand() % qtd];
                } else {
                    // Comportamentos normais e únicos
                    if (f.cor == 0) { 
                        // Blinky (Vermelho): Persegue o Pac-man diretamente
                        targetX = pacman.x; targetY = pacman.y;
                    } 
                    else if (f.cor == 1) { 
                        // Pinky (Rosa): Tenta interceptar 4 espaços à frente
                        if (pacman.direcao == CIMA) { targetY = pacman.y - 4; targetX = pacman.x - 4; } // Bug clássico emulado
                        else if (pacman.direcao == BAIXO) targetY = pacman.y + 4;
                        else if (pacman.direcao == ESQUERDA) targetX = pacman.x - 4;
                        else if (pacman.direcao == DIREITA) targetX = pacman.x + 4;
                    } 
                    else if (f.cor == 2) { 
                        // Inky (Ciano): Vetor baseado no Blinky e no Pac-Man
                        int bX = fantasmas[0].x;
                        int bY = fantasmas[0].y;
                        int pX = pacman.x;
                        int pY = pacman.y;
                        if (pacman.direcao == CIMA) { pY -= 2; pX -= 2; }
                        else if (pacman.direcao == BAIXO) pY += 2;
                        else if (pacman.direcao == ESQUERDA) pX -= 2;
                        else if (pacman.direcao == DIREITA) pX += 2;
                        targetX = bX + 2 * (pX - bX);
                        targetY = bY + 2 * (pY - bY);
                    } 
                    else if (f.cor == 3) { 
                        // Clyde (Laranja): Persegue se longe, foge para o canto se perto
                        int distQuadrada = (f.x - pacman.x) * (f.x - pacman.x) + (f.y - pacman.y) * (f.y - pacman.y);
                        if (distQuadrada > 64) { // Mais de 8 blocos de distância
                            targetX = pacman.x; targetY = pacman.y;
                        } else { // Perto demais: vai pro canto inferior esquerdo
                            targetX = 0; targetY = 32;
                        }
                    }
                    
                    Direcao proxima = obterMelhorDirecao(f.x, f.y, targetX, targetY, f.direcao);
                    if (proxima != NENHUMA) f.direcao = proxima;
                }

                // Efetua a movimentação do fantasma
                if (f.direcao == CIMA && podeIr(f.x, f.y - 1)) f.y--;
                else if (f.direcao == BAIXO && podeIr(f.x, f.y + 1)) f.y++;
                else if (f.direcao == ESQUERDA) {
                    if (f.x == 0) f.x = 27;
                    else if (podeIr(f.x - 1, f.y)) f.x--;
                } else if (f.direcao == DIREITA) {
                    if (f.x == 27) f.x = 0;
                    else if (podeIr(f.x + 1, f.y)) f.x++;
                }

                // Verificação precisa de Game Over ou Comer Fantasma
                if (f.x == pacman.x && f.y == pacman.y) {
                    if (f.assustado) {
                        score += 200; textoScore.setString("Score: " + std::to_string(score));
                        f.x = 13 + (i % 2); f.y = 11; f.assustado = false; f.direcao = NENHUMA;
                    } else {
                        if (score > recorde) { recorde = score; salvarRecorde(recorde); novoRecorde = true; }
                        estado = GAMEOVER;
                    }
                }
            }
        }

        // --- RENDERIZAÇÃO GRÁFICA ---
        window.clear(sf::Color(4, 4, 15));

        if (estado == MENU) {
            for (int i = 0; i < 33; i++) for (int j = 0; j < 28; j++) {
                if (mapaOriginal[i][j] == 2) {
                    quad.setPosition({j * TB + 2.f, i * TB + 2.f});
                    quad.setOutlineColor(sf::Color(0, 60, 150, 70));
                    quad.setFillColor(sf::Color(0, 10, 25, 40));
                    window.draw(quad);
                }
            }
            window.draw(painelMenu);

            float pulso = 0.5f + 0.5f * std::sin(t * 3.f);
            titMenu.setFillColor(sf::Color(255, static_cast<uint8_t>(200 + 55 * pulso), 0));
            centralizarTexto(titMenu, CX, painelMenu.getPosition().y + 25.f);
            window.draw(titMenu);

            centralizarTexto(subMenu, CX, painelMenu.getPosition().y + 120.f);
            window.draw(subMenu);

            recMenu.setString("RECORD: " + std::to_string(recorde));
            centralizarTexto(recMenu, CX, painelMenu.getPosition().y + 170.f);
            window.draw(recMenu);

            btnIniciar.setPosition({CX - 120.f, painelMenu.getPosition().y + 240.f});
            sf::Vector2f mouse = sf::Vector2f(sf::Mouse::getPosition(window));
            btnIniciar.setFillColor(btnIniciar.getGlobalBounds().contains(mouse) ? sf::Color(0, 255, 180) : sf::Color(0, 255, 255));
            desenharBotao(window, btnIniciar, txtIniciar);

            for (int i = 0; i < 4; i++) {
                float xF = 60.f + (PW / 4.f) * i + (PW / 4.f) / 2.f - 16.f;
                float yF = painelMenu.getPosition().y + 345.f + 5.f * std::sin(t * 3.f + i * 1.2f);
                desenharFantasma(window, xF, yF, i, false, t);
            }
        } 
        else if (estado == JOGANDO) {
            quad.setOutlineColor(sf::Color(0, 120, 255));
            quad.setFillColor(sf::Color(0, 15, 45));
            for (int i = 0; i < 33; i++) for (int j = 0; j < 28; j++) {
                if (mapa[i][j] == 2) {
                    quad.setPosition({j * TB + 2.f, i * TB + 2.f}); window.draw(quad);
                } else if (mapa[i][j] == 1) {
                    pastilha.setPosition({j * TB + (TB / 2.f - 3.f), i * TB + (TB / 2.f - 3.f)}); window.draw(pastilha);
                } else if (mapa[i][j] == 3) {
                    if (static_cast<int>(t * 4) % 2 == 0) {
                        pPoder.setPosition({j * TB + (TB / 2.f - 7.f), i * TB + (TB / 2.f - 7.f)}); window.draw(pPoder);
                    }
                }
            }

            desenharPacman(window, pacman.x * TB, pacman.y * TB, pacman.direcao, bocaAngle);

            for (int i = 0; i < 4; i++) {
                desenharFantasma(window, fantasmas[i].x * TB, fantasmas[i].y * TB, fantasmas[i].cor, fantasmas[i].assustado, t);
            }

            window.draw(textoScore);
            sf::Text recHUD(fonte); recHUD.setCharacterSize(20);
            recHUD.setFillColor(sf::Color(0, 255, 150));
            recHUD.setString("RECORD: " + std::to_string(recorde));
            sf::FloatRect b = recHUD.getLocalBounds();
            recHUD.setPosition({LJ - b.size.x - b.position.x - 10.f, 5.f});
            window.draw(recHUD);

            if (poderAtivo) {
                float restante = 8.f - clockPoder.getElapsedTime().asSeconds();
                sf::Text tp(fonte); tp.setCharacterSize(18);
                tp.setFillColor(sf::Color(0, 255, 255));
                tp.setString("POWER TIME: " + std::to_string((int)restante + 1) + "s");
                centralizarTexto(tp, CX, 5.f);
                window.draw(tp);
            }
        } 
        else if (estado == GAMEOVER) {
            for (int i = 0; i < 33; i++) for (int j = 0; j < 28; j++) {
                if (mapaOriginal[i][j] == 2) {
                    quad.setPosition({j * TB + 2.f, i * TB + 2.f});
                    quad.setOutlineColor(sf::Color(150, 0, 40, 60));
                    quad.setFillColor(sf::Color(25, 0, 5, 40));
                    window.draw(quad);
                }
            }
            window.draw(painelGO);

            float pulso = 0.5f + 0.5f * std::sin(t * 4.f);
            titGO.setFillColor(sf::Color(static_cast<uint8_t>(180 + 75 * pulso), 15, 40));
            centralizarTexto(titGO, CX, painelGO.getPosition().y + 20.f);
            window.draw(titGO);

            txtPontFinal.setString("SCORE: " + std::to_string(score));
            centralizarTexto(txtPontFinal, CX, painelGO.getPosition().y + 110.f);
            window.draw(txtPontFinal);

            txtRecGO.setString("BEST RECORD: " + std::to_string(recorde));
            centralizarTexto(txtRecGO, CX, painelGO.getPosition().y + 155.f);
            window.draw(txtRecGO);

            if (novoRecorde && static_cast<int>(t * 3) % 2 == 0) {
                centralizarTexto(txtNovRec, CX, painelGO.getPosition().y + 200.f);
                window.draw(txtNovRec);
            }

            float bY = painelGO.getPosition().y + (novoRecorde ? 250.f : 230.f);
            sf::Vector2f mouse = sf::Vector2f(sf::Mouse::getPosition(window));

            btnReiniciar.setPosition({CX - 130.f, bY});
            btnReiniciar.setFillColor(btnReiniciar.getGlobalBounds().contains(mouse) ? sf::Color(0, 255, 180) : sf::Color(0, 255, 255));
            desenharBotao(window, btnReiniciar, txtReiniciar);

            btnMenuGO.setPosition({CX - 130.f, bY + 65.f});
            btnMenuGO.setFillColor(btnMenuGO.getGlobalBounds().contains(mouse) ? sf::Color(90, 90, 100) : sf::Color(50, 50, 60));
            desenharBotao(window, btnMenuGO, txtMenuGO);
        }

        window.display();
    }
    return 0;
}