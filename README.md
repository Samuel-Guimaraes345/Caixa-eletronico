# Atividade 02 – Caixa Eletrônico

Atividade da disciplina **Algoritmos e Pensamento Computacional (ALGPC)**, da **UNICID**. O objetivo é simular o saque de um caixa eletrônico em linguagem C: o programa lê o valor, valida a operação e mostra quantas notas de **R$ 100, 50, 20, 10 e 5** serão entregues, sempre começando pelas maiores.

A turma foi dividida em dois grupos. Cada grupo desenvolveu sua solução e seu relatório, depois os grupos trocaram os códigos e fizeram um feedback um do outro. Este repositório reúne tudo isso.

## O que tem aqui

| Arquivo | Descrição |
|---|---|
| `Atividade_02_Caixa_Eletronico.pdf` | Documento único com a capa, o relatório do Grupo 1, o relatório do Grupo 2 e os dois feedbacks |
| `caixa_eletronico_atividade2.c` | Código em C do **Grupo 1** |
| `caixa_eletronico.c` | Código em C do **Grupo 2** |

O documento está dividido em três partes:

1. **Relatório do Grupo 1:** Passos 1 a 6 (entendimento do problema, pseudocódigo, variáveis, implementação, testes e ajustes), exemplo de execução e o código-fonte completo.
2. **Relatório do Grupo 2:** contextualização, entradas, saídas e validações, variáveis, pseudocódigo, código em C e documentação de 9 testes.
3. **Feedback entre os grupos:** o do Grupo 1 para o Grupo 2 e o do Grupo 2 para o Grupo 1.

## Integrantes

**Grupo 1**
- Alessandra Guimarães da Silva
- Davi Pereira de Oliveira Silva
- Ellen Cristina Soares de Jesus
- Samuel Guimarães da Silva

**Grupo 2**
- Gabriel Anjos Albuquerque
- João Pedro Theodoro de Sousa Andrade
- Samuel Carmoni de Oliveira
- Petterson Michel Lima Aguilar

## Os dois códigos

### Grupo 1 – `caixa_eletronico_atividade2.c`

Além do saque, que é o que o enunciado pede, inclui acréscimos feitos por iniciativa do grupo:

- 3 clientes, cada um com senha (3 tentativas; depois disso o cartão é bloqueado);
- menu com ver saldo, depositar, sacar, extrato (últimas 10 transações) e sair;
- estoque fixo de notas no caixa, que diminui a cada saque. Se faltar nota, o caixa entrega as que tem; se mesmo assim sobrar valor, recusa o saque.

| Cliente | Senha | Saldo inicial |
|---|---|---|
| 1 | 1234 | R$ 500 |
| 2 | 2222 | R$ 1000 |
| 3 | 3333 | R$ 300 |

Estoque inicial: 10 notas de 100, 10 de 50 e 20 de cada uma das notas de 20, 10 e 5.

### Grupo 2 – `caixa_eletronico.c`

Faz somente o saque, como pede o enunciado, com saldo fixo de **R$ 500**: lê o valor, valida e mostra as notas.

### Regras de validação do saque (nos dois códigos)

O valor é conferido nesta ordem:

1. maior que zero;
2. múltiplo de 5 (a menor nota é a de 5);
3. menor ou igual ao saldo.

As notas são calculadas com divisão inteira (`/`) e resto da divisão (`%`). Exemplo para R$ 285: 2 notas de 100, 1 de 50, 1 de 20, 1 de 10 e 1 de 5.

## Como compilar e executar

É preciso ter um compilador C, como o `gcc`.

```bash
# Grupo 1
gcc caixa_eletronico_atividade2.c -o caixa_grupo1
./caixa_grupo1

# Grupo 2
gcc caixa_eletronico.c -o caixa_grupo2
./caixa_grupo2
```

No Windows, execute `caixa_grupo1.exe` e `caixa_grupo2.exe` (ou use uma IDE como o Code::Blocks).

> As mensagens exibidas pelos programas foram escritas **sem acento** de propósito, porque o terminal do Windows pode mostrar letras acentuadas de forma errada.

### Exemplo de execução (Grupo 2)

```
Digite o valor do saque: 285
Notas entregues:
2 nota(s) de 100
1 nota(s) de 50
1 nota(s) de 20
1 nota(s) de 10
1 nota(s) de 5
```

### Exemplo de execução (Grupo 1)

Entrando como cliente 1 (senha 1234) e sacando R$ 95:

```
Digite o valor do saque: 95

Notas entregues:
1 nota(s) de 50
2 nota(s) de 20
1 nota(s) de 5

Novo saldo: R$ 405
```

## Testes realizados

Valores testados nos relatórios:

| Valor | Resultado esperado |
|---|---|
| R$ 50 | 1 nota de 50 |
| R$ 95 | 1 nota de 50, 2 de 20 e 1 de 5 |
| R$ 123 | Recusado: não é múltiplo de 5 |
| R$ 1005 | Recusado: saldo insuficiente |
| R$ 0 | Recusado: valor não positivo |
| R$ -10 | Recusado: valor não positivo |
| R$ 285 | 2 notas de 100, 1 de 50, 1 de 20, 1 de 10 e 1 de 5 |
| R$ 500 | 5 notas de 100 (testado no Grupo 2) |
| R$ 5 | 1 nota de 5 (testado no Grupo 2) |

Os detalhes de cada teste estão no documento `.docx`.
