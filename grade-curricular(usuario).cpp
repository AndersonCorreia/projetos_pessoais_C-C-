/*******************************************************************************
Autor: anderson da luz correia
inicio do desnvolvimento: 15/08/2018
******************************************************************************************/
#include "main.h"

//funções das opções do usuario
void exibir_co_req(disciplina *);
void exibir_pre_req(disciplina *, int , int *);
void exibir_pos_req(disciplina *, int , int *);

int main(){

    setlocale(LC_ALL,"Portuguese"); // para permite uso de acentuação
    disciplina *lista=NULL,*aux;
    Beta busca;
    FILE *dados=fopen("dados.ecomp","r");
    int opcao=1,direto=0;

    if(dados==NULL){
    	printf("erro ao abrir o arquivo com as informações do curso");
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
        opcao=0;
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
            if(busca.retorno==0 && busca.dis_return->pre[0]==NULL)
                cout << "\n A disciplina " << busca.dis_return->Name << " não tem pré-requisitos." << endl;
            else if(busca.retorno==0){
                cout << "\nos pré-requisitos de " << busca.dis_return->Name << " são:" << endl << endl;
                exibir_pre_req(busca.dis_return,0,&direto);
                printf("\n %s tem %d pré-requisitos diretos.\n",busca.dis_return->Name,direto);
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
            if(busca.retorno==0 && busca.dis_return->pos[0]==NULL)
                cout << "\n A disciplina " << busca.dis_return->Name << " não tem pos-requisitos." << endl;
            else if(busca.retorno==0){
                cout << "\nos pos-requisitos de " << busca.dis_return->Name << " são:" << endl << endl;
                exibir_pos_req(busca.dis_return,0,&direto);
                printf("\n %s é pré-requisito direto de %d disciplinas.\n",busca.dis_return->Name,direto);
                direto=0;
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
            if(busca.retorno==0 && busca.dis_return->co[0]==NULL){
                cout << " A disciplina " << busca.dis_return->Name << " não tem co-requisitos." << endl;
            }
            else if(busca.retorno==0){
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

void exibir_co_req(disciplina *lista){

    int a;
    textcolor(9);
    for(a=0;a<4;a++){
        if(lista->co[a]!=NULL){
            printf(" %s: %s   Ch:%d   Tipo:%s \n",lista->co[a]->Cod,lista->co[a]->Name,lista->co[a]->Qt_Horas,tipo[lista->co[a]->natureza-1]);
        }
    }
    textcolor(7);
}

void exibir_pre_req(disciplina *lista,int tab, int *dir){

    if(lista->pre[0]==NULL){
        //cout << "\n";
        return ;
    }
    int a,b;
    for(a=0;a<6;a++){
        textcolor((tab*3)+tab*12);
        textbackground(tab*tab+tab+15);
        for(b=0;b<tab && lista->pre[a]!=NULL ;b++)
            cout << "\t";
        if(lista->pre[a]!=NULL){
            (*dir)++;
            printf(" %s: %s  Tipo:%s \n",lista->pre[a]->Cod,lista->pre[a]->Name,tipo[lista->pre[a]->natureza-1]);
            exibir_pre_req(lista->pre[a],tab+1,&b);
        }
        else
            a=7;
    }
    textcolor(7);
    textbackground(0);
}

void exibir_pos_req(disciplina *lista,int tab,int *dir){

    if(lista->pos[0]==NULL){
        //cout << "\n";
        return ;
    }
    int a,b;

    for(a=0;a<30;a++){
        textcolor((tab*3)+tab*12);
        textbackground(tab*tab+tab+15);
        for(b=0;b<tab && lista->pos[a]!=NULL ;b++)
            cout << "\t";
        if(lista->pos[a]!=NULL){
            (*dir)++;
            printf(" %s: %s  Tipo:%s \n",lista->pos[a]->Cod,lista->pos[a]->Name,tipo[lista->pos[a]->natureza-1]);
            exibir_pos_req(lista->pos[a],tab+1,&b);
        }
        else
            a=30;
    }
    textcolor(7);
    textbackground(0);
}
