#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <curses.h>

#define altura 40
#define largura 80
#define INFO_ALTURA 10
#define INFO_LARGURA 25 // Ajustei o tamanho da janela de informações

typedef enum {
    FACIL,
    MEDIO,
    DIFICIL
} ModoDificuldade;

typedef struct {
    char nick_jog[50];
    int tempo;
    char personagem;
    ModoDificuldade dificuldade;
} Jogador;

void print_game_info(WINDOW *info_win, const Jogador *jogador, time_t start_time, time_t end_time) {
    // Limpa a janela de informações
    werase(info_win);

    // Imprime informações do jogador
    mvwprintw(info_win, 1, 1, "Nick: %s", jogador->nick_jog);
    mvwprintw(info_win, 2, 1, "Started at: %s", ctime(&start_time));
    mvwprintw(info_win, 3, 1, "Ended at: %s", ctime(&end_time));
    mvwprintw(info_win, 4, 1, "Time played: %.2f seconds", difftime(end_time, start_time));
    mvwprintw(info_win, 6, 1, "Personagem: %c", jogador->personagem);
    mvwprintw(info_win, 7, 1, "Dificuldade: %d", jogador->dificuldade);

    // Atualiza a janela de informações
    wrefresh(info_win);
}

//-------- FUNCOES DO MENU PRINCIPAL (MAIN) ---------//
void JOGAR(const Jogador *jogador) {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    curs_set(0);
    clear();
    refresh();
    resize_term(altura, largura);

    // Cria a janela principal
    WINDOW *win = newwin(altura, largura, 0, 0);
    box(win, 0, 0);

    // Ajustei as coordenadas e o tamanho da janela de informações
    WINDOW *info_win = newwin(INFO_ALTURA, INFO_LARGURA, 1, largura - INFO_LARGURA - 1);
    box(info_win, 0, 0);

    // Exibe os criadores
    for (int i = 0; i < 5; i++) {
        mvwprintw(win, 33 + i, 3,"Criadores[i]");
    }

    // Atualiza a janela principal
    wrefresh(win);

    time_t start_time, end_time;
    time(&start_time);

    int ch;
    while ((ch = getch()) != 'q') {
        // Lógica do jogo aqui
    }

    // Fim do jogo
    time(&end_time);
    print_game_info(info_win, jogador, start_time, end_time);

    // Espera por uma tecla antes de encerrar
    wgetch(win);

    // Finaliza o curses
    endwin();
}
int main() {
    Jogador jogador = {"SeuNickAqui", 0, 'A', FACIL};
    JOGAR(&jogador);

    return 0;
}