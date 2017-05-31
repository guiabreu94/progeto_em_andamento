#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Trabalho de estrutura de dados complexas Exemplo de arvore de busca
*/

struct NO{
  int info;
  char nome[30];
  float preco;
  struct NO * esq;
  struct NO * dir;
};
typedef NO* ArvBin;
//ArvBin* raiz;
ArvBin* cria_ArvBin();
void libera_ArvBin(ArvBin *raiz);
int estaVazia_ArvBin(ArvBin *raiz);
int altura_ArvBin(ArvBin *raiz);
int totalNO_ArvBin(ArvBin *raiz);
int preOrdem_Arvbin(ArvBin *raiz);
int emOrdem_ArvBin(ArvBin *raiz);
int posOrdem_ArvBin(ArvBin *raiz);
int insere_ArvBin(ArvBin *raiz, int valor);
int remove_ArvBin(ArvBin *raiz, int valor);
struct NO* remove_atual(struct NO* atual);
int consulta_ArvBin(ArvBin *raiz, int valor);


ArvBin* cria_ArvBin(){//cria uma árvore binária
ArvBin* raiz = (ArvBin*)  malloc(sizeof(ArvBin));// fazendo a alocação da árvore binária
if(raiz != NULL){//verificando se a raiz foi criada ou se ela retornou nulo(se deu certo a alocação)
  *raiz = NULL;
}
return raiz;
/*
Primeiramente ela irá apontar para um nó nulo, que depois serão inseridos os seguintes nós;
*/
};

//----------------------------------------------------------------------------------------------------------------------

void libera_NO(struct NO* no){//libera um nó da arvore
  if(no == NULL){
    return;
  }else{
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no == NULL;
  }
};
//----------------------------------------------------------------------------------------------------------------------

void libera_ArvBin(ArvBin *raiz){//libera a arvore inteira
  if(raiz == NULL){
    return;
  }else{
    libera_NO(*raiz);//libera cada nó
    free(raiz);//libera a raiz
  }
};
//----------------------------------------------------------------------------------------------------------------------

int estaVazia_ArvBin(ArvBin * raiz){//Verifica se a árvore está vazia
  if(raiz == NULL){
    return 1;
  }else if(*raiz == NULL){
    return 1;
  }else{
    return 0;
  }
}
//----------------------------------------------------------------------------------------------------------------------

int altura_ArvBin(ArvBin *raiz){//verifica a altura da árvore
  if(raiz == NULL){
    return 0;
  }else if(*raiz == NULL){
    return 0;
  }else{
    int alt_esq= altura_ArvBin(&((*raiz)->esq));
    int alt_dir= altura_ArvBin(&((*raiz)->dir));
    if(alt_esq > alt_dir){
      return (alt_esq +1);
    }else{
      return (alt_dir +1);
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------
int totalNO_ArvBin(ArvBin *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = totalNO_ArvBin(&((*raiz)->esq));
    int alt_dir = totalNO_ArvBin(&((*raiz)->dir));
    return(alt_esq + alt_dir + 1);
}

//----------------------------------------------------------------------------------------------------------------------

int preOrdem_Arvbin(ArvBin *raiz){//utiliza o conceito de pre ordem(raiz,esq,dir) para printar os valores da arvore
  if(raiz == NULL){
    return 0;
  }else if(*raiz != NULL){
    printf("->(");
    printf("%d",(*raiz)->info);
    printf(")");
    printf("------nome do produto: %s",(*raiz)->nome);
    printf("------preco do produto: %f.2\n",(*raiz)->preco);
    preOrdem_Arvbin(&((*raiz)->esq));
    preOrdem_Arvbin(&((*raiz)->dir));
  }

}

//----------------------------------------------------------------------------------------------------------------------
int emOrdem_ArvBin(ArvBin *raiz){//utiliza o conceito de intra ordem(esq,raiz,dir) para printar os valores da arvore
  if(raiz == NULL){
    return 0;
  }else if(*raiz != NULL){
    emOrdem_ArvBin(&((*raiz)->esq));
    printf("->(");
    printf("%d",(*raiz)->info);
    printf(")");
    printf("------nome do produto: %s",(*raiz)->nome);
    printf("------preco do produto: %f.2\n",(*raiz)->preco);
    emOrdem_ArvBin(&((*raiz)->esq));
  }
}

//----------------------------------------------------------------------------------------------------------------------
int posOrdem_ArvBin(ArvBin *raiz){//utiliza o conceito de intra ordem(esq,dir,raiz) para printar os valores da arvore
  if(raiz == NULL){
    return 0;
  }else if(*raiz != NULL){
    posOrdem_ArvBin(&((*raiz)->esq));
    posOrdem_ArvBin(&((*raiz)->dir));
    printf("->(");
    printf("%d",(*raiz)->info);
    printf(")");
    printf("------nome do produto: %s",(*raiz)->nome);
    printf("------preco do produto: %f.2\n",(*raiz)->preco);
  }
}
//----------------------------------------------------------------------------------------------------------------------

int insere_ArvBin(ArvBin* raiz, int valor, char nome[30] , float preco){
  int i;
    if(raiz == NULL)
        return 0;
    struct NO* novo;
    novo = (struct NO*) malloc(sizeof(struct NO));
    if(novo == NULL)
        return 0;
    novo->info = valor;
    strcpy(novo->nome, nome);
    novo->preco = preco;
    novo->dir = NULL;
    novo->esq = NULL;

    if(*raiz == NULL)
        *raiz = novo;
    else{
        struct NO* atual = *raiz;
        struct NO* ant = NULL;
        while(atual != NULL){
            ant = atual;
            if(valor == atual->info){
                free(novo);
                return 0;//elemento já existe
            }

            if(valor > atual->info)
                atual = atual->dir;
            else
                atual = atual->esq;
        }
        if(valor > ant->info)
            ant->dir = novo;
        else
            ant->esq = novo;
    }
    return 1;
}
//----------------------------------------------------------------------------------------------------------------------
int remove_ArvBin(ArvBin *raiz, int valor){
//	struct NO* ant,atual;
  if(raiz == NULL)
  return 0;
  struct NO* ant = NULL;
  struct NO* atual = *raiz;
  while(atual != NULL){
    if(valor == atual->info){
      if(atual == *raiz)
        *raiz == remove_atual(atual);
        else{
          if(ant->dir == atual)
            ant->dir = remove_atual(atual);
            else
              ant->esq = remove_atual(atual);
        }
        return 1;
    }
    ant = atual;
    if(valor > atual->info)
      atual = atual->dir;
      else
        atual = atual->esq;
  }
}

//----------------------------------------------------------------------------------------------------------------------
struct NO* remove_atual(struct NO* atual){// faz a remoção e a reestruturação dos nós
  struct NO *no1, *no2;
  if(atual->esq == NULL){
    no2 = atual->dir;
    free(atual);
    return no2;
  }
  no1 = atual;
  no2 = atual->esq;
  while(no2->dir != NULL){
    no1 = no2;
    no2 = no2->dir;
  }

  if(no1 != atual){
    no1->dir = no2->esq;
    no2->esq = atual->esq;
  }
  no2->dir = atual->dir;
  free(atual);
  return no2;
}

//----------------------------------------------------------------------------------------------------------------------
int consulta_ArvBin(ArvBin *raiz, int valor){// rprocura o valor na árvore retorna 0 quando não achou o valor e 1 quando achar
  if(raiz == NULL)
  return 0;
  struct NO* atual = *raiz;
  while(atual != NULL){
    if(valor == atual->info){
      return 1;
    }
    if(valor > atual->info){
    return 1;
    }
    if(valor > atual->info)
      atual = atual->dir;
      else
      atual = atual->esq;
  }
  return 0;
}
//----------------------------------------------------------------------------------------------------------------------
int main(){
  int valor,resultado,op;
  float preco;
  char nome[30];
  ArvBin* raiz = cria_ArvBin();
  printf("Esse e um programa que utiliza uma arvore de busca:\n\n");
  printf("Insira o primeiro valor identificador do produto na arvore\n");
  scanf("%d",&valor);
  printf("\n" );
  printf("Informe o nome do produto\n");
  scanf("%s", &nome);
  printf("informe o preco do produto\n");
  scanf("%f", &preco);
   insere_ArvBin(raiz,valor,nome,preco);
//  printf("resultado é : %d", resultado);
printf("informe a operacao que deseja fazer\n");
printf("1-Caso queira inserir um elemento\n" );
printf("2-Caso queira remover um elemento\n" );
printf("3-Caso queira vizualizar em pre ordem\n" );
printf("4-Caso queira vizualizar em pos ordem\n" );
printf("5-Caso queira vizualizar em intra ordem\n" );
printf("6-Caso queira consultar se um elemento existe na árvore\n" );
printf("7-Caso queria deletar a arvore\n" );
printf("Informe a opcao por favor\n");
scanf("%d", &op);

while(op != 7){
switch (op) {

  case 1:
  printf("//----------------------------------------//");
  printf("\n\n");
  printf("Insira o primeiro valor identificador do produto na arvore\n");
  scanf("%d", &valor);
  printf("\n" );
  printf("Informe o nome do produto\n");
  scanf("%s", &nome);
  printf("informe o preco do produto:\n");
  scanf("%f", &preco);
  insere_ArvBin(raiz,valor,nome,preco);
  printf("\n\n");
  printf("//----------------------------------------//\n");
  break;

  case 2:
  printf("//----------------------------------------//");
  printf("\n\n");
  printf("Informe o valor que deseja remover\n");
  scanf("%d", &valor);
  remove_ArvBin(raiz,valor);
  printf("\n\n");
  printf("//----------------------------------------//\n");
  break;

  case 3:
  printf("//----------------------------------------//");
  printf("\n\n");
  preOrdem_Arvbin(raiz);
  printf("\n\n");
  printf("//----------------------------------------//\n");
  break;

  case 4:
  printf("//----------------------------------------//");
  printf("\n\n");
  posOrdem_ArvBin(raiz);
  printf("\n\n");
  printf("//----------------------------------------//\n");
  break;

  case 5:
  printf("//----------------------------------------//");
  printf("\n\n");
  emOrdem_ArvBin(raiz);
  printf("\n\n");
  printf("//----------------------------------------//\n");
  break;

  case 6:
  printf("//----------------------------------------//");
  printf("\n\n");
  printf("Informe o valor que deseja procurar\n");
  scanf("%d", &valor);
  resultado = consulta_ArvBin(raiz,valor);
  /*printf("%d",resultado);
  Se retornar 1 quer dizer que achou o valor, caso retorne 0 não foi encontrado*/
  if(resultado == 1){
    printf("O valor foi encontrado na arvore\n");
  }else{
    printf("O valor nao foi encontrado na arvore\n");
  }
  printf("\n\n");
  printf("//----------------------------------------//");
  break;

  case 7:
  libera_ArvBin(raiz);
  printf("Arvore deletada com sucesso\n", );
  system("pause");
  return 0;
  break;



  default:
  break;
  }
  printf("informe a operacao que deseja fazer\n");
  printf("1-Caso queira inserir um elemento\n" );
  printf("2-Caso queira remover um elemento\n" );
  printf("3-Caso queira vizualizar em pre ordem\n" );
  printf("4-Caso queira vizualizar em pos ordem\n" );
  printf("5-Caso queira vizualizar em intra ordem\n" );
  printf("6-Caso queira consultar se um elemento existe na árvore\n" );
  printf("7-Caso queria deletar a arvore\n" );
  printf("Informe a opcao por favor\n");
  scanf("%d", &op);
}
return 0;
  system("pause");
  return 0;
}
