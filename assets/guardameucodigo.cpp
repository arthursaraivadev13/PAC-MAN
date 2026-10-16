#include <SFML/Graphics.hpp>
#include <iostream>
#include<random>
using namespace std;

// MAPA CORRIGIDO: 31 linhas por 28 colunas reais. 
// Sem duplicatas, com a casa dos fantasmas oca no centro e apenas um túnel central.
 int mapa[31][28] = {
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,2},
    {2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2},
    {2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2},
    {2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
    {2,1,2,2,2,2,1,2,2,1,2,2,2,2,2,2,2,2,1,2,2,1,2,2,2,2,1,2},
    {2,1,1,1,1,1,1,2,2,1,1,1,1,2,2,1,1,1,1,2,2,1,1,1,1,1,1,2},
    {2,2,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,2,2},
    {2,2,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,2,2},
    {2,2,2,2,2,2,1,2,2,1,1,1,1,1,1,1,1,1,1,2,2,1,2,2,2,2,2,2},
    {2,2,2,2,2,2,1,2,2,1,2,2,1,1,1,2,2,2,1,2,2,1,2,2,2,2,2,2},
    {2,2,2,2,2,2,1,2,2,1,2,0,0,0,0,0,0,2,1,2,2,1,2,2,2,2,2,2}, // Casa dos Fantasmas (vazia)
    {0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0}, // Túnel lateral (vazio)
    {2,2,2,2,2,2,1,2,2,1,2,0,0,0,0,0,0,2,1,2,2,1,2,2,2,2,2,2}, // Casa dos Fantasmas (vazia)
    {2,2,2,2,2,2,1,2,2,1,2,2,2,2,2,2,2,2,1,2,2,1,2,2,2,2,2,2},
    {2,2,2,2,2,2,1,2,2,1,1,1,1,1,1,1,1,1,1,2,2,1,2,2,2,2,2,2},
    {2,2,2,2,2,2,1,2,2,1,2,2,2,2,2,2,2,2,1,2,2,1,2,2,2,2,2,2},
    {2,2,2,2,2,2,1,2,2,1,2,2,2,2,2,2,2,2,1,2,2,1,2,2,2,2,2,2},
    {2,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,2},
    {2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2},
    {2,1,1,1,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,1,1,1,2},
    {2,2,2,1,2,2,1,2,2,1,2,2,2,2,2,2,2,2,1,2,2,1,2,2,1,2,2,2},
    {2,1,1,1,1,1,1,2,2,1,1,1,1,2,2,1,1,1,1,2,2,1,1,1,1,1,1,2},
    {2,1,2,2,2,2,2,2,2,2,2,2,1,2,2,1,2,2,2,2,2,2,2,2,2,2,1,2},
    {2,1,2,2,2,2,2,2,2,2,2,2,1,2,2,1,2,2,2,2,2,2,2,2,2,2,1,2},
    {2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
    {2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2},
    {2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2,2,2,2,1,2},
    {2,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2}
};
  


int score = 0; // contador de pontos


enum DIRECAO{NENHUMA, CIMA, BAIXO, ESQUERDA, DIREITA};         //variavel enum que lista os movimentos 
                              
struct Pacman {                                                //struct que agrupa todas as variáveis do Pacman
    int posx = 1; // Posição inicial 
    int posy = 1;
    DIRECAO direcaoatual = NENHUMA;                            //variavel que guarda o movimento que o jogador quer fazer
    DIRECAO proximadirecao = NENHUMA;                          //variavel que realiza, caso possivel, o movimento

};
Pacman pacman;   //variável que altera as variáveis do struct                                             



struct Fantasma {                               //struct que agrupa todas as variáveis dos Fantasmas
    int posx;
    int posy;
    DIRECAO direcao = NENHUMA;
};

Fantasma bulmer = {14,11,NENHUMA};      //variavel que indica a posição e a direção do fantasma BULMER
   


int main() {
    // Ajusta a janela perfeitamente para o tamanho do mapa (28 colunas * 32px, 31 linhas * 320px)
    sf::RenderWindow window(sf::VideoMode({896, 1056}), "Pac-Man");

    // cria um quadrado de tamanho 20 para as paredes
    sf::RectangleShape quad({32.f, 32.f});
    quad.setFillColor(sf::Color(0, 100, 200));

    //cria um círculo para as pílulas
    sf::CircleShape pill({8.f});
    pill.setFillColor(sf::Color(200, 100, 0));



    // sprites do PacMan
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



    //sprite Fantasma 1
    sf::Texture Fantasma1;
    if(!Fantasma1.loadFromFile("bulmer.png")){
        std::cout << "Erro lendo imagem bulmer.png\n";
        return 0;
    }
    sf::Sprite spritefantasma1(Fantasma1);

 //ajusta o tamanho do pacman pra essa versao em que cada bloco tem 20x20
    spritedir.setScale({32.f / texture.getSize().x, 32.f / texture.getSize().y});      
    spriteesq.setScale({32.f / texture2.getSize().x, 32.f / texture2.getSize().y});
    spritebaixo.setScale({32.f / texture3.getSize().x, 32.f / texture3.getSize().y});
    spritecima.setScale({32.f / texture4.getSize().x, 32.f / texture4.getSize().y});
    spritefantasma1.setScale({32.f/Fantasma1.getSize().x, 32.f / Fantasma1.getSize().y});

    // cria um relogio para medir o tempo
    sf::Clock clock;

    // executa o programa enquanto a janela está aberta
    while (window.isOpen()) {

        // verifica todos os eventos que foram acionados na janela, se forem teclas de movimento atribui o valor da tecla para a variavel proximadirecao
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    window.close();
                else if (keyPressed->scancode == sf::Keyboard::Scancode::Left) {
                    pacman.proximadirecao = ESQUERDA;
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::Right) {
                    pacman.proximadirecao = DIREITA;
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::Up) {
                    pacman.proximadirecao = CIMA;
                }
                else if (keyPressed->scancode == sf::Keyboard::Scancode::Down) {
                    pacman.proximadirecao = BAIXO; 
                }
                else if(keyPressed->scancode == sf::Keyboard::Scancode::R){         //(APENAS TESTE)ao pressionar a tecla R o pacman é resetado pra posição original imóvel
                    pacman.posx = 1;       
                    pacman.posy = 1;
                    pacman.proximadirecao = NENHUMA;
                    pacman.direcaoatual = DIREITA;
                }
            }
        }

        // Muda a posição do PacMan a cada 0.2 segundos
        if (clock.getElapsedTime() > sf::seconds(0.2)) { 
            clock.restart();      
        
        // 1°- verifica se é possível realizar o movimento pretendido pelo jogador, analisa a próxima posição que o pacman ocuparia se o movimento acontecesse, se não for parede, permite acontecer

        if(pacman.proximadirecao == CIMA && mapa[pacman.posy-1][pacman.posx] != 2)               
            pacman.direcaoatual = CIMA;

        if(pacman.proximadirecao == BAIXO  && mapa[pacman.posy+1][pacman.posx] != 2)
            pacman.direcaoatual = BAIXO;

        if(pacman.proximadirecao == ESQUERDA && mapa[pacman.posy][pacman.posx-1] != 2)
            pacman.direcaoatual = ESQUERDA;

         if(pacman.proximadirecao == DIREITA && mapa[pacman.posy][pacman.posx+1] != 2)
            pacman.direcaoatual = DIREITA;

        
        // 2°- realiza o movimento e altera o sprite do pacman pra que ele esteja direcionado na direção em que se move

        if(pacman.direcaoatual == CIMA){
            if(mapa[pacman.posy-1][pacman.posx] != 2){
                pacman.posy--;
                if(pacman.posy==bulmer.posy && pacman.posx==bulmer.posx)
                    return 0;
                if(mapa[pacman.posy][pacman.posx]==1){
                    score+=10;
                    mapa[pacman.posy][pacman.posx]=0;
                }
        }
    }

        if(pacman.direcaoatual == BAIXO){
            if(mapa[pacman.posy+1][pacman.posx] != 2){
                pacman.posy++;
                if(pacman.posy==bulmer.posy && pacman.posx==bulmer.posx)
                    return 0;
                if(mapa[pacman.posy][pacman.posx]==1){
                    score+=10;
                    mapa[pacman.posy][pacman.posx]=0;
                }
            }
        }

        if(pacman.direcaoatual == ESQUERDA){
            if(pacman.posx== 0)                                    //verifica se o pacman se encontra na última posição do túnel da esquerda
                pacman.posx = 27;                                  //como o pacman ainda deseja se mover pra esquerda, teletransporta-o para o tunel da direita
            else 
                if(mapa[pacman.posy][pacman.posx-1] != 2){
                    pacman.posx--;
                    if(pacman.posy==bulmer.posy && pacman.posx==bulmer.posx )
                    return 0;
                    if(mapa[pacman.posy][pacman.posx] == 1){
                        score += 10;
                        mapa[pacman.posy][pacman.posx]=0;
                    }
            }
        }

        if(pacman.direcaoatual == DIREITA){
            if(pacman.posx == 27)                                  //verifica se o pacman se encontra na última posição do túnel da direita
                pacman.posx = 0;                                   //como o pacman ainda deseja se mover pra direita, teletransporta-o para o tunel da esquerda
            else 
                if(mapa[pacman.posy][pacman.posx+1] < 2){
                    pacman.posx++;
                    if(pacman.posy==bulmer.posy && pacman.posx==bulmer.posx)
                    return 0;
                    if(mapa[pacman.posy][pacman.posx] == 1){
                        score += 10;
                        mapa[pacman.posy][pacman.posx]=0;
                    }
            }
           
        }
//movimentaçao fantasma

        random_device rd;
        mt19937 gerador(rd());

        uniform_int_distribution<int> distribuicao(1,4);
        int direcaobulmer = distribuicao(gerador);

        if(direcaobulmer==1){
            bulmer.direcao= CIMA;
            if(mapa[bulmer.posy-1][bulmer.posx] != 2)
                bulmer.posy--;
        }
        if(direcaobulmer==2){
            bulmer.direcao= BAIXO;
            if(mapa[bulmer.posy+1][bulmer.posx] != 2)
                bulmer.posy++;
        } 
        if(direcaobulmer==3){
            bulmer.direcao= ESQUERDA;
            if(mapa[bulmer.posy][bulmer.posx-1] != 2)
                bulmer.posx--;
        } 
        if(direcaobulmer==4){
            bulmer.direcao= DIREITA;
            if(mapa[bulmer.posy][bulmer.posx+1] != 2)
                bulmer.posx++;
        } 
        
    }
        // limpa a janela com a cor preta
        window.clear(sf::Color::Black);

        // desenha paredes - como todas as paredes são o número 2 na matriz do labirinto, desenha um quadrado onde for 2
        for(int i = 0; i < 31; i++) {
            for(int j = 0; j < 28; j++) {
                if (mapa[i][j] == 2) {
                    quad.setPosition({j * 32.f, i * 32.f});
                    window.draw(quad);
                }
                else if(mapa[i][j]==1){
                    pill.setPosition({j*32.f + 8.f, i * 32.f + 8.f});
                    window.draw(pill);
                }
            }
        }

        // desenha Pacman - analisa qual direção do movimento, e, portanto, a direção a qual o pacman olha e desenha ele
        if (pacman.direcaoatual == DIREITA || pacman.direcaoatual == NENHUMA) {
            spritedir.setPosition({pacman.posx * 32.f, pacman.posy * 32.f});
            window.draw(spritedir);
        }

        else if (pacman.direcaoatual == BAIXO){
            spritebaixo.setPosition({pacman.posx * 32.f, pacman.posy *32.f});
            window.draw(spritebaixo);
        }
        else if (pacman.direcaoatual == ESQUERDA){
            spriteesq.setPosition({pacman.posx * 32.f, pacman.posy * 32.f});
            window.draw(spriteesq);
        }
        else if(pacman.direcaoatual == CIMA){
            spritecima.setPosition({pacman.posx * 32.f, pacman.posy * 32.f});
            window.draw(spritecima);
        }

        spritefantasma1.setPosition({bulmer.posx * 32.f, bulmer.posy * 32.f});
        window.draw(spritefantasma1);


        // termina e desenha o frame corrente
        window.display();
    }

    return 0;
}
