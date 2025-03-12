/*----------------------------------------------------------------------------------*/
/*   FATEC-São Caetano do Sul                 Estrutura de Dados                    */
/*                         Id da Atividade: S1-B1-2                                 */
/*             Objetivo: <<  Manipulacao de Array com ponteiro  >>                  */
/*                                                                                  */
/*                                  Autora: Carolina Pichelli Souza                 */
/*                                                                   Data:06/03/2024*/
/*----------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Candidato {
    char nome[50];
    float PE[4];
    float AC[5];
    float PP[10];
    float EB[3];
    float NF;
    struct Candidato *proximo;
};

float mediaCentral(float notas[], int tamanho) {
    float soma = 0, maior, menor;
    float *notasPtr = notas; 
    maior = menor = *notasPtr;
        for (int i = 0; i < tamanho; i++) {
            float nota = *(notasPtr + i);
            soma += nota;
            if (nota > maior)
                maior = nota;
            if (nota < menor)
                menor = nota;
        }
    
    return (soma - maior - menor) / (tamanho - 2);
}

void incluirCandidato(struct Candidato **comeco, char nome[], float PE[], float AC[], float PP[], float EB[]) {
    struct Candidato *novoCandidato = (struct Candidato*)malloc(sizeof(struct Candidato));
    
    if (novoCandidato == NULL) {
        printf("Erro ao alocar memória. \n");
        return;
    }
        strcpy(novoCandidato->nome, nome);
        memcpy(novoCandidato->PE, PE, 4 * sizeof(float));
        memcpy(novoCandidato->AC, AC, 5 * sizeof(float));
        memcpy(novoCandidato->PP, PP, 10 * sizeof(float));
        memcpy(novoCandidato->EB, EB, 3 * sizeof(float));
        float media_PE = mediaCentral(PE, 4); 
        float media_AC = mediaCentral(AC, 5);  
        float media_PP = mediaCentral(PP, 10); 
        float media_EB = mediaCentral(EB, 3);  
    
        novoCandidato->NF = (media_PE * 0.3f) + (media_AC * 0.1f) + (media_PP * 0.4f) + (media_EB * 0.2f);
    
        novoCandidato->proximo = *comeco;
        *comeco = novoCandidato;
}

void classCandidatos(struct Candidato **comeco) {
    struct Candidato *i, *j;
    float tempNF;
    char tempNome[50];
    for (i = *comeco; i != NULL; i = i->proximo) {
        for (j = i->proximo; j != NULL; j = j->proximo) {
            if (i->NF < j->NF) {
                tempNF = i->NF;
                i->NF = j->NF;
                j->NF = tempNF;
                strcpy(tempNome, i->nome);
                strcpy(i->nome, j->nome);
                strcpy(j->nome, tempNome);
            }
        }
    }
}

void imprimirClassificacao(struct Candidato *comeco) {
    struct Candidato *ptr = comeco;
    printf("Classificação dos melhores candidatos: \n");
    for (int i = 0; i < 5 && ptr != NULL; i++) {
        printf("%dº %s - Nota Final: %.2f \n", i + 1, ptr->nome, ptr->NF);
        ptr = ptr->proximo;
    }
}

int main(void) {
    struct Candidato *comeco = NULL;
    int numero_candidatos = 0;
    int prosseguir = 1;  

    while (prosseguir == 1) {
        char nome[50];
        float PE[4], AC[5], PP[10], EB[3];
        
        printf("Usuários cadastrados: %i\n", numero_candidatos);
        printf("Insira o nome do candidato: ");
        scanf("%s", nome);
        printf("Insira as 4 notas para Prova Escrita(PE):\n");
        for (int qtde = 0; qtde < 4; qtde++) {
            scanf("%f", &PE[qtde]);
        }
        printf("Insira as 5 notas para Análise Curricular(AC):\n");
        for (int qtde = 0; qtde < 5; qtde++) {
            scanf("%f", &AC[qtde]);
        }
        printf("Insira as 10 notas para Prova Prática(PP):\n");
        for (int qtde = 0; qtde < 10; qtde++) {
            scanf("%f", &PP[qtde]);
        }
        printf("Insira as 3 notas para Entrevista em Banca(EB):\n");
        for (int qtde = 0; qtde < 3; qtde++) {
            scanf("%f", &EB[qtde]);
        }
        incluirCandidato(&comeco, nome, PE, AC, PP, EB);
        numero_candidatos++;
        if (numero_candidatos >= 50) {
            printf("Você atingiu o limite máximo de candidatos (50). \n");
            break;
        }
        printf("\nDeseja adicionar mais um candidato? (1 para SIM, 0 para NÃO): ");
        scanf("%d", &prosseguir);
    }

    classCandidatos(&comeco);
    imprimirClassificacao(comeco);
    
    return 0;

}
