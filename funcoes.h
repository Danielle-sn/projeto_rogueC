#ifndef FUNCOES_H  // Importa o arquivo de constantes
#define FUNCOES_H


// CONSTANTES
extern char* MonsterEscape[];
extern char* instru[];
extern char *venceu[];
extern char *fimdejogo[];
extern char *Criadores[];


typedef enum { // enum
    FACIL,
    MEDIO,
    DIFICIL 
}  ModoDificuldade;

typedef struct {
    char nick_jog[50]; 
    int tempo;
    char personagem;
    ModoDificuldade dificuldade;
}Jogador;


//--------------------FUNCOES ----------------------------//

Jogador WIN_NICK_JOG();
void ABERTURA();

//-------- FUNCOES DO MENU PRINCIPAL (MAIN) ---------//


void JOGAR();
void RANKING();
Jogador CONFIGURACOES();
void INSTRUCOES();

//// MENU PAUSAR ///

void menu_pausar();


#endif