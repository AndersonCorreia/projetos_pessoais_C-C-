/*******************************************************************************
Autor: anderson da luz correia
inicio do desnvolvimento: 15/08/2018
******************************************************************************************/
#include <locale.h>  // funções de linguagem,para o uso do português
#include <iostream>
#include <fstream>
#include <stdio.h>   // funções de entrada e saida
#include <stdlib.h>  // biblioteca para gerenciamento de memoria
#include <string.h> // biblioteca de funções de string

using namespace std;

const char tipo[9][40]={"módulos intregadores obrigatórios","Módulos Obrigatórios","Disciplinas Obrigatórias","TCC","Estágio",
                "Projeto Empreendedor","Optativa Profissionalizante","Optativa de Formação Humanística","Optativa de Formação Complementar"};
typedef struct d{
        char Cod[10],Name[50];
        int Qt_Horas;
        int natureza;//se refere ao tipo acima
        struct d *pre[6];
        struct d *pos[6];
        struct d *co[4];
        struct d *proximo;
}disciplina;

typedef struct s{
        char procura[10];
        int returno;
        disciplina *dis_return;
}Beta;

disciplina *aumentar_lista(disciplina *);
disciplina *inserir_fim(disciplina *);
void busca_lista(disciplina *, Beta *);
//funçoes para cadastrar as disciplinas
disciplina *inserir_dados(disciplina *, int , Beta *);
void pre_requisitos(disciplina *, int);
void co_requisitos(disciplina *, int);
//função para carregar as informações que ja foram cadastradas
disciplina *ler_dados(disciplina *, int , Beta *, FILE *);
void pre_req_dados(disciplina *, int, FILE *);
void co_req_dados(disciplina *, int, FILE *);
//funções das opções do usuario
void exibir_co_req(disciplina *);
void exibir_pre_req(disciplina *, int );
void exibir_pos_req(disciplina *, int );

void apagar_QuebraDeLinha(char *);//apagar o '\n' de um string

int main(){

    setlocale(LC_ALL,"Portuguese"); // para permite uso de acentuação
    disciplina *lista=NULL,*aux;
    Beta busca;
    FILE *dados=fopen("dados.ecomp","r");
    int opcao=1;

    if(dados==NULL){
    	printf("erro ao abrir o arquivo");
    	return 0;
    }

    while(opcao==1){
        lista=ler_dados(lista,1,NULL,dados);
        fscanf(dados,"%d\n",&opcao);
    }
    opcao=0;
    printf("\tIniciar no modo desenvolvedor, para cadastrar as disciplinas?  sim(1)\n\topção: ");
    scanf("%d",&opcao);
    setbuf(stdin,NULL);

    while(opcao==1){
        lista=inserir_dados(lista,1,NULL);
        printf("\n\ndeseja continuar ? sim(1)\n\topção: ");
        scanf("%d",&opcao);
        setbuf(stdin,NULL);
        fscanf(dados,"%d",&opcao);
        system("cls");
    }
    opcao=0;

    while(opcao!=9){
        system("cls");
        cout << " Grade curricular do curso de Engenharia de computação da UEFS\n\nEscolha uma das opções abaixo,";
        cout << " para informações sobre alguma disciplina do curso." << endl;
        cout << " [1]: Ver pré-requisitos\n [2]: Ver pós-requisitos\n [3]: Ver co-requisitos\n [9]: encerrar o programa\nopção: ";
        scanf("%d",&opcao);
        setbuf(stdin,NULL);

        if(opcao==1){

            cout << "informe uma disciplina para ver os pré-requisitos:" << endl;
            fgets(busca.procura,10,stdin);
            setbuf(stdin,NULL);
            apagar_QuebraDeLinha(busca.procura);
            busca_lista(lista,&busca);
            if(busca.returno==0 && busca.dis_return->pre[0]==NULL)
                cout << "\n A disciplina " << busca.dis_return->Name << " não tem pré-requisitos." << endl;
            else if(busca.returno==0){
                cout << "\nos pré-requisitos de " << busca.dis_return->Name << " são:" << endl << endl;
                exibir_pre_req(busca.dis_return,1);
            }
            else
                cout << "\n Disiciplina não encontrada ";
        }
        else if(opcao==2){

            cout << "informe uma disciplina para ver os pos-requisitos:" << endl;
            fgets(busca.procura,10,stdin);
            setbuf(stdin,NULL);
            apagar_QuebraDeLinha(busca.procura);
            busca_lista(lista,&busca);
            if(busca.returno==0 && busca.dis_return->pos[0]==NULL)
                cout << "\n A disciplina " << busca.dis_return->Name << " não tem pos-requisitos." << endl;
            else if(busca.returno==0){
                cout << "\nos pos-requisitos de " << busca.dis_return->Name << " são:" << endl << endl;
                exibir_pos_req(busca.dis_return,1);
            }
            else
                cout << "\n Disiciplina não encontrada ";
        }
        else if(opcao==3){

            cout << "informe uma disciplina para ver os co-requisitos:" << endl << endl;
            fgets(busca.procura,10,stdin);
            setbuf(stdin,NULL);
            apagar_QuebraDeLinha(busca.procura);
            busca_lista(lista,&busca);
            if(busca.returno==0){
                cout << "\nos co-requisitos de " << busca.dis_return->Name << " são:" << endl;
                exibir_co_req(busca.dis_return);
            }
            else
                cout << "\n Disiciplina não encontrada ";
        }
        else if(opcao!=9)
            cout << "\nOpção invalida";

        cout << endl << endl;
        system("pause");
    }
    while(lista!=NULL){
        aux=lista;
        lista=lista->proximo;
        free(aux);
    }

    return 0;
}

disciplina *aumentar_lista(disciplina *lista){

    disciplina *nova=(disciplina*)malloc(sizeof(disciplina));//criando novo elemento da lista
	if(nova==NULL){//verificando se tinha memoria suficiente no sistema
        cout <<"\n erro falta de memoria" << endl;
        return nova;
	}
    nova->proximo=lista;
	int a;
	for(a=0;a<6;a++){
        if(a<4)
            nova->co[a]=NULL;
        nova->pos[a]=NULL;
        nova->pre[a]=NULL;
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
	for(a=0;a<6;a++){
        if(a<4)
            nova->co[a]=NULL;
        nova->pos[a]=NULL;
        nova->pre[a]=NULL;
	}
	nova->pos[0]=lista;
    return nova;
}

disciplina *inserir_dados(disciplina *lista,int modo,Beta *cod){

    int a,Qtr;
    Beta busca;
    ofstream dados;
    dados.open("dados.ecomp",ios::app);
    if(dados==NULL){
    	printf("erro ao abrir o arquivo");
    	return NULL;
    }

    if(modo==1){
        cout <<"\n Informe o código da disciplina:" << endl << " ";
        fgets(busca.procura,10,stdin);
        setbuf(stdin,NULL);
        apagar_QuebraDeLinha(busca.procura);
        dados << busca.procura << endl;
        busca_lista(lista,&busca);
        if(busca.returno==0){
            cout << "disciplina " << busca.dis_return->Name << " já está cadastrada";
            return lista;
        }
        lista=aumentar_lista(lista);
        strcpy(lista->Cod,busca.procura);
    }
    else{
        strcpy(lista->Cod,cod->procura);
    }
    cout <<"\n Informe o nome da disciplina:" << endl << " ";
    fgets(lista->Name,50,stdin);
    setbuf(stdin,NULL);
    apagar_QuebraDeLinha(lista->Name);
    dados << lista->Name << endl;

    cout <<"\n Informe a carga horaria de " << lista->Name << endl << " ";
    scanf("%d",&lista->Qt_Horas);
    setbuf(stdin,NULL);
    dados << lista->Qt_Horas << endl;

    cout <<"\n Informe a natureza de " << lista->Name << endl << endl;
    for(a=0;a<9;a++){
        printf("[%d]: %s\n",a+1,tipo[a]);
    }
    cout << "\nopção: ";
    scanf("%d",&lista->natureza);
    setbuf(stdin,NULL);
    dados << lista->natureza<< endl;

    cout << "\ninforme quantos pré-requistos " << lista->Name << " tem:" << endl;
    scanf("%d",&Qtr);
    setbuf(stdin,NULL);
    dados << Qtr << endl;
    if(Qtr>0 && Qtr<7)
        pre_requisitos(lista,Qtr);

    if(modo==1){
        cout << "\ninforme quantos co-requistos " << lista->Name << " tem:" << endl << " ";
        scanf("%d",&Qtr);
        setbuf(stdin,NULL);
        dados << Qtr << endl;
        if(Qtr>0 && Qtr<5)
            co_requisitos(lista,Qtr);
    }
return lista;
}

void pre_requisitos(disciplina *lista, int Qtr){

    disciplina *aux;
    Beta busca;
    ofstream dados;
    dados.open("dados.ecomp",ios::app);

    cout <<"\n\tInforme os pré-requisitos de " << lista->Name << endl;
    int a,b;
    for(a=0;a<Qtr;a++){
        cout <<"\npré-requisito " << a+1 << endl;
        fgets(busca.procura,10,stdin);
        setbuf(stdin,NULL);
        apagar_QuebraDeLinha(busca.procura);
        dados << busca.procura << endl;
        busca_lista(lista,&busca);
        if(busca.returno==1){
            cout << "\n\tdisciplina não está cadastrada,\n\ta sequir insira as informações dela:";
            aux=inserir_fim(lista);
            lista->pre[a]=aux;
            aux=inserir_dados(aux,0,&busca);
        }
        else{
            cout << "\n\ndisciplina encontrada" << endl;
            aux=busca.dis_return;
            lista->pre[a]=aux;
            for(b=0;b<6;b++){
                if(aux->pos[b]==NULL){
                    aux->pos[b]=lista;
                    break;
                }
            }
        }
    }
}

void co_requisitos(disciplina *lista, int Qtr){

    disciplina *aux;
    Beta busca;
    ofstream dados;
    dados.open("dados.ecomp",ios::app);

    cout <<"\n\tInforme os co-requisitos de " << lista->Name << endl;
    int a,b;
    for(a=0;a<Qtr;a++){
        cout <<"\nco-requisito " << a+1 << endl;
        fgets(busca.procura,10,stdin);
        setbuf(stdin,NULL);
        apagar_QuebraDeLinha(busca.procura);
        dados << busca.procura << endl;
        busca_lista(lista,&busca);
        if(busca.returno==1){
            cout << "\n\tdisciplina não está cadastrada,\n\ta sequir insira as informações dela:";
            aux=inserir_fim(lista);
            aux->pos[0]=NULL;
            lista->co[a]=aux;
            aux=inserir_dados(aux,0,&busca);
        }
        else{
            cout << "\n\ndisciplina encontrada" << endl;
            aux=busca.dis_return;
            lista->co[a]=aux;
            for(b=0;b<4;b++){
                if(aux->co[b]==NULL){
                    aux->co[b]=lista;
                    break;
                }
            }
        }
    }
}

disciplina *ler_dados(disciplina *lista,int modo,Beta *cod,FILE *dados){

    int Qtr;
    Beta busca;

    if(dados==NULL){
    	printf("erro ao abrir o arquivo");
    	return 0;//encerrando a execução pela falta do arquivo de entrada
    }

    if(modo==1){
        fgets(busca.procura,10,dados);
        apagar_QuebraDeLinha(busca.procura);
        busca_lista(lista,&busca);
        if(busca.returno==0){
            return lista;
        }
        lista=aumentar_lista(lista);
        strcpy(lista->Cod,busca.procura);
    }
    else{
        strcpy(lista->Cod,cod->procura);
    }
    fgets(lista->Name,50,dados);
    apagar_QuebraDeLinha(lista->Name);
    fscanf(dados,"%d\n",&lista->Qt_Horas);
    fscanf(dados,"%d\n",&lista->natureza);
    fscanf(dados,"%d\n",&Qtr);
    if(Qtr>0 && Qtr<7)
        pre_req_dados(lista,Qtr,dados);
    if(modo==1){
        fscanf(dados,"%d\n",&Qtr);
        if(Qtr>0 && Qtr<5)
            co_req_dados(lista,Qtr,dados);
    }

    return lista;
}

void pre_req_dados(disciplina *lista, int Qtr,FILE *dados){

    disciplina *aux;
    Beta busca;

    int a,b;
    for(a=0;a<Qtr;a++){
        fgets(busca.procura,10,dados);
        apagar_QuebraDeLinha(busca.procura);
        busca_lista(lista,&busca);
        if(busca.returno==1){
            aux=inserir_fim(lista);
            lista->pre[a]=aux;
            aux=ler_dados(aux,0,&busca,dados);
        }
        else{
            aux=busca.dis_return;
            lista->pre[a]=aux;
            for(b=0;b<6;b++){
                if(aux->pos[b]==NULL){
                    aux->pos[b]=lista;
                    break;
                }
            }
        }
    }
}

void co_req_dados(disciplina *lista, int Qtr,FILE *dados){

    disciplina *aux;
    Beta busca;

    int a,b;
    for(a=0;a<Qtr;a++){
        fgets(busca.procura,10,dados);
        apagar_QuebraDeLinha(busca.procura);
        busca_lista(lista,&busca);
        if(busca.returno==1){
            aux=inserir_fim(lista);
            lista->co[a]=aux;
            aux=ler_dados(aux,0,&busca,dados);
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

void exibir_co_req(disciplina *lista){

    if(lista->co[0]==NULL){
        cout << " A disciplina " << lista->Name << " não tem co-requisitos." << endl;
        return ;
    }
    int a;
    for(a=0;a<4;a++){
        if(lista->co[a]!=NULL){
            printf(" %s: %s\n",lista->co[a]->Cod,lista->co[a]->Name);
        }
    }
}

void exibir_pre_req(disciplina *lista,int tab){

    if(lista->pre[0]==NULL){
        return ;
    }
    int a,b;
    cout << "\n";
    for(a=0;a<6;a++){
        for(b=0;b<tab && lista->pre[a]!=NULL ;b++)
            cout << "\t";
        if(lista->pre[a]!=NULL){
            printf(" %s: %s\n",lista->pre[a]->Cod,lista->pre[a]->Name);
            exibir_pre_req(lista->pre[a],tab+1);
        }
    }
}

void exibir_pos_req(disciplina *lista,int tab){

    if(lista->pos[0]==NULL){
        return ;
    }
    int a,b;

    for(a=0;a<6;a++){
        for(b=0;b<tab && lista->pos[a]!=NULL ;b++)
            cout << "\t";
        if(lista->pos[a]!=NULL){
            printf(" %s: %s\n",lista->pos[a]->Cod,lista->pos[a]->Name);
            exibir_pos_req(lista->pos[a],tab+1);
        }
    }
    cout << "\n";
}

void busca_lista(disciplina *lista, Beta *busca){

    if(lista==NULL){
        busca->returno=1;
        return;
    }
    cout <<lista->Cod << "|" << busca->procura << "|"<< endl;
    if(strcasecmp(lista->Cod,busca->procura)==0){
        busca->dis_return=lista;
        busca->returno=0;
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
