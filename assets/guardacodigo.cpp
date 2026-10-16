#include <SFML/Graphics.hpp>
#include <optional>
#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <cmath>
#include <SFML/Audio.hpp>  //bbt do áudio
using namespace std;

// FANTASMA QUE TELEPORTA PELO mapaatual
// FANTASMA QUE SEGUE A FRUTA ESPECIAL LA
// FANTASMA CAMPER QUE ESPERA NO CANTINHO DA PILULA DE FORÇA
// FANTASMA QUE CONSEGUE ATRAVESSAR UMA PAREDE (FANTASMA DE VERDADE)

// mapaatual CORRIGIDO: 31 linhas por 28 colunas reais.
//  com a casa dos fantasmas oca no centro e apenas um túnel central.
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
int mapaatual[33][28]; // essa será a matriz usada efetivamente no jogo

int score = 0; // contador de pontos

enum ESTADO
{
    MENU,
    JOGANDO,
    GAMEOVER,
    VITORIA
}; // variável enum que lista os estados do jogo
enum DIRECAO
{
    NENHUMA,
    CIMA,
    BAIXO,
    ESQUERDA,
    DIREITA
}; // variavel enum que lista os movimentos

struct Pacman
{                  // struct que agrupa todas as variáveis do Pacman
    int posx = 14; // Posição inicial
    int posy = 21;
    DIRECAO direcaoatual = NENHUMA;   // variavel que realiza, caso possivel, o movimento
    DIRECAO proximadirecao = NENHUMA; // variavel que guarda o movimento que o jogador quer fazer
    bool abre = true;                //variável que guarda se a boca do pacman esta aberta ou fechada (animação)
    sf::Clock animacao;               // relógio que controla a animação de abrir e fechar a boca do pacman
    float posAnteriorX = 0;          //guardam a posição anterior do pacman - pra ver se ele está parado na hora de animar
    float posAnteriorY = 0;
};
Pacman pacman; // variável de tipo Pacman

enum ESTADOFANTASMA
{
    PRESO,
    SAINDO,
    LIVRE
}; // enum que lista os estados do fantasma

struct Fantasma
{ // struct que agrupa todas as variáveis dos Fantasmas
    int posx;
    int posy;
    DIRECAO direcaoatual = NENHUMA; // seguem a mesma ideia de movimento do pacman
    DIRECAO proximadirecao = NENHUMA;
    ESTADOFANTASMA estadoatual = PRESO; // variável que guarda qual o estado atual do fantasma
    sf::Clock relogio;                  // relógio pra cada fantasma
};

Fantasma aleatorio = {15, 14, NENHUMA, NENHUMA, PRESO}; // variavel que indica a posição, a direção, e o estado do fantasma aleatorio
Fantasma cacador = {13, 14, NENHUMA, NENHUMA, PRESO};   // variavel que indica a posição, a direção, e o estado do fantasma cacador

struct caminhos
{ // struct que guarda a direção do movimento e a distância entre o fantasma caçador e o pacman
    DIRECAO direcao;
    float distancia;
};

bool comparadistancias(caminhos a, caminhos b)
{ // função utilizada no sort do fantasma caçador, analisa duas distâncias e retorna true ou false, assim o sort sabe qual caminhovalido colocar na frente no vector
    return a.distancia < b.distancia;
}
void ResetarJogo() //função que reseta o jogo, coloca pacman e fantasmas em suas posições originais, reseta o score, e redesenha o mapa
{
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



int main()
{
    // copia a matriz original na matriz usada pelo jogo
    for (int i = 0; i < 33; i++)
    {
        for (int j = 0; j < 28; j++)
            mapaatual[i][j] = mapaoriginal[i][j];
    }

    ESTADO estadoatual = MENU;        // váriavel que guarda qual o estado do jogo
    const float TAMANHO_BLOCO = 32.f; // tamanho de cada bloco
    const float OFFSET_Y = 64.f;      // variável que guarda o distanciamente que coloca 2 linhas de bloco preto no topo da tela

    const unsigned int larguraJanela = static_cast<unsigned int>(28 * TAMANHO_BLOCO);           // calcula largura da janela
    const unsigned int alturaJanela = static_cast<unsigned int>(33 * TAMANHO_BLOCO + OFFSET_Y); // calcula altura da janela

    // Ajusta a janela perfeitamente para o tamanho do mapaatual
    sf::RenderWindow window(sf::VideoMode({larguraJanela, alturaJanela}), "Pac-Man UFV");

   sf::Music musicaFundo;
    if (!musicaFundo.openFromFile("moonlight.mp3")) {
        std::cout << "Erro ao carregar a moonlight.mp3\n";
    } else {
        musicaFundo.setLooping(true);   // Diz para repetir infinitamente
        musicaFundo.setVolume(100.f); // Ajusta o volume
        musicaFundo.play();          //COMEÇA A TOCAR AQUI E NÃO PARA MAIS!
    }
    // cria um quadrado de tamanho 20 para as paredes
    sf::RectangleShape quad({32.f, 32.f});
    quad.setFillColor(sf::Color(0, 100, 200));
    quad.setOutlineThickness(-1.5f); // coloca bordas nos quadrados
    quad.setOutlineColor(sf::Color(0, 40, 120));

    // cria um círculo para as pílulas
    sf::CircleShape pill({8.f});
    pill.setFillColor(sf::Color(200, 100, 0));


    // sprites do PacMan

    // cria um círculo para pacman com a boca fechada
    sf::CircleShape pacmanfechado({16.f});
    pacmanfechado.setFillColor(sf::Color(255, 255, 0));

    sf::Texture texture;
    if (!texture.loadFromFile("pacman.png"))
    {
        std::cout << "Erro lendo imagem pacman.png\n";
        return 0;
    }
    sf::Sprite spritedir{texture};

    sf::Texture texture2;
    if (!texture2.loadFromFile("pacman-esq.png"))
    {
        std::cout << "Erro lendo imagem pacman-esq.png\n";
        return 0;
    }
    sf::Sprite spriteesq(texture2);

    sf::Texture texture3;
    if (!texture3.loadFromFile("pacmanbaixo.png"))
    {
        std::cout << "Erro lendo imagem pacmanbaixo.png\n";
        return 0;
    }
    sf::Sprite spritebaixo(texture3);

    sf::Texture texture4;
    if (!texture4.loadFromFile("pacmancima.png"))
    {
        std::cout << "Erro lendo imagem pacmancima.png\n";
        return 0;
    }
    sf::Sprite spritecima(texture4);

    // sprite Fantasma 1 - aleatório
    sf::Texture Fantasma1;
    if (!Fantasma1.loadFromFile("fantasmalaranja.png"))
    {
        std::cout << "Erro lendo imagem fantasmalaranja.png\n";
        return 0;
    }
    sf::Sprite spritefantasma1(Fantasma1);

    // sprite Fantasma 2 - caçador
    sf::Texture Fantasma2;
    if (!Fantasma2.loadFromFile("fantasmavermelho.png"))
    {
        std::cout << "Erro lendo imagem fantasmavermelho.png\n";
        return 0;
    }
    sf::Sprite spritefantasma2(Fantasma2);

    // ajusta o tamanho do pacman e dos fantamas pra essa versao em que cada bloco tem 32x32
    spritedir.setScale({32.f / texture.getSize().x, 32.f / texture.getSize().y});
    spriteesq.setScale({32.f / texture2.getSize().x, 32.f / texture2.getSize().y});
    spritebaixo.setScale({32.f / texture3.getSize().x, 32.f / texture3.getSize().y});
    spritecima.setScale({32.f / texture4.getSize().x, 32.f / texture4.getSize().y});
    spritefantasma1.setScale({32.f / Fantasma1.getSize().x, 32.f / Fantasma1.getSize().y});
    spritefantasma2.setScale({32.f / Fantasma2.getSize().x, 32.f / Fantasma2.getSize().y});

    // cria um relogio para medir o tempo
    sf::Clock clock;

    // carrega uma fonte
    sf::Font font;
    if (!font.openFromFile("arial.ttf"))
    {
        std::cout << "Erro lendo fonte arial\n";
        return 0;
    }

    // cria texto da pontuação (score)
    sf::Text textscore(font);
    textscore.setCharacterSize(18);
    textscore.setFillColor(sf::Color::White);
    textscore.setPosition({20.f, 24.f + OFFSET_Y});

    //cria texto do menu
    sf::Text sadface(font);
    sadface.setCharacterSize(300);
    sadface.setFillColor(sf::Color::White);
    sadface.setPosition({450.f, 500.f + OFFSET_Y});

    //cria texto do menu
    sf::Text titulomenu(font);
    titulomenu.setCharacterSize(100);
     titulomenu.setFillColor(sf::Color::White);
     titulomenu.setPosition({350.f, 400.f });

     //cria texto do menu
    sf::Text titulofim(font);
    titulofim.setCharacterSize(100);
    titulofim.setFillColor(sf::Color::White);
    titulofim.setPosition({450.f, 500.f + OFFSET_Y});
    // executa o programa enquanto a janela está aberta
    while (window.isOpen())
    {

        // verifica todos os eventos que foram acionados na janela, se forem teclas de movimento atribui o valor da tecla para a variavel proximadirecao
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            else if (estadoatual == MENU)              //começa o jogo no estado MENU
            {
                if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
                {
                    if (keyPressed->scancode == sf::Keyboard::Scancode::Enter)        //apertar enter faz o mapa ser gerado e passa para o estado JOGANDO
                    {
                        ResetarJogo();
                        estadoatual = JOGANDO;
                    }
                }
            }
            else if (estadoatual == GAMEOVER || estadoatual == VITORIA)         //tanto os estados de GAMEOVER quanto de VITORIA
            {
                if (const auto *kp = event->getIf<sf::Event::KeyPressed>())
                {
                    if (kp->scancode == sf::Keyboard::Scancode::R)          //apertar R faz jogar novamente
                    {
                        ResetarJogo();
                        estadoatual = JOGANDO;
                    }
                    else if (kp->scancode == sf::Keyboard::Scancode::M)      //apertar M faz voltar para o menu
                        estadoatual = MENU;
                }
            }
            else if (estadoatual == JOGANDO)                //no estado JOGANDO tudo que efetivamente acontece no jogo
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
            // Muda a posição do PacMan e dos fantasmas a cada 0.2 segundos, no geral, é como se o jogo funcionasse a cada 0,2s
            if (clock.getElapsedTime() > sf::seconds(0.2))
            {
                clock.restart();

                //=================================================================================================================================//
                // movimento pac-man
                // 1°- verifica se é possível realizar o movimento pretendido pelo jogador, analisa a próxima posição que o pacman ocuparia se o movimento acontecesse, se não for parede, permite acontecer

                if (pacman.proximadirecao == CIMA && mapaatual[pacman.posy - 1][pacman.posx] != 2)
                    pacman.direcaoatual = CIMA;

                if (pacman.proximadirecao == BAIXO && mapaatual[pacman.posy + 1][pacman.posx] != 2 && mapaatual[pacman.posy + 1][pacman.posx] != 4)
                    pacman.direcaoatual = BAIXO;

                if (pacman.proximadirecao == ESQUERDA && mapaatual[pacman.posy][pacman.posx - 1] != 2)
                    pacman.direcaoatual = ESQUERDA;

                if (pacman.proximadirecao == DIREITA && mapaatual[pacman.posy][pacman.posx + 1] != 2)
                    pacman.direcaoatual = DIREITA;

                // 2°- realiza o movimento e altera o sprite do pacman pra que ele esteja direcionado na direção em que se move
                
            pacman.posAnteriorX = pacman.posx;   //guarda a posição atual antes dele se mexer
            pacman.posAnteriorY = pacman.posy;

                if (pacman.direcaoatual == CIMA)
                {
                    if (mapaatual[pacman.posy - 1][pacman.posx] != 2)
                    {
                        pacman.posy--;
                        if (pacman.posy == aleatorio.posy && pacman.posx == aleatorio.posx || pacman.posx == cacador.posx && pacman.posy == cacador.posy) // encosta no fantasma e morre
                           estadoatual = GAMEOVER;
                        if (mapaatual[pacman.posy][pacman.posx] == 1)
                        { // se a posição atual tiver uma pílula come e soma 10 no score
                            score += 10;
                            mapaatual[pacman.posy][pacman.posx] = 0; // transforma a posição em um caminho vazio
                        }
                    }
                }

                if (pacman.direcaoatual == BAIXO)
                {
                    if (mapaatual[pacman.posy + 1][pacman.posx] != 2 && mapaatual[pacman.posy + 1][pacman.posx] != 4)
                    {
                        pacman.posy++;
                        if (pacman.posy == aleatorio.posy && pacman.posx == aleatorio.posx || pacman.posx == cacador.posx && pacman.posy == cacador.posy)
                           estadoatual = GAMEOVER;
                        if (mapaatual[pacman.posy][pacman.posx] == 1)
                        {
                            score += 10;
                            mapaatual[pacman.posy][pacman.posx] = 0;
                        }
                    }
                }

                if (pacman.direcaoatual == ESQUERDA)
                {
                    if (pacman.posx == 0) // verifica se o pacman se encontra na última posição do túnel da esquerda
                        pacman.posx = 27; // como o pacman ainda deseja se mover pra esquerda, teletransporta-o para o tunel da direita
                    else if (mapaatual[pacman.posy][pacman.posx - 1] != 2)
                    {
                        pacman.posx--;
                        if (pacman.posy == aleatorio.posy && pacman.posx == aleatorio.posx || pacman.posx == cacador.posx && pacman.posy == cacador.posy)
                            estadoatual = GAMEOVER;
                        if (mapaatual[pacman.posy][pacman.posx] == 1)
                        {
                            score += 10;
                            mapaatual[pacman.posy][pacman.posx] = 0;
                        }
                    }
                }

                if (pacman.direcaoatual == DIREITA)
                {
                    if (pacman.posx == 27) // verifica se o pacman se encontra na última posição do túnel da direita
                        pacman.posx = 0;   // como o pacman ainda deseja se mover pra direita, teletransporta-o para o tunel da esquerda
                    else if (mapaatual[pacman.posy][pacman.posx + 1] != 2)
                    {
                        pacman.posx++;
                        if (pacman.posy == aleatorio.posy && pacman.posx == aleatorio.posx || pacman.posx == cacador.posx && pacman.posy == cacador.posy)
                            estadoatual = GAMEOVER;
                        if (mapaatual[pacman.posy][pacman.posx] == 1)
                        {
                            score += 10;
                            mapaatual[pacman.posy][pacman.posx] = 0;
                        }
                    }
                }

                //============================================================================================================================//
                //***movimentação fantasma aleatório***//

                // 1° começa passando por cada estado seguindo o tempo de jogo
                if (aleatorio.estadoatual == PRESO)
                {
                    if (aleatorio.relogio.getElapsedTime().asSeconds() >= 5.0f)
                    {
                        aleatorio.estadoatual = SAINDO;
                    }
                    else
                    {
                        if (aleatorio.posy == 14) // enquanto estiver preso ficando indo pra cima e pra baixo (ansioso)
                            aleatorio.posy = 13;
                        else
                            aleatorio.posy = 14;
                    }
                }
                else if (aleatorio.estadoatual == SAINDO)
                {
                    // ajeita a sua posição com o eixo x, ou seja, fica na coluna da saída
                    if (aleatorio.posx < 14)
                    {
                        aleatorio.posx++;
                    }
                    else if (aleatorio.posx > 14)
                    {
                        aleatorio.posx--;
                    }
                    // se o x já está alinhado, ele começa a subir até o corredor
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

                    // parte que impede o fantasma de realizar U-turn - lógica de "encruzilhada"
                    bool movimentovertical = (aleatorio.direcaoatual == CIMA || aleatorio.direcaoatual == BAIXO);
                    bool movimentohorizontal = (aleatorio.direcaoatual == ESQUERDA || aleatorio.direcaoatual == DIREITA);

                    int caminhoslivres = 0; // contador que analisa quantos caminhos ao redor são possíveis de se movimentar
                    if (mapaatual[aleatorio.posy - 1][aleatorio.posx] != 2)
                        caminhoslivres++;
                    if (mapaatual[aleatorio.posy + 1][aleatorio.posx] != 2)
                        caminhoslivres++;
                    if (mapaatual[aleatorio.posy][aleatorio.posx - 1] != 2)
                        caminhoslivres++;
                    if (mapaatual[aleatorio.posy][aleatorio.posx + 1] != 2)
                        caminhoslivres++;

                    bool mudadirecao = false;

                   

                    if ((aleatorio.direcaoatual == NENHUMA) ||                                                                      // se o fantasma está parado
                        (aleatorio.direcaoatual == CIMA && mapaatual[aleatorio.posy - 1][aleatorio.posx] == 2) ||                   // se vai se chocar contra uma parede
                        (aleatorio.direcaoatual == BAIXO && (mapaatual[aleatorio.posy + 1][aleatorio.posx] == 2 ||(mapaatual[aleatorio.posy + 1][aleatorio.posx] == 4))) || // esse também olha se está em cima porta da casa
                        (aleatorio.direcaoatual == ESQUERDA && aleatorio.posx > 0 && mapaatual[aleatorio.posy][aleatorio.posx - 1] == 2) ||
                        (aleatorio.direcaoatual == DIREITA && aleatorio.posx < 27 && mapaatual[aleatorio.posy][aleatorio.posx + 1] == 2) ||
                        (movimentohorizontal == true && (mapaatual[aleatorio.posy - 1][aleatorio.posx] != 2 || mapaatual[aleatorio.posy + 1][aleatorio.posx] != 2)) || // se pode se movimentar em algum caminho em uma encruzilhada
                        (movimentovertical == true && (mapaatual[aleatorio.posy][aleatorio.posx - 1] != 2 || mapaatual[aleatorio.posy][aleatorio.posx + 1] != 2)))
                    {
                        mudadirecao = true; // então muda de direção
                    }

                    // gerador de números aleatórios da biblioteca <random>
                    static random_device rd;
                    static mt19937 gerador(rd());
                    uniform_int_distribution<int> distribuicao(1, 4);

                    // sorteia um novo número enquanto for necessário mudar de direção
                    while (mudadirecao)
                    {
                        int sorteio = distribuicao(gerador);

                        // 1° analisa se é possível realizar o movimento, se não, sorteia novamente
                        if (sorteio == 1 && mapaatual[aleatorio.posy - 1][aleatorio.posx] != 2)
                        {
                            if (movimentohorizontal || aleatorio.direcaoatual == CIMA || caminhoslivres <= 1 || aleatorio.direcaoatual == NENHUMA)
                            {
                                aleatorio.direcaoatual = CIMA;
                                mudadirecao = false;
                            }
                        }
                        else if (sorteio == 2 && mapaatual[aleatorio.posy + 1][aleatorio.posx] != 2 && mapaatual[aleatorio.posy + 1][aleatorio.posx] != 4)
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

                    // 2° - movimenta efetivamente o fantasma
                    if (aleatorio.direcaoatual == CIMA && mapaatual[aleatorio.posy - 1][aleatorio.posx] != 2)
                    {
                        aleatorio.posy--;
                    }
                    else if (aleatorio.direcaoatual == BAIXO && mapaatual[aleatorio.posy + 1][aleatorio.posx] != 2)
                    {
                        aleatorio.posy++;
                    }
                    else if (aleatorio.direcaoatual == ESQUERDA)
                    {
                        if (aleatorio.posx == 0) // túnel da esquerda
                            aleatorio.posx = 27;
                        else if (mapaatual[aleatorio.posy][aleatorio.posx - 1] != 2)
                        {
                            aleatorio.posx--;
                        }
                    }
                    else if (aleatorio.direcaoatual == DIREITA)
                    {
                        if (aleatorio.posx == 27) // túnel da direita
                            aleatorio.posx = 0;
                        else if (mapaatual[aleatorio.posy][aleatorio.posx + 1] != 2)
                        {
                            aleatorio.posx++;
                        }
                    }
                }

                //
                if (pacman.posy == aleatorio.posy && pacman.posx == aleatorio.posx)
                { // colisão entre fantasma e pacman, ou seja, morte do pacman
                    estadoatual = GAMEOVER;
                }

                //===============================================================================================================================================================================//
                //** movimentação do fantasma caçador **//

                std::vector<caminhos> caminhosvalidos; // vetor dinâmico (vector) de tipo caminhos(struct) para guardar as direções válidas e suas respectivas distâncias

                // 1° começa passando por cada estado seguindo o tempo de jogo
                if (cacador.estadoatual == PRESO)
                {
                    if (cacador.relogio.getElapsedTime().asSeconds() >= 10.0f)
                    { // esse só começa a sair após 10s de jogo (PODE SER ALTERADO)
                        cacador.estadoatual = SAINDO;
                    }
                    else
                    {
                        if (cacador.posy == 14) // enquanto estiver preso ficando indo pra cima e pra baixo (ansioso)
                            cacador.posy = 13;
                        else
                            cacador.posy = 14;
                    }
                }
                else if (cacador.estadoatual == SAINDO)
                {
                    // ajeita a sua posição com o eixo x, ou seja, fica na coluna da saída
                    if (cacador.posx < 13)
                    {
                        cacador.posx++;
                    }
                    else if (cacador.posx > 13)
                    {
                        cacador.posx--;
                    }
                    // se o X já está alinhado, ele começa a subir até o corredor
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
                    

                    // analisa se é possível realizar o movimento em cada uma das posições, se for, calcula a distância entre caçador e pacman e guarda no vector de caminhosvalidos
                    if (mapaatual[cacador.posy - 1][cacador.posx] != 2 && cacador.direcaoatual != BAIXO)
                    { // analisa CIMA
                        float distancia = pow(pacman.posx - cacador.posx, 2) + pow(pacman.posy - (cacador.posy - 1), 2);
                        caminhosvalidos.push_back({CIMA, distancia});
                    }
                    if (mapaatual[cacador.posy + 1][cacador.posx] != 2 && cacador.direcaoatual != CIMA && mapaatual[cacador.posy + 1][cacador.posx] != 4)
                    { // analisa BAIXO, aqui também analisa se ele está na posição exatamente acima da porta da casa, pra que ele não volte pra dentro
                        float distancia = pow(pacman.posx - cacador.posx, 2) + pow(pacman.posy - (cacador.posy + 1), 2);
                        caminhosvalidos.push_back({BAIXO, distancia});
                    }
                    if (cacador.posx == 0 || mapaatual[cacador.posy][cacador.posx - 1] != 2 && cacador.direcaoatual != DIREITA)
                    { // analisa ESQUERDA
                        if (cacador.posx == 0)
                        {
                            float distancia = pow(pacman.posx - (0), 2) + pow(pacman.posy - cacador.posy, 2);
                            caminhosvalidos.push_back({ESQUERDA, distancia});
                        }
                        else
                        {
                            float distancia = pow(pacman.posx - (cacador.posx - 1), 2) + pow(pacman.posy - cacador.posy, 2);
                            caminhosvalidos.push_back({ESQUERDA, distancia});
                        }
                    }
                    if (cacador.posx == 27 || mapaatual[cacador.posy][cacador.posx + 1] != 2 && cacador.direcaoatual != ESQUERDA)
                    { // analisa DIREITA
                        if (cacador.posx == 27)
                        {
                            float distancia = pow(pacman.posx - (27), 2) + pow(pacman.posy - cacador.posy, 2);
                            caminhosvalidos.push_back({DIREITA, distancia});
                        }
                        else
                        {
                            float distancia = pow(pacman.posx - (cacador.posx + 1), 2) + pow(pacman.posy - cacador.posy, 2);
                            caminhosvalidos.push_back({DIREITA, distancia});
                        }
                    }

                    sort(caminhosvalidos.begin(), caminhosvalidos.end(), comparadistancias); // sort para ordenar (da mais perto a mais longe) as distâncias e suas respectivas direções, pra isso, usa a função comparadistancias

                    if (caminhosvalidos.size() == 0)
                    { // analisa se está em um beco sem saída, se sim o fantasma pode e deve fazer o movimento de volta (u-turn)
                        if (cacador.direcaoatual == CIMA)
                            cacador.direcaoatual = BAIXO;
                        else if (cacador.direcaoatual == BAIXO)
                            cacador.direcaoatual = CIMA;
                        else if (cacador.direcaoatual == ESQUERDA)
                            cacador.direcaoatual = DIREITA;
                        else if (cacador.direcaoatual == DIREITA)
                            cacador.direcaoatual = ESQUERDA;
                    }

                    else
                    {
                        cacador.direcaoatual = caminhosvalidos[0].direcao; // se não for um beco passa a se mover na direção que estiver na primeira posição do vector, ou seja, a de menor distância
                    }

                    // 2° - movimenta efetivamente o fantasma
                    if (cacador.direcaoatual == CIMA && mapaatual[cacador.posy - 1][cacador.posx] != 2)
                    {
                        cacador.posy--;
                    }
                    else if (cacador.direcaoatual == BAIXO && mapaatual[cacador.posy + 1][cacador.posx] != 2 && mapaatual[cacador.posy + 1][cacador.posx] != 4)
                    {
                        cacador.posy++;
                    }
                    else if (cacador.direcaoatual == ESQUERDA)
                    {
                        if (cacador.posx == 0) // túnel da esquerda
                            cacador.posx = 27;
                        else if (mapaatual[cacador.posy][cacador.posx - 1] != 2)
                        {
                            cacador.posx--;
                        }
                    }
                    else if (cacador.direcaoatual == DIREITA)
                    {
                        if (cacador.posx == 27) // túnel da direita
                            cacador.posx = 0;
                        else if (mapaatual[cacador.posy][cacador.posx + 1] != 2)
                        {
                            cacador.posx++;
                        }
                    }

                    if (pacman.posy == cacador.posy && pacman.posx == cacador.posx)
                    { // encosta no pacman
                        estadoatual = GAMEOVER;
                    }
                }
            }
        }
            // limpa a janela com a cor preta
            window.clear(sf::Color::Black);

        if (estadoatual == MENU) {
                char s[3];
            snprintf(s, 20, ":(" ); // "Escreve" no string s, no maximo 20 char (contando \0)
            sadface.setString(s);
            sadface.setPosition({400.f, 500.f});
            window.draw(sadface);

                 char t[20];
            snprintf(t, 20, "pacman" ); // "Escreve" no string s, no maximo 20 char (contando \0)
            titulomenu.setString(t);
            titulomenu.setPosition({200.f, 100.f});
            window.draw(titulomenu);
        }
       
        if(estadoatual == JOGANDO || estadoatual == GAMEOVER){
            // desenha mapaatual - analisa o valor de cada posição da matriz mapaatual
            for (int i = 0; i < 33; i++)
            {
                for (int j = 0; j < 28; j++)
                {
                    if (mapaatual[i][j] == 2)
                    { // desenha um quadrado(parede) nas posições de valor 2
                        quad.setPosition({j * 32.f, i * 32.f + OFFSET_Y});
                        window.draw(quad);
                    }
                    else if (mapaatual[i][j] == 1)
                    {                                                                  // desenha as pílulas nas posições de valor 1
                        pill.setPosition({j * 32.f + 8.f, i * 32.f + 8.f + OFFSET_Y}); // soma-se +8 para que as pílulas sejam desenhadas no meio do bloco
                        window.draw(pill);
                    }
                }
            }
        
            // desenha Pacman - analisa qual direção do movimento, e, portanto, a direção a qual o pacman olha e desenha ele
        
        if(pacman.posAnteriorX != pacman.posx || pacman.posAnteriorY != pacman.posy){   //só muda a boca quando em movimento
        if (pacman.animacao.getElapsedTime().asSeconds() > 0.1f) {   //a cada 0,2s muda a animação
            pacman.abre = !pacman.abre; //inverte o valor atual da variável
            pacman.animacao.restart();
           }
        }
        else                                   //parado fica com a boca aberta
            pacman.abre = true;

                  
            if(pacman.abre){  // boca aberta
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
            else{  //boca fechada
                pacmanfechado.setPosition({pacman.posx * 32.f, pacman.posy * 32.f + OFFSET_Y});
                window.draw(pacmanfechado);
            }
        


            // desenha fantasmas
            spritefantasma1.setPosition({aleatorio.posx * 32.f, aleatorio.posy * 32.f + OFFSET_Y});
            window.draw(spritefantasma1);

            spritefantasma2.setPosition({cacador.posx * 32.f, cacador.posy * 32.f + OFFSET_Y});
            window.draw(spritefantasma2);

            // volta a camêra ao normal
            window.setView(window.getDefaultView());

            // desenha o score
            char s[20];
            snprintf(s, 20, "Score: %d", score); // "Escreve" no string s, no maximo 20 char (contando \0)
            textscore.setString(s);
            textscore.setPosition({20.f, 24.f});
            window.draw(textscore);

            if (estadoatual == GAMEOVER) {
         char f[20];
            snprintf(f, 20, ":( voce morreu xxx" ); // "Escreve" no string s, no maximo 20 char (contando \0)
            titulofim.setString(f);
            titulofim.setPosition({100.f, 50.f});
            window.draw(titulofim);
}
        }
            // termina e desenha o frame corrente
            window.display();
       
            }
            return 0;
        }

     
        
    