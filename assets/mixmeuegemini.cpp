#include <SFML/Graphics.hpp>
#include <optional>
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <cmath>
#include <SFML/Audio.hpp>

using namespace std;

// Definições de Direções
enum Direcao { DIREITA, ESQUERDA, CIMA, BAIXO, NENHUMA };
// Estados do Jogo
enum EstadoJogo { MENU, JOGANDO, GAMEOVER, VITORIA };
// Estados dos Fantasmas
enum EstadoFantasma { PRESO, SAINDO, LIVRE, ASSUSTADO };

// Estrutura para ordenar caminhos do caçador/emboscador
struct caminhos {
    Direcao direcao;
    float distancia;
};

bool comparadistancias(caminhos a, caminhos b) {
    return a.distancia < b.distancia;
}

// Estrutura do Jogador
struct Jogador {
    int posx, posy;
    Direcao direcaoatual;
    Direcao proximadirecao;
    sf::Clock animacao;
    bool abre;
};

// Estrutura dos Fantasmas
struct Fantasma {
    int posx, posy;
    Direcao direcaoatual;
    EstadoFantasma estadoatual;
    sf::Clock relogio;
    sf::Color corOriginal;
};

// Configurações do Mapa (33 linhas por 28 colunas)
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

int main() {
    // Dimensões baseadas na sua escala de bloco de 32 pixels
    sf::RenderWindow window(sf::VideoMode({28 * 32, 33 * 32 + 80}), "Pac-Man - MyGame");
    window.setFramerateLimit(60);

    // Estado Inicial do Jogo
    EstadoJogo estadoatual = MENU;

    // Criando o Personagem e os 4 Fantasmas
    Jogador pacman;
    Fantasma aleatorio;   // Clyde (Laranja)
    Fantasma cacador;     // Blinky (Vermelho)
    Fantasma emboscador; // Pinky (Rosa)
    Fantasma patrulheiro; // Inky (Ciano)

    // Variáveis de Controle do Jogo
    int score = 0;
    int pilulasRestantes = 252; // 248 normais + 4 de força
    int pilulasComidas = 0;
    
    // Variáveis da Pílula de Força e Fruta
    sf::Clock relogioSuperPoder;
    bool pacmanComPoder = false;
    bool frutaAtiva = false;
    sf::Clock relogioFruta;

    // Função de Inicialização/Reinício
    auto ResetarJogo = [&]() {
        score = 0;
        pilulasRestantes = 252;
        pilulasComidas = 0;
        pacmanComPoder = false;
        frutaAtiva = false;

        // Copia o mapa original
        for (int r = 0; r < 33; r++) {
            for (int c = 0; c < 28; c++) {
                mapaatual[r][c] = mapaoriginal[r][c];
            }
        }

        // Posiciona o Pacman
        pacman.posx = 14;
        pacman.posy = 23;
        pacman.direcaoatual = NENHUMA;
        pacman.proximadirecao = NENHUMA;
        pacman.abre = true;

        // Configura Fantasma 1: Aleatório (Laranja)
        aleatorio.posx = 13; aleatorio.posy = 14;
        aleatorio.direcaoatual = NENHUMA; aleatorio.estadoatual = PRESO;
        aleatorio.corOriginal = sf::Color(255, 140, 0); // Laranja

        // Configura Fantasma 2: Caçador (Vermelho)
        cacador.posx = 14; cacador.posy = 14;
        cacador.direcaoatual = NENHUMA; cacador.estadoatual = PRESO;
        cacador.corOriginal = sf::Color::Red;

        // Configura Fantasma 3: Emboscador (Rosa)
        emboscador.posx = 13; emboscador.posy = 13;
        emboscador.direcaoatual = NENHUMA; emboscador.estadoatual = PRESO;
        emboscador.corOriginal = sf::Color(255, 105, 180); // Rosa

        // Configura Fantasma 4: Patrulheiro (Ciano)
        patrulheiro.posx = 14; patrulheiro.posy = 13;
        patrulheiro.direcaoatual = NENHUMA; patrulheiro.estadoatual = PRESO;
        patrulheiro.corOriginal = sf::Color::Cyan;

        aleatorio.relogio.restart();
        cacador.relogio.restart();
        emboscador.relogio.restart();
        patrulheiro.relogio.restart();
    };

    ResetarJogo();

    // Carregamento de Recursos Clássicos (Substitua pelos seus arquivos se necessário)
    sf::Texture texturapacman, texturafantasma;
    if (!texturapacman.loadFromFile("pacman.png")) { /* Tratamento de erro ou placeholder */ }
    if (!texturafantasma.loadFromFile("fantasma.png")) { /* Tratamento de erro ou placeholder */ }

    // Sprites do Pac-man (Boca Aberta direcionada)
    sf::Sprite spritedir(texturapacman), spritecima(texturapacman), spriteesq(texturapacman), spritebaixo(texturapacman), pacmanfechado(texturapacman);
    sf::Sprite spritefantasma(texturafantasma);

    // Fontes e Textos
    sf::Font fonte;
    if (!fonte.openFromFile("arial.ttf")) { std::cout << "Erro ao carregar fonte!\n"; }
    
    sf::Text textscore(fonte), textomenu(fonte), textofim(fonte);
    textscore.setCharacterSize(20); textscore.setFillColor(sf::Color::White);
    textomenu.setCharacterSize(24); textomenu.setFillColor(sf::Color::Yellow);
    textofim.setCharacterSize(24); textofim.setFillColor(sf::Color::Red);

    // Deslocamento vertical para criar o HUD superior
    float OFFSET_Y = 60.f; 
    sf::Clock clockGeral;

    // Loops Auxiliares de Direção Reutilizáveis
    auto moverFandAleatorio = [&](Fantasma &f, float tempoLimite) {
        if (f.estadoatual == PRESO) {
            if (f.relogio.getElapsedTime().asSeconds() >= tempoLimite) f.estadoatual = SAINDO;
            else f.posy = (f.posy == 14) ? 13 : 14;
        } 
        else if (f.estadoatual == SAINDO) {
            if (f.posx < 14) f.posx++;
            else if (f.posx > 14) f.posx--;
            else {
                if (f.posy != 11) f.posy--;
                else { f.estadoatual = LIVRE; f.direcaoatual = NENHUMA; }
            }
        } 
        else if (f.estadoatual == LIVRE || f.estadoatual == ASSUSTADO) {
            float velocidade = (f.estadoatual == ASSUSTADO) ? 0.55f : 0.40f;
            if (f.relogio.getElapsedTime().asSeconds() > velocidade) {
                static random_device rd; static mt19937 gerador(rd());
                uniform_int_distribution<int> distribuicao(1, 4);
                bool mudadirecao = (f.direcaoatual == NENHUMA);
                
                // Checa paredes ao redor
                if (f.direcaoatual == CIMA && mapaatual[f.posy - 1][f.posx] == 2) mudadirecao = true;
                if (f.direcaoatual == BAIXO && (mapaatual[f.posy + 1][f.posx] == 2 || mapaatual[f.posy + 1][f.posx] == 4)) mudadirecao = true;
                if (f.direcaoatual == ESQUERDA && mapaatual[f.posy][f.posx - 1] == 2) mudadirecao = true;
                if (f.direcaoatual == DIREITA && mapaatual[f.posy][f.posx + 1] == 2) mudadirecao = true;

                int tentativas = 0;
                while (mudadirecao && tentativas < 20) {
                    int sorteio = distribuicao(gerador);
                    if (sorteio == 1 && mapaatual[f.posy - 1][f.posx] != 2) { f.direcaoatual = CIMA; mudadirecao = false; }
                    else if (sorteio == 2 && mapaatual[f.posy + 1][f.posx] != 2 && mapaatual[f.posy + 1][f.posx] != 4) { f.direcaoatual = BAIXO; mudadirecao = false; }
                    else if (sorteio == 3 && mapaatual[f.posy][f.posx - 1] != 2) { f.direcaoatual = ESQUERDA; mudadirecao = false; }
                    else if (sorteio == 4 && mapaatual[f.posy][f.posx + 1] != 2) { f.direcaoatual = DIREITA; mudadirecao = false; }
                    tentativas++;
                }

                // Executa o passo
                if (f.direcaoatual == CIMA && mapaatual[f.posy - 1][f.posx] != 2) f.posy--;
                else if (f.direcaoatual == BAIXO && mapaatual[f.posy + 1][f.posx] != 2) f.posy++;
                else if (f.direcaoatual == ESQUERDA) {
                    if (f.posx == 0) f.posx = 27; else if (mapaatual[f.posy][f.posx - 1] != 2) f.posx--;
                } 
                else if (f.direcaoatual == DIREITA) {
                    if (f.posx == 27) f.posx = 0; else if (mapaatual[f.posy][f.posx + 1] != 2) f.posx++;
                }
                f.relogio.restart();
            }
        }
    };

    // Loop Principal do SFML
    while (window.isOpen()) {
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();

            // Gerenciamento de Telas através do Teclado
            if (estadoatual == MENU) {
                if (event->getIf<sf::Event::KeyPressed>()) estadoatual = JOGANDO;
            } 
            else if (estadoatual == GAMEOVER || estadoatual == VITORIA) {
                if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                    if (keyPressed->scancode == sf::Keyboard::Scancode::R) {
                        ResetarJogo();
                        estadoatual = JOGANDO;
                    }
                }
            } 
            else if (estadoatual == JOGANDO) {
                if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                    if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) window.close();
                    else if (keyPressed->scancode == sf::Keyboard::Scancode::Left)  pacman.proximadirecao = ESQUERDA;
                    else if (keyPressed->scancode == sf::Keyboard::Scancode::Right) pacman.proximadirecao = DIREITA;
                    else if (keyPressed->scancode == sf::Keyboard::Scancode::Up)    pacman.proximadirecao = CIMA;
                    else if (keyPressed->scancode == sf::Keyboard::Scancode::Down)  pacman.proximadirecao = BAIXO;
                }
            }
        }

        // ==========================================
        // SETOR: ATUALIZAÇÃO DA LÓGICA DO JOGO
        // ==========================================
        if (estadoatual == JOGANDO) {

            // Controle do Tempo de Duração da Pílula de Força
            if (pacmanComPoder && relogioSuperPoder.getElapsedTime().asSeconds() > 7.0f) {
                pacmanComPoder = false;
                if (cacador.estadoatual == ASSUSTADO) cacador.estadoatual = LIVRE;
                if (aleatorio.estadoatual == ASSUSTADO) aleatorio.estadoatual = LIVRE;
                if (emboscador.estadoatual == ASSUSTADO) emboscador.estadoatual = LIVRE;
                if (patrulheiro.estadoatual == ASSUSTADO) patrulheiro.estadoatual = LIVRE;
            }

            // Controle de Aparição e Desaparecimento da Frutinha
            if (pilulasComidas >= 30 && !frutaAtiva && mapaatual[17][14] == 0) {
                frutaAtiva = true;
                mapaatual[17][14] = 5; // Código 5 na matriz representa a Fruta!
                relogioFruta.restart();
            }
            if (frutaAtiva && relogioFruta.getElapsedTime().asSeconds() > 10.0f) {
                frutaAtiva = false;
                if (mapaatual[17][14] == 5) mapaatual[17][14] = 0;
            }

            // Lógica da Animação da Boca (Somente se estiver em movimento)
            if (pacman.direcaoatual != NENHUMA) {
                if (pacman.animacao.getElapsedTime().asSeconds() > 0.1f) {
                    pacman.abre = !pacman.abre;
                    pacman.animacao.restart();
                }
            } else {
                pacman.abre = true;
            }

            // --- MOVIMENTAÇÃO DO PAC-MAN (A cada 0.2 segundos) ---
            if (clockGeral.getElapsedTime() > sf::seconds(0.18f)) {
                clockGeral.restart();

                // Validação da próxima curva intencionada pelo jogador
                if (pacman.proximadirecao == CIMA && mapaatual[pacman.posy - 1][pacman.posx] != 2) pacman.direcaoatual = CIMA;
                if (pacman.proximadirecao == BAIXO && mapaatual[pacman.posy + 1][pacman.posx] != 2 && mapaatual[pacman.posy + 1][pacman.posx] != 4) pacman.direcaoatual = BAIXO;
                if (pacman.proximadirecao == ESQUERDA && mapaatual[pacman.posy][pacman.posx - 1] != 2) pacman.direcaoatual = ESQUERDA;
                if (pacman.proximadirecao == DIREITA && mapaatual[pacman.posy][pacman.posx + 1] != 2) pacman.direcaoatual = DIREITA;

                // Execução do Passo e Processamento de Itens Devorados
                if (pacman.direcaoatual == CIMA) {
                    if (mapaatual[pacman.posy - 1][pacman.posx] != 2) pacman.posy--;
                    else pacman.direcaoatual = NENHUMA;
                }
                else if (pacman.direcaoatual == BAIXO) {
                    if (mapaatual[pacman.posy + 1][pacman.posx] != 2 && mapaatual[pacman.posy + 1][pacman.posx] != 4) pacman.posy++;
                    else pacman.direcaoatual = NENHUMA;
                }
                else if (pacman.direcaoatual == ESQUERDA) {
                    if (pacman.posx == 0) pacman.posx = 27;
                    else if (mapaatual[pacman.posy][pacman.posx - 1] != 2) pacman.posx--;
                    else pacman.direcaoatual = NENHUMA;
                }
                else if (pacman.direcaoatual == DIREITA) {
                    if (pacman.posx == 27) pacman.posx = 0;
                    else if (mapaatual[pacman.posy][pacman.posx + 1] != 2) pacman.posx++;
                    else pacman.direcaoatual = NENHUMA;
                }

                // Processamento de Pílula Normal, Pílula de Força e Fruta
                int itemAtual = mapaatual[pacman.posy][pacman.posx];
                if (itemAtual == 1) { // Pílula Normal
                    score += 10; pilulasComidas++; pilulasRestantes--;
                    mapaatual[pacman.posy][pacman.posx] = 0;
                } 
                else if (itemAtual == 3) { // Pílula de Força
                    score += 50; pilulasComidas++; pilulasRestantes--;
                    mapaatual[pacman.posy][pacman.posx] = 0;
                    pacmanComPoder = true;
                    relogioSuperPoder.restart();
                    if (cacador.estadoatual == LIVRE) cacador.estadoatual = ASSUSTADO;
                    if (aleatorio.estadoatual == LIVRE) aleatorio.estadoatual = ASSUSTADO;
                    if (emboscador.estadoatual == LIVRE) emboscador.estadoatual = ASSUSTADO;
                    if (patrulheiro.estadoatual == LIVRE) patrulheiro.estadoatual = ASSUSTADO;
                }
                else if (itemAtual == 5) { // Frutinha
                    score += 500; frutaAtiva = false;
                    mapaatual[pacman.posy][pacman.posx] = 0;
                }

                if (pilulasRestantes <= 0) estadoatual = VITORIA;
            }

            // --- MOVIMENTAÇÃO DOS 4 FANTASMAS ---
            
            // 1. Fantasma Aleatório (Clyde - Laranja) - Sai após 1 segundo
            moverFandAleatorio(aleatorio, 1.0f);

            // 2. Fantasma Caçador (Blinky - Vermelho) - Sai após 3 segundos (Perseguição Direta)
            if (cacador.estadoatual == PRESO) {
                if (cacador.relogio.getElapsedTime().asSeconds() >= 3.0f) cacador.estadoatual = SAINDO;
                else cacador.posy = (cacador.posy == 14) ? 13 : 14;
            } 
            else if (cacador.estadoatual == SAINDO) {
                if (cacador.posx < 14) cacador.posx++; else if (cacador.posx > 14) cacador.posx--;
                else { if (cacador.posy != 11) cacador.posy--; else { cacador.estadoatual = LIVRE; cacador.direcaoatual = NENHUMA; } }
            } 
            else if (cacador.estadoatual == ASSUSTADO) {
                moverFandAleatorio(cacador, 0.f); // Se assustado, move de forma aleatória
            }
            else if (cacador.estadoatual == LIVRE) {
                if (cacador.relogio.getElapsedTime().asSeconds() > 0.30f) {
                    vector<caminhos> caminhosvalidos;
                    if (mapaatual[cacador.posy - 1][cacador.posx] != 2 && cacador.direcaoatual != BAIXO) {
                        float dist = pow(pacman.posx - cacador.posx, 2) + pow(pacman.posy - (cacador.posy - 1), 2);
                        caminhosvalidos.push_back({CIMA, dist});
                    }
                    if (mapaatual[cacador.posy + 1][cacador.posx] != 2 && cacador.direcaoatual != CIMA && mapaatual[cacador.posy + 1][cacador.posx] != 4) {
                        float dist = pow(pacman.posx - cacador.posx, 2) + pow(pacman.posy - (cacador.posy + 1), 2);
                        caminhosvalidos.push_back({BAIXO, dist});
                    }
                    if (cacador.posx == 0 || (mapaatual[cacador.posy][cacador.posx - 1] != 2 && cacador.direcaoatual != DIREITA)) {
                        int nx = (cacador.posx == 0) ? 27 : cacador.posx - 1;
                        float dist = pow(pacman.posx - nx, 2) + pow(pacman.posy - cacador.posy, 2);
                        caminhosvalidos.push_back({ESQUERDA, dist});
                    }
                    if (cacador.posx == 27 || (mapaatual[cacador.posy][cacador.posx + 1] != 2 && cacador.direcaoatual != ESQUERDA)) {
                        int nx = (cacador.posx == 27) ? 0 : cacador.posx + 1;
                        float dist = pow(pacman.posx - nx, 2) + pow(pacman.posy - cacador.posy, 2);
                        caminhosvalidos.push_back({DIREITA, dist});
                    }

                    if (caminhosvalidos.empty()) {
                        if (cacador.direcaoatual == CIMA) cacador.direcaoatual = BAIXO;
                        else if (cacador.direcaoatual == BAIXO) cacador.direcaoatual = CIMA;
                        else if (cacador.direcaoatual == ESQUERDA) cacador.direcaoatual = DIREITA;
                        else if (cacador.direcaoatual == DIREITA) cacador.direcaoatual = ESQUERDA;
                    } else {
                        sort(caminhosvalidos.begin(), caminhosvalidos.end(), comparadistancias);
                        cacador.direcaoatual = caminhosvalidos[0].direcao;
                    }

                    if (cacador.direcaoatual == CIMA && mapaatual[cacador.posy - 1][cacador.posx] != 2) cacador.posy--;
                    else if (cacador.direcaoatual == BAIXO && mapaatual[cacador.posy + 1][cacador.posx] != 2) cacador.posy++;
                    else if (cacador.direcaoatual == ESQUERDA) { if (cacador.posx == 0) cacador.posx = 27; else if (mapaatual[cacador.posy][cacador.posx - 1] != 2) cacador.posx--; }
                    else if (cacador.direcaoatual == DIREITA) { if (cacador.posx == 27) cacador.posx = 0; else if (mapaatual[cacador.posy][cacador.posx + 1] != 2) cacador.posx++; }
                    cacador.relogio.restart();
                }
            }

            // 3. Fantasma Emboscador (Pinky - Rosa) - Alvo 2 blocos à frente do Pac-Man
            if (emboscador.estadoatual == PRESO) {
                if (emboscador.relogio.getElapsedTime().asSeconds() >= 5.0f) emboscador.estadoatual = SAINDO;
                else emboscador.posy = (emboscador.posy == 14) ? 13 : 14;
            }
            else if (emboscador.estadoatual == SAINDO) {
                if (emboscador.posx < 14) emboscador.posx++; else if (emboscador.posx > 14) emboscador.posx--;
                else { if (emboscador.posy != 11) emboscador.posy--; else { emboscador.estadoatual = LIVRE; emboscador.direcaoatual = NENHUMA; } }
            }
            else if (emboscador.estadoatual == ASSUSTADO) {
                moverFandAleatorio(emboscador, 0.f);
            }
            else if (emboscador.estadoatual == LIVRE) {
                if (emboscador.relogio.getElapsedTime().asSeconds() > 0.32f) {
                    // Calcula ponto de emboscada (2 telhas à frente do Pac-man)
                    int alvoX = pacman.posx; int alvoY = pacman.posy;
                    if (pacman.direcaoatual == CIMA) alvoY -= 2;
                    else if (pacman.direcaoatual == BAIXO) alvoY += 2;
                    else if (pacman.direcaoatual == ESQUERDA) alvoX -= 2;
                    else if (pacman.direcaoatual == DIREITA) alvoX += 2;

                    vector<caminhos> caminhosvalidos;
                    if (mapaatual[emboscador.posy - 1][emboscador.posx] != 2 && emboscador.direcaoatual != BAIXO) {
                        float dist = pow(alvoX - emboscador.posx, 2) + pow(alvoY - (emboscador.posy - 1), 2);
                        caminhosvalidos.push_back({CIMA, dist});
                    }
                    if (mapaatual[emboscador.posy + 1][emboscador.posx] != 2 && emboscador.direcaoatual != CIMA && mapaatual[emboscador.posy + 1][emboscador.posx] != 4) {
                        float dist = pow(alvoX - emboscador.posx, 2) + pow(alvoY - (emboscador.posy + 1), 2);
                        caminhosvalidos.push_back({BAIXO, dist});
                    }
                    if (emboscador.posx == 0 || (mapaatual[emboscador.posy][emboscador.posx - 1] != 2 && emboscador.direcaoatual != DIREITA)) {
                        int nx = (emboscador.posx == 0) ? 27 : emboscador.posx - 1;
                        float dist = pow(alvoX - nx, 2) + pow(alvoY - emboscador.posy, 2);
                        caminhosvalidos.push_back({ESQUERDA, dist});
                    }
                    if (emboscador.posx == 27 || (mapaatual[emboscador.posy][emboscador.posx + 1] != 2 && emboscador.direcaoatual != ESQUERDA)) {
                        int nx = (emboscador.posx == 27) ? 0 : emboscador.posx + 1;
                        float dist = pow(alvoX - nx, 2) + pow(alvoY - emboscador.posy, 2);
                        caminhosvalidos.push_back({DIREITA, dist});
                    }

                    if (!caminhosvalidos.empty()) {
                        sort(caminhosvalidos.begin(), caminhosvalidos.end(), comparadistancias);
                        emboscador.direcaoatual = caminhosvalidos[0].direcao;
                    }

                    if (emboscador.direcaoatual == CIMA && mapaatual[emboscador.posy - 1][emboscador.posx] != 2) emboscador.posy--;
                    else if (emboscador.direcaoatual == BAIXO && mapaatual[emboscador.posy + 1][emboscador.posx] != 2) emboscador.posy++;
                    else if (emboscador.direcaoatual == ESQUERDA) { if (emboscador.posx == 0) emboscador.posx = 27; else if (mapaatual[emboscador.posy][emboscador.posx - 1] != 2) emboscador.posx--; }
                    else if (emboscador.direcaoatual == DIREITA) { if (emboscador.posx == 27) emboscador.posx = 0; else if (mapaatual[emboscador.posy][emboscador.posx + 1] != 2) emboscador.posx++; }
                    emboscador.relogio.restart();
                }
            }

            // 4. Fantasma Patrulheiro (Inky - Ciano) - Sai após 8 segundos
            if (patrulheiro.estadoatual == PRESO) {
                if (patrulheiro.relogio.getElapsedTime().asSeconds() >= 8.0f) patrulheiro.estadoatual = SAINDO;
                else patrulheiro.posy = (patrulheiro.posy == 14) ? 13 : 14;
            }
            else if (patrulheiro.estadoatual == SAINDO) {
                if (patrulheiro.posx < 14) patrulheiro.posx++; else if (patrulheiro.posx > 14) patrulheiro.posx--;
                else { if (patrulheiro.posy != 11) patrulheiro.posy--; else { patrulheiro.estadoatual = LIVRE; patrulheiro.direcaoatual = NENHUMA; } }
            }
            else if (patrulheiro.estadoatual == ASSUSTADO) {
                moverFandAleatorio(patrulheiro, 0.f);
            }
            else if (patrulheiro.estadoatual == LIVRE) {
                // Alvo dinâmico combinando a posição do Caçador e do Pacman
                if (patrulheiro.relogio.getElapsedTime().asSeconds() > 0.35f) {
                    int alvoX = pacman.posx + (pacman.posx - cacador.posx);
                    int alvoY = pacman.posy + (pacman.posy - cacador.posy);

                    vector<caminhos> caminhosvalidos;
                    if (mapaatual[patrulheiro.posy - 1][patrulheiro.posx] != 2 && patrulheiro.direcaoatual != BAIXO) {
                        float dist = pow(alvoX - patrulheiro.posx, 2) + pow(alvoY - (patrulheiro.posy - 1), 2);
                        caminhosvalidos.push_back({CIMA, dist});
                    }
                    if (mapaatual[patrulheiro.posy + 1][patrulheiro.posx] != 2 && patrulheiro.direcaoatual != CIMA && mapaatual[patrulheiro.posy + 1][patrulheiro.posx] != 4) {
                        float dist = pow(alvoX - patrulheiro.posx, 2) + pow(alvoY - (patrulheiro.posy + 1), 2);
                        caminhosvalidos.push_back({BAIXO, dist});
                    }
                    if (patrulheiro.posx == 0 || (mapaatual[patrulheiro.posy][patrulheiro.posx - 1] != 2 && patrulheiro.direcaoatual != DIREITA)) {
                        int nx = (patrulheiro.posx == 0) ? 27 : patrulheiro.posx - 1;
                        float dist = pow(alvoX - nx, 2) + pow(alvoY - patrulheiro.posy, 2);
                        caminhosvalidos.push_back({ESQUERDA, dist});
                    }
                    if (patrulheiro.posx == 27 || (mapaatual[patrulheiro.posy][patrulheiro.posx + 1] != 2 && patrulheiro.direcaoatual != ESQUERDA)) {
                        int nx = (patrulheiro.posx == 27) ? 0 : patrulheiro.posx + 1;
                        float dist = pow(alvoX - nx, 2) + pow(alvoY - patrulheiro.posy, 2);
                        caminhosvalidos.push_back({DIREITA, dist});
                    }

                    if (!caminhosvalidos.empty()) {
                        sort(caminhosvalidos.begin(), caminhosvalidos.end(), comparadistancias);
                        patrulheiro.direcaoatual = caminhosvalidos[0].direcao;
                    }

                    if (patrulheiro.direcaoatual == CIMA && mapaatual[patrulheiro.posy - 1][patrulheiro.posx] != 2) patrulheiro.posy--;
                    else if (patrulheiro.direcaoatual == BAIXO && mapaatual[patrulheiro.posy + 1][patrulheiro.posx] != 2) patrulheiro.posy++;
                    else if (patrulheiro.direcaoatual == ESQUERDA) { if (patrulheiro.posx == 0) patrulheiro.posx = 27; else if (mapaatual[patrulheiro.posy][patrulheiro.posx - 1] != 2) patrulheiro.posx--; }
                    else if (patrulheiro.direcaoatual == DIREITA) { if (patrulheiro.posx == 27) patrulheiro.posx = 0; else if (mapaatual[patrulheiro.posy][patrulheiro.posx + 1] != 2) patrulheiro.posx++; }
                    patrulheiro.relogio.restart();
                }
            }

            // --- SISTEMA GLOBAL DE COLISÕES (Executado a 60 FPS) ---
            auto verificarColisao = [&](Fantasma &f) {
                if (pacman.posx == f.posx && pacman.posy == f.posy) {
                    if (f.estadoatual == ASSUSTADO) {
                        score += 200;
                        f.posx = 14; f.posy = 14;
                        f.estadoatual = PRESO;
                        f.relogio.restart();
                    } else if (f.estadoatual == LIVRE || f.estadoatual == SAINDO) {
                        estadoatual = GAMEOVER;
                    }
                }
            };

            verificarColisao(aleatorio);
            verificarColisao(cacador);
            verificarColisao(emboscador);
            verificarColisao(patrulheiro);
        }

        // ==========================================
        // SETOR: RENDERIZAÇÃO NA TELA (DESENHO)
        // ==========================================
        window.clear(sf::Color::Black);

        if (estadoatual == MENU) {
            textomenu.setString("PAC-MAN MYGAME\n\nPressione qualquer tecla\npara comecar...");
            textomenu.setPosition({100.f, 300.f});
            window.draw(textomenu);
        } 
        else if (estadoatual == GAMEOVER) {
            textofim.setString("GAME OVER\n\nPontuacao Final: " + to_string(score) + "\n\nPressione 'R' para Recomecar");
            textofim.setPosition({100.f, 300.f});
            window.draw(textofim);
        } 
        else if (estadoatual == VITORIA) {
            textomenu.setString("VOCE VENCEU!\n\nPontuacao Final: " + to_string(score) + "\n\nPressione 'R' para Jogar Novamente");
            textomenu.setPosition({100.f, 300.f});
            window.draw(textomenu);
        } 
        else if (estadoatual == JOGANDO) {
            
            // Desenho do Labirinto e Itens
            for (int r = 0; r < 33; r++) {
                for (int c = 0; c < 28; c++) {
                    float xPos = c * 32.f;
                    float yPos = r * 32.f + OFFSET_Y;

                    if (mapaatual[r][c] == 2) { // Paredes
                        sf::RectangleShape bloco({30.f, 30.f});
                        bloco.setFillColor(sf::Color(25, 25, 166));
                        bloco.setPosition({xPos + 1.f, yPos + 1.f});
                        window.draw(bloco);
                    } 
                    else if (mapaatual[r][c] == 1) { // Pílulas Comuns
                        sf::CircleShape pilula(4.f);
                        pilula.setFillColor(sf::Color(255, 184, 151));
                        pilula.setPosition({xPos + 12.f, yPos + 12.f});
                        window.draw(pilula);
                    } 
                    else if (mapaatual[r][c] == 3) { // Pílulas de Força (Piscando)
                        static sf::Clock piscado;
                        if ((int)(piscado.getElapsedTime().asMilliseconds() / 200) % 2 == 0) {
                            sf::CircleShape superPilula(8.f);
                            superPilula.setFillColor(sf::Color(255, 184, 151));
                            superPilula.setPosition({xPos + 8.f, yPos + 8.f});
                            window.draw(superPilula);
                        }
                    }
                    else if (mapaatual[r][c] == 4) { // Porta da Base
                        sf::RectangleShape porta({32.f, 8.f});
                        porta.setFillColor(sf::Color(255, 192, 203));
                        porta.setPosition({xPos, yPos + 12.f});
                        window.draw(porta);
                    }
                    else if (mapaatual[r][c] == 5) { // Frutinha (Forma geométrica geométrica retro)
                        sf::CircleShape fruta(10.f, 5); // Pentágono Vermelho
                        fruta.setFillColor(sf::Color::Red);
                        fruta.setPosition({xPos + 6.f, yPos + 6.f});
                        window.draw(fruta);
                    }
                }
            }

            // Desenho do Pac-Man (Respeitando seu if/else de Boca Aberta/Fechada corrigido)
            if (pacman.abre) {
                if (pacman.direcaoatual == DIREITA || pacman.direcaoatual == NENHUMA) {
                    spritedir.setPosition({pacman.posx * 32.f, pacman.posy * 32.f + OFFSET_Y});
                    window.draw(spritedir);
                }
                else if (pacman.direcaoatual == BAIXO) {
                    spritebaixo.setPosition({pacman.posx * 32.f, pacman.posy * 32.f + OFFSET_Y});
                    window.draw(spritebaixo);
                }
                else if (pacman.direcaoatual == ESQUERDA) {
                    spriteesq.setPosition({pacman.posx * 32.f, pacman.posy * 32.f + OFFSET_Y});
                    window.draw(spriteesq);
                }
                else if (pacman.direcaoatual == CIMA) {
                    spritecima.setPosition({pacman.posx * 32.f, pacman.posy * 32.f + OFFSET_Y});
                    window.draw(spritecima);
                }
            } else {
                pacmanfechado.setPosition({pacman.posx * 32.f, pacman.posy * 32.f + OFFSET_Y});
                window.draw(pacmanfechado);
            }

            // Renderização e Coloração dos Fantasmas
            auto desenharFantasma = [&](Fantasma &f) {
                spritefantasma.setPosition({f.posx * 32.f, f.posy * 32.f + OFFSET_Y});
                if (f.estadoatual == ASSUSTADO) {
                    // Pisca em branco nos últimos 2 segundos do poder
                    if (relogioSuperPoder.getElapsedTime().asSeconds() > 5.0f && (int)(relogioSuperPoder.getElapsedTime().asMilliseconds() / 150) % 2 == 0)
                        spritefantasma.setColor(sf::Color::White);
                    else
                        spritefantasma.setColor(sf::Color::Blue);
                } else {
                    spritefantasma.setColor(f.corOriginal);
                }
                window.draw(spritefantasma);
            };

            desenharFantasma(aleatorio);
            desenharFantasma(cacador);
            desenharFantasma(emboscador);
            desenharFantasma(patrulheiro);

            // Desenho do Painel Superior (HUD)
            textscore.setString("SCORE: " + to_string(score) + "   RESTANTES: " + to_string(pilulasRestantes));
            textscore.setPosition({20.f, 15.f});
            window.draw(textscore);
        }

        window.display();
    }

    return 0;
}