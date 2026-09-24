# Jogo do Caderno: Batalha Naval em C

Batalha naval para terminal, feita em C como projeto em grupo da disciplina de programação com o Prof. Leonardo Angelo Virginio de Souto.

## Modos de jogo

- **Um jogador**: encontre os navios escondidos no tabuleiro 5x5.
- **Dois jogadores**: cada jogador posiciona seus navios e os dois se alternam atirando. Acertos somam pontos e erros descontam.
- **Personalizado**: o tamanho do tabuleiro é definido pelo jogador (até 15x15 no modo solo e 10x10 no modo para dois).

O jogo também tem telas de regras e créditos, valida as coordenadas digitadas e usa cores no terminal para indicar acertos e erros.

## Como compilar e jogar

Windows (MinGW ou Dev-C++, que usa o `Makefile.win` do projeto):

```bash
gcc main.c -o batalha_naval.exe
batalha_naval.exe
```

Linux ou macOS:

```bash
gcc main.c -o batalha_naval
./batalha_naval
```

## O que praticamos

Matrizes bidimensionais, funções com passagem por referência, validação de entrada do usuário, geração de posições aleatórias com `rand()` e organização de menus com `switch`.

## Grupo

**Grupo do Caderno**

- Jorge Luis Heringer Bublitz
- Íris C. do C. Lins
- Vitor Ferreira Gonçalves Silva
- Rafael Queiroz Almeida
