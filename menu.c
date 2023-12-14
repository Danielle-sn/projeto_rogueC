#include <ncurses.h>
#include <string.h>
#include "constantes.h"
#include <unistd.h>
//#include "menu.h"
#define altura 40
#define largura 160

//int x0 = 0
//inicializar fora do exibir menu depois importar a x0 para dentro do exibir menu nao fumcione provaverlmente
// criar um aray e return ele


void jogar


void exibirmenu() {
    initscr(); // Inicializa a tela
    noecho();
    curs_set(0); // Configura a visibilidade do cursor

    keypad(stdscr, TRUE);

    resize_term(altura, largura); // Redimensiona a janela padrão para as dimensões especificadas
    
    start_color(); // Inicializa as cores
    init_pair(1, COLOR_YELLOW, COLOR_BLACK); // Define um par de cores



    int x0 = largura / 2;
    int y0 = altura / 2;

    char texto1[] = "JOGAR";
    int x1 = largura / 2 - strlen(texto1) / 2;
    int y1 = altura / 2 + 1;

    char texto2[] = "RANKING";
    int x2 = largura / 2 - strlen(texto2) / 2;
    int y2 = altura / 2 + 2;

    char texto3[] = "CONFIGURACOES";
    int x3 = largura / 2 - strlen(texto3) / 2;
    int y3 = altura / 2 + 3;

    char texto4[] = " INSTRUCOES";
    int x4 = largura / 2 - strlen(texto4) / 2;
    int y4 = altura / 2 + 4;

    char texto5[] = "SAIR";
    int x5 = largura / 2 - strlen(texto5) / 2;
    int y5 = altura / 2 + 5;

    int retangulo_y1 = y2 - 2;
    int retangulo_x1 = x2 - 10;
    int retangulo_y2 = y5 + 1;
    int retangulo_x2 = x2 + strlen(texto2) + 10;

    int escolha = 1; // Inicializa a escolha com a opção "JOGAR"

    while (1) {
        // EXIBE O TITULO MOSTER ESCAPE
        attron(COLOR_PAIR(1));
        for (int i = 0; i < 5; i++) {
            mvprintw(y0 + i - 12, x0 - 40, "%s", MonsterEscape[i]);
        }

        // EXIBE O RETANGULO
        for (int i = retangulo_y1; i <= retangulo_y2; i++) {
            for (int j = retangulo_x1; j <= retangulo_x2; j++) {
                if (i == retangulo_y1 || i == retangulo_y2 || j == retangulo_x1 || j == retangulo_x2) {
                    mvaddch(i, j, ACS_CKBOARD);
                }
            }
        }

        mvprintw(y1, x1, "%s", (escolha == 1) ? "> JOGAR" : "  JOGAR");
        mvprintw(y2, x2, "%s", (escolha == 2) ? "> RANKING" : "  RANKING");
        mvprintw(y3, x3, "%s", (escolha == 3) ? "> CONFIGURACOES" : "  CONFIGURACOES");
        mvprintw(y4, x4, "%s", (escolha == 4) ? "> INSTRUCOES" : "  INSTRUCOES");
        mvprintw(y5, x5, "%s", (escolha == 5) ? "> SAIR" : "  SAIR");
        attroff(COLOR_PAIR(1));

        refresh();

        int ch = getch();
        switch (ch) {
            case KEY_UP:
                escolha = (escolha > 1) ? escolha - 1 : 5;

                break;
            case KEY_DOWN:
                escolha = (escolha < 5) ? escolha + 1 : 1;
                break;
            case 10: // Enter key
                clear();
                mvprintw(altura / 2, largura / 2 - 10, "Opção selecionada: %d", escolha);
                refresh();
                getch();
                endwin();
                return;
        }
    }
}

    
    //endwin(); // encerra curses


int main(){
    exibirmenu();
    return 0;
}

