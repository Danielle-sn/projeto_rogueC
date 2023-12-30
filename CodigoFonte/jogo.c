#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>


////////////////////////////SALA///////////////////
void criarSala(Sala *sala, int alt, int larg) {
    sala->alt = alt;  // Altere para a alt desejada
    sala->larg = larg; // Altere para a larg desejada


    sala->layout = (char **)malloc(sala->alt * sizeof(char *));
    for (int i = 0; i < sala->alt; i++) {
        sala->layout[i] = (char *)malloc(sala->larg * sizeof(char));
        for (int j = 0; j < sala->larg; j++) {
            if (i == 0 || j == 0 || i == sala->alt - 1 || j == sala->larg - 1) {
                sala->layout[i][j] = '#';
            } else {
                sala->layout[i][j] = '.';
            }
        }
    }
}

void desenharSala(WINDOW *win, Sala sala, int comecoY, int comecoX) {
    for (int i = 0; i < sala.alt; ++i) {
        for (int j = 0; j < sala.larg; ++j) {
            int posY = comecoY + i;
            int posX = comecoX + j;

            if (posY >= 0 && posY < getmaxy(win) && posX >= 0 && posX < getmaxx(win)) {
                mvwaddch(win, posY, posX, sala.layout[i][j]);
            }
        }
    }
}

void obterLimitesDaSala(int sala, int *comecoY, int *comecoX, int *altSala, int *largSala) {
    switch (sala) {
    case 1:
        *comecoY = 7;
        *comecoX = 20;
        *altSala = 20;
        *largSala = 40;
        break;
    case 2:
        *comecoY = 20;
        *comecoX = 80;
        *altSala = 15;
        *largSala = 30;
        break;
    case 3:
        *comecoY = 13;
        *comecoX = 120;
        *altSala = 10;
        *largSala = 20;
        break;
    }
}

void liberarSala(Sala *sala) {
    for (int i = 0; i < sala->alt; i++) {
        free(sala->layout[i]);
    }
    free(sala->layout);
}

void desenharCaminho(WINDOW* win, int yCaminho, int xCaminho, int alt, int comprimento) {
    if (alt == 1) {  // caminho na horizontal
        for (int i = 0; i < comprimento; ++i) {
            mvwaddch(win, yCaminho, xCaminho + i, '.');
        }
    }


    if (comprimento == 1) {  // caminho na vertical
        for (int j = 0; j < alt; ++j) {
            mvwaddch(win, yCaminho + j, xCaminho, '.');
        }
    }
}

// Desenhar os limites dos caminhos
void desenharBorda(WINDOW* win, int yCaminho, int xCaminho, int alt, int comprimento) {
    if (alt == 1) {  // caminho na horizontal
        for (int i = 0; i < comprimento; ++i) {
            mvwaddch(win, yCaminho, xCaminho + i, '#');
        }
    }




    if (comprimento == 1) {  // caminho na vertical
        for (int j = 0; j < alt; ++j) {
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

///////////////////////////////////////////////////
//          BONECO

void criarBoneco_meio(Boneco *boneco, int posY, int posX) {
    boneco->posY = posY;
    boneco->posX = posX;
    boneco->character = 'B';
}

void exibirBoneco(WINDOW *win, Boneco boneco, int comecoY, int comecoX) {
    mvwaddch(win, comecoY + boneco.posY, comecoX + boneco.posX, 'B');
}

/////MOVIMENTACAO////

int posicaoValida(Sala sala, int posY, int posX) {
    if (posY >= 0 && posY < sala.alt && posX >= 0 && posX < sala.larg &&
        sala.layout[posY][posX] == '.') {
        return 1;  // Posição válida
    }
    return 0;  // Posição inválida
}

void moverBoneco(Boneco *boneco, Sala *sala, int deltaY, int deltaX) {
    int novaPosY = boneco->posY + deltaY;
    int novaPosX = boneco->posX + deltaX;

    if (posicaoValida(*sala, novaPosY, novaPosX)) {
        boneco->posY = novaPosY;
        boneco->posX = novaPosX;
    }
}

////////////////////////////////////////////////////////
//// CHAVES
Chave criarChave(Sala *sala, int comecoY, int comecoX, int alt, int larg) {
    Chave chave;

    do {
        chave.posX = rand() % (larg - 2) + comecoX + 1;
        chave.posY = rand() % (alt - 2) + comecoY + 1;
    } while (sala->layout[chave.posY - comecoY][chave.posX - comecoX] != '.' ||
            sala->layout[chave.posY - comecoY + 1][chave.posX - comecoX] != '.');

    chave.character = 'K';
    chave.coletada = 0;

    // Adiciona a chave à matriz da sala
    sala->layout[chave.posY - comecoY][chave.posX - comecoX] = chave.character;

    return chave;
}

void exibirChave(Chave chave, Sala sala) {
    if (!chave.coletada) {
        mvaddch(chave.posY, chave.posX, chave.character);
    }
}

/////////////////////////////////////
void jogarRogue(WINDOW *win) {
    Sala sala1, sala2, sala3;
    Boneco boneco;

    criarSala(&sala1, 20, 40);
    criarSala(&sala2, 15, 30);
    criarSala(&sala3, 10, 20);

    criarBoneco_meio(&boneco, 8, 18);

    chaveSala1 = criarChave(&sala1, 7, 20, 20, 40);
    chaveSala2 = criarChave(&sala2, 20, 80, 15, 30);
    chaveSala3 = criarChave(&sala3, 13, 120, 10, 20);

    // Loop principal do jogo
    while (1) {
        werase(win);

        desenharSala(win, sala1, 7, 20);
        desenharSala(win, sala2, 20, 80);
        desenharSala(win, sala3, 13, 120);

        exibirCaminhoBorda(win);

        exibirBoneco(win, boneco, 7, 20);

        exibirChave(chaveSala1, sala1);
        exibirChave(chaveSala2, sala2);
        exibirChave(chaveSala3, sala3);

        wrefresh(win);  // Atualiza a tela principal



//////////////////////// PEGAR TECLA DO USUARIO P MOVIMENTAR O BONECO /////////////////////////////////////


        int ch = getch();  // Obtém a entrada do usuário
        switch (ch) {
            case KEY_UP:
            case 'w':
            case 'W':
                moverBoneco(&boneco, &sala1, -1, 0);
                break;
            case KEY_DOWN:
            case 's':
            case 'S':
                moverBoneco(&boneco, &sala1, 1, 0);
                break;
            case KEY_LEFT:
            case 'a':
            case 'A':
                moverBoneco(&boneco,&sala1, 0, -1);
                break;
            case KEY_RIGHT:
            case 'd':
            case 'D':
                moverBoneco(&boneco, &sala1, 0, 1);
                break;
            case 27: // ESC
                //gameover = 1;
                break;
        }

    }
}

int main() {
    initscr(); 
    noecho(); // esconde o cursor
    curs_set(0); 
    keypad(stdscr, TRUE);
    resize_term(40, 160); 

    WINDOW *win = newwin(40, 160, 0, 0);

    jogarRogue(win);

    delwin(win);  // Deleta a janela
    endwin();

    return 0;
}