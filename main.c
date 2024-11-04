#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "main.h"

struct lista{
    int qnt;
    struct fruta dados[MAX];
};

Lista* criar_lista(){
    Lista *li;
    li = (Lista*) malloc(sizeof(Lista));
    if(li != NULL)
        li->qnt = 0;
    return li;
}

int cadastra_fruta(Lista* li, struct fruta fr){
    if(li == NULL)
        return 0;
    int  k;
    for(k = 0; k < li->qnt; k++)
        if (li->dados[k].codigo == fr.codigo){
            return 0;
        }
    li->dados[li->qnt] = fr;
    li->qnt++;
    return 1;
}

int lista_fruta(Lista* li){
    int i;
    printf("Lista: \n");
    for(i = 0; i < li->qnt; i++)
        printf("%d - %s - R$%.2lf - %d unidades | \n",li->dados[i].codigo, li->dados[i].nome, li->dados[i].preco, li->dados[i].quantidade);
    return 1;
}

int busca_fruta(Lista* li, int codigo, struct fruta *fr){
    if(li == NULL)
        return 0;
    int i = 0;
    while (i < li->qnt && li->dados[i].codigo != codigo){
        i++;
    }
    *fr = li->dados[i];
    return 1;


}

int exclui_fruta(Lista* li, int codigo){
    if(li == NULL)
        return 0;
    if(li->qnt == 0)
        return 0;
    int i = 0, k = 0;
    while(i < li->qnt && li->dados[i].codigo != codigo)
        i++;
    if(i == li->qnt)
        return 0;
    if (li->dados[i].quantidade == 0)
    {
        for(k = i; k < li->qnt-1; k++)
        li->dados[k] = li->dados[k+1];
        li->qnt--;
        return 1;
    }
    return 0;
}

int altera_fruta(Lista* li, struct fruta fr){
    if(li == NULL)
        return 0;
    if(li->qnt == 0)
        return 0;
    int k;
    for(k = 0; k < li->qnt; k++)
        if (li->dados[k].codigo == fr.codigo){
            li->dados[k] = fr;
            return 1;
            }
    return 0;
}

int vende_fruta(Lista* li, int codigo, int quantidade){
    if(li == NULL)
        return 0;
    if(li->qnt == 0)
        return 0;
    int i = 0;
    while(i < li->qnt && li->dados[i].codigo != codigo)
        i++;
    if(i == li->qnt)
        return 0;
    if(li->dados[i].quantidade == 0)
        return 0;
    if(li->dados[i].quantidade - quantidade < 0)
        return 0;
    li->dados[i].quantidade -= quantidade;    
    return 1;

}

void libera_lista(Lista* li){
    free(li);
}

int main(){
    int x, sel = 0;
    Lista* li = NULL;
    struct fruta dados_fruta;
    li = criar_lista();
    FILE *f;

    do{
        printf("Digite 1 para cadastrar uma fruta\n");
        printf("Digite 2 para listar as frutas\n");
        printf("Digite 3 para buscar uma fruta\n");
        printf("Digite 4 para alterar uma fruta\n");
        printf("Digite 5 para excluir uma fruta\n");
        printf("Digite 6 para vender uma fruta\n");
        printf("Digite 7 para sair\n");
        scanf("%d", &sel);
        switch (sel){
            case 1:
                if(li == NULL){
                    printf("A lista nao foi criada ainda.\n");
                    break;
                }
                printf("Digite o codigo da fruta\n");
                scanf("%d", &dados_fruta.codigo);
                printf("Digite o nome da fruta\n");
                scanf("%99s", dados_fruta.nome);
                printf("Digite o preco\n");
                scanf("%f", &dados_fruta.preco);
                printf("Digite a quantidade\n");
                scanf("%d", &dados_fruta.quantidade);
                
                x = cadastra_fruta(li, dados_fruta);
                if (x == 0){
                    printf("Ja existe uma fruta com esse codigo\n");
                }

                break;

            case 2:
                if(li == NULL){
                    printf("A lista nao foi criada ainda.\n");
                    break;
                }
                lista_fruta(li);
                break;

            case 3:
                printf("Digite o codigo da fruta\n");
                scanf("%d", &dados_fruta.codigo);
                x = busca_fruta(li, dados_fruta.codigo, &dados_fruta);
                if(x == 1)
                    printf("%d - %s - R$%.2lf - %d unidades | \n",dados_fruta.codigo, dados_fruta.nome, dados_fruta.preco, dados_fruta.quantidade);
                else
                    printf("O codigo nao esta na lista\n");
                break;

            case 4:
                if(li == NULL){
                    printf("A lista nao foi criada ainda.\n");
                    break;
                }
                printf("Digite o codigo da fruta\n");
                scanf("%d", &dados_fruta.codigo);
                printf("Digite o nome da fruta\n");
                scanf("%99s", dados_fruta.nome);
                printf("Digite o preco\n");
                scanf("%f", &dados_fruta.preco);
                printf("Digite a quantidade\n");
                scanf("%d", &dados_fruta.quantidade);

                altera_fruta(li, dados_fruta);
                break;

            case 5:
                printf("Digite o codigo da fruta\n");
                scanf("%d", &dados_fruta.codigo);
                x = exclui_fruta(li, dados_fruta.codigo);
                if (x == 1)
                    printf("A fruta foi removida com sucesso\n");
                else
                    printf("Erro ao remover fruta\n");
                break;

            case 6:
                printf("Digite o codigo da fruta\n");
                scanf("%d", &dados_fruta.codigo);
                printf("Digite a quantidade de venda\n");
                scanf("%d", &dados_fruta.quantidade);
                x = vende_fruta(li, dados_fruta.codigo, dados_fruta.quantidade);
                if (x == 1){
                    printf("Foram vendidas %d %s(s) a R$%.2lf cada\n", dados_fruta.quantidade, dados_fruta.nome, dados_fruta.preco);
                    f = fopen("vendas.txt", "a");
                    fprintf(f, "Foram vendidas %d %s(s) a R$%.2lf cada\n", dados_fruta.quantidade, dados_fruta.nome, dados_fruta.preco);
                    fclose(f);
                    break;
                }
                printf("Nao foi possivel vender a(s) frutas\n");
                break;

            default:
                break;
        }
    }while (sel != 7);

    libera_lista(li);
    li = NULL;

    return 0;
}