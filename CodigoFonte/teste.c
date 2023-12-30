#include <ncurses.h>
#include <stdlib.h>

struct ChaveColetada {
    int total;
};

void desenharJogador(WINDOW *win, int x, int y) {
    mvwprintw(win, y, x, "P");
}

void desenharChave(WINDOW *win, int x, int y) {
    mvwprintw(win, y, x, "K");
}

int main() {
    // Inicializa a biblioteca ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    curs_set(0);
    clear();
    refresh();

    // Cria uma janela principal
    WINDOW *win = newwin(40, 160, 0, 0);
    box(win, 0, 0);
    wrefresh(win);

    int altura, largura;
    getmaxyx(win, altura, largura);

    int jogadorX = largura / 2;
    int jogadorY = altura / 2;

    int chaveX = rand() % largura;
    int chaveY = rand() % altura;

    struct ChaveColetada chaves = {0};

    while (1) {
        // Limpa a janela principal
        wclear(win);
        box(win, 0, 0);

        if (jogadorX == chaveX && jogadorY == chaveY) {
            chaves.total++;
            chaveX = rand() % largura;
            chaveY = rand() % altura;
        }

        // Desenha o jogador e a chave na janela principal
        desenharJogador(win, jogadorX, jogadorY);
        desenharChave(win, chaveX, chaveY);

        // Atualiza a janela principal
        wrefresh(win);

        int tecla = wgetch(win);

        switch (tecla) {
            case KEY_LEFT:
                if (jogadorX > 1) jogadorX--;
                break;
            case KEY_RIGHT:
                if (jogadorX < largura - 2) jogadorX++;
                break;
            case KEY_UP:
                if (jogadorY > 1) jogadorY--;
                break;
            case KEY_DOWN:
                if (jogadorY < altura - 2) jogadorY++;
                break;
        }

        if (tecla == 'q') break;
    }

    // Finaliza a janela e a biblioteca ncurses
    wrefresh(win);
    wgetch(win);
    endwin();
}