#include <ncurses.h>
#include <string.h>
#include <stdlib.h>
#include "funcoes.h"

#define altura 40
#define largura 160

void exibirmenu() {
    initscr(); 
    noecho(); // esconde o cursor
    curs_set(0); 
    keypad(stdscr, TRUE);
    resize_term(altura, largura); 
    WINDOW *Win = newwin(altura, largura, 0,0);
    int offset = 0;

    //ABERTURA(Win, offset);
    clear();
    Jogador jogador;

    int meio_x = largura / 2;
    int meio_y = altura / 2;

    char *textos[]= {"JOGAR", "RANKING", "CONFIGURACOES", "INSTRUCOES", "SAIR"};
    int num_opcoes = sizeof(textos) / sizeof(textos[0]);

    int retangulo_y1 = meio_y - 4 ;
    int retangulo_x1 = meio_x - 10;
    int retangulo_y2 = meio_y + num_opcoes - 1 ;
    int retangulo_x2 = meio_x + 11;

    int escolha = 1; 
    while (1) {
        // EXIBE O TITULO MOSTER ESCAPE
        for (int i = 0; i < 5; i++) {
            mvprintw(meio_y + i - 12, meio_x - 45, "%s", MonsterEscape[i]);
        }
        for (int i = 0; i < 5; i++) {  // EXIB CRIADORES
            mvprintw(33 + i, 3, "%s", Criadores[i]);
            }
        box(stdscr, 0, 0);     
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
                switch (escolha){
                case 1:
                    jogador =  WIN_NICK_JOG(jogador);
                    jogarRogue(jogador);
                    //JOGAR(jogador);
                    RANKING(jogador);
                    break;
                case 2:
                    RANKING(jogador);
                    clear();
                    break;
                case 3:
                    jogador.personagem = CONFIGURACOES(jogador);
                    clear();
                    break; 
                case 4:
                    INSTRUCOES();
                    clear();
                    break;
                case 5:
                    endwin();
                    exit(0);
                    } break;
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

