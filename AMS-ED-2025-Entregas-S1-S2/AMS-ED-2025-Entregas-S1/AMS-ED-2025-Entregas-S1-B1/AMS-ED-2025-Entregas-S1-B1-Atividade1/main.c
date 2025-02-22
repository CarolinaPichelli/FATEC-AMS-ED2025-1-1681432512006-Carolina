
#include <stdio.h>

double funcaoDesc(double *PrecoPtr, double Desc, int Porcentagem) {
    double totalDesc;
    
    if(Porcentagem) {
        totalDesc = (*PrecoPtr * (Desc/100));
    }
    else {
        totalDesc = Desc;
    }
    *PrecoPtr = *PrecoPtr-totalDesc;
    
    return 0;
}

int main(){
    double Preco, Desc;
    int Porcentagem;
    
    printf("Digite o valor a ser descontado: R$ ");
    scanf("%lf", &Preco);
    
    printf("Digite o valor do desconto: ");
    scanf("%lf", &Desc);
    
    printf("O desconto deve ser aplicado em porcentagem ou não? (1 para Sim e 0 para Não)");
    scanf("%d", &Porcentagem);
    
    printf("Preço do produto: R$%.2f\n ", Preco);
    
    funcaoDesc(&Preco, Desc, Porcentagem);
    
    if (Porcentagem) {
            printf("Desconto: %.2lf%%\n", Desc);
        }
        else {
            printf("Desconto: R$ %.2lf\n", Desc);
        }
    
    printf("Preço final: R$%.2f\n ", Preco);

    return 0;
}
