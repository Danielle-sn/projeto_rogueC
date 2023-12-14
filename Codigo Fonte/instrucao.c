#include <ncurses.h>
#include <string.h> // manipulação de strings
#include <locale.h>
// Função para escolher um personagem
char escolherPersonagem(WINDOW *win) {
    wclear(win); // Limpa a janela
    box(win, 0, 0); // Adiciona uma borda à janela o outro não tinha borda eu acho 
    wrefresh(win); // Atualiza a janela

    // Define as opções de personagem
    char opcao1 = 'A';
    char opcao2 = 'B';
    char opcao3 = 'C';

    // Imprime as opções na janela
    mvwprintw(win, 1, 10, "ESCOLHA UM PERSONAGEM:");
    mvwprintw(win, 4, 18, "1. %c", opcao1);
    mvwprintw(win, 5, 18, "2. %c", opcao2);
    mvwprintw(win, 6, 18, "3. %c", opcao3);

    wrefresh(win); // Atualiza a janela

    curs_set(0); // Torna o cursor invisível
    // Loop para aguardar a entrada do usuário
    while (1) {
        int key = wgetch(win);
        char confirma[] = "PERSONAGEM ESCOLHIDO";

        // Determina a opção escolhida com base na tecla pressionada
        switch (key) {
            case '1':
                mvwprintw(win, 8, 8, "%s: %c", confirma, opcao1);
                wrefresh(win);
                return opcao1;
            case '2':
                mvwprintw(win, 8, 8, "%s: %c", confirma, opcao2);
                wrefresh(win);
                return opcao2;
            case '3':
                mvwprintw(win, 8, 8, "%s: %c", confirma, opcao3);
                wrefresh(win);
                return opcao3;
            default:
                mvwprintw(win, 8, 13, "OPCAO INVALIDA");
        }
    }
}

int main() {
    // Inicializa a biblioteca ncurses
    setlocale(LC_ALL, ""); // Configura a localização para a configuração padrão do ambiente
    
    initscr();
    cbreak(); // Desativa o buffer de linha, permitindo a leitura de uma tecla por vez
    noecho(); // Não exibe caracteres na tela quando são digitados
    keypad(stdscr, TRUE); // Habilita as teclas especiais, como as setas

    // Obtém as dimensões da tela
    //int h, w;
    //getmaxyx(stdscr, h, w);
    int h = 40;
    int w = 160; 
    resize_term(h, w); // Redimensiona o terminal para 40 linhas e 160 colunas
       // Cria uma janela para a escolha do personagem
    WINDOW *win = newwin(12, 40, h / 2 - 6, w / 2 - 20);

    // Chama a função para escolher um personagem
    char personagemEscolhido = escolherPersonagem(win);

    // Aguarda uma tecla antes de encerrar
    napms(2000);
    mvprintw(h - 1, 0, "Pressione qualquer tecla para sair...");
    refresh();
    getch();

    // Encerra a biblioteca ncurses
    endwin();

    return 0;
}
