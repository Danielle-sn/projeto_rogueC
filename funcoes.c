#include <ncurses.h>
#include <string.h>
#include <unistd.h> // usar a funcao sleep
#include "funcoes.h"
#include <time.h>
#include <stdlib.h>

#define altura 40
#define largura 160
Chave chaves[3];
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

//////////////////////JOGO ////////////////////////////

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

/////////////////////////////CHAVES /////////////

Chave criarChave(Sala *sala, int comecoY, int comecoX, int alt, int larg) {
    Chave chave;

    do {
        chave.posX = rand() % (larg - 2) + comecoX + 1;
        chave.posY = rand() % (alt - 2) + comecoY + 1;
    } while (sala->layout[chave.posY - comecoY][chave.posX - comecoX] != '.' );

    chave.character = 'K';
    chave.coletada = 0;

    return chave;
}


void exibirChave(Chave chave, Sala sala) {
    if (!chave.coletada) {
        mvaddch(chave.posY, chave.posX, chave.character);
    }
}


///////////////////////BONECO////////////////////////////
         

void criarBoneco_meio(Boneco *boneco, Jogador *jogador, int posY, int posX) {
    boneco->posY = posY;
    boneco->posX = posX;
    boneco->character = jogador->personagem;
}

void exibirBoneco(WINDOW *win, Boneco boneco, int comecoY, int comecoX) {
    mvwaddch(win, comecoY + boneco.posY, comecoX + boneco.posX, boneco.character);
}

/////MOVIMENTACAO////
int posicaoValida(Sala sala, int posY, int posX, Chave chave) {
    if (posY >= 0 && posY < sala.alt && posX >= 0 && posX < sala.larg) {
        char elemento = sala.layout[posY][posX];
        
        if (elemento == '.') {

            return 1;  // Posição válida
        } else if (elemento == 'K') {
            chave.coletada ++;
            //sala.layout[posY][posX] = '.';  // Remover a chave da sala
                mvaddch(3 , 59, chave.coletada);

                return chave.coletada;  // Posição válida
        }
    }
    return 0;  // Posição inválida
}

void moverBoneco(Boneco *boneco, Sala *sala, int deltaY, int deltaX, Chave *chave) {
    int novaPosY = boneco->posY + deltaY;
    int novaPosX = boneco->posX + deltaX;

    if (posicaoValida(*sala, novaPosY, novaPosX, *chave)) {
        boneco->posY = novaPosY;
        boneco->posX = novaPosX;
    }
}


void jogarRogue(Jogador jogador) {

    initscr(); 
    noecho(); // esconde o cursor
    curs_set(0); 
    keypad(stdscr, TRUE);
    resize_term(40, 160); 

    WINDOW *win = newwin(40, 160, 0, 0);


    Sala sala1, sala2, sala3;
    Chave chave;
    Chave chaveSala1, chaveSala2, chaveSala3;
    Boneco boneco;
    criarSala(&sala1, 20, 40);
    criarSala(&sala2, 15, 30);
    criarSala(&sala3, 10, 20);
    criarBoneco_meio(&boneco, &jogador, 8, 18);

    chaveSala1 = criarChave(&sala1, 7, 20, 20, 40);
    chaveSala2 = criarChave(&sala2, 20, 80, 15, 30);
    chaveSala3 = criarChave(&sala3, 13, 120, 10, 20);
    
    //captr o tempo para ranking
    time_t inicio_tempo, tempo_atual;
    jogador.tempo = 0;
    time(&inicio_tempo);
    int tempo_limite = 20;  // Tempo padrão
    switch (jogador.dificuldade) {
            case FACIL:
                tempo_limite = 2;
                break;
            case MEDIO:
                tempo_limite = 5;
                break;
            case DIFICIL:
                tempo_limite = 5;
                break;
            default:
                break;
        }
        mvwprintw(win, 5, 35, "Dificuldade: %s", dificuldadeToString(jogador.dificuldade));

    while (1) {
        werase(win);
        time(&tempo_atual);
        jogador.tempo = difftime(tempo_atual, inicio_tempo);


        time(&tempo_atual);
        jogador.tempo = difftime(tempo_atual, inicio_tempo);

        mvwprintw(win, 3, 35, "TEMPO: %d segundos", (int)jogador.tempo);
        usleep(1000);
        mvwprintw(win, 5, 35, "Dificuldade: %s", dificuldadeToString(jogador.dificuldade));

        mvwprintw(win, 4, 35, "Personagem: %c", jogador.personagem);

        desenharSala(win, sala1, 7, 20);
        desenharSala(win, sala2, 20, 80);
        desenharSala(win, sala3, 13, 120);
        exibirCaminhoBorda(win);
        exibirBoneco(win, boneco, 7, 20);

        
        exibirChave(chaveSala1, sala1);
        exibirChave(chaveSala2, sala2);
        exibirChave(chaveSala3, sala3);
        
        
        //if (boneco.posY == chave.posY && boneco.posX == chave.posX){
        //mvwaddch(win, chave.posY, chave.posX, '.');
        //}

        wrefresh(win); 

//////////////////////// PEGAR TECLA DO USUARIO P MOVIMENTAR O BONECO /////////////////////////////////////


        int ch = getch();  // Obtém a entrada do usuário
        switch (ch) {
            case KEY_UP:
            case 'w':
            case 'W':
moverBoneco(&boneco, &sala1, -1, 0, chaves);
                break;
            case KEY_DOWN:
            case 's':
            case 'S':
moverBoneco(&boneco, &sala1, 1, 0, chaves);
                break;
            case KEY_LEFT:
            case 'a':
            case 'A':
moverBoneco(&boneco, &sala1, 0, -1, chaves);
                break;
            case KEY_RIGHT:
            case 'd':
            case 'D':
moverBoneco(&boneco, &sala1, 0, 1, chaves);
                break;
            case 27: // ESC
                //gameover = 1;
                break;
        }
    }

delwin(win);  // Deleta a janela
endwin();
}


//void JOGAR_MAIN() {




/////////////////////////////////////////////////////

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




