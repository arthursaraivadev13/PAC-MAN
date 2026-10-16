#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <optional>
#include <string>
#include <cmath>
#include <vector>
#include <ctime>

// Comando para compilação (Linux/MinGW):
// g++ original.cpp -o pacman -std=c++20 -lsfml-graphics -lsfml-window -lsfml-system && ./pacman

// ============================================================================
// PARTE 1: CONFIGURAÇÕES INICIAIS E ESTRUTURAS DE DADOS
// ============================================================================

// Mapa original do jogo
// 0 = Vazio
// 1 = Pílula Normal (10 pontos)
// 2 = Parede (Colisão)
// 3 = Pílula de Força (50 pontos e assusta os fantasmas)
// 4 = Porta da base dos fantasmas (Pac-Man não entra)
const int mapaOriginal[33][28] = {
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
    {2,2,2,2,2,2,1,2,2,0,2,2,2,4,4,2,2,2,0,2,2,1,2,2,2,2,2,2},
    {0,0,0,0,0,0,1,0,0,0,2,0,0,0,0,0,0,2,0,0,0,1,0,0,0,0,0,0},
    {2,2,2,2,2,2,1,2,2,0,2,0,0,0,0,0,0,2,0,2,2,1,2,2,2,2,2,2},
    {0,0,0,0,0,2,1,2,2,0,2,2,2,2,2,2,2,2,0,2,2,1,2,0,0,0,0,0},
    {0,0,0,0,0,2,1,2,2,1,1,1,1,1,1,1,1,1,1,2,2,1,2,0,0,0,0,0},
    {2,2,2,2,2,2,1,2,2,1,2,2,2,2,2,2,2,2,1,2,2,1,2,2,2,2,2,2},
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
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

int mapaAtual[33][28];

enum Direcao { NENHUMA, CIMA, BAIXO, ESQUERDA, DIREITA };
enum ESTADO { MENU, JOGANDO, GAMEOVER, VITORIA };

// ============================================================================
// SISTEMA DE FRUTAS
// ============================================================================
// As frutas aparecem no centro do mapa (posição 17, 20 aprox.) após comer certa
// quantidade de pílulas. Ficam visíveis por 9 segundos. Quando coletadas, o ícone
// aparece no HUD abaixo do mapa.

enum TipoFruta { FRUTA_NENHUMA = -1, FRUTA_CEREJA = 0, FRUTA_LARANJA = 1, FRUTA_ANANAS = 2, FRUTA_MORANGO = 3 };

const int   PONTOS_FRUTA[4]     = { 100, 300, 500, 700 };
const float TEMPO_FRUTA_VISIVEL = 9.0f;

// Posição central onde a fruta aparece no labirinto
// mapaOriginal[21][13] == 0 -> célula livre no centro inferior (posição clássica do Pac-Man)
const int FRUTA_X = 13;
const int FRUTA_Y = 21;

// Quantidade de pílulas comidas para cada fruta aparecer (total ~186 pílulas no mapa)
const int PILULAS_PARA_FRUTA[4] = { 30, 70, 110, 150 };

struct SistemaFrutas {
    TipoFruta tipoAtivo    = FRUTA_NENHUMA; // Fruta atualmente no mapa
    float     tempoRestante = 0.0f;          // Quanto tempo ainda fica visível
    int       pilulasComidas = 0;            // Contador de pílulas normais/força comidas
    int       proximaFruta   = 0;            // Índice da próxima fruta a spawnar (0-3)
    std::vector<TipoFruta> coletadas;        // Histórico para HUD
};

SistemaFrutas sistemaFrutas;

struct Pacman {
    int x = 14;
    int y = 21;
    int xAnterior = 14;
    int yAnterior = 21;
    Direcao direcao = NENHUMA;
    Direcao proxima_direcao = NENHUMA;
};

struct Fantasma {
    int x;
    int y;
    int xAnterior;
    int yAnterior;
    Direcao direcao;
    int tipo;
    bool assustado;
    bool retornando;
    bool sinalizadorVelocidade;
    float tempoPreso;
    bool estaSaindo;
};

Pacman pacman;
Fantasma fantasmas[4];

bool olhadireita = true, olhaesquerda = false, olhacima = false, olhabaixo = false;
int score = 0;
int highScore = 0;
float tempoAssustadoRestante = 0.0f;
int frameAnimacaoPacman = 0;

// ============================================================================
// PARTE 2: FUNÇÕES AUXILIARES
// ============================================================================

void centralizarTexto(sf::Text& texto) {
    sf::FloatRect bounds = texto.getLocalBounds();
    texto.setOrigin({bounds.position.x + bounds.size.x / 2.0f, bounds.position.y + bounds.size.y / 2.0f});
}

bool VerificarVitoria() {
    for (int i = 0; i < 33; i++)
        for (int j = 0; j < 28; j++)
            if (mapaAtual[i][j] == 1 || mapaAtual[i][j] == 3)
                return false;
    return true;
}

void ResetarJogo() {
    pacman.x = 14; pacman.y = 21;
    pacman.xAnterior = 14; pacman.yAnterior = 21;
    pacman.direcao = NENHUMA; pacman.proxima_direcao = NENHUMA;
    olhadireita = true; olhaesquerda = false; olhacima = false; olhabaixo = false;

    fantasmas[0] = {12, 14, 12, 14, NENHUMA, 0, false, false, false, 0.0f,  false};
    fantasmas[1] = {13, 14, 13, 14, NENHUMA, 1, false, false, false, 4.0f,  false};
    fantasmas[2] = {14, 14, 14, 14, NENHUMA, 2, false, false, false, 8.0f,  false};
    fantasmas[3] = {15, 14, 15, 14, NENHUMA, 3, false, false, false, 12.0f, false};

    score = 0;
    tempoAssustadoRestante = 0.0f;

    // Reseta sistema de frutas
    sistemaFrutas.tipoAtivo     = FRUTA_NENHUMA;
    sistemaFrutas.tempoRestante  = 0.0f;
    sistemaFrutas.pilulasComidas = 0;
    sistemaFrutas.proximaFruta   = 0;
    sistemaFrutas.coletadas.clear();

    for (int i = 0; i < 33; i++)
        for (int j = 0; j < 28; j++)
            mapaAtual[i][j] = mapaOriginal[i][j];
}

float obterDistanciaQuad(int x1, int y1, int x2, int y2) {
    return static_cast<float>((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

Direcao obterOposta(Direcao d) {
    if (d == CIMA) return BAIXO;
    if (d == BAIXO) return CIMA;
    if (d == ESQUERDA) return DIREITA;
    if (d == DIREITA) return ESQUERDA;
    return NENHUMA;
}

// ============================================================================
// FANTASMAS
// ============================================================================

void AtualizarFantasma(int index) {
    if (fantasmas[index].tempoPreso > 0.0f) return;

    fantasmas[index].xAnterior = fantasmas[index].x;
    fantasmas[index].yAnterior = fantasmas[index].y;

    int fx = fantasmas[index].x;
    int fy = fantasmas[index].y;
    Direcao dirAtual = fantasmas[index].direcao;
    int tipo = fantasmas[index].tipo;

    if (fantasmas[index].retornando && (fx == 13 || fx == 14) && fy == 14) {
        fantasmas[index].retornando = false;
        fantasmas[index].assustado = false;
        fantasmas[index].tempoPreso = 2.0f;
        fantasmas[index].estaSaindo = false;
        return;
    }

    if (fy >= 13 && fy <= 14 && fx >= 11 && fx <= 16 && !fantasmas[index].retornando)
        fantasmas[index].estaSaindo = true;
    if (fantasmas[index].estaSaindo && fy <= 11)
        fantasmas[index].estaSaindo = false;

    if (fantasmas[index].assustado && !fantasmas[index].retornando && !fantasmas[index].estaSaindo) {
        fantasmas[index].sinalizadorVelocidade = !fantasmas[index].sinalizadorVelocidade;
        if (fantasmas[index].sinalizadorVelocidade) return;
    }

    if (fx < 0) { fantasmas[index].x = 27; return; }
    if (fx > 27) { fantasmas[index].x = 0; return; }

    int targetX = pacman.x;
    int targetY = pacman.y;

    if (fantasmas[index].retornando) { targetX = 14; targetY = 14; }
    else if (fantasmas[index].estaSaindo) { targetX = 14; targetY = 11; }
    else if (fantasmas[index].assustado) {
        if (tipo == 0) { targetX = 0; targetY = 0; }
        else if (tipo == 1) { targetX = 27; targetY = 0; }
        else if (tipo == 2) { targetX = 0; targetY = 32; }
        else if (tipo == 3) { targetX = 27; targetY = 32; }
    } else {
        if (tipo == 1) {
            if (pacman.direcao == CIMA) { targetY -= 4; targetX -= 4; }
            else if (pacman.direcao == BAIXO) targetY += 4;
            else if (pacman.direcao == ESQUERDA) targetX -= 4;
            else if (pacman.direcao == DIREITA) targetX += 4;
        } else if (tipo == 2) {
            if (pacman.direcao == CIMA) targetY += 2;
            else if (pacman.direcao == BAIXO) targetY -= 2;
            else if (pacman.direcao == ESQUERDA) targetX += 2;
            else if (pacman.direcao == DIREITA) targetX -= 2;
        } else if (tipo == 3) {
            float distAoPacman = std::sqrt(obterDistanciaQuad(fx, fy, pacman.x, pacman.y));
            if (distAoPacman < 8.0f) { targetX = 0; targetY = 32; }
        }
    }

    Direcao direcoesPossiveis[4] = { CIMA, BAIXO, ESQUERDA, DIREITA };
    Direcao melhorDirecao = NENHUMA;
    float menorDistancia = 9999999.f;
    Direcao oposta = obterOposta(dirAtual);

    for (int i = 0; i < 4; i++) {
        Direcao d = direcoesPossiveis[i];
        if (d == oposta && dirAtual != NENHUMA && !fantasmas[index].estaSaindo) continue;

        int proximoX = fx, proximoY = fy;
        if (d == CIMA) proximoY--;
        else if (d == BAIXO) proximoY++;
        else if (d == ESQUERDA) proximoX--;
        else if (d == DIREITA) proximoX++;

        if (proximoY == 13 && (proximoX < 0 || proximoX > 27)) {
            // túnel livre
        } else {
            if (proximoY < 0 || proximoY >= 33 || proximoX < 0 || proximoX >= 28) continue;
            if (mapaAtual[proximoY][proximoX] == 2) continue;
            if (mapaAtual[proximoY][proximoX] == 4) {
                if (!fantasmas[index].retornando && !fantasmas[index].estaSaindo) continue;
            }
        }

        float dist = obterDistanciaQuad(proximoX, proximoY, targetX, targetY);
        if (dist < menorDistancia) { menorDistancia = dist; melhorDirecao = d; }
    }

    if (melhorDirecao == NENHUMA) {
        for (int i = 0; i < 4; i++) {
            Direcao d = direcoesPossiveis[i];
            int px = fx + (d == DIREITA) - (d == ESQUERDA);
            int py = fy + (d == BAIXO) - (d == CIMA);
            if (py >= 0 && py < 33 && px >= 0 && px < 28 && mapaAtual[py][px] != 2) {
                melhorDirecao = d; break;
            }
        }
    }

    fantasmas[index].direcao = melhorDirecao;
    if (melhorDirecao == CIMA) fantasmas[index].y--;
    else if (melhorDirecao == BAIXO) fantasmas[index].y++;
    else if (melhorDirecao == ESQUERDA) fantasmas[index].x--;
    else if (melhorDirecao == DIREITA) fantasmas[index].x++;
}

// ============================================================================
// SISTEMA DE FRUTAS — helpers
// ============================================================================

// Tenta spawnar a próxima fruta se o limiar de pílulas foi atingido
void TentarSpawnarFruta() {
    if (sistemaFrutas.proximaFruta >= 4) return;          // Todas as 4 já apareceram
    if (sistemaFrutas.tipoAtivo != FRUTA_NENHUMA) return;  // Já tem uma no mapa

    int limiar = PILULAS_PARA_FRUTA[sistemaFrutas.proximaFruta];
    if (sistemaFrutas.pilulasComidas >= limiar) {
        sistemaFrutas.tipoAtivo    = static_cast<TipoFruta>(sistemaFrutas.proximaFruta);
        sistemaFrutas.tempoRestante = TEMPO_FRUTA_VISIVEL;
        sistemaFrutas.proximaFruta++;
    }
}

// Verifica se o Pac-Man coletou a fruta e aplica pontuação
void VerificarColetaFruta() {
    if (sistemaFrutas.tipoAtivo == FRUTA_NENHUMA) return;
    if (pacman.x == FRUTA_X && pacman.y == FRUTA_Y) {
        score += PONTOS_FRUTA[static_cast<int>(sistemaFrutas.tipoAtivo)];
        sistemaFrutas.coletadas.push_back(sistemaFrutas.tipoAtivo);
        sistemaFrutas.tipoAtivo    = FRUTA_NENHUMA;
        sistemaFrutas.tempoRestante = 0.0f;
    }
}

// ============================================================================
// LOOP PRINCIPAL
// ============================================================================

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    ResetarJogo();
    ESTADO estadoAtual = MENU;

    const float TAMANHO_BLOCO = 32.f;
    const float OFFSET_Y = 64.f;
    const float ALTURA_HUD_BAIXO = 48.f; // Espaço extra abaixo do mapa para HUD de frutas

    const unsigned int larguraJanela = static_cast<unsigned int>(28 * TAMANHO_BLOCO);
    const unsigned int alturaJanela  = static_cast<unsigned int>(33 * TAMANHO_BLOCO + OFFSET_Y + ALTURA_HUD_BAIXO);

    sf::RenderWindow window(sf::VideoMode({larguraJanela, alturaJanela}), "Pac-Man UFV");

    sf::RectangleShape quad({TAMANHO_BLOCO, TAMANHO_BLOCO});
    quad.setFillColor(sf::Color::Black);
    quad.setOutlineThickness(-3.f);
    quad.setOutlineColor(sf::Color(25, 25, 180));

    sf::RectangleShape portaVisual({TAMANHO_BLOCO, TAMANHO_BLOCO / 4.f});
    portaVisual.setFillColor(sf::Color(255, 184, 222, 200));

    sf::RectangleShape painelGameOver({static_cast<float>(larguraJanela), static_cast<float>(alturaJanela)});
    painelGameOver.setFillColor(sf::Color(0, 0, 0, 180));

    // Linha separadora HUD inferior
    sf::RectangleShape linhaHUD({static_cast<float>(larguraJanela), 2.f});
    linhaHUD.setFillColor(sf::Color(60, 60, 60));
    linhaHUD.setPosition({0.f, 33 * TAMANHO_BLOCO + OFFSET_Y});

    sf::CircleShape circle(4.f);
    circle.setFillColor(sf::Color(255, 184, 151));

    sf::CircleShape powerPellet(8.f);
    powerPellet.setFillColor(sf::Color(255, 184, 151));

    sf::Font fonte;
    if (!fonte.openFromFile("retrofonte.ttf"))
        std::cout << "Aviso: retrofonte.ttf não encontrada.\n";

    sf::Text textoScore(fonte);
    textoScore.setCharacterSize(18);
    textoScore.setFillColor(sf::Color::White);
    textoScore.setPosition({20.f, 24.f});

    sf::Text textoPacmanTopo(fonte);
    textoPacmanTopo.setString("PAC-MAN");
    textoPacmanTopo.setCharacterSize(30);
    textoPacmanTopo.setFillColor(sf::Color::Yellow);
    centralizarTexto(textoPacmanTopo);
    textoPacmanTopo.setPosition({larguraJanela / 2.f, 32.f});

    sf::Text textoHighScore(fonte);
    textoHighScore.setCharacterSize(18);
    textoHighScore.setFillColor(sf::Color::White);

    sf::Text textoTitulo(fonte);
    textoTitulo.setString("PAC-MAN");
    textoTitulo.setCharacterSize(80);
    textoTitulo.setFillColor(sf::Color::Yellow);
    centralizarTexto(textoTitulo);
    textoTitulo.setPosition({larguraJanela / 2.f, alturaJanela / 3.f});

    sf::Text textoIniciar(fonte);
    textoIniciar.setString("PRESS ENTER TO START");
    textoIniciar.setCharacterSize(20);
    textoIniciar.setFillColor(sf::Color::White);
    centralizarTexto(textoIniciar);
    textoIniciar.setPosition({larguraJanela / 2.f, alturaJanela / 1.5f});

    sf::Text textoGameOver(fonte);
    textoGameOver.setString("GAME OVER");
    textoGameOver.setCharacterSize(60);
    textoGameOver.setFillColor(sf::Color::Red);
    centralizarTexto(textoGameOver);
    textoGameOver.setPosition({larguraJanela / 2.f, alturaJanela / 3.f});

    sf::Text textoVitoria(fonte);
    textoVitoria.setString("YOU WIN!");
    textoVitoria.setCharacterSize(60);
    textoVitoria.setFillColor(sf::Color::Green);
    centralizarTexto(textoVitoria);
    textoVitoria.setPosition({larguraJanela / 2.f, alturaJanela / 3.f});

    sf::Text textoOpcoesGO(fonte);
    textoOpcoesGO.setString("PRESS 'R' TO RESTART\n\nPRESS 'M' FOR MENU");
    textoOpcoesGO.setCharacterSize(20);
    textoOpcoesGO.setFillColor(sf::Color::White);
    centralizarTexto(textoOpcoesGO);
    textoOpcoesGO.setPosition({larguraJanela / 2.f, alturaJanela / 1.5f});

    sf::Text textoFinalScore(fonte);
    textoFinalScore.setCharacterSize(25);
    textoFinalScore.setFillColor(sf::Color::Yellow);

    // ---- Texturas do Pac-Man ----
    sf::Texture texture, textureCima, textureBaixo, textureEsq;
    sf::Texture texFechadoDir, texFechadoCima, texFechadoBaixo, texFechadoEsq;

    if (!texture.loadFromFile("pacman.png") || !textureCima.loadFromFile("pacman-cima.png") ||
        !textureBaixo.loadFromFile("pacman-baixo.png") || !textureEsq.loadFromFile("pacman-esq.png") ||
        !texFechadoDir.loadFromFile("fechado-dir.png") || !texFechadoCima.loadFromFile("fechado-cima.png") ||
        !texFechadoBaixo.loadFromFile("fechado-baixo.png") || !texFechadoEsq.loadFromFile("fechado-esq.png"))
        std::cout << "Aviso: Imagens do Pac-Man ausentes.\n";

    sf::Sprite spritedir{texture}, spritecima{textureCima}, spritebaixo{textureBaixo}, spriteesq{textureEsq};
    spritedir.setScale({TAMANHO_BLOCO / texture.getSize().x, TAMANHO_BLOCO / texture.getSize().y});
    spritecima.setScale({TAMANHO_BLOCO / textureCima.getSize().x, TAMANHO_BLOCO / textureCima.getSize().y});
    spritebaixo.setScale({TAMANHO_BLOCO / textureBaixo.getSize().x, TAMANHO_BLOCO / textureBaixo.getSize().y});
    spriteesq.setScale({TAMANHO_BLOCO / textureEsq.getSize().x, TAMANHO_BLOCO / textureEsq.getSize().y});

    sf::Sprite sFechadoDir{texFechadoDir}, sFechadoCima{texFechadoCima}, sFechadoBaixo{texFechadoBaixo}, sFechadoEsq{texFechadoEsq};
    sFechadoDir.setScale({TAMANHO_BLOCO / texFechadoDir.getSize().x, TAMANHO_BLOCO / texFechadoDir.getSize().y});
    sFechadoCima.setScale({TAMANHO_BLOCO / texFechadoCima.getSize().x, TAMANHO_BLOCO / texFechadoCima.getSize().y});
    sFechadoBaixo.setScale({TAMANHO_BLOCO / texFechadoBaixo.getSize().x, TAMANHO_BLOCO / texFechadoBaixo.getSize().y});
    sFechadoEsq.setScale({TAMANHO_BLOCO / texFechadoEsq.getSize().x, TAMANHO_BLOCO / texFechadoEsq.getSize().y});

    // ---- Texturas dos Fantasmas ----
    std::string coresFantasmas[4] = {"vermelho", "rosa", "azul", "laranja"};
    std::string sufixosDir[4] = {"cima", "baixo", "esq", "dir"};

    sf::Texture texFantasmas[4][4];
    std::vector<std::vector<sf::Sprite>> spriteFantasmas(4, std::vector<sf::Sprite>());

    for (int f = 0; f < 4; f++) {
        for (int d = 0; d < 4; d++) {
            std::string nomeArquivo = "fantasma-" + coresFantasmas[f] + "-" + sufixosDir[d] + ".png";
            if (!texFantasmas[f][d].loadFromFile(nomeArquivo)) {
                std::cout << "Erro ao carregar: " << nomeArquivo << "\n";
                spriteFantasmas[f].push_back(sf::Sprite(texFantasmas[f][d]));
            } else {
                sf::Sprite novoSprite(texFantasmas[f][d]);
                float escalaX = (TAMANHO_BLOCO / texFantasmas[f][d].getSize().x) * 1.2f;
                float escalaY = (TAMANHO_BLOCO / texFantasmas[f][d].getSize().y) * 1.2f;
                novoSprite.setScale({escalaX, escalaY});
                float difX = (texFantasmas[f][d].getSize().x * escalaX - TAMANHO_BLOCO) / 2.0f;
                float difY = (texFantasmas[f][d].getSize().y * escalaY - TAMANHO_BLOCO) / 2.0f;
                novoSprite.setOrigin({difX / escalaX, difY / escalaY});
                spriteFantasmas[f].push_back(novoSprite);
            }
        }
    }

    // ---- Texturas das Frutas ----
    // Ordem: cereja, laranja, ananas, morango  (índice == TipoFruta)
    std::string nomesFrutas[4] = {"cereja", "laranja", "ananas", "morango"};
    sf::Texture texFrutas[4];
    const float TAMANHO_FRUTA_MAPA = TAMANHO_BLOCO * 1.85f;
    const float TAMANHO_FRUTA_HUD  = 76.f;

    for (int i = 0; i < 4; i++) {
        std::string arq = nomesFrutas[i] + ".png";
        if (!texFrutas[i].loadFromFile(arq))
            std::cout << "Aviso: " << arq << " não encontrada.\n";
    }

    // Sprites criados depois que todas as texturas estão carregadas
    std::vector<sf::Sprite> spriteFrutas;
    for (int i = 0; i < 4; i++)
        spriteFrutas.emplace_back(texFrutas[i]);

    sf::Clock clock, blinkClock, tempoDelta;
    bool drawTextoIniciar = true;
    bool piscarOlhosMorte = false;

    // ============================================================================
    // LOOP DE EVENTOS E LÓGICA
    // ============================================================================

    while (window.isOpen()) {
        float dt = tempoDelta.restart().asSeconds();

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();
            else if (estadoAtual == MENU) {
                if (const auto* kp = event->getIf<sf::Event::KeyPressed>())
                    if (kp->scancode == sf::Keyboard::Scancode::Enter) { ResetarJogo(); estadoAtual = JOGANDO; }
            }
            else if (estadoAtual == GAMEOVER || estadoAtual == VITORIA) {
                if (const auto* kp = event->getIf<sf::Event::KeyPressed>()) {
                    if (kp->scancode == sf::Keyboard::Scancode::R) { ResetarJogo(); estadoAtual = JOGANDO; }
                    else if (kp->scancode == sf::Keyboard::Scancode::M) estadoAtual = MENU;
                }
            }
            else if (estadoAtual == JOGANDO) {
                if (const auto* kp = event->getIf<sf::Event::KeyPressed>()) {
                    if (kp->scancode == sf::Keyboard::Scancode::Escape) window.close();
                    else if (kp->scancode == sf::Keyboard::Scancode::Left)  pacman.proxima_direcao = ESQUERDA;
                    else if (kp->scancode == sf::Keyboard::Scancode::Right) pacman.proxima_direcao = DIREITA;
                    else if (kp->scancode == sf::Keyboard::Scancode::Up)    pacman.proxima_direcao = CIMA;
                    else if (kp->scancode == sf::Keyboard::Scancode::Down)  pacman.proxima_direcao = BAIXO;
                    else if (kp->scancode == sf::Keyboard::Scancode::Semicolon) estadoAtual = VITORIA;
                }
            }
        }

        // ---- LÓGICA DO JOGO ----
        if (estadoAtual == JOGANDO) {

            // Timer do poder assustado
            if (tempoAssustadoRestante > 0.0f) {
                tempoAssustadoRestante -= dt;
                if (tempoAssustadoRestante <= 0.0f)
                    for (int i = 0; i < 4; i++)
                        if (!fantasmas[i].retornando) fantasmas[i].assustado = false;
            }

            // Timers dos fantasmas presos
            for (int i = 0; i < 4; i++)
                if (fantasmas[i].tempoPreso > 0.0f) fantasmas[i].tempoPreso -= dt;

            // ---- Timer da fruta visível ----
            if (sistemaFrutas.tipoAtivo != FRUTA_NENHUMA) {
                sistemaFrutas.tempoRestante -= dt;
                if (sistemaFrutas.tempoRestante <= 0.0f)
                    sistemaFrutas.tipoAtivo = FRUTA_NENHUMA; // Expirou sem ser coletada
            }

            // GAME TICK (0.18s)
            if (clock.getElapsedTime() > sf::seconds(0.18f)) {
                clock.restart();

                frameAnimacaoPacman = (frameAnimacaoPacman == 0) ? 1 : 0;
                piscarOlhosMorte = !piscarOlhosMorte;

                pacman.xAnterior = pacman.x;
                pacman.yAnterior = pacman.y;

                // Intenção → direção real
                if (pacman.proxima_direcao == CIMA && mapaAtual[pacman.y - 1][pacman.x] != 2 && mapaAtual[pacman.y - 1][pacman.x] != 4)
                    pacman.direcao = CIMA;
                else if (pacman.proxima_direcao == BAIXO && mapaAtual[pacman.y + 1][pacman.x] != 2 && mapaAtual[pacman.y + 1][pacman.x] != 4)
                    pacman.direcao = BAIXO;
                else if (pacman.proxima_direcao == ESQUERDA && (pacman.x == 0 || (mapaAtual[pacman.y][pacman.x - 1] != 2 && mapaAtual[pacman.y][pacman.x - 1] != 4)))
                    pacman.direcao = ESQUERDA;
                else if (pacman.proxima_direcao == DIREITA && (pacman.x == 27 || (mapaAtual[pacman.y][pacman.x + 1] != 2 && mapaAtual[pacman.y][pacman.x + 1] != 4)))
                    pacman.direcao = DIREITA;

                // Movimento
                if (pacman.direcao == CIMA) {
                    if (mapaAtual[pacman.y - 1][pacman.x] != 2 && mapaAtual[pacman.y - 1][pacman.x] != 4) { olhacima = true; olhabaixo = false; olhadireita = false; olhaesquerda = false; pacman.y--; }
                    else pacman.direcao = NENHUMA;
                } else if (pacman.direcao == BAIXO) {
                    if (mapaAtual[pacman.y + 1][pacman.x] != 2 && mapaAtual[pacman.y + 1][pacman.x] != 4) { olhabaixo = true; olhacima = false; olhadireita = false; olhaesquerda = false; pacman.y++; }
                    else pacman.direcao = NENHUMA;
                } else if (pacman.direcao == ESQUERDA) {
                    if (pacman.x == 0) { pacman.x = 27; }
                    else if (mapaAtual[pacman.y][pacman.x - 1] != 2 && mapaAtual[pacman.y][pacman.x - 1] != 4) { olhaesquerda = true; olhadireita = false; olhacima = false; olhabaixo = false; pacman.x--; }
                    else pacman.direcao = NENHUMA;
                } else if (pacman.direcao == DIREITA) {
                    if (pacman.x == 27) { pacman.x = 0; }
                    else if (mapaAtual[pacman.y][pacman.x + 1] != 2 && mapaAtual[pacman.y][pacman.x + 1] != 4) { olhadireita = true; olhacima = false; olhabaixo = false; olhaesquerda = false; pacman.x++; }
                    else pacman.direcao = NENHUMA;
                }

                // Comer pílulas
                if (mapaAtual[pacman.y][pacman.x] == 1) {
                    score += 10;
                    mapaAtual[pacman.y][pacman.x] = 0;
                    sistemaFrutas.pilulasComidas++;
                    TentarSpawnarFruta();
                    if (VerificarVitoria()) estadoAtual = VITORIA;
                } else if (mapaAtual[pacman.y][pacman.x] == 3) {
                    score += 50;
                    mapaAtual[pacman.y][pacman.x] = 0;
                    sistemaFrutas.pilulasComidas++;
                    TentarSpawnarFruta();
                    tempoAssustadoRestante = 7.0f;
                    for (int i = 0; i < 4; i++)
                        if (!fantasmas[i].retornando && fantasmas[i].tempoPreso <= 0.0f)
                            fantasmas[i].assustado = true;
                    if (VerificarVitoria()) estadoAtual = VITORIA;
                }

                // Coleta de fruta
                VerificarColetaFruta();

                if (score > highScore) highScore = score;

                textoScore.setString("SCORE\n" + std::to_string(score));
                textoHighScore.setString("HI-SCORE\n" + std::to_string(highScore));
                sf::FloatRect boundsHS = textoHighScore.getLocalBounds();
                textoHighScore.setOrigin({boundsHS.position.x + boundsHS.size.x, boundsHS.position.y});
                textoHighScore.setPosition({larguraJanela - 20.f, 24.f});

                // IA Fantasmas + colisão
                for (int i = 0; i < 4; i++) {
                    AtualizarFantasma(i);

                    bool mesmaCelula = (pacman.x == fantasmas[i].x && pacman.y == fantasmas[i].y);
                    bool cruzamento  = (pacman.x == fantasmas[i].xAnterior && pacman.y == fantasmas[i].yAnterior &&
                                        pacman.xAnterior == fantasmas[i].x && pacman.yAnterior == fantasmas[i].y);

                    if ((mesmaCelula || cruzamento) && fantasmas[i].tempoPreso <= 0.0f && !fantasmas[i].estaSaindo) {
                        if (fantasmas[i].retornando) continue;
                        else if (fantasmas[i].assustado) {
                            score += 200;
                            fantasmas[i].retornando = true;
                            fantasmas[i].assustado = false;
                        } else {
                            estadoAtual = GAMEOVER;
                        }
                    }
                }
            }
        }

        // ============================================================================
        // RENDERIZAÇÃO
        // ============================================================================

        window.clear(sf::Color::Black);

        if (estadoAtual == MENU) {
            if (blinkClock.getElapsedTime() > sf::seconds(0.5f)) { drawTextoIniciar = !drawTextoIniciar; blinkClock.restart(); }
            window.draw(textoTitulo);
            if (drawTextoIniciar) window.draw(textoIniciar);
        }
        else if (estadoAtual == JOGANDO || estadoAtual == GAMEOVER || estadoAtual == VITORIA) {
            window.draw(textoScore);
            window.draw(textoPacmanTopo);
            window.draw(textoHighScore);

            // Mapa
            for (int i = 0; i < 33; i++) {
                for (int j = 0; j < 28; j++) {
                    if (mapaAtual[i][j] == 2) {
                        quad.setPosition({j * TAMANHO_BLOCO, i * TAMANHO_BLOCO + OFFSET_Y});
                        window.draw(quad);
                    } else if (mapaAtual[i][j] == 4) {
                        portaVisual.setPosition({j * TAMANHO_BLOCO, i * TAMANHO_BLOCO + OFFSET_Y + (TAMANHO_BLOCO / 4.f)});
                        window.draw(portaVisual);
                    } else if (mapaAtual[i][j] == 1) {
                        circle.setPosition({(j * TAMANHO_BLOCO) + (TAMANHO_BLOCO / 2.f - circle.getRadius()),
                                            (i * TAMANHO_BLOCO) + OFFSET_Y + (TAMANHO_BLOCO / 2.f - circle.getRadius())});
                        window.draw(circle);
                    } else if (mapaAtual[i][j] == 3) {
                        powerPellet.setPosition({(j * TAMANHO_BLOCO) + (TAMANHO_BLOCO / 2.f - powerPellet.getRadius()),
                                                 (i * TAMANHO_BLOCO) + OFFSET_Y + (TAMANHO_BLOCO / 2.f - powerPellet.getRadius())});
                        window.draw(powerPellet);
                    }
                }
            }

            // ---- Fruta no labirinto ----
            if (sistemaFrutas.tipoAtivo != FRUTA_NENHUMA) {
                int idx = static_cast<int>(sistemaFrutas.tipoAtivo);
                float fx = FRUTA_X * TAMANHO_BLOCO + (TAMANHO_BLOCO - TAMANHO_FRUTA_MAPA) / 2.f;
                float fy = FRUTA_Y * TAMANHO_BLOCO + OFFSET_Y + (TAMANHO_BLOCO - TAMANHO_FRUTA_MAPA) / 2.f;
                spriteFrutas[idx].setScale({TAMANHO_FRUTA_MAPA / texFrutas[idx].getSize().x,
                                            TAMANHO_FRUTA_MAPA / texFrutas[idx].getSize().y});
                spriteFrutas[idx].setPosition({fx, fy});
                spriteFrutas[idx].setColor(sf::Color::White);
                window.draw(spriteFrutas[idx]);
            }

            // Pac-Man
            if (frameAnimacaoPacman == 1 || pacman.direcao == NENHUMA) {
                if (olhadireita)  { sFechadoDir.setPosition({pacman.x * TAMANHO_BLOCO, pacman.y * TAMANHO_BLOCO + OFFSET_Y});  window.draw(sFechadoDir); }
                else if (olhabaixo)  { sFechadoBaixo.setPosition({pacman.x * TAMANHO_BLOCO, pacman.y * TAMANHO_BLOCO + OFFSET_Y}); window.draw(sFechadoBaixo); }
                else if (olhaesquerda) { sFechadoEsq.setPosition({pacman.x * TAMANHO_BLOCO, pacman.y * TAMANHO_BLOCO + OFFSET_Y});  window.draw(sFechadoEsq); }
                else if (olhacima)   { sFechadoCima.setPosition({pacman.x * TAMANHO_BLOCO, pacman.y * TAMANHO_BLOCO + OFFSET_Y}); window.draw(sFechadoCima); }
            } else {
                if (olhadireita)  { spritedir.setPosition({pacman.x * TAMANHO_BLOCO, pacman.y * TAMANHO_BLOCO + OFFSET_Y});  window.draw(spritedir); }
                else if (olhabaixo)  { spritebaixo.setPosition({pacman.x * TAMANHO_BLOCO, pacman.y * TAMANHO_BLOCO + OFFSET_Y}); window.draw(spritebaixo); }
                else if (olhaesquerda) { spriteesq.setPosition({pacman.x * TAMANHO_BLOCO, pacman.y * TAMANHO_BLOCO + OFFSET_Y});  window.draw(spriteesq); }
                else if (olhacima)   { spritecima.setPosition({pacman.x * TAMANHO_BLOCO, pacman.y * TAMANHO_BLOCO + OFFSET_Y}); window.draw(spritecima); }
            }

            // Fantasmas
            for (int i = 0; i < 4; i++) {
                int indiceDirecao = 3;
                if (fantasmas[i].direcao == CIMA) indiceDirecao = 0;
                else if (fantasmas[i].direcao == BAIXO) indiceDirecao = 1;
                else if (fantasmas[i].direcao == ESQUERDA) indiceDirecao = 2;
                else if (fantasmas[i].direcao == DIREITA) indiceDirecao = 3;

                sf::Sprite& spriteAtual = spriteFantasmas[i][indiceDirecao];

                if (fantasmas[i].retornando)
                    spriteAtual.setColor(piscarOlhosMorte ? sf::Color(255, 50, 50, 100) : sf::Color(255, 255, 255, 80));
                else if (fantasmas[i].assustado)
                    spriteAtual.setColor(sf::Color(30, 60, 255, 255));
                else
                    spriteAtual.setColor(sf::Color::White);

                spriteAtual.setPosition({fantasmas[i].x * TAMANHO_BLOCO, fantasmas[i].y * TAMANHO_BLOCO + OFFSET_Y});
                window.draw(spriteAtual);
            }

            // ---- HUD inferior: frutas coletadas ----
            window.draw(linhaHUD);
            {
                const float yHUD = 33 * TAMANHO_BLOCO + OFFSET_Y + (ALTURA_HUD_BAIXO - TAMANHO_FRUTA_HUD) / 2.f;
                // Alinhar da direita para a esquerda, espaçamento de 34px
                const float espaco = 34.f;
                int total = static_cast<int>(sistemaFrutas.coletadas.size());
                float xInicio = larguraJanela - 10.f - TAMANHO_FRUTA_HUD;

                for (int i = total - 1; i >= 0; i--) {
                    int idx = static_cast<int>(sistemaFrutas.coletadas[i]);
                    float xPos = xInicio - (total - 1 - i) * espaco;
                    spriteFrutas[idx].setScale({TAMANHO_FRUTA_HUD / texFrutas[idx].getSize().x,
                                                TAMANHO_FRUTA_HUD / texFrutas[idx].getSize().y});
                    spriteFrutas[idx].setPosition({xPos, yHUD});
                    spriteFrutas[idx].setColor(sf::Color::White);
                    window.draw(spriteFrutas[idx]);
                }

                // Rótulo "FRUTAS:" à esquerda do HUD
                sf::Text textoFrutasLabel(fonte);
                textoFrutasLabel.setString("FRUTAS:");
                textoFrutasLabel.setCharacterSize(14);
                textoFrutasLabel.setFillColor(sf::Color(200, 200, 200));
                textoFrutasLabel.setPosition({10.f, yHUD + (TAMANHO_FRUTA_HUD - 14.f) / 2.f});
                window.draw(textoFrutasLabel);
            }

            // Sobreposição Game Over / Vitória
            if (estadoAtual == GAMEOVER || estadoAtual == VITORIA) {
                window.draw(painelGameOver);
                textoFinalScore.setString("SCORE: " + std::to_string(score));
                centralizarTexto(textoFinalScore);
                textoFinalScore.setPosition({larguraJanela / 2.f, alturaJanela / 2.f});
                if (estadoAtual == GAMEOVER) window.draw(textoGameOver);
                else window.draw(textoVitoria);
                window.draw(textoFinalScore);
                window.draw(textoOpcoesGO);
            }
        }

        window.display();
    }

    return 0;
}