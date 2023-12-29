#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>




typedef struct {
    int altura;
    int largura;
    char **layout;
} Sala;


typedef struct {
    int posY;
    int posX;
    char character;
} Boneco;


typedef struct {
    int posY;
    int posX;
    char character;
    int coletada;  // Adicione um campo para verificar se a chave foi coletada
} Chave;




// Salas
void criarSala(Sala *sala, int altura, int largura) {
    sala->altura = altura;  // Altere para a altura desejada
    sala->largura = largura; // Altere para a largura desejada


    sala->layout = (char **)malloc(sala->altura * sizeof(char *));
    for (int i = 0; i < sala->altura; i++) {
        sala->layout[i] = (char *)malloc(sala->largura * sizeof(char));
        for (int j = 0; j < sala->largura; j++) {
            if (i == 0 || j == 0 || i == sala->altura - 1 || j == sala->largura - 1) {
                sala->layout[i][j] = '#';
            } else {
                sala->layout[i][j] = '.';
            }
        }
    }
}



void desenharSala(WINDOW *win, Sala sala, int comecoY, int comecoX) {
    for (int i = 0; i < sala.altura; ++i) {
        for (int j = 0; j < sala.largura; ++j) {
            int posY = comecoY + i;
            int posX = comecoX + j;

            if (posY >= 0 && posY < getmaxy(win) && posX >= 0 && posX < getmaxx(win)) {
                mvwaddch(win, posY, posX, sala.layout[i][j]);
            }
        }
    }
}


void obterLimitesDaSala(int sala, int *comecoY, int *comecoX, int *alturaSala, int *larguraSala) {
    switch (sala) {
    case 1:
        *comecoY = 7;
        *comecoX = 20;
        *alturaSala = 20;
        *larguraSala = 40;
        break;
    case 2:
        *comecoY = 20;
        *comecoX = 80;
        *alturaSala = 15;
        *larguraSala = 30;
        break;
    case 3:
        *comecoY = 13;
        *comecoX = 120;
        *alturaSala = 10;
        *larguraSala = 20;
        break;
    }
}



void liberarSala(Sala *sala) {
    for (int i = 0; i < sala->altura; i++) {
        free(sala->layout[i]);
    }
    free(sala->layout);
}


void desenharCaminho(WINDOW* win, int yCaminho, int xCaminho, int altura, int comprimento) {
    if (altura == 1) {  // caminho na horizontal
        for (int i = 0; i < comprimento; ++i) {
            mvwaddch(win, yCaminho, xCaminho + i, '.');
        }
    }


    if (comprimento == 1) {  // caminho na vertical
        for (int j = 0; j < altura; ++j) {
            mvwaddch(win, yCaminho + j, xCaminho, '.');
        }
    }
}




// Desenhar os limites dos caminhos
void desenharBorda(WINDOW* win, int yCaminho, int xCaminho, int altura, int comprimento) {
    if (altura == 1) {  // caminho na horizontal
        for (int i = 0; i < comprimento; ++i) {
            mvwaddch(win, yCaminho, xCaminho + i, '#');
        }
    }




    if (comprimento == 1) {  // caminho na vertical
        for (int j = 0; j < altura; ++j) {
            mvwaddch(win, yCaminho + j, xCaminho, '#');
        }
    }
}




// Exibir caminhos e bordas
void exibirCaminhoBorda(WINDOW* win) {
    desenharCaminho(win, 32, 30, 1, 50);  // sala1 horizontal
    desenharCaminho(win, 27, 30, 5, 1);   // sala1 vertical
    desenharCaminho(win, 16, 89, 1, 31);  // sala2 horizontal
    desenharCaminho(win, 16, 88, 4, 1);   // sala2 vertical




    desenharBorda(win, 31, 32, 1, 49);  // sala 1 horizontal
    desenharBorda(win, 33, 30, 1, 50);  // sala 1 horizontal
    desenharBorda(win, 27, 29, 7, 1);   // sala1 vertical
    desenharBorda(win, 27, 31, 5, 1);   // sala1 vertical
    desenharBorda(win, 15, 87, 1, 33);  // sala2 horizontal
    desenharBorda(win, 17, 89, 1, 31);  // sala2 horizontal
    desenharBorda(win, 15, 87, 5, 1);   // sala2 vertical
    desenharBorda(win, 18, 89, 3, 1);   // sala2 vertical
}

char gerarPlayer() {
    return 'B';
}

void inicializarBoneco(Boneco *boneco, int posY, int posX) {
    boneco->posY = posY;
    boneco->posX = posX;
    boneco->character = 'B';
}


void exibirBoneco(WINDOW *win, Boneco boneco, int comecoY, int comecoX) {
    mvwaddch(win, comecoY + boneco.posY, comecoX + boneco.posX, 'B');
}


int posicaoValida(Sala sala, int posY, int posX) {
    return (posY >= 0 && posY < sala.altura && posX >= 0 && posX < sala.largura &&
            sala.layout[posY][posX] == '.');
}


void moverBoneco(Boneco *boneco, Sala sala, int deltaY, int deltaX) {
    int novaPosY = boneco->posY + deltaY;
    int novaPosX = boneco->posX + deltaX;


    if (posicaoValida(sala, novaPosY, novaPosX)) {
        boneco->posY = novaPosY;
        boneco->posX = novaPosX;
    }
}


// Chaves


int chaves_coletadas = 0; // Adicionei esta variável para controlar as chaves coletadas



char chave = 'K'; // Variável chave para a fase
int x_boneco = 10, y_boneco = 10; // Posição do boneco
int x_monstro = 15, y_monstro = 15; // Posição do monstro
int comeco_x = 0, comeco_y = 0; // Posição inicial da sala
int largura_sala = 20, altura_sala = 10; // Tamanho da sala


char *vitoria[] = {                                            
"_____ _____ _____ _____    _____ _____ _____ _____ _____ _____  ",
"|  |  |     |     |   __|  |  |  |   __|   | |     |   __|  |  |",  
"|  |  |  |  |   --|   __|  |  |  |   __| | | |   --|   __|  |  |",  
" \\___/|_____|_____|_____|   \\___/|_____|_|___|_____|_____|_____|"                                                
};
char *vocemorreu[] = {
                                                   
" _____ _____ _____    ____  _____       __ _____ _____ _____ ",
"|   __|     |     |  |    \\|   __|   __|  |     |   __|     |",
"|   __|-   -| | | |  |  |  |   __|  |  |  |  |  |  |  |  |  |",
"|__|  |_____|_|_|_|  |____/|_____|  |_____|_____|_____|_____|"
};
// TEM QUE TIRAR ISSO
// Variáveis globais
int alt = 40;  // Altura da sala
int larg = 160; // Largura da sala




Chave criarChave(Sala sala, int comecoY, int comecoX, int altura, int largura) {
    Chave chave;
    do {
        chave.posX = rand() % (largura - 2) + comecoX + 1;
        chave.posY = rand() % (altura - 2) + comecoY + 1;
    } while (sala.layout[chave.posY - comecoY][chave.posX - comecoX] != '.');


    chave.character = 'K';
    chave.coletada = 0;


    mvaddch(chave.posY, chave.posX, chave.character);
    return chave;
}
void exibirChave(Chave chave, Sala sala) {
    if (!chave.coletada) {
        mvaddch(chave.posY, chave.posX, chave.character);
    }
}
void verificacao_morte_ou_vitoria() {
    if (y_boneco == y_monstro && x_boneco == x_monstro) {
        clear();
        // Mostra derrota na tela
        int x = ((largura_sala + comeco_x) / 2) - 1;
        int y = ((altura_sala + comeco_y) / 2) - 1;
        for (int i = 0; i < sizeof(vocemorreu) / sizeof(vocemorreu[0]); i++) {
            mvaddstr(y + i, x, vocemorreu[i]);
            refresh();
        }
    } else if (chaves_coletadas == 3) {
        clear();
        // Mostra vitória na tela
        int x = ((largura_sala + comeco_x) / 2) - 1;
        int y = ((altura_sala + comeco_y) / 2) - 1;
        for (int i = 0; i < sizeof(vitoria) / sizeof(vitoria[0]); i++) {
            mvaddstr(y + i, x, vitoria[i]);
            refresh();
        }
    }
}






// Verifica se uma coordenada já foi usada
int coordenadaUsada(int coordenadasUsadas[][2], int numMonstros, int x, int y) {
    for (int i = 0; i < numMonstros; i++) {
        if (coordenadasUsadas[i][0] == x && coordenadasUsadas[i][1] == y) {
            return 1; // Coordenada já usada
        }
    }
    return 0; // Coordenada não usada
}


//Distribui monstros aleatoriamente em uma sala
void distribuirMonstros(int sala, int numMonstrosPorSala) {
    int comecoY, comecoX, altSala, largSala;
    obterLimitesDaSala(sala, &comecoY, &comecoX, &altSala, &largSala);


    // Rastrear as coordenadas dos monstros já geradas
    int coordenadasUsadas[numMonstrosPorSala][2];


    for (int i = 0; i < numMonstrosPorSala; i++) {
        int x, y;


        // Gera coordenadas únicas que não se sobrepõem
        do {
            x = rand() % (largSala - 2) + comecoX + 1;
            y = rand() % (altSala - 2) + comecoY + 1;
        } while (coordenadaUsada(coordenadasUsadas, i, x, y));


        // Adiciona as coordenadas ao array
        coordenadasUsadas[i][0] = x;
        coordenadasUsadas[i][1] = y;


        // Adicionar o monstro no console
        mvaddch(y, x, 'M');
    }
}


// Função para mover o monstro dentro dos limites da sala
void moverMonstro(int *xMonstro, int *yMonstro, int salaAtual) {
    int direcoes[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};  // Movimentos possíveis: cima, baixo, direita, esquerda
    int direcaoSelecionada = rand() % 4;
    int direcao[2] = {direcoes[direcaoSelecionada][0], direcoes[direcaoSelecionada][1]};


    // Obter limites da sala
    int comecoY, comecoX, altSala, largSala;
    obterLimitesDaSala(salaAtual, &comecoY, &comecoX, &altSala, &largSala);


    // Calcular a próxima posição do monstro dentro dos limites da sala
    int proximoXMonstro = *xMonstro + direcao[0];
    int proximoYMonstro = *yMonstro + direcao[1];


    // Verificar se o próximo movimento mantém o monstro dentro da sala
    if (comecoX + 1 <= proximoXMonstro && proximoXMonstro < comecoX + largSala - 1 &&
        comecoY + 1 <= proximoYMonstro && proximoYMonstro < comecoY + altSala - 1) {
        // Atualizar as coordenadas do monstro
        *xMonstro = proximoXMonstro;
        *yMonstro = proximoYMonstro;
    }
}


void jogarRogue(WINDOW *win, int alturaSala1, int larguraSala1, int numMonstrosPorSala){
    Sala sala1, sala2, sala3;
    Chave chaveSala1, chaveSala2, chaveSala3;


    criarSala(&sala1, 20, 40);
    criarSala(&sala2, 15, 30);
    criarSala(&sala3, 10, 20);


    chaveSala1 = criarChave(sala1, 7, 20, 20, 40);
    chaveSala2 = criarChave(sala2, 20, 80, 15, 30);
    chaveSala3 = criarChave(sala3, 13, 120, 10, 20);
    Boneco boneco;
    inicializarBoneco(&boneco, alturaSala1 / 2, larguraSala1 / 2);


    // Array para armazenar as coordenadas dos monstros (3 salas e 3 monstros por sala, ajuste conforme necessário)
    int monstros[3][3];

/*

    // Distribuir monstros aleatoriamente na sala1
    for (int i = 0; i < numMonstrosPorSala; i++) {
        // Obter limites da sala1
        int comecoY, comecoX, altSala, largSala;
        obterLimitesDaSala(1, &comecoY, &comecoX, &altSala, &largSala);


        // Gerar coordenadas aleatórias para o monstro dentro dos limites da sala1
        monstros[0][i] = rand() % (largSala - 2) + comecoX + 1;  // Coordenada X
        monstros[1][i] = rand() % (altSala - 2) + comecoY + 1;    // Coordenada Y


        // Adicionar o monstro no console
        mvaddch(monstros[1][i], monstros[0][i], 'M');
    }

*/




    int gameover = 0;


    while (!gameover) {
        werase(win);
        refresh();
        desenharSala(win, sala1, 7, 20);
        desenharSala(win, sala2, 20, 80);
        desenharSala(win, sala3, 13, 120);
        exibirBoneco(win, boneco, 7, 20);

        mvwprintw(win, 3, 60, "CHAVES COLETADAS: %s", &chaves_coletadas);

        //distribuirMonstros(1, numMonstrosPorSala);  // Adicionar a chamada para exibir monstros na sala1
        //distribuirMonstros(2, numMonstrosPorSala);  // Adicionar a chamada para exibir monstros na sala2
        //distribuirMonstros(3, numMonstrosPorSala);  // Adicionar a chamada para exibir monstros na sala3
       


        exibirChave(chaveSala1, sala1);
        exibirChave(chaveSala2, sala2);
        exibirChave(chaveSala3, sala3);
       




        exibirCaminhoBorda(win);


       
        verificacao_morte_ou_vitoria();


        int troca = 0;
        // if (chaveSala1.posX == boneco.posX && chaveSala1.posY == boneco.posY && !chaveSala1.coletada) {
        //     chaveSala1.coletada = 1; // Marca a chave como coletada
        //     chaves_coletadas++; // Incrementa o contador de chaves coletadas
        // }


       if (chaves_coletadas == 1 && !troca) {
            mvwprintw(win, 4, 125, "MUITO BEM! Você coletou uma chave!");
            mvwaddch(win, 32, 80, '.');  // Desenha um ponto em vez do portão
            wrefresh(win);
            getch();
            troca = 1;
        }


        if (chaves_coletadas == 2 && !troca) {
            mvwprintw(win, 4, 122, "Agora você está mais perto de vencer!");
            mvwaddch(win, 16, 130, '.');  // Desenha um ponto em vez do portão
            wrefresh(win);
            getch();
            troca = 1;
        }
        //(opcional eu acho)
        if (chaves_coletadas == 3 && !troca) {
            //exibir ‘você venceu’
            troca = 1;
        }


        wrefresh(win);




        int ch = getch();
        switch (ch) {
            case KEY_UP:
            case 'w':
            case 'W':
                moverBoneco(&boneco, sala1, -1, 0);
                break;
            case KEY_DOWN:
            case 's':
            case 'S':
                moverBoneco(&boneco, sala1, 1, 0);
                break;
            case KEY_LEFT:
            case 'a':
            case 'A':
                moverBoneco(&boneco, sala1, 0, -1);
                break;
            case KEY_RIGHT:
            case 'd':
            case 'D':
                moverBoneco(&boneco, sala1, 0, 1);
                break;
            case 27: // ESC
                gameover = 1;
                break;
        }


        usleep(15000);
    }


    liberarSala(&sala1);
    liberarSala(&sala2);
    liberarSala(&sala3);
}






int main() {
    srand(time(NULL));


    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    resize_term(40,160);
    start_color();
    init_pair(1, 166, 0);
    init_pair(2, 214, 0);


    int alturaSala1, larguraSala1, numMonstrosPorSala;


    // Defina aqui as dimensões da sala1
    alturaSala1 = 20;
    larguraSala1 = 40;


    // Defina o número de monstros por sala (altere para 1)
    numMonstrosPorSala = 1;


    WINDOW *win = newwin(40, 160, 0, 0);
    nodelay(win, 1);
    timeout(100);


    // Chame a função jogarRogue com o número de monstros por sala
    jogarRogue(win, alturaSala1, larguraSala1, numMonstrosPorSala);


    endwin();
    //getch();
    return 0;
}


