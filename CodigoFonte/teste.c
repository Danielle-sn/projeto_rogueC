#include <ncurses.h>
#include <string.h>
#include <unistd.h> // usar a funcao sleep
#include <time.h>
#include <stdlib.h>

#define altura 40
#define largura 160


void menu_pausar(){
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    clear();
    resize_term(40, 160);
    WINDOW *win = newwin(10, 40, 15, 60);
    box(win, 0,0);

    refresh();

    char *textos[]= {"REINICIAR", "CONTINUAR", "MENU  ", "SAIR  "};
    int num_textos = sizeof(textos) / sizeof(textos[0]);
    
    int escolha = 1;

    
    while(1){

    for (int i = 0; i < num_textos; i++) {
        mvwprintw(win, 3 + i, 16, (escolha == i + 1) ? ">%s" : " %s", textos[i]);
    }

    wrefresh(win);
    int key = getch();

    switch (key){ // switch permite q um valor seja comparado com vários casos.
        case KEY_UP:
            escolha = (escolha > 1) ? escolha - 1 : num_textos;
            break;
        case KEY_DOWN:
            escolha = (escolha < num_textos ) ? escolha + 1 : 1 ;
            break;
        case 10:
            switch (escolha)
            {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;

            case 4:
                break;
            } break;
    wrefresh(win);
    wgetch(win);
    endwin();
    return;
    }

    }


}

int main(){
        menu_pausar();
        return 0;

}