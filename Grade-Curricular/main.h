/*******************************************************************************
Autor: anderson da luz correia
funções utilizadas no projeto "grade-curricular"
******************************************************************************************/
#include <iostream> // Biblioteca padrão para objetos da linquagem c++
#include <locale.h> // funções de linguagem,para o uso do português
#include <fstream>  // para manipulação de arquivos como Objetos
#include <stdio.h>  // funções de entrada e saida
#include <stdlib.h> // biblioteca para gerenciamento de memoria
#include <string.h> // biblioteca de funções de string
#include <conio.c>  // utilizada para alterar cores do texto e do fundo

using namespace std;

const char tipo[9][40]={"módulos intregadores obrigatórios","Módulos Obrigatórios","Disciplinas Obrigatórias","TCC","Estágio",
                "Projeto Empreendedor","Optativa Profissionalizante","Optativa de Formação Humanística","Optativa de Formação Complementar"};
typedef struct d{
        char Cod[10],Name[60];
        int Qt_Horas;
        int natureza;//se refere ao tipo acima
        struct d *pre[6];
        struct d *pos[30];
        struct d *co[4];
        struct d *proximo;
}disciplina;

typedef struct s{
        char procura[10];
        int retorno;
        disciplina *dis_return;
}Beta;

disciplina *aumentar_lista(disciplina *);
/** Recebe como parametro o ponteiro de uma lista do tipo disciplina
  * insere um novo elemento no começo da lista
  * Retorna um ponteiro para o novo elemento
  */
disciplina *inserir_fim(disciplina *);
/** Recebe como parametro o ponteiro de uma lista do tipo disciplina
  * insere um novo elemento no fim da lista
  * Retorna um ponteiro para o novo elemento
  */
void busca_lista(disciplina *, Beta *);
/** Recebe como parametro 2 ponteiros de listas, uma do tipo disciplina e outra do tipo Beta
  * Busca um elemento na lista de disciplina, e prenche a beta com o ponteiro do elementro encontrado e o int retorno iqual a 0
  * ou apenas com retorno iqual a 1 caso o elemento não seja encontrado
  */

disciplina *ler_dados(disciplina *, int , Beta *, FILE * , disciplina *);
void pre_req_dados(disciplina *, int , FILE * , disciplina *);
void co_req_dados(disciplina *, int , FILE * , disciplina *);
/** As funções acima servem para ler todas as informações sobre as disciplinas de um arquivo previamente preenchido,
  * Atraveis de outro executavel do projeto
  */

void apagar_QuebraDeLinha(char *);//apagar o '\n' de uma string

disciplina *aumentar_lista(disciplina *lista){

    disciplina *nova=(disciplina*)malloc(sizeof(disciplina));//criando novo elemento da lista
	if(nova==NULL){//verificando se tinha memoria suficiente no sistema
        cout <<"\n erro falta de memoria" << endl;
        return nova;
	}
    nova->proximo=lista;
	int a;
	for(a=0;a<20;a++){
        if(a<4)
            nova->co[a]=NULL;
        if(a<6)
            nova->pre[a]=NULL;
        nova->pos[a]=NULL;
	}
    return nova;//retornando o ponteiro do novo inicio da lista
}

disciplina *inserir_fim(disciplina *lista){

    disciplina *nova=(disciplina*)malloc(sizeof(disciplina));//criando novo elemento da lista
    disciplina *aux;
	if(nova==NULL){//verificando se tinha memoria suficiente no sistema
        cout <<"\n erro falta de memoria ";
        return nova;
	}
    for(aux=lista;aux->proximo!=NULL;aux=aux->proximo);
    aux->proximo=nova;
    nova->proximo=NULL;
	int a;
	for(a=0;a<20;a++){
        if(a<4)
            nova->co[a]=NULL;
        if(a<6)
            nova->pre[a]=NULL;
        nova->pos[a]=NULL;
	}
	nova->pos[0]=lista;
    return nova;
}

disciplina *ler_dados(disciplina *lista, int modo, Beta *cod, FILE *dados, disciplina *inicio){

    int Qtr;
    Beta busca;

    if(modo==1){
        fgets(busca.procura,10,dados);
        apagar_QuebraDeLinha(busca.procura);
        busca_lista(inicio,&busca);
        if(busca.retorno==0){
            return lista;
        }
        lista=aumentar_lista(lista);
        strcpy(lista->Cod,busca.procura);
    }
    else{
        strcpy(lista->Cod,cod->procura);
    }
    fgets(lista->Name,60,dados);
    apagar_QuebraDeLinha(lista->Name);
    fscanf(dados,"%d\n",&lista->Qt_Horas);
    fscanf(dados,"%d\n",&lista->natureza);
    fscanf(dados,"%d\n",&Qtr);
    if(Qtr>0 && Qtr<7)
        pre_req_dados(lista,Qtr,dados,inicio);

    fscanf(dados,"%d\n",&Qtr);
    if(Qtr>0 && Qtr<5)
        co_req_dados(lista,Qtr,dados,inicio);

    return lista;
}

void pre_req_dados(disciplina *lista, int Qtr,FILE *dados, disciplina *inicio){

    disciplina *aux;
    Beta busca;

    int a,b;
    for(a=0;a<Qtr;a++){
        fgets(busca.procura,10,dados);
        apagar_QuebraDeLinha(busca.procura);
        busca_lista(inicio,&busca);
        if(busca.retorno==1){
            aux=inserir_fim(lista);
            lista->pre[a]=aux;
            aux=ler_dados(aux,0,&busca,dados,inicio);
        }
        else{
            aux=busca.dis_return;
            lista->pre[a]=aux;
            for(b=0;b<30;b++){
                if(aux->pos[b]==NULL){
                    aux->pos[b]=lista;
                    break;
                }
            }
        }
    }
}

void co_req_dados(disciplina *lista, int Qtr,FILE *dados, disciplina *inicio){

    disciplina *aux;
    Beta busca;

    int a,b;
    for(a=0;a<Qtr;a++){
        fgets(busca.procura,10,dados);
        apagar_QuebraDeLinha(busca.procura);
        busca_lista(inicio,&busca);
        if(busca.retorno==1){
            aux=inserir_fim(lista);
            aux->pos[0]=NULL;
            lista->co[a]=aux;
            aux=ler_dados(aux,0,&busca,dados,inicio);
        }
        else{
            aux=busca.dis_return;
            lista->co[a]=aux;
        }
        for(b=0;b<4;b++){
            if(aux->co[b]==NULL){
                aux->co[b]=lista;
                break;
            }
        }
    }
}

void busca_lista(disciplina *lista, Beta *busca){

    if(lista==NULL){
        busca->retorno=1;
        return;
    }
    //cout << lista->Cod << "|" << busca->procura << "|\n";
    if(strcasecmp(lista->Cod,busca->procura)==0){
        busca->dis_return=lista;
        busca->retorno=0;
        return ;
    }
    busca_lista(lista->proximo,busca);
    return ;
}

void apagar_QuebraDeLinha(char *palavra){

    int tam_pal;//para guadar o tamanho de uma palavra/frase qualquer

    tam_pal=strlen(palavra);//descobrindo o tamanho da string,para saber o final dela
    if(palavra[tam_pal-1]=='\n'){//verificando o caso de existir um \n no fim da string,se sim substituindo logo depois
        palavra[tam_pal-1]='\0';//evitando de inserir quebra de linha automaticamente no arquivo de saida ao gravar a palavra
    }
}
