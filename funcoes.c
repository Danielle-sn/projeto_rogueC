#include <ncurses.h>
#include <string.h>
#include <unistd.h> // usar a funcao sleep

#define altura 40
#define largura 160


void JOGAR(){
    clear();
    mvprintw(altura / 2, largura / 2 - 10, "Iniciando o jogo...");


    // atualiza e espera selecionar algo para voltar
    refresh();
    getch();

}
void RANKING(){
    clear();
    mvprintw(altura / 2, largura / 2 - 10, "Mostrando o ranking...");



    // atualiza e espera selecionar algo para voltar //
    refresh();
    getch();


}
void CONFIGURACOES(WINDOW *win) {
    wclear(win);
    wrefresh(win);

    char opcao1 = 'A';
    char opcao2 = 'B';
    char opcao3 = 'C';

    int num_opcoes = 3; // Número de opções

    //posição vertical central
    int inicia_y = (altura - num_opcoes) / 2;

    // Imprime as opções centralizadas na janela
    mvwprintw(win, inicia_y - 2, (largura - 20) / 2, "ESCOLHA UM PERSONAGEM:");

    // Loop para imprimir as opções centralizadas
    for (int i = 0; i < num_opcoes; i++) {
        mvwprintw(win, inicia_y + i, (largura - 4) / 2, "%d. %c", i + 1, (i == 0) ? opcao1 : (i == 1) ? opcao2 : opcao3);
    }

    wrefresh(win); 

    curs_set(0); 
    int escolha = 0; // nenhuma escolha feita
    int confirmacao = 0; // nenhuma confirmação feita

    // aguardar a entrada do usuário
    while (1) {
        int key = wgetch(win);
        char confirma[] = "SELECIONADO";

        // opção escolhida com base na tecla pressionada
        switch (key) {
            case '1':
                escolha = 1;
                break;
            case '2':
                escolha = 2;
                break;
            case '3':
                escolha = 3;
                break;
            case 10: // Enter
                if (escolha != 0) {
                    confirmacao = 1;
                }
                break;
            default:
                break;
        }

        // Se uma escolha foi feita, exibe a confirmação
        if (escolha != 0 && !confirmacao) {
            mvwprintw(win, inicia_y + 4, (largura - 20) / 2, "%s: %c. Confirmar? (Enter)", confirma, (escolha == 1) ? opcao1 : (escolha == 2) ? opcao2 : opcao3);
        } else if (confirmacao) {
            // lógica para salvar a escolha do personagem
            return;
        } else {
            mvwprintw(win,inicia_y + 4, (largura - 20) / 2, "OPCAO INVALIDA");
        }
    }
}

void INSTRUCOES(){
    clear();
    mvprintw(altura / 2, largura / 2 - 10, "Mostrando as instruções...");



    // atualiza e espera selecionar algo para voltar //
    refresh();
    getch();

}

//////// CONSTANTES //////

char* MonsterEscape[] = {
        "                                           _                                               ",
        " _____ _____ _____ _____ _____ _____ _____| |_____    _____ _____ _____ _____ _____ _____ ",
        "|     |     |   | |   __|_   _|   __| __  |_|   __|  |   __|   __|     |  _  |  _  |   __|",
        "| | | |  |  | | | |__   | | | |   __|    -| |__   |  |   __|__   |   --|     |   __|   __|",
        "|_|_|_|_____|_|___|_____| |_| |_____|__|__| |_____|  |_____|_____|_____|__|__|__|  |_____|",
        "                                                                                          "
    };

