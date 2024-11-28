//  Arquivo ArvBinaria.h
//  TAD: ProjArvoreBinaria-V2

#define FALSO      0
#define VERDADEIRO 1

#define OK         1
#define ERRO       0

typedef struct {
    char us[46];
    char pt[46];
} Tipo_Dado;

//Definição do tipo Arvore
struct NO{
    Tipo_Dado info;
    struct NO *esq;
    struct NO *dir;
};

typedef struct NO NodoArvBin;
typedef struct NO *ArvBin;

ArvBin* cria_ArvBin();
void libera_ArvBin(ArvBin *raiz);
int insere_ArvBin(ArvBin* raiz, Tipo_Dado valor, int (*compara)(char*, char*));
int remove_ArvBin(ArvBin *raiz, Tipo_Dado valor, int (*compara)(char*, char*));
int estaVazia_ArvBin(ArvBin *raiz);
int altura_ArvBin(ArvBin *raiz);
int totalNO_ArvBin(ArvBin *raiz);
int consulta_ArvBin(ArvBin *raiz, char *chave, Tipo_Dado *resultado, int (*compara)(char*, char*));
void preOrdem_ArvBin(ArvBin *raiz);
void emOrdem_ArvBin(ArvBin *raiz);
void posOrdem_ArvBin(ArvBin *raiz);

// Funcoes Adicionais
void Procura_preOrdem_ArvBin(ArvBin *raiz, Tipo_Dado valor, int *achou, int (*compara)(char*, char*));
void Exibe_emOrdem_ArvBin(ArvBin *raiz);

int compara_us(char *a, char *b);
int compara_pt(char *a, char *b);
