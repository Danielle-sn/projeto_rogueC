#include <ncurses.h>
#include <string.h>
#include <unistd.h> // usar a funcao sleep
#include "funcoes.h"
#include <time.h>
#include <stdlib.h>

#define altura 40
#define largura 160

Ranking ranking = {.quantidade = 0};

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
const char* dificuldadeToString(ModoDificuldade dificuldade) {
    switch (dificuldade) {
        case FACIL:
            return "FACIL";
        case MEDIO:
            return "MEDIO";
        case DIFICIL:
            return "DIFICIL";
        default:
            return "(Desconhecido)";
    }
}
//--------------------FUNCOES ----------------------------//


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
char CONFIGURACOES(Jogador jogador) {
    initscr();
    curs_set(0);
    int alt = 20;
    int larg = 80;

    int inicioy = (LINES - alt ) / 2;
    int iniciox = (COLS - larg ) / 2;
    WINDOW *win = newwin(20, 80, 15, 40);
    keypad(win, TRUE);

    char *personagem[] = {"O", "#", "@"};
    int num_pers = sizeof(personagem) / sizeof(personagem[0]);

    wrefresh(win);
    int escolha = 0;
    box(win, 0, 0);

    mvwprintw(win, 18, 30, "ESQ para voltar");

    while (1) {
        mvwprintw(win, 3, 27, "ESCOLHA UM PERSONAGEM:");

        mvwaddch(win, 5, 25, ACS_HLINE);
        whline(win, ACS_HLINE, 25);

        for (int i = 0; i < num_pers; i++) {
            mvwprintw(win, 6 + i, 35, (escolha == i) ? ">%s" : " %s", personagem[i]);
        }

        mvwaddch(win, 9 , 25, ACS_HLINE);
        whline(win, ACS_HLINE, 25);

        int key = wgetch(win);
        switch (key) {
            case KEY_UP:
                escolha = (escolha > 0) ? escolha - 1 : num_pers - 1;
                break;
            case KEY_DOWN:
                escolha = (escolha < num_pers - 1) ? escolha + 1 : 0;
                break;
            case 27: // esq
                endwin();
                flushinp();
                return jogador.personagem;
            case 10: // Enter
                jogador.personagem = personagem[escolha][0];

                mvwprintw(win, 12, 23, "Personagem selecionado: %c", jogador.personagem);
                mvwprintw(win, 14, 20, "Pressione a tecla ENTER para CONTINUAR ");
                wrefresh(win);

                int confirmar = wgetch(win);
                if (confirmar == 10) {
                    wrefresh(win);
                    flushinp();
                    endwin();
                    return jogador.personagem;
                }
                break;
        }
        wrefresh(win);
    }

    // Adicione um retorno padrão caso o código atinja esse ponto
    return '\0';
}

Jogador WIN_NICK_JOG(Jogador jogador) {
    
    initscr(); 
    curs_set(1); 
    keypad(stdscr, TRUE);
    resize_term(altura, largura);
    wrefresh(stdscr);
    // Calcula as coordenadas para centralizar a janela
    int inicioy = (LINES - altura) / 2;
    int iniciox = (COLS - largura) / 2;
    WINDOW *win = newwin(altura, largura, inicioy, iniciox);

    char *dif[] = {"FACIL  ", "MEDIO  ", "DIFICIL"};
    int num_dif = sizeof(dif) / sizeof(dif[0]);

    box(win, 0, 0);
    mvwprintw(win, 14, 60, "DIGITE SEU NOME E ESCOLHA A DIFICULDADE");    for (int i = 0; i < num_dif; i++) {
        mvwprintw(win, 22 + i, 76, dif[i]);
    }
        // EXIBE O TITULO MOSTER ESCAPE
    for (int i = 0; i < 5; i++) {
        mvwprintw(win, 6 + i , 40 , "%s", MonsterEscape[i]);
        }
    mvwprintw(win, 29, 62, "Pressione a tecla ENTER para CONTINUAR ");

    if (jogador.personagem != 'O' && jogador.personagem != '#' && jogador.personagem != '@') {
        jogador.personagem = '@';
    }
    
    mvwprintw(win, 20, 73, "Personagem: %c", jogador.personagem);

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
                noecho();
            break;  // Sai do loop se o nick for digitado corretamente
        } else {
            mvwprintw(win, 16, 63, "Por favor, digite um nick válido.");
            wrefresh(win);
        }
    }
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
            return jogador; }
        else {
            wrefresh(win);
            mvwprintw(win, 26, 65, "                                "); //limpar dific
            } break;
        }
    }
        endwin();  
        return jogador;
}


void adicionarAoRanking(Jogador jogador) {
    if (ranking.quantidade < 10) {
        ranking.jogadores[ranking.quantidade] = jogador;
        ranking.quantidade++;
    } else {
        // Encontrar o índice do pior jogador no ranking
        int indicePiorJogador = 0;
        for (int i = 1; i < 10; i++) {
            if (ranking.jogadores[i].tempo > ranking.jogadores[indicePiorJogador].tempo) {
                indicePiorJogador = i;
            }
        }
        // Substituir o pior jogador se o novo jogador tiver um tempo melhor
        if (jogador.tempo < ranking.jogadores[indicePiorJogador].tempo) {
            ranking.jogadores[indicePiorJogador] = jogador;
        }
    }
}
void ordenarRanking() {
    for (int i = 0; i < ranking.quantidade - 1; i++) {
        for (int j = i + 1; j < ranking.quantidade; j++) {
            //comparando pela dificuldade
            if (ranking.jogadores[i].dificuldade < ranking.jogadores[j].dificuldade || (ranking.jogadores[i].dificuldade == ranking.jogadores[j].dificuldade && ranking.jogadores[i].tempo > ranking.jogadores[j].tempo )) {
                // Trocar os jogadores de posição se o tempo for maior
                Jogador temp = ranking.jogadores[i];
                ranking.jogadores[i] = ranking.jogadores[j];
                ranking.jogadores[j] = temp;
            }
        }
    }
}
void RANKING(Jogador jogador) {
    initscr();
    curs_set(0);
    resize_term(altura, largura);
    clear();
    WINDOW *win = newwin(20, 80, 15, 40);
    box(win, 0, 0);

    ordenarRanking();

    // Título e borda superior
    mvwprintw(win, 1, 32, "=== RANKING ===");
    mvwhline(win, 2, 1, ACS_HLINE, 78);

    // Cabeçalhos
    mvwprintw(win, 4, 5, "Posição");
    mvwprintw(win, 4, 20, "Jogador");
    mvwprintw(win, 4, 45, "  Tempo");
    mvwprintw(win, 4, 65, "Dificuldade");

    // Linha separadora
    mvwhline(win, 5, 1, ACS_HLINE, 78);

    for (int i = 0; i < ranking.quantidade; i++) {
        mvwprintw(win, 6 + i, 5, "  %dº ", i + 1);
        mvwprintw(win, 6 + i, 20, "%s", ranking.jogadores[i].nick_jog);
        mvwprintw(win, 6 + i, 45, "%d segundos", (int)ranking.jogadores[i].tempo);
        mvwprintw(win, 6 + i, 65, "   %s", dificuldadeToString(ranking.jogadores[i].dificuldade));
    }

    wrefresh(win);
    wgetch(win);

    wrefresh(win);
    wgetch(win);
    endwin();
    return;
}

//// MENU PAUSAR ///

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

    char *textos[]= {"REINICIAR", "CONTINUAR"," RANKING", "  MENU  ", "  SAIR  "};
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
            switch (escolha){
            case 1:
                // REINICIAR O JOGO
                break;
            case 2:
                // CONTINUr jogando
                return;
            case 3:
                //RANKING
                return;
            case 4:
                //VOLTAR AO MENU
            case 5:
                endwin();
                exit(0); 

            } break;
    wrefresh(win);
    wgetch(win);
    endwin();
    return;
    }
    }
}



void JOGAR(Jogador jogador){
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);
    clear();
    refresh();
    resize_term(40, 160);
    WINDOW *win = newwin(altura, largura, 0, 0);
    box(win, 0, 0);
    nodelay(win, TRUE);

    time_t inicio_tempo, tempo_atual;
    jogador.tempo = 0;
    time(&inicio_tempo);

    // Ajuste de acordo com a dificuldade escolhida
    int range_max = 10;  // Faixa padrão
    int tempo_limite = 20;  // Tempo padrão

    switch (jogador.dificuldade) {
        case FACIL:
            range_max = 4;
            tempo_limite = 2;
            break;
        case MEDIO:
            range_max = 8;
            tempo_limite = 5;
            break;
        case DIFICIL:
            range_max = 10;
            tempo_limite = 5;
            break;
        default:
            break;
    }

    int numero_secreto = rand() % range_max + 1; // Escolher um número aleatório entre 1 e range_max
    int palpite, tentativas = 0;

    // Imprime a dificuldade escolhida
    mvwprintw(win, 15, 23, "Dificuldade: %s", dificuldadeToString(jogador.dificuldade));
    mvwprintw(win, 16, 23, "Personagem: %c", jogador.personagem);
    wrefresh(win);

    while (1) {
    // Verificar se o tempo limite foi atingido antes de solicitar uma nova tentativa
    time(&tempo_atual);
    jogador.tempo = difftime(tempo_atual, inicio_tempo);



    if (jogador.tempo >= tempo_limite) {
        mvwprintw(win, 14, 23, "Tempo esgotado! O número era %d.", numero_secreto);
        menu_pausar();
        break;
    }

    mvwprintw(win, 10, 23, "Adivinhe o número:");
    wrefresh(win);
    // Atualizar tempo na tela
    mvwprintw(win, 13, 23, "Tempo: %d segundos", (int)jogador.tempo);
    usleep(100000);

    echo();

    char palpite_str[10];  // Ajuste o tamanho conforme necessário
    mvwgetnstr(win, 10, 43, palpite_str, sizeof(palpite_str));

    // Atualizar tempo na tela
    mvwprintw(win, 13, 23, "Tempo: %d segundos", (int)jogador.tempo);
    usleep(100000);

    noecho();

    // Converta a string para um número
    if (sscanf(palpite_str, "%d", &palpite) != 1) {
        mvwprintw(win, 12, 23, "Por favor, digite um número válido.");
        wrefresh(win);
        continue;
    }

    tentativas++;

    if (palpite == numero_secreto) {
        mvwprintw(win, 12, 23, "Parabéns! Você acertou em %d tentativas.", tentativas);
        jogador.tempo = difftime(time(NULL), inicio_tempo);
        adicionarAoRanking(jogador);
        break;
    } else {
        mvwprintw(win, 12, 23, "Tente novamente!");
    }

    // Atualizar tempo na tela
    mvwprintw(win, 13, 23, "Tempo: %d segundos", (int)jogador.tempo);
    usleep(100000);

    wrefresh(win);
}

    wrefresh(win);
    wgetch(win);
    wclear(win);
    endwin();
    return;
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



