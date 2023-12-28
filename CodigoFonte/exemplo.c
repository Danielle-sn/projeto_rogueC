#include <ncurses.h>
#include <string.h>

#define altura 40
#define largura 160

typedef enum {
    FACIL,
    MEDIO,
    DIFICIL
} ModoDificuldade;

typedef struct {
    char nick_jog[30];
    int tempo;
    ModoDificuldade dificuldade;
} Jogador;

Jogador WIN_NICK_JOG() {
    Jogador jogador;
    initscr(); // Inicializa ncurses
    curs_set(1); // cursor visível
    keypad(stdscr, TRUE);

    resize_term(altura, largura);
    wrefresh(stdscr); // Atualiza a tela para exibir a borda

    // Calcula as coordenadas para centralizar a janela
    int inicioy = (LINES - altura) / 2;
    int iniciox = (COLS - largura) / 2;
    WINDOW *win = newwin(altura, largura, inicioy, iniciox);

    char *dif[] = {"FACIL", "MEDIO", "DIFICIL"};
    int num_dif = sizeof(dif) / sizeof(dif[0]);

    box(win, 0, 0);
    mvwprintw(win, 14, 60, "DIGITE SEU NOME E ESCOLHA A DIFICULDADE");    for (int i = 0; i < num_dif; i++) {
        mvwprintw(win, 22 + i, 76, dif[i]);
    }

    mvwaddch(win, 17, 55, ACS_HLINE);
    whline(win, ACS_HLINE, 55);
    mvwprintw(win, 18, 55, "Nick: ");
    mvwaddch(win, 19, 55, ACS_HLINE);
    whline(win, ACS_HLINE, 55);


    wrefresh(win);
    //Move o cursor para a posição de entrada do nick
    echo(); // Exibe os caracteres digitados na tela
    wmove(win, 18, 61);
    wgetnstr(win, jogador.nick_jog, sizeof(jogador.nick_jog) - 1);
    curs_set(0); // Torna o cursor invisível

    if (strlen(jogador.nick_jog) > 0) {
        int escolha = 1;
        wrefresh(win);

        while (1) {
            // Imprime instruções na janela
            mvwprintw(win, 14, 60, "DIGITE SEU NOME E ESCOLHA A DIFICULDADE");
            mvwprintw(win, 18, 55, "Nick: %s", jogador.nick_jog);

            // Exibe as opções de dificuldade
            for (int i = 0; i < num_dif; i++) {
                mvwprintw(win, 22 + i, 75, (escolha == i + 1) ? ">%s" : " %s", dif[i]);
            }
            wrefresh(win);

            int entrad = getch();
            switch (entrad) {
                case KEY_UP:
                    escolha = (escolha > 1) ? escolha - 1 : num_dif;
                    break;

                case KEY_DOWN:
                    escolha = (escolha < num_dif) ? escolha + 1 : 1;
                    break;

                case 10: // Enter
                    switch (escolha) {
                        case 1:
                            jogador.dificuldade = FACIL;
                            
                            break;

                        case 2:
                            jogador.dificuldade = MEDIO;
                            break;

                        case 3:
                            jogador.dificuldade = DIFICIL;
                            break;
                    }
            mvwprintw(win, 26, 65, "Dificuldade selecionada: %s", dif[jogador.dificuldade]);
            mvwprintw(win, 28, 62, "Pressione a tecla ENTER para CONTINUAR ");
            wrefresh(win);

            int confirmar = getch();
            if (confirmar == 10 ) {
                wclear(win);
                wrefresh(win);
                wgetch(win);
                delwin(win);
                return jogador; }
                
            else {
                wrefresh(win);
                mvwprintw(win, 26, 65, "                                "); //limpar dif

            }
            break;

            wgetch(win);
            delwin(win);

                    return jogador;  // Adicionei o retorno aqui para encerrar a função corretamente
            }
        }
    }           
    endwin();  // Certifique-se de chamar endwin() para restaurar o estado do terminal ao encerrar o programa.
    return jogador;  // Retorna uma estrutura vazia se o nome não for inserido
}

int main() {
    Jogador jogador = WIN_NICK_JOG();
    // Restante do seu código...
    return 0;
}
