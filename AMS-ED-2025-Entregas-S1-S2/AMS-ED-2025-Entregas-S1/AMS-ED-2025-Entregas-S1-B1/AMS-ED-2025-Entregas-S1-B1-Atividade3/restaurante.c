/*----------------------------------------------------------------------------------*/
/*   FATEC-SC#o Caetano do Sul                 Estrutura de Dados                   */
/*                         Id da Atividade: S1-B1-3                                 */
/*             Objetivo: << Maipulação de Lista Ligada >>                           */
/*                                                                                  */
/*                                  Autor: Carolina Pichelli Souza                  */
/*                                                                  Data:14/03/2025 */
/*----------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pedido
{
	int Numero;
	char Nome[30];
	char Descricao[50];
	int Quantidade;
	char Status[20];
	struct Pedido* Proximo;
} Pedido;

int Numero;
char TipoStatus[4][20] = {"Pendente", "Em Preparo", "Pronto", "Entregue"};

void ExibirMenu()
{
	printf("\n\nRestaurante \n");
	printf("Escolha uma opção:\n");
	printf("0 - Sair\n");
	printf("1 - Inserir pedido\n");
	printf("2 - Obter pedido\n");
	printf("3 - Atualizar Status do Pedido\n");
}

Pedido* CriarLista()
{
	return NULL;
}

Pedido* InserirPedido(Pedido* Lista)
{
	int Numero, Quantidade;
	char Nome[30], Descricao[50];

	printf("Insira o número do pedido: ");
	scanf("%d", &Numero);

	printf("Insira o seu nome: ");
	scanf("%s", Nome);

	printf("Insira a descrição do pedido: ");
	scanf("%s", Descricao);

	printf("Insira a quantidade: ");
	scanf("%d", &Quantidade);


	Pedido* NewPedido = (Pedido*)malloc(sizeof(Pedido));
	if (NewPedido == NULL)
	{
		printf("Erro na alocação de memória!\n");
		return Lista;
	}

	NewPedido->Numero = Numero;
	strcpy(NewPedido->Nome, Nome);
	strcpy(NewPedido->Descricao, Descricao);
	NewPedido->Quantidade = Quantidade;
	strcpy(NewPedido->Status, TipoStatus[0]);

	NewPedido->Proximo = Lista;

	return NewPedido;
}

void ObterPedido(Pedido* Lista, int Numero)
{
	Pedido* Atual = Lista;
	while (Atual != NULL) {
		if (Atual->Numero == Numero)
		{
			printf("NC:mero: %d\nCliente: %s\nDescrição: %s\nQuantidade: %d\nStatus: %s\n",
			       Atual->Numero, Atual->Nome, Atual->Descricao, Atual->Quantidade, Atual->Status);
			return;
		}
		Atual = Atual->Proximo;
	}
	printf("Pedido não encontrado.\n");
}

void AtualizarStatus(Pedido** Lista, int Numero)
{
	Pedido* Atual = *Lista;
	Pedido* Anterior = NULL;

	while (Atual != NULL)
	{
		if (Atual->Numero == Numero)
		{
			if (strcmp(Atual->Status, TipoStatus[3]) == 0)
			{
				if (Anterior == NULL)
				{
					*Lista = Atual->Proximo;
				}
				else
				{
					Anterior->Proximo = Atual->Proximo;
				}
				free(Atual);
				printf("O pedido foi removido, pois já estava 'Entregue'.\n");
				return;
			}
			else
			{
				for (int i = 0; i < 3; i++)
				{
					if (strcmp(Atual->Status, TipoStatus[i]) == 0)
					{
						strcpy(Atual->Status, TipoStatus[i + 1]);
						printf("O status do pedido foi atualizado para: %s\n", Atual->Status);
						return;
					}
				}
			}
		}
		Anterior = Atual;
		Atual = Atual->Proximo;
	}

	printf("Pedido não encontrado.\n");
}

void LiberarLista(Pedido *Lista)
{
	free(Lista);
}

int main()
{
	Pedido* Lista = CriarLista();
	int Escolha;

	while (1)
	{
		ExibirMenu();
		printf("Opção: ");
		scanf("%d", &Escolha);

		switch (Escolha)
		{
		case 0:
			LiberarLista(Lista);
			return 0;
			break;
		case 1:
			Lista = InserirPedido(Lista);
			break;
		case 2:
			printf("Insira o número do pedido a ser obtido: ");
			scanf("%d", &Numero);
			ObterPedido(Lista, Numero);
			break;
		case 3:
			printf("Insira o número do pedido a ser atualizado: ");
			scanf("%d", &Numero);
			AtualizarStatus(&Lista, Numero);
			break;
		default:
			printf("\nInsira uma opção válida no menu.\n");
		}
	}

	return 0;
}
