#include <ncurses.h>
#include <string.h>
#include "funcoes.h"

#define altura 40
#define largura 160

void exibirmenu() {
    initscr(); 
    curs_set(0); // Configura a visibilidade do cursor
    keypad(stdscr, TRUE);
    resize_term(altura, largura); // Redimensiona a janela padrão para as dimensões especificadas
    start_color(); // Inicializa as cores
    init_pair(1, COLOR_YELLOW, COLOR_BLACK); // Define um par de cores

    WINDOW *Win = newwin(altura, largura, 0,0);
    int offset = 0;

    //ABERTURA(Win, offset);


    clear();


    int meio_x = largura / 2;
    int meio_y = altura / 2;

    char *textos[]= {"JOGAR", "RANKING", "CONFIGURACOES", "INSTRUCOES", "SAIR"};
    int num_opcoes = sizeof(textos) / sizeof(textos[0]);

    int retangulo_y1 = meio_y - 4 ;
    int retangulo_x1 = meio_x - 10;
    int retangulo_y2 = meio_y + num_opcoes - 1 ;
    int retangulo_x2 = meio_x + 11;


    int escolha = 1; // Inicializa a escolha com a opção "JOGAR"

    while (1) {
        // EXIBE O TITULO MOSTER ESCAPE
        attron(COLOR_PAIR(1));
        for (int i = 0; i < 5; i++) {
            mvprintw(meio_y + i - 12, meio_x - 45, "%s", MonsterEscape[i]);
        }

        for (int i = 0; i < 5; i++) {  // EXIB CRIADORES
            mvprintw(33 + i, 3, "%s", Criadores[i]);
            }


        box(stdscr, 0, 0);        // borda

        //EXIBE O RETANGULO
        for (int i = retangulo_y1; i <= retangulo_y2; i++) {
            for (int j = retangulo_x1; j <= retangulo_x2; j++) {
                if (i == retangulo_y1 || i == retangulo_y2) {
                    mvaddch(i, j, ACS_HLINE); // horizontal
                } else if (j == retangulo_x1 || j == retangulo_x2) {
                    mvaddch(i, j, ACS_VLINE); // vertical
                }
            }
        }
        // EXIBE AS OPCOES DO MENU + aparecer > quando eu mover para baixo
        for (int i = 0; i< num_opcoes; i++){
            mvprintw(meio_y + i - num_opcoes / 2, meio_x - strlen(textos[i]) / 2, (escolha == i + 1) ? ">%s" : " %s", textos[i]);
        } 
        attroff(COLOR_PAIR(1));
        refresh();

        Jogador jogador;

        int entrad = getch();
        switch (entrad) {
            case KEY_UP:
                escolha = (escolha > 1) ? escolha - 1 : num_opcoes;
                break;

            case KEY_DOWN:
                escolha = (escolha < num_opcoes) ? escolha + 1 : 1;
                break;

            case 10: // Enter 
                switch (escolha)
                {
                case 1:
                    jogador = WIN_NICK_JOG();
                    JOGAR(jogador);
                    clear();
                    break;
                case 2:
                    RANKING();
                    clear();
                    break;
                case 3:
                    jogador = CONFIGURACOES(Win);
                    clear();
                    break; 
                case 4:
                    INSTRUCOES();
                    clear();
                    break;
                case 5:
                    endwin();
                    return; }
            break;

                refresh();
                getch();
                endwin();
                return;
        }
    }
}

int main(){
    exibirmenu();
    return 0;
}

