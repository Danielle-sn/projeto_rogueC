#include <ncurses.h>
#include <string.h>
#include <unistd.h> // usar a funcao sleep
#include "funcoes.h"
#include <time.h>

#define altura 40
#define largura 160

//////// CONSTANTES //////

char* MonsterEscape[] = {
        "                                           _                                               ",
        " _____ _____ _____ _____ _____ _____ _____| |_____    _____ _____ _____ _____ _____ _____ ",
        "|     |     |   | |   __|_   _|   __| __  |_|   __|  |   __|   __|     |  _  |  _  |   __|",
        "| | | |  |  | | | |__   | | | |   __|    -| |__   |  |   __|__   |   --|     |   __|   __|",
        "|_|_|_|_____|_|___|_____| |_| |_____|__|__| |_____|  |_____|_____|_____|__|__|__|  |_____|",
        "                                                                                          "
    };
char *instru[] = {
    "                         BEM-VINDO AO MONSTER ESCAPE!",
    "--------------------------------------------------------------------------------",
    "           OBJETIVO",
    "--------------------------------------------------------------------------------",
    "Você está preso em um labirinto perigoso cheio de monstros e portas trancadas.",
    "Sua missão é escapar o mais rápido possível, coletando todas as chaves pelo caminho",
    "e alcançando a saída antes que os monstros o alcancem!",
    "--------------------------------------------------------------------------------",
    "          COMO JOGAR",
    "--------------------------------------------------------------------------------",
    "Use as teclas W A S D para se movimentar.", "W (cima), A (esquerda), S (baixo) e D (direita).","   ",
    "Fique atento aos monstros que patrulham o labirinto e evite ser pego por eles!",
    "Colete todas as chaves espalhadas pelo labirinto para destrancar as portas e",
    "abra caminho para a liberdade.", "Não se esqueça de manter um olho no medidor de tempo. ",
    "Selecione sua dificuldade e Adicione seu nick", "Ajuste sua estratégia para obter a melhor colocação no ranking.",
    "--------------------------------------------------------------------------------",
    "         CONTROLES DO MENU",
    "--------------------------------------------------------------------------------",
    "Pressione a tecla ESC para pausar o jogo e use o botão esquerdo do mouse",
    "para selecionar as opções do menu.", "Prepare-se para a aventura e boa sorte!",
};
char *venceu[] = {                                             
"_____ _____ _____ _____    _____ _____ _____ _____ _____ _____  ", 
"|  |  |     |     |   __|  |  |  |   __|   | |     |   __|  |  |",  
"|  |  |  |  |   --|   __|  |  |  |   __| | | |   --|   __|  |  |",  
" \\___/|_____|_____|_____|   \\___/|_____|_|___|_____|_____|_____|"                                                 
};
char *fimdejogo[] = {
                                                    
" _____ _____ _____    ____  _____       __ _____ _____ _____ ",
"|   __|     |     |  |    \\|   __|   __|  |     |   __|     |",
"|   __|-   -| | | |  |  |  |   __|  |  |  |  |  |  |  |  |  |",
"|__|  |_____|_|_|_|  |____/|_____|  |_____|_____|_____|_____|"
};
char *Criadores[] = { "  CRIADORES ",
"Danielle Nunes", 
"Isabella Costa", 
"Michelly Darquia" , 
"Thiago Cavalcanti" };

//--------------------FUNCOES ----------------------------//

Jogador WIN_NICK_JOG() {
    Jogador jogador;
    initscr(); 
    curs_set(1); 
    keypad(stdscr, TRUE);

    resize_term(altura, largura);
    wrefresh(stdscr);

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
        // EXIBE O TITULO MOSTER ESCAPE
    for (int i = 0; i < 5; i++) {
        mvwprintw(win, 6 + i , 40 , "%s", MonsterEscape[i]);
        }

    while (1) {
        mvwaddch(win, 17, 55, ACS_HLINE);
        whline(win, ACS_HLINE, 55);
        mvwprintw(win, 18, 55, "Nick: ");
        mvwaddch(win, 19, 55, ACS_HLINE);
        whline(win, ACS_HLINE, 55);

        echo();
        wmove(win, 18, 61);
        wgetnstr(win, jogador.nick_jog, sizeof(jogador.nick_jog) - 1);
        curs_set(0);

        if (strlen(jogador.nick_jog) > 0) {
            break;  // Sai do loop se o nick for digitado corretamente
        } else {
            mvwprintw(win, 16, 63, "Por favor, digite um nick válido.");
            wrefresh(win);
        }
    }


    if (strlen(jogador.nick_jog) > 0) {
        int escolha = 1;
        wrefresh(win);

        while (1) {
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
            mvwprintw(win, 27, 65, "Dificuldade selecionada: %s", dif[jogador.dificuldade]);
            mvwprintw(win, 29, 62, "Pressione a tecla ENTER para CONTINUAR ");
            wrefresh(win);

            int confirmar = getch();
            if (confirmar == 10 ) {
                
                wrefresh(win);
                wgetch(win);
                return jogador; }
            else {
                wrefresh(win);
                mvwprintw(win, 26, 65, "                                "); //limpar dific
            } break;
            wgetch(win);
            delwin(win);
                    return jogador;  // Adicionei o retorno aqui para encerrar a função corretamente
            }
        }
    } 
        


                endwin();  
                return jogador;
}
void ABERTURA(WINDOW *win, int offset) {
    wclear(win);
    box(win, 0, 0); 
    wrefresh(win);
    resize_term(altura, largura);
    start_color(); // Inicializa as cores
    init_pair(1, COLOR_YELLOW, COLOR_BLACK); // Define um par de cores
    // init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    // wattron(win, COLOR_PAIR(1));
    attron(COLOR_PAIR(1));
    for (int i = 0; i < sizeof(MonsterEscape) / sizeof(MonsterEscape[0]); i++) {
        for (int j = 0; j < strlen(MonsterEscape[i]); j++) {
            mvwaddch(win, altura / 2 + i - 12, largura / 2 - strlen(MonsterEscape[i]) / 2 + j + offset, MonsterEscape[i][j]);
            wrefresh(win);
            usleep(1000);
        }
     
    }
    int tempo_abertura = 4;
    sleep(tempo_abertura);
    attroff(COLOR_PAIR(1));
    endwin();
}

//-------- FUNCOES DO MENU PRINCIPAL (MAIN) ---------//
void JOGAR() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    WINDOW *win = newwin(altura, largura, 0, 0);

    curs_set(0);
    clear();
    refresh();
    resize_term(altura, largura);


    // Exibe os criadores
    for (int i = 0; i < 5; i++) {
        mvwprintw(win, 33 + i, 3, "%s", Criadores[i]);
    }

    wrefresh(win);

    endwin();
}

void RANKING(){
    initscr();
    resize_term(40, 160);
    //cbreak(); //entrada é pross imediatamente , sem Enter
    curs_set(0);
    clear();

    WINDOW *win = newwin(20, 80, 15, 40 );
    
    box(win, 0,0);


    wrefresh(win);
    wgetch(win);
    endwin();
    return;
}
Jogador CONFIGURACOES() {
    initscr(); //iniciei a janela, se eu n iniio ela não abre junto com o menu principal
    curs_set(0);
    int alt = 20;
    int larg = 80;

    int inicioy = (LINES - alt ) / 2;
    int iniciox = (COLS - larg ) / 2;
    WINDOW *win = newwin(20, 80, 15, 40 ); // (finaly , finalx inicioy , iniciox)
    keypad(win ,TRUE);

    char *personagem[] = {"O", "#", "@"};
    int num_pers = sizeof(personagem) / sizeof(personagem[0]);

    wrefresh(win);
    int escolha = 0;
    box(win, 0, 0);
    Jogador jogador;

    while (1) {
        mvwprintw(win, 3, 27, "ESCOLHA UM PERSONAGEM:");

            mvwaddch(win, 5, 25, ACS_HLINE);
            whline(win, ACS_HLINE, 25);

        for (int i = 0; i < num_pers; i++) {  // EXIBE AS OPC DO PERSON
            mvwprintw(win, 6 + i, 35, (escolha == i) ? ">%s" : " %s", personagem[i]);
        }
            mvwaddch(win, 9 , 25, ACS_HLINE);
            whline(win, ACS_HLINE, 25);

        int key = wgetch(win);
        switch (key) {
            case KEY_UP:
                escolha = (escolha > 0) ? escolha - 1 : num_pers -1;
                break;
            case KEY_DOWN:
                escolha = (escolha < num_pers - 1) ? escolha + 1 : 0;
                break;
            case 10: // Enter
                jogador.personagem = personagem[escolha][0];

                mvwprintw(win, 12, 23, "Personagem selecionado: %c", jogador.personagem);
                mvwprintw(win, 14, 20, "Pressione a tecla ENTER para CONTINUAR ");
                wrefresh(win);

                int confirmar = wgetch(win);
                if (confirmar == 10) {
                    wrefresh(win);
                    return jogador;
                }
                break;
        }
        wrefresh(win);
    } return jogador;
}
void INSTRUCOES() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    curs_set(0);
    clear();
    refresh();
    resize_term(40, 160);
    int inicioy = (LINES - altura) / 2;
    int iniciox = (COLS - largura) / 2;
    WINDOW *win = newwin(altura, largura, inicioy, iniciox);

    int texto_alt = sizeof(instru) / sizeof(instru[0]);
    int texto_larg = 0;

    box(win, 0,0);
    // Calcula o comprimento da linha mais longa nas instruções
    for (int i = 0; i < texto_alt; i++) {
        int comprimento_instrucao = strlen(instru[i]);
        texto_larg = comprimento_instrucao > texto_larg ? comprimento_instrucao : texto_larg;
    }

    // Calcula as coordenadas para posicionar a janela de instruções centralmente na tela
    int instru_y = (altura - texto_alt) / 2;
    int instru_x = (largura - texto_larg) / 2;
    

    // Exibe as instruções na tela
    for (int i = 0; i < texto_alt; i++) {
    mvwaddstr(win, instru_y + i, instru_x, instru[i]);
    }
    for (int i = 0; i < 5; i++) {  // EXIB CRIADORES
        mvwprintw(win, 33 + i, 3, "%s", Criadores[i]);
    }

    wrefresh(win);
    wgetch(win);
    endwin();
    return;
}


//// MENU PAUSAR ///

void menu_pausar(WINDOW *stdscr) {
    initscr(); // Inicializar a tela
    keypad(stdscr, TRUE); // Habilitar teclas especiais
    noecho(); // Não exibir as teclas pressionadas
    curs_set(0); // Ocultar o cursor

    int x = largura / 2;
    int y = altura / 2;

    // Coordenadas para as opções do menu
    int x2 = largura / 2 - strlen("REINICIAR") / 2;
    int y2 = altura / 2 + 1;
    int x3 = largura / 2 - strlen("CONTINUAR") / 2;
    int y3 = altura / 2 + 2;
    int x4 = largura / 2 - strlen("MENU") / 2;
    int y4 = altura / 2 + 3;
    int x5 = largura / 2 - strlen("SAIR") / 2;
    int y5 = altura / 2 + 4;

    werase(stdscr);
    int retangulo_y1 = y2 - 2;
    int retangulo_x1 = x2 - 3 < x4 - 3 ? x2 - 3 : x4 - 3;
    int retangulo_y2 = y4 + 3;
    int retangulo_x2 = x2 + strlen("REINICIAR") + 3 > x4 + strlen("SAIR") + 3 ? x2 + strlen("REINICIAR") + 3 : x4 + strlen("SAIR") + 3;

    wborder(stdscr, '|', '|', '-', '-', '+', '+', '+', '+');

    mvwaddch(stdscr, 20, 74, ACS_HLINE);
    wmove(stdscr, 20, 74);
    whline(stdscr, ACS_HLINE, 13);
    mvwaddch(stdscr, 25, 74, ACS_HLINE);
    wmove(stdscr, 25, 74);
    whline(stdscr, ACS_HLINE, 13);
    mvprintw(y2, x2, "REINICIAR");
    mvprintw(y3, x3, "CONTINUAR");
    mvprintw(y4, x4, "MENU");
    mvprintw(y5, x5, "SAIR");
    refresh();

    getch(); 
    endwin(); 
}


