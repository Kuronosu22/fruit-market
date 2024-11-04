#define MAX 100

struct fruta{
    char nome[MAX];
    float preco;
    int codigo;
    int quantidade;
};

typedef struct lista Lista;

Lista* criar_lista();

int cadastra_fruta(Lista* li, struct fruta fr);

int lista_fruta(Lista* li);

int busca_fruta(Lista* li, int codigo, struct fruta *al);

int exclui_fruta(Lista* li, int codigo);

int altera_fruta(Lista* li, struct fruta fr);

int vende_fruta(Lista* li, int codigo, int quantidade);

void libera_lista(Lista* li);