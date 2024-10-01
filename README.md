# Trabalho Prático I

## Autores

@Alan Barbosa Lima [AlanLima287](https://github.com/AlanLima287)             <br>
@Breno Augusto Braga Oliveira                                                <br>
@Juan Pablo Ferreira Costa [juanzinhobs18](https://github.com/juanzinhobs18) <br>
@Luiz Felipe Melo Oliveira                                                   <br>
@Otávio Gomes Calazans

# Do Trabalho

Esse Trabalho foi desenvolvido como projeto acadêmico da diciplinade de ALGORITMOS E ESTRUTURAS DE DADOS III, do Curso de Graduação em Sistemas de Informação da Universidade Federal dos Vales do Jequitinhonha e Mucuri, sob comando da Professora Luciana de Assis.

### Definição 1: Árvores Binárias
Uma árvore binária aqui é um conjunto vazio $\emptyset$ ou uma tripla ordenada $T = \langle v, E, D \rangle$, onde $E$ e $D$ são árvores ($E$ é chamada _sub-árvore esquerda_ e $D$ é chamada _sub-árvore direita_), e $v$ uma variável de conjunto totalmente ordenado. Formalmente:<br>

$$BTree(T) \iff T = \emptyset \vee (T = \langle v, E, D \rangle \wedge BTree(D) \wedge BTree(E))$$

Em C++, a estrutura de um nó de uma árvore binária é definido:

```C++
typedef struct Node {
   Record* content;
   Node* left_child;
   Node* rght_child;
   uint64 height;
} Node;
```

Como requerido pelo trabalho, a estrutura de registro é definida:

```C++
typedef int32 key_t;
static const uint64 NAME_SIZE = 1000;

typedef struct Record {
   key_t key;
   int   data;
   char  name[NAME_SIZE + 1];
} Record;
```

Sendo o maior comprimento do nome para acomodar um `\0` (terminador nulo), caso necessário, mantendo `NAME_SIZE` caracteres úteis.<br>

A ordenação total do conjunto de `Record`'s, denotada $<$, é dada, para `Record`'s $R$ e $S$:

$$R < S \iff R.key < S.key$$

Quando $R < S$, $R$ é dito _menor_ que $S$, analogamente, se $R > S$, $R$ é dito _maior_ que $S$. Para esse trabalho, toda árvore $T = \langle v, E, D \rangle$ possuirá $v$ do tipo `Record`. Quando diz-se um nó é menor/maior que outro, refere-se aos registros contidos nesses nós.

### Definição 2: Árvores Binárias de Busca

Uma árvore binária de busca é uma árvore binaria que satisfaz a seguinte propriedade, para todo nó $T = \langle v, E, D \rangle$, todo nó $N_E$ na sub-árvore esquerda, é menor que $v$, e todo nó $N_D$ na sub-árvore direita, é maior que $v$. É entendido que cada nó tenha uma chave única por árvore.