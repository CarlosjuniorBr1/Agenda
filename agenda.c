#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOSTRAR 1 
#define INSERIR 2
#define EXCLUIR 3
#define BUSCAR  4
#define SALVAR  5 
#define LER     6 
#define SAIR    0

typedef struct{

    char nome[128];
    char tel[16];
    int idade;

}Contato;

typedef struct{

    int n; // qtd de elementos
    Contato * dados;
    
}Agenda;



int menu(void){

    int op;
    printf("%d) Mostrar contatos\n",MOSTRAR);
    printf("%d) Inserir Contato\n",INSERIR);
    printf("%d) Excluir contato\n",EXCLUIR);
    printf("%d) Buscar  contato\n",BUSCAR);
    printf("%d) Salvar  contato\\n",SALVAR);
    printf("%d) Ler contato\n",LER);
    printf("%d) Sair\n",SAIR);
    scanf("%d",&op);
    return op;

}

void print_contato(Contato c){
    printf("-------------------------------------------------\n");
    printf("Nome: %s\n",c.nome);
    printf("Telefone: %s\n",c.tel);
    printf("Idade: %d\n",c.idade);
    printf("-------------------------------------------------\n");
    printf("\n");

}

void mostrar(Agenda A){

    int i ;
    if(A.n == 0){
        printf("Agenda vazia\n");
        return;
    }
    for(i=0; i<A.n;i++){
        //; imprimir o contato A.dados[0]
         printf("IDX: %d -----------------------\n",i);
        print_contato(A.dados[i]);
       
    }             
}

void inserir(Agenda * A){


    Contato * ptr = NULL;

    ptr = (Contato *)realloc(A->dados, (A->n+1)*sizeof(Contato));
    if(ptr == NULL){
        printf(" Nao foi posssivel inserir um novo contato, por questoes de memoria!\n");
        return;
    }
    A->dados = ptr;
    (A->n)++;

    printf("Nome do contato: ");
    scanf("%*c%[^\n]%*c",A->dados[A-> n-1].nome);
    printf("\nTelefone do contato: ");
    scanf("%[^\n]",A->dados[A-> n-1].tel);
    printf("\nIdade do contato: ");
    scanf("%d",&(A->dados[A->n-1].idade));

}
void  remove_contato_por_indice(Agenda * A, int idx){
    if (idx < 0 || idx > A->n-1){

        printf("Indice invalido!!!\n");
        return ;
    }
    for( ; idx < A->n-1; idx++){

        A->dados[idx] = A->dados[idx+1];
    }
    A->dados = (Contato*)realloc(A->dados, (A->n-1)*sizeof(Contato));
    (A->n) --;
}
void remove_contato(Agenda * A){
    int idx;
    printf("Digite o indice do contato: ")/
    scanf("%d",&idx);
    remove_contato_por_indice(A, idx);
}
void buscar(Agenda A){

    char str[64];
    char * end = NULL;
    printf("Digite a string de busca: ");
    scanf("%*c%[^\n]",str);
    
    int i;
    for(i = 0; i< A.n;i++){

       

        end = strstr(A.dados[i].nome, str);
        if(end == NULL) end = strstr(A.dados[i].tel,str );
        if(end != NULL){

            printf("------   IDX: %d --------\n",i);
            print_contato(A.dados[i]);
        }
    }
}
void carrega_agenda(Agenda * A){


    FILE * arq = NULL;
    Contato c;
    arq = fopen("contato.txt","r");

    while(1){
        if(fscanf(arq,"%[^\n]%*c",c.nome) == EOF) break;
        fscanf(arq,"%[^\n]%*c",c.nome);
        fscanf(arq,"%[^\n]%*c",c.tel);
        fscanf(arq,"%d%*c",&c.idade);

        A->dados = realloc(A->dados, (A-> n+1)*sizeof(Contato));
        (A->n)++;
        A->dados[A->n-1] = c;


    }
    fclose(arq);


}
void grava_agenda(Agenda A){

    FILE *arq = NULL;
    arq = fopen("contato.txt","w");
    int i;
    for(i=0; i<A.n;i++){
        fprintf(arq, "%s\n",A.dados[i].nome);
        fprintf(arq, "%s\n",A.dados[i].tel);
        fprintf(arq, "%d\n",A.dados[i].idade);
        

    }
    fclose(arq);
}

int main(){

    int op;
    Agenda A = {.n = 0, .dados = NULL};
    //Contato c  = {.nome = "Joao", .tel = "62 98888 8888", .idade = 20};
    carrega_agenda(&A);

   
    

    while (1)
    {
        op = menu();
        if(op == SAIR){

            break;
        }

        switch(op){
            case MOSTRAR :
                printf("APRESENTANDO LISTAS DE CONTATO\n");
                mostrar(A);
                break;
            case INSERIR:
                printf("INSERINDO CONTATO\n");
                inserir(&A);
                break;
            case EXCLUIR:
                printf("EXCLUINDO CONTATO\n");
                remove_contato(&A);
                break;
            case BUSCAR:
                printf("BUSCANDO CONTATO\n");
                buscar(A);
                break;
            case SALVAR:
                printf("SALVANDO CONTATO\n");
                break;
            case LER:
                printf("LENDO CONTATO\n");
                break;

            default:
                printf("Opcao invalida!!\n");
                break;
                
        }
        
    }
    grava_agenda(A);
    
    return 0;
}