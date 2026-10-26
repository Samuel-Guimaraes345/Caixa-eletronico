#include <stdio.h>
#include <stdbool.h>

/*
 * Atividade 02 - Caixa Eletrônico
 * Algoritmos e Pensamento Computacional (ALGPC)
 * Integrantes: Alessandra Guimarães da Silva, Davi Pereira de Oliveira Silva,
 * Ellen Cristina Soares de Jesus e Samuel Guimarães da Silva
 *
 * Caixa eletrônico com 3 clientes e quantidade fixa de notas (100, 50, 20, 10 e 5).
 * O caixa dá sempre as maiores notas possíveis primeiro.
 *
 * OBSERVAÇÃO SOBRE OS ACENTOS: as mensagens que o programa mostra na tela estão
 * escritas SEM acento de propósito, porque o terminal do Windows pode exibir
 * letras acentuadas de forma errada (símbolos estranhos no lugar das letras).
 *
 * OBSERVAÇÃO SOBRE O ESCOPO: a atividade pede apenas o saque (valor, validações e
 * distribuição das notas). Os 3 clientes com senha, o menu com saldo, depósito e
 * extrato e o estoque fixo de notas são acréscimos feitos por iniciativa própria.
 *
 * Os dados dos clientes ficam em vetores de 3 posições:
 *   posição 0 = cliente 1, posição 1 = cliente 2, posição 2 = cliente 3
 */

int main() {
    // ---------- dados dos clientes ----------
    int senha[3] = {1234, 2222, 3333};
    int saldo[3] = {500, 1000, 300};
    int tentativas[3] = {0, 0, 0};
    bool bloqueado[3] = {false, false, false};
    bool finalizou[3] = {false, false, false};
    int historico[3][10];            // depósito = valor positivo, saque = valor negativo
    int qtdTransacoes[3] = {0, 0, 0};

    // ---------- notas que existem no caixa (quantidade fixa no início) ----------
    int estoque100 = 10, estoque50 = 10, estoque20 = 20, estoque10 = 20, estoque5 = 20;

    // ---------- contadores: quantas notas de cada tipo serão entregues no saque ----------
    int notas100, notas50, notas20, notas10, notas5;

    int c = 0;                       // cliente atual (0, 1 ou 2)
    int opcao_cliente = 0, opcao = 0;
    int senhaDigitada = 0;
    int valorDeposito = 0, valorSaque = 0, restante = 0;
    int totalNotas = 0, i = 0;
    bool logado = false, sair = false, todosFinalizados = false;

    printf("=== Caixa eletronico ===\n");

    // ---------- LOOP CENTRAL ----------
    // termina quando os 3 clientes saírem (ou forem bloqueados) ou quando as notas acabarem
    while (true) {
        totalNotas = estoque100 + estoque50 + estoque20 + estoque10 + estoque5;

        todosFinalizados = true;
        for (i = 0; i < 3; i++) {
            if (finalizou[i] == false && bloqueado[i] == false) {
                todosFinalizados = false;
            }
        }

        if (totalNotas == 0) {
            printf("\nO caixa ficou sem notas. Encerrando.\n");
            break;
        }
        if (todosFinalizados == true) {
            printf("\nTodos os clientes ja foram atendidos. Encerrando.\n");
            break;
        }

        // ---------- escolha do cliente ----------
        printf("\nInforme qual cliente e:\n");
        printf("1 - Cliente 1\n");
        printf("2 - Cliente 2\n");
        printf("3 - Cliente 3\n");
        scanf("%d", &opcao_cliente);

        if (opcao_cliente < 1 || opcao_cliente > 3) {
            printf("Cliente invalido!\n");
            continue;
        }
        c = opcao_cliente - 1;       // 1 vira 0, 2 vira 1, 3 vira 2

        if (finalizou[c] == true) {
            printf("Este cliente ja finalizou o atendimento.\n");
            continue;
        }
        if (bloqueado[c] == true) {
            printf("Cartao bloqueado!\n");
            continue;
        }

        // ---------- pede a senha (3 tentativas) ----------
        logado = false;
        while (tentativas[c] < 3 && logado == false) {
            printf("Digite sua senha:\n");
            scanf("%d", &senhaDigitada);

            if (senhaDigitada == senha[c]) {
                logado = true;
                tentativas[c] = 0;
            } else {
                tentativas[c] = tentativas[c] + 1;
                if (tentativas[c] < 3) {
                    printf("Senha incorreta! Tentativas restantes: %d\n", 3 - tentativas[c]);
                }
            }
        }

        // se errou 3 vezes o cartão é bloqueado
        if (logado == false) {
            bloqueado[c] = true;
            printf("Senha errada 3 vezes. Cartao bloqueado!\n");
            continue;
        }

        printf("Bem-vindo, cliente %d!\n", opcao_cliente);

        // ---------- menu principal (repete até o cliente escolher sair) ----------
        sair = false;
        while (sair == false) {
            printf("\nEscolha uma das seguintes opcoes:\n");
            printf("1 - Ver saldo\n");
            printf("2 - Depositar\n");
            printf("3 - Sacar\n");
            printf("4 - Extrato\n");
            printf("0 - Sair\n");
            scanf("%d", &opcao);

            switch (opcao) {
                case 1:
                    printf("Seu saldo e: R$ %d\n", saldo[c]);
                    break;

                case 2:
                    printf("Digite o valor do deposito (multiplo de 5):\n");
                    scanf("%d", &valorDeposito);

                    if (valorDeposito <= 0) {
                        printf("Digite um valor maior que zero.\n");
                    } else if (valorDeposito % 5 != 0) {
                        printf("So aceitamos notas de 100, 50, 20, 10 e 5. Digite um multiplo de 5.\n");
                    } else {
                        saldo[c] = saldo[c] + valorDeposito;

                        // o extrato guarda as últimas 10 transações: se já estiver cheio,
                        // descarta a mais antiga (posição 0) e desloca as outras uma posição
                        if (qtdTransacoes[c] == 10) {
                            for (i = 0; i < 9; i++) {
                                historico[c][i] = historico[c][i + 1];
                            }
                            qtdTransacoes[c] = 9;
                        }
                        historico[c][qtdTransacoes[c]] = valorDeposito;
                        qtdTransacoes[c] = qtdTransacoes[c] + 1;

                        printf("Deposito realizado! Novo saldo: R$ %d\n", saldo[c]);
                    }
                    break;

                case 3:
                    // ----- 1) Solicita o valor do saque -----
                    printf("Digite o valor do saque: ");
                    scanf("%d", &valorSaque);

                    // ----- 2) Valida o valor: positivo, múltiplo de 5 e dentro do saldo -----
                    if (valorSaque <= 0) {
                        printf("Valor invalido! Digite um valor maior que zero.\n");
                    } else if (valorSaque % 5 != 0) {
                        // % devolve o resto da divisão: se não for 0, não é múltiplo de 5
                        printf("Valor invalido! O saque deve ser multiplo de 5 (notas de 100, 50, 20, 10 e 5).\n");
                    } else if (valorSaque > saldo[c]) {
                        printf("Saldo insuficiente! Seu saldo e R$ %d.\n", saldo[c]);
                    } else {
                        // ----- 3) Calcula as notas (sempre começando pela maior) -----
                        // "/" (divisão inteira) diz quantas notas cabem no valor.
                        // "%" (módulo) diz quanto sobra depois dessas notas.
                        // Exemplo: 285 / 100 = 2 notas e 285 % 100 = 85 de restante.
                        // Se o caixa tiver menos notas do que o necessário, entrega só as que
                        // existem e o que não foi pago continua no restante para as notas menores.
                        restante = valorSaque;

                        // notas de 100
                        notas100 = restante / 100;
                        if (notas100 > estoque100) {
                            notas100 = estoque100;
                            restante = restante - notas100 * 100;
                        } else {
                            restante = restante % 100;
                        }

                        // notas de 50
                        notas50 = restante / 50;
                        if (notas50 > estoque50) {
                            notas50 = estoque50;
                            restante = restante - notas50 * 50;
                        } else {
                            restante = restante % 50;
                        }

                        // notas de 20
                        notas20 = restante / 20;
                        if (notas20 > estoque20) {
                            notas20 = estoque20;
                            restante = restante - notas20 * 20;
                        } else {
                            restante = restante % 20;
                        }

                        // notas de 10
                        notas10 = restante / 10;
                        if (notas10 > estoque10) {
                            notas10 = estoque10;
                            restante = restante - notas10 * 10;
                        } else {
                            restante = restante % 10;
                        }

                        // notas de 5
                        notas5 = restante / 5;
                        if (notas5 > estoque5) {
                            notas5 = estoque5;
                            restante = restante - notas5 * 5;
                        } else {
                            restante = restante % 5;
                        }

                        // ----- 4) Mostra o resultado ou a mensagem de erro -----
                        if (restante != 0) {
                            // sobrou valor sem nota para pagar: o caixa não consegue entregar
                            printf("O caixa nao tem notas suficientes para esse valor. Tente outro valor.\n");
                        } else {
                            // tira as notas do caixa e o dinheiro da conta
                            estoque100 = estoque100 - notas100;
                            estoque50 = estoque50 - notas50;
                            estoque20 = estoque20 - notas20;
                            estoque10 = estoque10 - notas10;
                            estoque5 = estoque5 - notas5;
                            saldo[c] = saldo[c] - valorSaque;

                            // o extrato guarda as últimas 10 transações: se já estiver cheio,
                            // descarta a mais antiga (posição 0) e desloca as outras uma posição
                            if (qtdTransacoes[c] == 10) {
                                for (i = 0; i < 9; i++) {
                                    historico[c][i] = historico[c][i + 1];
                                }
                                qtdTransacoes[c] = 9;
                            }
                            historico[c][qtdTransacoes[c]] = -valorSaque;
                            qtdTransacoes[c] = qtdTransacoes[c] + 1;

                            // só mostra as notas com quantidade maior que zero
                            printf("\nNotas entregues:\n");
                            if (notas100 > 0) printf("%d nota(s) de 100\n", notas100);
                            if (notas50 > 0)  printf("%d nota(s) de 50\n", notas50);
                            if (notas20 > 0)  printf("%d nota(s) de 20\n", notas20);
                            if (notas10 > 0)  printf("%d nota(s) de 10\n", notas10);
                            if (notas5 > 0)   printf("%d nota(s) de 5\n", notas5);

                            printf("\nNovo saldo: R$ %d\n", saldo[c]);

                            // se o caixa zerou, só avisa (o cliente continua no menu)
                            totalNotas = estoque100 + estoque50 + estoque20 + estoque10 + estoque5;
                            if (totalNotas == 0) {
                                printf("\nO caixa ficou sem notas! Voce ainda pode ver saldo e extrato.\n");
                            }
                        }
                    }
                    break;

                case 4:   // Extrato
                    if (qtdTransacoes[c] == 0) {
                        printf("Nenhuma transacao realizada.\n");
                    } else {
                        printf("\n--- Extrato ---\n");
                        for (i = 0; i < qtdTransacoes[c]; i++) {
                            if (historico[c][i] > 0) {
                                printf("%d) Deposito: R$ %d\n", i + 1, historico[c][i]);
                            } else {
                                printf("%d) Saque:    R$ %d\n", i + 1, -historico[c][i]);
                            }
                        }
                        printf("Obs.: o extrato mostra apenas as ultimas 10 transacoes.\n");
                    }
                    break;

                case 0: //sair
                    printf("Obrigado e ate logo, cliente %d!\n", opcao_cliente);
                    sair = true;
                    break;

                default:
                    printf("Opcao invalida!\n");
            }
        }

        finalizou[c] = true;
    }

    return 0;
}
