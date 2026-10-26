//Grupo - 2
#include <stdio.h>
int main() {
    int valorSaque, saldo, restante;
    int notas100, notas50, notas20, notas10, notas5;

    //define o saldo inicial da conta
    saldo = 500;

    //lê o valor do saque
    printf("Digite o valor do saque: ");
    scanf("%d", &valorSaque);

    //o valor deve ser positivo
    if (valorSaque <= 0) {
        printf("Erro: Saldo incorreto\n");
    } else {
        // o valor tem que ser multiplo de 5
        if (valorSaque % 5 != 0) {
            printf("Erro: valor deve ser multiplo de 5.\n");
        } else {
            // o valor nao pode ser maior que o saldo
            if (valorSaque > saldo) {
                printf("Erro: saldo insuficiente.\n");
            } else {
                // calculo da quantidade de notas, começando pela maior

                // Notas de 100: quantas cabem no valor e o que sobra
                notas100 = valorSaque / 100;
                restante = valorSaque % 100;

                // Notas de 50: quantas cabem no restante e o que sobra
                notas50 = restante / 50;
                restante = restante % 50;

                // Notas de 20: quantas cabem no restante e o que sobra
                notas20 = restante / 20;
                restante = restante % 20;

                // Notas de 10: quantas cabem no restante e o que sobra
                notas10 = restante / 10;
                restante = restante % 10;

                // Notas de 5: quantas cabem no restante e o que sobra
                notas5 = restante / 5;
                restante = restante % 5;

                // Exibe o resultado
                printf("Notas entregues:\n");
                if (notas100 > 0) {
                    printf("%d nota(s) de 100\n", notas100);
                }
                if (notas50 > 0) {
                    printf("%d nota(s) de 50\n", notas50);
                }
                if (notas20 > 0) {
                    printf("%d nota(s) de 20\n", notas20);
                }
                if (notas10 > 0) {
                    printf("%d nota(s) de 10\n", notas10);
                }
                if (notas5 > 0) {
                    printf("%d nota(s) de 5\n", notas5);
                }
            }
        }
    }

    return 0;
}