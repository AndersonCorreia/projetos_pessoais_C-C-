/*******************************************************************************
Autor: anderson da luz correia
inicio do desnvolvimento: 15/08/2018
******************************************************************************************/
#include "main.h"

//fun��es das op��es do usuario
void exibir_co_req(disciplina *);
void exibir_pre_req(disciplina *, int , int *);
void exibir_pos_req(disciplina *, int , int *);

int main(){

    setlocale(LC_ALL,"Portuguese"); // para permite uso de acentua��o
    disciplina *lista=NULL,*aux;
    Beta busca;
    FILE *dados=fopen("dados.ecomp","r");
    int opcao=1,direto=0;

    if(dados==NULL){
    	printf("erro ao abrir o arquivo com as informa��es do curso");
    	return 0;
    }
    while(opcao==1){
        lista=ler_dados(lista,1,NULL,dados,lista);
        fscanf(dados,"%d\n",&opcao);
    }
    opcao=0;
    fclose(dados);

    while(opcao!=9){
        system("cls");
        opcao=0; direto=0; //restaurando valor padr�o das variaveis
        cout << " Grade curricular do curso de Engenharia de computa��o da UEFS\n\nEscolha uma das op��es abaixo,";
        cout << " para informa��es sobre alguma disciplina do curso." << endl;
        cout << " [1]: Ver pr�-requisitos\n [2]: Ver p�s-requisitos\n [3]: Ver co-requisitos\n [9]: encerrar o programa\nop��o: ";
        scanf("%d",&opcao);
        setbuf(stdin,NULL);

        if(opcao==1){

            cout << "informe o codigo de uma disciplina para ver os pr�-requisitos:\n por ex: exa 704 (para calculo 1)." << endl;
            fgets(busca.procura,10,stdin);
            setbuf(stdin,NULL);
            apagar_QuebraDeLinha(busca.procura);
            busca_lista(lista,&busca);
            if(busca.retorno==0 && busca.dis_return->pre[0]==NULL)
                cout << "\n A disciplina " << busca.dis_return->Name << " n�o tem pr�-requisitos." << endl;
            else if(busca.retorno==0){
                cout << "\nos pr�-requisitos de " << busca.dis_return->Name << " s�o:" << endl << endl;
                exibir_pre_req(busca.dis_return,0,&direto);
                printf("\n %s tem %d pr�-requisitos diretos.\n",busca.dis_return->Name,direto);
            }
            else
                cout << "\n Disiciplina n�o encontrada ";
        }
        else if(opcao==2){

            cout << "informe o codigo de uma disciplina para ver os pos-requisitos:\n por ex: tec 497 (para introdu��o a eletronica)." << endl;
            fgets(busca.procura,10,stdin);
            setbuf(stdin,NULL);
            apagar_QuebraDeLinha(busca.procura);
            busca_lista(lista,&busca);
            if(busca.retorno==0 && busca.dis_return->pos[0]==NULL)
                cout << "\n A disciplina " << busca.dis_return->Name << " n�o tem pos-requisitos." << endl;
            else if(busca.retorno==0){
                cout << "\nos pos-requisitos de " << busca.dis_return->Name << " s�o:" << endl << endl;
                exibir_pos_req(busca.dis_return,0,&direto);
                printf("\n %s � pr�-requisito direto de %d disciplinas.\n",busca.dis_return->Name,direto);
            }
            else
                cout << "\n Disiciplina n�o encontrada ";
        }
        else if(opcao==3){

            cout << "informe o codigo de uma disciplina para ver os co-requisitos:\n por ex: exa 801 (para algoritimos e programa��o 1)." << endl;
            fgets(busca.procura,10,stdin);
            setbuf(stdin,NULL);
            apagar_QuebraDeLinha(busca.procura);
            busca_lista(lista,&busca);
            if(busca.retorno==0 && busca.dis_return->co[0]==NULL){
                cout << " A disciplina " << busca.dis_return->Name << " n�o tem co-requisitos." << endl;
            }
            else if(busca.retorno==0){
                cout << "\nos co-requisitos de " << busca.dis_return->Name << " s�o:" << endl;
                exibir_co_req(busca.dis_return);
            }
            else
                cout << "\n Disiciplina n�o encontrada ";
        }
        else if(opcao!=9)
            cout << "\nOp��o invalida";

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

void exibir_co_req(disciplina *lista){

    int a;
    textcolor(9);
    for(a=0;lista->co[a]!=NULL;a++){
        printf(" %s: %s   Ch:%d   Tipo:%s \n",lista->co[a]->Cod,lista->co[a]->Name,lista->co[a]->Qt_Horas,tipo[lista->co[a]->natureza-1]);
    }
    textcolor(7);
}

void exibir_pre_req(disciplina *lista,int tab, int *dir){

    if(lista->pre[0]==NULL){
        return ;
    }
    int cor_texto[7]={0,15,0,15,0,15,15}, cor_fundo[7]={15,1,9,3,5,4,8};

    int a,b;
    for(a=0;lista->pre[a]!=NULL;a++){
        textcolor(cor_texto[tab%7]);
        textbackground(cor_fundo[tab%7]);
        for(b=0;b<tab && lista->pre[a]!=NULL ;b++)
            cout << "\t";
        (*dir)++;
        printf(" %s: %s  Tipo:%s \n",lista->pre[a]->Cod,lista->pre[a]->Name,tipo[lista->pre[a]->natureza-1]);
        exibir_pre_req(lista->pre[a],tab+1,&b);
    }
    textcolor(7);
    textbackground(0);
}

void exibir_pos_req(disciplina *lista,int tab,int *dir){

    if(lista->pos[0]==NULL){
        return ;
    }
    int cor_texto[7]={0,15,0,15,0,15,15}, cor_fundo[7]={15,1,9,3,5,4,8};

    int a,b;
    for(a=0;lista->pos[a]!=NULL;a++){
        textcolor(cor_texto[tab%7]);
        textbackground(cor_fundo[tab%7]);
        for(b=0;b<tab;b++)
            cout << "\t";
        (*dir)++;
        printf(" %s: %s  Tipo:%s \n",lista->pos[a]->Cod,lista->pos[a]->Name,tipo[lista->pos[a]->natureza-1]);
        exibir_pos_req(lista->pos[a],tab+1,&b);
    }
    textcolor(7);
    textbackground(0);
}
