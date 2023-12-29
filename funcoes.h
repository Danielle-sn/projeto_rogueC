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

typedef struct {
    Jogador jogadores[10];
    int quantidade; // Número atual de jogadores no ranking
} Ranking;


const char* dificuldadeToString(ModoDificuldade dificuldade);

//--------------------FUNCOES ----------------------------//

Jogador WIN_NICK_JOG(Jogador jogador);
void ABERTURA();

//-------- FUNCOES DO MENU PRINCIPAL (MAIN) ---------//


void JOGAR(Jogador jogador);
void RANKING(Jogador jogador);
char CONFIGURACOES(Jogador jogador);
void INSTRUCOES();

//// MENU PAUSAR ///

void menu_pausar();


#endif