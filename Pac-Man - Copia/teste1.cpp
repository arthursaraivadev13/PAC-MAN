#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib>
#include <optional>
#include <string>
#include <cmath>
#include <vector>
#include <ctime>
#include <fstream>

//g++ original.cpp -o pacman -std=c++20 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio && ./pacman

// Mapa original do jogo
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
// MELHORIA 3: Novo estado para tela de controles
enum ESTADO { MENU, JOGANDO, GAMEOVER, CONTROLES };
// MELHORIA 3: Opções do menu navegável
enum OpcaoMenu { OPCAO_START = 0, OPCAO_CONTROLS = 1, OPCAO_EXIT = 2 };

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

// MELHORIA 1: Estrutura para os sprites da cutscene do menu
struct SpriteMenu {
    float x;
    float y;
    float velocidade;
    bool ativo;
};

Pacman pacman;
Fantasma fantasmas[4];

bool olhadireita = true, olhaesquerda = false, olhacima = false, olhabaixo = false;
int score = 0;
int highScore = 0; 
float tempoAssustadoRestante = 0.0f; 
int frameAnimacaoPacman = 0;

// MELHORIA 5: Funções para ler/salvar High Score em arquivo
void CarregarHighScore() {
    std::ifstream arquivo("highscore.txt");
    if (arquivo.is_open()) {
        arquivo >> highScore;
        arquivo.close();
    } else {
        highScore = 0;
    }
}

void SalvarHighScore() {
    std::ofstream arquivo("highscore.txt");
    if (arquivo.is_open()) {
        arquivo << highScore;
        arquivo.close();
    }
}

void centralizarTexto(sf::Text& texto) {
    sf::FloatRect bounds = texto.getLocalBounds();
    texto.setOrigin({bounds.position.x + bounds.size.x / 2.0f, bounds.position.y + bounds.size.y / 2.0f});
}

void ResetarJogo() {
    pacman.x = 14; pacman.y = 21;
    pacman.xAnterior = 14; pacman.yAnterior = 21;
    pacman.direcao = NENHUMA; pacman.proxima_direcao = NENHUMA;
    olhadireita = true; olhaesquerda = false; olhacima = false; olhabaixo = false;
    
    fantasmas[0] = {12, 14, 12, 14, NENHUMA, 0, false, false, false, 0.0f, false};  
    fantasmas[1] = {13, 14, 13, 14, NENHUMA, 1, false, false, false, 4.0f, false};  
    fantasmas[2] = {14, 14, 14, 14, NENHUMA, 2, false, false, false, 8.0f, false};  
    fantasmas[3] = {15, 14, 15, 14, NENHUMA, 3, false, false, false, 12.0f, false}; 
    
    score = 0;
    tempoAssustadoRestante = 0.0f;

    for (int i = 0; i < 33; i++) {
        for (int j = 0; j < 28; j++) {
            mapaAtual[i][j] = mapaOriginal[i][j];
        }
    }
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

void AtualizarFantasma(int index) {
    if (fantasmas[index].tempoPreso > 0.0f) {
        return; 
    }

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

    if (fy >= 13 && fy <= 14 && fx >= 11 && fx <= 16 && !fantasmas[index].retornando) {
        fantasmas[index].estaSaindo = true;
    }

    if (fantasmas[index].estaSaindo && fy <= 11) {
        fantasmas[index].estaSaindo = false;
    }

    if (fantasmas[index].assustado && !fantasmas[index].retornando && !fantasmas[index].estaSaindo) {
        fantasmas[index].sinalizadorVelocidade = !fantasmas[index].sinalizadorVelocidade;
        if (fantasmas[index].sinalizadorVelocidade) return; 
    }

    if (fx < 0) { fantasmas[index].x = 27; return; }
    if (fx > 27) { fantasmas[index].x = 0; return; }

    int targetX = pacman.x;
    int targetY = pacman.y;

    if (fantasmas[index].retornando) {
        targetX = 14; targetY = 14;
    }
    else if (fantasmas[index].estaSaindo) {
        targetX = 14; targetY = 11; 
    }
    else if (fantasmas[index].assustado) {
        if (tipo == 0) { targetX = 0; targetY = 0; }
        else if (tipo == 1) { targetX = 27; targetY = 0; }
        else if (tipo == 2) { targetX = 0; targetY = 32; }
        else if (tipo == 3) { targetX = 27; targetY = 32; }
    } 
    else {
        if (tipo == 1) { 
            if (pacman.direcao == CIMA) { targetY -= 4; targetX -= 4; }
            else if (pacman.direcao == BAIXO) targetY += 4;
            else if (pacman.direcao == ESQUERDA) targetX -= 4;
            else if (pacman.direcao == DIREITA) targetX += 4;
        }
        else if (tipo == 2) { 
            if (pacman.direcao == CIMA) targetY += 2;
            else if (pacman.direcao == BAIXO) targetY -= 2;
            else if (pacman.direcao == ESQUERDA) targetX += 2;
            else if (pacman.direcao == DIREITA) targetX -= 2;
        }
        else if (tipo == 3) { 
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

        int proximoX = fx;
        int proximoY = fy;

        if (d == CIMA) proximoY--;
        else if (d == BAIXO) proximoY++;
        else if (d == ESQUERDA) proximoX--;
        else if (d == DIREITA) proximoX++;

        if (proximoY == 13 && (proximoX < 0 || proximoX > 27)) {
        } else {
            if (proximoY < 0 || proximoY >= 33 || proximoX < 0 || proximoX >= 28) continue;
            if (mapaAtual[proximoY][proximoX] == 2) continue;
            
            if (mapaAtual[proximoY][proximoX] == 4) {
                if (!fantasmas[index].retornando && !fantasmas[index].estaSaindo) continue;
            }
        }

        float dist = obterDistanciaQuad(proximoX, proximoY, targetX, targetY);
        if (dist < menorDistancia) {
            menorDistancia = dist;
            melhorDirecao = d;
        }
    }

    if (melhorDirecao == NENHUMA) {
        for (int i = 0; i < 4; i++) {
            Direcao d = direcoesPossiveis[i];
            int px = fx + (d == DIREITA) - (d == ESQUERDA);
            int py = fy + (d == BAIXO) - (d == CIMA);
            if (py >= 0 && py < 33 && px >= 0 && px < 28 && mapaAtual[py][px] != 2) {
                melhorDirecao = d;
                break;
            }
        }
    }

    fantasmas[index].direcao = melhorDirecao;
    if (melhorDirecao == CIMA) fantasmas[index].y--;
    else if (melhorDirecao == BAIXO) fantasmas[index].y++;
    else if (melhorDirecao == ESQUERDA) fantasmas[index].x--;
    else if (melhorDirecao == DIREITA) fantasmas[index].x++;
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    // MELHORIA 5: Carrega o highscore salvo em disco ao iniciar
    CarregarHighScore();
    
    ResetarJogo(); 
    ESTADO estadoAtual = MENU; 

    const float TAMANHO_BLOCO = 32.f; 
    const float OFFSET_Y = 64.f; 
    
    const unsigned int larguraJanela = static_cast<unsigned int>(28 * TAMANHO_BLOCO);
    const unsigned int alturaJanela = static_cast<unsigned int>(33 * TAMANHO_BLOCO + OFFSET_Y); 

    sf::RenderWindow window(sf::VideoMode({larguraJanela, alturaJanela}), "Pac-Man");
    window.setFramerateLimit(60);

    sf::RectangleShape quad({TAMANHO_BLOCO, TAMANHO_BLOCO});
    quad.setFillColor(sf::Color::Black);
    quad.setOutlineThickness(-3.f); 
    quad.setOutlineColor(sf::Color(25, 25, 180)); 

    sf::RectangleShape portaVisual({TAMANHO_BLOCO, TAMANHO_BLOCO / 4.f});
    portaVisual.setFillColor(sf::Color(255, 184, 222, 200));

    sf::RectangleShape painelGameOver({static_cast<float>(larguraJanela), static_cast<float>(alturaJanela)});
    painelGameOver.setFillColor(sf::Color(0, 0, 0, 180));

    sf::CircleShape circle(4.f); 
    circle.setFillColor(sf::Color(255, 184, 151)); 

    sf::CircleShape powerPellet(8.f);
    powerPellet.setFillColor(sf::Color(255, 184, 151)); 

    sf::Font fonte;
    if (!fonte.openFromFile("retrofonte.ttf")) { 
        std::cout << "Aviso: retrofonte.ttf não encontrada.\n";
    }
    
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

    // MELHORIA 2: Título no menu com efeito de "respiração" (pulse)
    sf::Text textoTitulo(fonte);
    textoTitulo.setString("PAC-MAN");
    textoTitulo.setCharacterSize(80);
    textoTitulo.setFillColor(sf::Color::Yellow);
    centralizarTexto(textoTitulo);
    textoTitulo.setPosition({larguraJanela / 2.f, alturaJanela / 4.f});

    // MELHORIA 3: Textos das opções navegáveis do menu
    const int NUM_OPCOES = 3;
    std::string nomesOpcoes[NUM_OPCOES] = {"START GAME", "CONTROLS", "EXIT"};
    sf::Text textosOpcoes[NUM_OPCOES] = {sf::Text(fonte), sf::Text(fonte), sf::Text(fonte)};
    OpcaoMenu opcaoSelecionada = OPCAO_START;

    for (int i = 0; i < NUM_OPCOES; i++) {
        textosOpcoes[i].setString(nomesOpcoes[i]);
        textosOpcoes[i].setCharacterSize(24);
        centralizarTexto(textosOpcoes[i]);
        textosOpcoes[i].setPosition({larguraJanela / 2.f, alturaJanela / 2.f + i * 50.f});
    }

    // MELHORIA 3: Seta indicadora da opção selecionada (mini Pac-Man textual)
    sf::Text textoSeta(fonte);
    textoSeta.setString(">");
    textoSeta.setCharacterSize(24);
    textoSeta.setFillColor(sf::Color::Yellow);

    // MELHORIA 5: Texto do High Score no menu com destaque
    sf::Text textoHighScoreMenu(fonte);
    textoHighScoreMenu.setCharacterSize(22);
    textoHighScoreMenu.setFillColor(sf::Color(255, 215, 0)); // Dourado

    sf::Text textoHighScoreLabel(fonte);
    textoHighScoreLabel.setString("HI-SCORE");
    textoHighScoreLabel.setCharacterSize(16);
    textoHighScoreLabel.setFillColor(sf::Color(200, 200, 200));
    centralizarTexto(textoHighScoreLabel);
    textoHighScoreLabel.setPosition({largurraJanela / 2.f, alturaJanela / 4.f + 90.f});

    // MELHORIA 3: Tela de controles
    sf::Text textoTelaControles(fonte);
    textoTelaControles.setString(
        "CONTROLS\n\n"
        "Arrow Keys - Move Pac-Man\n\n"
        "Eat dots    +10 pts\n"
        "Power pellet +50 pts\n"
        "Eat ghost  +200 pts\n\n"
        "ESC - Quit game\n\n"
        "Press BACKSPACE to return"
    );
    textoTelaControles.setCharacterSize(20);
    textoTelaControles.setFillColor(sf::Color::White);
    centralizarTexto(textoTelaControles);
    textoTelaControles.setPosition({larguraJanela / 2.f, alturaJanela / 2.f});

    sf::Text textoGameOver(fonte);
    textoGameOver.setString("GAME OVER BB");
    textoGameOver.setCharacterSize(60);
    textoGameOver.setFillColor(sf::Color::Red);
    centralizarTexto(textoGameOver);
    textoGameOver.setPosition({larguraJanela / 2.f, alturaJanela / 3.f});

    sf::Text textoOpcoesGO(fonte);
    textoOpcoesGO.setString("PRESS 'R' TO RESTART\n\nPRESS 'M' FOR MENU");
    textoOpcoesGO.setCharacterSize(20);
    textoOpcoesGO.setFillColor(sf::Color::White);
    centralizarTexto(textoOpcoesGO);
    textoOpcoesGO.setPosition({larguraJanela / 2.f, alturaJanela / 1.5f});

    sf::Text textoFinalScore(fonte);
    textoFinalScore.setCharacterSize(25);
    textoFinalScore.setFillColor(sf::Color::Yellow);

    // Texturas Pac-man
    sf::Texture texture, textureCima, textureBaixo, textureEsq;
    sf::Texture texFechadoDir, texFechadoCima, texFechadoBaixo, texFechadoEsq;

    if (!texture.loadFromFile("pacman.png") || !textureCima.loadFromFile("pacman-cima.png") ||
        !textureBaixo.loadFromFile("pacman-baixo.png") || !textureEsq.loadFromFile("pacman-esq.png") ||
        !texFechadoDir.loadFromFile("fechado-dir.png") || !texFechadoCima.loadFromFile("fechado-cima.png") ||
        !texFechadoBaixo.loadFromFile("fechado-baixo.png") || !texFechadoEsq.loadFromFile("fechado-esq.png")) {
        std::cout << "Aviso: Imagens do Pac-Man ausentes.\n";
    }

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

    // Carregamento dos Fantasmas
    std::string coresFantasmas[4] = {"vermelho", "rosa", "azul", "laranja"};
    std::string sufixosDir[4] = {"cima", "baixo", "esq", "dir"};
    
    sf::Texture texFantasmas[4][4];
    std::vector<std::vector<sf::Sprite>> spriteFantasmas(4, std::vector<sf::Sprite>());

    for (int f = 0; f < 4; f++) {
        for (int d = 0; d < 4; d++) {
            std::string nomeArquivo = "fantasma-" + coresFantasmas[f] + "-" + sufixosDir[d] + ".png";
            
            if (!texFantasmas[f][d].loadFromFile(nomeArquivo)) {
                std::cout << "Erro crítico ao carregar: " << nomeArquivo << "\n";
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

    // MELHORIA 4: Carregamento de áudio
    // sf::Music é usado para o loop de menu (suporta setLooping); sf::Sound para efeitos curtos
    sf::Music somBgMenu;
    sf::SoundBuffer bufferCoin;
    sf::Sound somCoin(bufferCoin);
    bool audioCarregado = false;
    bool coinTocado = false;
    float tempoCoin = 0.0f;
    bool aguardandoIniciar = false;

    if (somBgMenu.openFromFile("menu.mp3") && bufferCoin.loadFromFile("coin.mp3")) {
        audioCarregado = true;
        somCoin.setBuffer(bufferCoin);
        somBgMenu.setLooping(true);
        somBgMenu.play();
    } else {
        std::cout << "Aviso: Arquivos de áudio ausentes (menu.mp3, coin.mp3). Jogo funciona sem som.\n";
    }

    // MELHORIA 1: Inicialização da cutscene animada do menu
    // Fase 0 = Pac-Man perseguido (direita → esquerda)
    // Fase 1 = Pac-Man perseguindo (esquerda → direita, fantasmas azuis)
    int faseCutscene = 0;
    float posXCutscene = static_cast<float>(larguraJanela) + 32.f; // Pac-Man começa fora da tela (direita)
    float posYCutscene = alturaJanela * 0.72f;
    const float VEL_CUTSCENE = 120.f; // pixels por segundo

    // Sprites da cutscene usam os mesmos sprites do jogo
    // (spritedir, spriteesq e spriteFantasmas já carregados)

    sf::Clock clock;
    sf::Clock blinkClock;
    sf::Clock tempoDelta;
    sf::Clock tempoTotal; // Para efeitos baseados em seno
    bool piscarOlhosMorte = false;

    while (window.isOpen()) {
        float dt = tempoDelta.restart().asSeconds();
        float tempoTotalSeg = tempoTotal.getElapsedTime().asSeconds();

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                SalvarHighScore(); // MELHORIA 5: Salva ao fechar
                window.close();
            }
            
            else if (estadoAtual == MENU) {
                if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                    // MELHORIA 3: Navegação com setas no menu
                    if (keyPressed->scancode == sf::Keyboard::Scancode::Up) {
                        int op = static_cast<int>(opcaoSelecionada) - 1;
                        if (op < 0) op = NUM_OPCOES - 1;
                        opcaoSelecionada = static_cast<OpcaoMenu>(op);
                    }
                    else if (keyPressed->scancode == sf::Keyboard::Scancode::Down) {
                        int op = (static_cast<int>(opcaoSelecionada) + 1) % NUM_OPCOES;
                        opcaoSelecionada = static_cast<OpcaoMenu>(op);
                    }
                    else if (keyPressed->scancode == sf::Keyboard::Scancode::Enter) {
                        if (opcaoSelecionada == OPCAO_EXIT) {
                            SalvarHighScore();
                            window.close();
                        }
                        else if (opcaoSelecionada == OPCAO_CONTROLS) {
                            estadoAtual = CONTROLES;
                        }
                        else if (opcaoSelecionada == OPCAO_START) {
                            // MELHORIA 4: Toca o som de moeda e aguarda 1 segundo
                            if (audioCarregado) {
                                somBgMenu.stop();
                                somCoin.play();
                            }
                            coinTocado = true;
                            aguardandoIniciar = true;
                            tempoCoin = 0.0f;
                        }
                    }
                }
            }

            else if (estadoAtual == CONTROLES) {
                if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                    if (keyPressed->scancode == sf::Keyboard::Scancode::Backspace ||
                        keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
                        estadoAtual = MENU;
                        if (audioCarregado && somBgMenu.getStatus() != sf::Music::Status::Playing)
                            somBgMenu.play();
                    }
                }
            }
            
            else if (estadoAtual == GAMEOVER) {
                if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                    if (keyPressed->scancode == sf::Keyboard::Scancode::R) {
                        ResetarJogo();
                        estadoAtual = JOGANDO; 
                    }
                    else if (keyPressed->scancode == sf::Keyboard::Scancode::M) {
                        estadoAtual = MENU;
                        // MELHORIA 1: Reinicia a cutscene ao voltar ao menu
                        faseCutscene = 0;
                        posXCutscene = static_cast<float>(larguraJanela) + 32.f;
                        if (audioCarregado && somBgMenu.getStatus() != sf::Music::Status::Playing)
                            somBgMenu.play();
                    }
                }
            }
            
            else if (estadoAtual == JOGANDO) {
                if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                    if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                        window.close();
                    else if (keyPressed->scancode == sf::Keyboard::Scancode::Left)
                        pacman.proxima_direcao = ESQUERDA;
                    else if (keyPressed->scancode == sf::Keyboard::Scancode::Right)
                        pacman.proxima_direcao = DIREITA;
                    else if (keyPressed->scancode == sf::Keyboard::Scancode::Up)
                        pacman.proxima_direcao = CIMA;
                    else if (keyPressed->scancode == sf::Keyboard::Scancode::Down)
                        pacman.proxima_direcao = BAIXO;
                }
            }
        }

        // MELHORIA 4: Aguarda 1 segundo do som de moeda antes de iniciar
        if (aguardandoIniciar) {
            tempoCoin += dt;
            if (tempoCoin >= 1.0f) {
                aguardandoIniciar = false;
                ResetarJogo();
                estadoAtual = JOGANDO;
            }
        }

        if (estadoAtual == JOGANDO) {
            if (tempoAssustadoRestante > 0.0f) {
                tempoAssustadoRestante -= dt;
                if (tempoAssustadoRestante <= 0.0f) {
                    for (int i = 0; i < 4; i++) {
                        if(!fantasmas[i].retornando) fantasmas[i].assustado = false;
                    }
                }
            }

            for (int i = 0; i < 4; i++) {
                if (fantasmas[i].tempoPreso > 0.0f) {
                    fantasmas[i].tempoPreso -= dt;
                }
            }

            if (clock.getElapsedTime() > sf::seconds(0.18f)) {
                clock.restart();

                frameAnimacaoPacman = (frameAnimacaoPacman == 0) ? 1 : 0;
                piscarOlhosMorte = !piscarOlhosMorte;

                pacman.xAnterior = pacman.x;
                pacman.yAnterior = pacman.y;

                if (pacman.proxima_direcao == CIMA && mapaAtual[pacman.y - 1][pacman.x] != 2 && mapaAtual[pacman.y - 1][pacman.x] != 4)
                    pacman.direcao = CIMA;
                else if (pacman.proxima_direcao == BAIXO && mapaAtual[pacman.y + 1][pacman.x] != 2 && mapaAtual[pacman.y + 1][pacman.x] != 4)
                    pacman.direcao = BAIXO;
                else if (pacman.proxima_direcao == ESQUERDA && (pacman.x == 0 || (mapaAtual[pacman.y][pacman.x - 1] != 2 && mapaAtual[pacman.y][pacman.x - 1] != 4)))
                    pacman.direcao = ESQUERDA;
                else if (pacman.proxima_direcao == DIREITA && (pacman.x == 27 || (mapaAtual[pacman.y][pacman.x + 1] != 2 && mapaAtual[pacman.y][pacman.x + 1] != 4)))
                    pacman.direcao = DIREITA;

                if (pacman.direcao == CIMA) {
                    if (mapaAtual[pacman.y - 1][pacman.x] != 2 && mapaAtual[pacman.y - 1][pacman.x] != 4) { olhacima = true; olhabaixo = false; olhadireita = false; olhaesquerda = false; pacman.y--; } 
                    else { pacman.direcao = NENHUMA; }
                }
                else if (pacman.direcao == BAIXO) {
                    if (mapaAtual[pacman.y + 1][pacman.x] != 2 && mapaAtual[pacman.y + 1][pacman.x] != 4) { olhabaixo = true; olhacima = false; olhadireita = false; olhaesquerda = false; pacman.y++; } 
                    else { pacman.direcao = NENHUMA; }
                }
                else if (pacman.direcao == ESQUERDA) {
                    if (pacman.x == 0) { pacman.x = 27; } 
                    else if (mapaAtual[pacman.y][pacman.x - 1] != 2 && mapaAtual[pacman.y][pacman.x - 1] != 4) { olhaesquerda = true; olhadireita = false; olhacima = false; olhabaixo = false; pacman.x--; } 
                    else { pacman.direcao = NENHUMA; }
                }
                else if (pacman.direcao == DIREITA) {
                    if (pacman.x == 27) { pacman.x = 0; } 
                    else if (mapaAtual[pacman.y][pacman.x + 1] != 2 && mapaAtual[pacman.y][pacman.x + 1] != 4) { olhadireita = true; olhacima = false; olhabaixo = false; olhaesquerda = false; pacman.x++; } 
                    else { pacman.direcao = NENHUMA; }
                }

                if (mapaAtual[pacman.y][pacman.x] == 1) {
                    score += 10;
                    mapaAtual[pacman.y][pacman.x] = 0; 
                } 
                else if (mapaAtual[pacman.y][pacman.x] == 3) {
                    score += 50;
                    mapaAtual[pacman.y][pacman.x] = 0; 
                    tempoAssustadoRestante = 7.0f; 
                    for (int i = 0; i < 4; i++) {
                        if (!fantasmas[i].retornando && fantasmas[i].tempoPreso <= 0.0f) {
                            fantasmas[i].assustado = true;
                        }
                    }
                }

                // MELHORIA 5: Atualiza e salva o High Score em tempo real
                if (score > highScore) {
                    highScore = score;
                    SalvarHighScore();
                }
                
                textoScore.setString("SCORE\n" + std::to_string(score));
                textoHighScore.setString("HI-SCORE\n" + std::to_string(highScore));

                sf::FloatRect boundsHS = textoHighScore.getLocalBounds();
                textoHighScore.setOrigin({boundsHS.position.x + boundsHS.size.x, boundsHS.position.y}); 
                textoHighScore.setPosition({larguraJanela - 20.f, 24.f}); 

                for (int i = 0; i < 4; i++) {
                    AtualizarFantasma(i);

                    bool mesmaCelula = (pacman.x == fantasmas[i].x && pacman.y == fantasmas[i].y);
                    bool cruzamento = (pacman.x == fantasmas[i].xAnterior && pacman.y == fantasmas[i].yAnterior &&
                                       pacman.xAnterior == fantasmas[i].x && pacman.yAnterior == fantasmas[i].y);

                    if ((mesmaCelula || cruzamento) && fantasmas[i].tempoPreso <= 0.0f && !fantasmas[i].estaSaindo) {
                        if (fantasmas[i].retornando) {
                            continue; 
                        }
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

        // MELHORIA 1: Atualização da cutscene animada no menu
        if (estadoAtual == MENU && !aguardandoIniciar) {
            if (faseCutscene == 0) {
                // Fase 0: Pac-Man (olhando esquerda) + fantasmas normais, movendo da direita para esquerda
                posXCutscene -= VEL_CUTSCENE * dt;
                if (posXCutscene < -5.f * TAMANHO_BLOCO) {
                    // Troca de fase: agora a virada
                    faseCutscene = 1;
                    posXCutscene = -TAMANHO_BLOCO; // começa fora da tela pela esquerda
                }
            } else {
                // Fase 1: Pac-Man (olhando direita) + fantasmas azuis, movendo da esquerda para direita
                posXCutscene += VEL_CUTSCENE * dt;
                if (posXCutscene > static_cast<float>(larguraJanela) + 5.f * TAMANHO_BLOCO) {
                    // Reinicia a animação
                    faseCutscene = 0;
                    posXCutscene = static_cast<float>(larguraJanela) + TAMANHO_BLOCO;
                }
            }
        }

        // ==================== RENDERIZAÇÃO ====================
        window.clear(sf::Color::Black); 
        
        if (estadoAtual == MENU || aguardandoIniciar) {
            // MELHORIA 2: Título com efeito de "respiração" usando sin()
            float pulso = std::sin(tempoTotalSeg * 2.0f); // oscila entre -1 e 1
            float escalaBase = 1.0f;
            float escalaAtual = escalaBase + pulso * 0.04f; // variação suave de ±4%
            textoTitulo.setScale({escalaAtual, escalaAtual});
            // Leve variação de brilho no amarelo do título
            uint8_t brilho = static_cast<uint8_t>(200 + pulso * 55);
            textoTitulo.setFillColor(sf::Color(255, brilho, 0));
            window.draw(textoTitulo);

            // MELHORIA 5: High Score em destaque dourado no menu
            textoHighScoreMenu.setString(std::to_string(highScore));
            centralizarTexto(textoHighScoreMenu);
            textoHighScoreMenu.setPosition({larguraJanela / 2.f, alturaJanela / 4.f + 115.f});
            // Efeito de pulsação dourada no high score também
            float pulsoHS = std::sin(tempoTotalSeg * 3.0f + 1.0f);
            uint8_t brilhoHS = static_cast<uint8_t>(180 + pulsoHS * 75);
            textoHighScoreMenu.setFillColor(sf::Color(255, brilhoHS, 0));
            window.draw(textoHighScoreLabel);
            window.draw(textoHighScoreMenu);

            // MELHORIA 3: Opções navegáveis
            for (int i = 0; i < NUM_OPCOES; i++) {
                if (i == static_cast<int>(opcaoSelecionada)) {
                    textosOpcoes[i].setFillColor(sf::Color::Yellow);
                    // Posiciona a seta ">" à esquerda da opção selecionada
                    sf::FloatRect bounds = textosOpcoes[i].getGlobalBounds();
                    textoSeta.setPosition({bounds.position.x - 30.f, bounds.position.y});
                    window.draw(textoSeta);
                } else {
                    textosOpcoes[i].setFillColor(sf::Color(180, 180, 180));
                }
                window.draw(textosOpcoes[i]);
            }

            // MELHORIA 1: Renderização da cutscene
            float frameAnim = std::fmod(tempoTotalSeg * 5.5f, 2.0f) < 1.0f ? 0.f : 1.f; // alterna frame
            bool bocaAberta = (frameAnim < 1.0f);

            if (faseCutscene == 0) {
                // Pac-Man olhando para a esquerda, sendo perseguido
                sf::Sprite& sPacCutscene = bocaAberta ? spriteesq : sFechadoEsq;
                sPacCutscene.setPosition({posXCutscene, posYCutscene});
                window.draw(sPacCutscene);

                // 4 fantasmas normais atrás do Pac-Man (à direita dele)
                for (int f = 0; f < 4; f++) {
                    float offsetX = posXCutscene + (f + 1) * (TAMANHO_BLOCO + 8.f);
                    if (offsetX < static_cast<float>(larguraJanela) + TAMANHO_BLOCO) {
                        sf::Sprite& spF = spriteFantasmas[f][2]; // índice 2 = esq
                        spF.setColor(sf::Color::White);
                        spF.setPosition({offsetX, posYCutscene});
                        window.draw(spF);
                    }
                }
            } else {
                // Pac-Man olhando para a direita, perseguindo fantasmas azuis
                sf::Sprite& sPacCutscene = bocaAberta ? spritedir : sFechadoDir;
                sPacCutscene.setPosition({posXCutscene, posYCutscene});
                window.draw(sPacCutscene);

                // 4 fantasmas azuis (assustados) à esquerda do Pac-Man (fugindo)
                for (int f = 0; f < 4; f++) {
                    float offsetX = posXCutscene - (f + 1) * (TAMANHO_BLOCO + 8.f);
                    if (offsetX > -TAMANHO_BLOCO) {
                        sf::Sprite& spF = spriteFantasmas[f][3]; // índice 3 = dir
                        spF.setColor(sf::Color(30, 60, 255, 255)); // azul assustado
                        spF.setPosition({offsetX, posYCutscene});
                        window.draw(spF);
                    }
                }
            }
        }

        else if (estadoAtual == CONTROLES) {
            // MELHORIA 3: Tela de controles simples
            window.draw(textoTelaControles);
        }

        else if (estadoAtual == JOGANDO || estadoAtual == GAMEOVER) {
            window.draw(textoScore);
            window.draw(textoPacmanTopo);
            window.draw(textoHighScore);

            for (int i = 0; i < 33; i++) {
                for (int j = 0; j < 28; j++) {
                    if (mapaAtual[i][j] == 2) {
                        quad.setPosition({j * TAMANHO_BLOCO, i * TAMANHO_BLOCO + OFFSET_Y});
                        window.draw(quad);
                    }
                    else if (mapaAtual[i][j] == 4) {
                        portaVisual.setPosition({j * TAMANHO_BLOCO, i * TAMANHO_BLOCO + OFFSET_Y + (TAMANHO_BLOCO / 4.f)});
                        window.draw(portaVisual);
                    }
                    else if (mapaAtual[i][j] == 1) {
                        float offsetX = (TAMANHO_BLOCO / 2.f) - circle.getRadius();
                        float offsetY = (TAMANHO_BLOCO / 2.f) - circle.getRadius();
                        circle.setPosition({(j * TAMANHO_BLOCO) + offsetX, (i * TAMANHO_BLOCO) + OFFSET_Y + offsetY});
                        window.draw(circle);
                    }
                    else if (mapaAtual[i][j] == 3) { 
                        float offsetX = (TAMANHO_BLOCO / 2.f) - powerPellet.getRadius();
                        float offsetY = (TAMANHO_BLOCO / 2.f) - powerPellet.getRadius();
                        powerPellet.setPosition({(j * TAMANHO_BLOCO) + offsetX, (i * TAMANHO_BLOCO) + OFFSET_Y + offsetY});
                        window.draw(powerPellet);
                    }
                }
            }

            if (frameAnimacaoPacman == 1 || pacman.direcao == NENHUMA) {
                if (olhadireita) { sFechadoDir.setPosition({pacman.x * TAMANHO_BLOCO, pacman.y * TAMANHO_BLOCO + OFFSET_Y}); window.draw(sFechadoDir); }
                else if (olhabaixo) { sFechadoBaixo.setPosition({pacman.x * TAMANHO_BLOCO, pacman.y * TAMANHO_BLOCO + OFFSET_Y}); window.draw(sFechadoBaixo); }
                else if (olhaesquerda) { sFechadoEsq.setPosition({pacman.x * TAMANHO_BLOCO, pacman.y * TAMANHO_BLOCO + OFFSET_Y}); window.draw(sFechadoEsq); }
                else if (olhacima) { sFechadoCima.setPosition({pacman.x * TAMANHO_BLOCO, pacman.y * TAMANHO_BLOCO + OFFSET_Y}); window.draw(sFechadoCima); }
            } 
            else {
                if (olhadireita) { spritedir.setPosition({pacman.x * TAMANHO_BLOCO, pacman.y * TAMANHO_BLOCO + OFFSET_Y}); window.draw(spritedir); }
                else if (olhabaixo) { spritebaixo.setPosition({pacman.x * TAMANHO_BLOCO, pacman.y * TAMANHO_BLOCO + OFFSET_Y}); window.draw(spritebaixo); }
                else if (olhaesquerda) { spriteesq.setPosition({pacman.x * TAMANHO_BLOCO, pacman.y * TAMANHO_BLOCO + OFFSET_Y}); window.draw(spriteesq); }
                else if (olhacima) { spritecima.setPosition({pacman.x * TAMANHO_BLOCO, pacman.y * TAMANHO_BLOCO + OFFSET_Y}); window.draw(spritecima); }
            }

            for (int i = 0; i < 4; i++) {
                int indiceDirecao = 3; 
                if (fantasmas[i].direcao == CIMA) indiceDirecao = 0;
                else if (fantasmas[i].direcao == BAIXO) indiceDirecao = 1;
                else if (fantasmas[i].direcao == ESQUERDA) indiceDirecao = 2;
                else if (fantasmas[i].direcao == DIREITA) indiceDirecao = 3;

                sf::Sprite& spriteAtual = spriteFantasmas[i][indiceDirecao];

                if (fantasmas[i].retornando) {
                    spriteAtual.setColor(piscarOlhosMorte ? sf::Color(255, 50, 50, 100) : sf::Color(255, 255, 255, 80));
                }
                else if (fantasmas[i].assustado) {
                    spriteAtual.setColor(sf::Color(30, 60, 255, 255));
                } 
                else {
                    spriteAtual.setColor(sf::Color::White); 
                }

                spriteAtual.setPosition({fantasmas[i].x * TAMANHO_BLOCO, fantasmas[i].y * TAMANHO_BLOCO + OFFSET_Y});
                window.draw(spriteAtual);
            }

            if (estadoAtual == GAMEOVER) {
                window.draw(painelGameOver);

                textoFinalScore.setString("SCORE: " + std::to_string(score));
                centralizarTexto(textoFinalScore);
                textoFinalScore.setPosition({larguraJanela / 2.f, alturaJanela / 2.f}); 
                
                window.draw(textoGameOver);
                window.draw(textoFinalScore);
                window.draw(textoOpcoesGO);
            }
        }

        window.display(); 
    }

    SalvarHighScore(); // MELHORIA 5: Garante salvamento ao sair pelo X
    return 0;
}