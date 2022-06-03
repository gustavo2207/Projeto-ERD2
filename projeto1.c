#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <conio.h>
#define tam_nome 50

typedef struct
{
    int dia;
    int mes;
    int ano;
} Data;

struct no
{
    char nome[tam_nome];
    Data data_compra;
    float divida;
    int num_prestacao, num_prest_pagas;
    struct no *prox;
};

typedef struct no Lista;

Lista *inicializa()
{
    return NULL;
}

int vazia(Lista *recebida)
{
    if (recebida == NULL)
    {
        return 1;
    }
    return 0;
}

Lista *inserir(Lista *recebida)
{
    system("cls");

    Lista *novo;
    Data data_inserida;

    novo = (Lista *)malloc(sizeof(Lista));
    fflush(stdin);
    printf("Digite seu nome: ");
    fgets(novo->nome, tam_nome, stdin);

    fflush(stdout);
    printf("\nDigite a Data da compra: ");

    printf("\n\tInsira o Dia da compra (dd): ");
    scanf("%d", &data_inserida.dia);
    printf("\n\tInsira o M�s da compra (mm): ");
    scanf("%d", &data_inserida.mes);
    printf("\n\tInsira o Ano da compra (aaaa): ");
    scanf("%d", &data_inserida.ano);

    novo->data_compra = data_inserida;

    printf("\nDigite o valor da compra: ");
    scanf("%f", &novo->divida);
    printf("\nDigite a quantidade de presta��es:");
    scanf("%d", &novo->num_prestacao);
    novo->num_prest_pagas = 0;
    novo->prox = recebida;

    return novo;
}

float calcula_divida(float divida_total, int num_parc, int num_parc_pagas)
{
    float divida_restante;

    divida_restante = divida_total - ((divida_total / num_parc) * num_parc_pagas);

    return divida_restante;
}

int update_verificacao_parcelas(Lista *recebida, char nome[])
{
    Lista *p;
    for (p = recebida; p->nome == nome; p = p->prox)
        ;

    if (strcmp(nome, p->nome) != 0)
    {
        return -1;
    }

    if (p->num_prestacao == p->num_prest_pagas)
    {
        return 0;
    }

    p->num_prest_pagas = p->num_prest_pagas + 1;

    printf("\n\t\tNovos Valores\n\n");
    printf("nome = ");
    puts(p->nome);
    printf("\nvalor da divida = %.2f\n", calcula_divida(p->divida, p->num_prestacao, p->num_prest_pagas));
    printf("quantidade de presta��es pagas = %d\n\n", p->num_prest_pagas);
}

void imprime(Lista *recebida)
{
    system("cls");

    if (vazia(recebida))
    {
        printf("\n\n\t\tLista Vazia!!\n\n");
    }
    else
    {
        Lista *p;
        for (p = recebida; p != NULL; p = p->prox)
        {
            printf("\nNome = ");
            puts(p->nome);
            printf("Data da compra = %d/%d/%d\n", p->data_compra.dia, p->data_compra.mes, p->data_compra.ano);
            printf("Valor da compra = %.2f\n", p->divida);
            printf("Quantidade de presta��es = %d\n\n", p->num_prestacao);
        }
    }
}

void update_parcelas(Lista *recebida)
{
    system("cls");

    int verificacao;
    char nome[tam_nome];

    if (vazia(recebida))
    {
        printf("\n\n\t\tLista Vazia!!\n\n");
    }
    else
    {
        fflush(stdin);
        printf("\n\nInsira o nome para atualiza��o de parcelas pagas: ");
        fgets(nome, tam_nome, stdin);
        fflush(stdout);

        verificacao = update_verificacao_parcelas(recebida, nome);
        if (verificacao == 0)
        {
            printf("Sem valores a pagar");
        }
        else if (verificacao == -1)
        {
            printf("Nome n�o encontrado");
        }
    }
}

void busca_cliente(Lista *recebida)
{
    system("cls");

    char nome[tam_nome];
    Lista *p;

    if (vazia(recebida))
    {
        printf("\n\n\t\tLista Vazia!!\n\n");
    }
    else
    {
        fflush(stdin);
        printf("\n\nInsira o nome para efetuar a busca: ");
        fgets(nome, tam_nome, stdin);
        fflush(stdout);

        for (p = recebida; p->nome == nome; p = p->prox)
            ;

        if (strcmp(nome, p->nome) != 0)
        {
            printf("\t\tNome n�o encontrado");
        }
        else
        {
            printf("\n\t\tInforma��es\n\n");
            printf("\n\n\t\tNome = ");
            puts(p->nome);
            printf("\t\tData da compra = %d/%d/%d\n", p->data_compra.dia, p->data_compra.mes, p->data_compra.ano);
            printf("\t\tValor da compra = %.2f\n", p->divida);
            printf("\t\tValor da divida = %.2f\n", calcula_divida(p->divida, p->num_prestacao, p->num_prest_pagas));
            printf("\t\tQuantidade de presta��es = %d\n", p->num_prestacao);
            printf("\t\tQuantidade de presta��es pagas = %d\n\n", p->num_prest_pagas);
        }
    }
}

Lista *liberar(Lista *recebida)
{
    system("cls");

    Lista *aux;
    Lista *p;
    char nome[tam_nome];

    if (vazia(recebida))
    {
        printf("\n\n\t\tLista Vazia!!\n\n");
    }
    else
    {
        fflush(stdin);
        printf("\n\nInsira o nome para deletar: ");
        fgets(nome, tam_nome, stdin);
        fflush(stdout);

        if (strcmp(recebida->nome, nome) == 0)
        {
            aux = recebida->prox;
            free(recebida);
            return aux;
        }
        else
        {
            p = recebida;
            while (strcmp(recebida->nome, nome) != 0)
            {
                aux = p;
                p = p->prox;
            }
        }
        aux->prox = p->prox;
        free(p);
        return recebida;
    }
}

void menu(Lista *recebida)
{
    int opcao = 0;
    while (opcao != 6)
    {
        printf("\n\t Op�ao 1: Inserir Novo Cliente");
        printf("\n\t Op�ao 2: Remover Cliente");
        printf("\n\t Op�ao 3: Atualizar Parcelamento");
        printf("\n\t Op�ao 4: Imprimir Informa��es de Todos os Clientes");
        printf("\n\t Op�ao 5: Imprimir Informa��es de um Cliente");
        printf("\n\t Op�ao 6: Sair");

        printf("\n\n\t\t Escolha uma op��o: ");
        scanf("%d", &opcao);

        if (opcao == 1)
        {
            recebida = inserir(recebida);
        }
        else if (opcao == 2)
        {
            recebida = liberar(recebida);
        }
        else if (opcao == 3)
        {
            update_parcelas(recebida);
        }
        else if (opcao == 4)
        {
            imprime(recebida);
        }
        else if (opcao == 5)
        {
            busca_cliente(recebida);
        }
        else
        {
            break;
        }
    }
}

int main()
{
    setlocale(LC_ALL, "portuguese");
    Lista *inicio;
    inicio = inicializa();
    menu(inicio);
    printf("Muito obrigado por usar o nosso sistema!");
}
