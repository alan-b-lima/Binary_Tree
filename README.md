# Trabalho Prático I

## Autores

@Alan Barbosa Lima [alan-b-lima](https://github.com/alan-b-lima)               <br>
@Breno Augusto Braga Oliveira [bragabreno](https://github.com/bragabreno)      <br>
@Juan Pablo Ferreira Costa [juan-ferreirax](https://github.com/juan-ferreirax) <br>
@Luiz Felipe Melo Oliveira                                                     <br>
@Otávio Gomes Calazans

# Do Trabalho

Esse Trabalho foi desenvolvido como projeto acadêmico da disciplina de ALGORITMOS E ESTRUTURAS DE DADOS III, do Curso de Graduação em Sistemas de Informação da Universidade Federal dos Vales do Jequitinhonha e Mucuri, sob comando da Professora Luciana de Assis.

# Sumário

<strong>[Como Usar](#como-usar)</strong>

- [Como compilar](#como-compilar)
- [Executando o programa](#executando-o-programa)
   - [Realizando testes](#realizando-testes)

<strong>[Estrutura das Dependências](#estrutura-das-dependências)</strong>

- [Diagrama da estrutura de dependências da aplicação](#diagrama-da-estrutura-de-dependências-da-aplicação)

<strong>[Estruturas de Dados](#estruturas-de-dados)</strong>

- [1 Registros](#1-registros)
- [2 Listas Encadeadas](#2-listas-encadeadas)
   - [Definição 2A: Lista Encadeada](#definição-2a-lista-encadeada)
   - [Definição e Implementação 2B: Algoritmo de Busca](#definição-e-implementação-2b-algoritmo-de-busca)
      - [Análise de Complexidade](#análise-de-complexidade)
   - [Definição e Implementação 2C: Algoritmo de Inserção](#definição-e-implementação-2c-algoritmo-de-inserção)
      - [Análise de Complexidade](#análise-de-complexidade-1)
- [3 Árvores Binárias](#3-árvores-binárias)
   - [Definição 3A: Árvore Binária](#definição-3a-árvore-binária)
   - [Definição 3B: Relações entre nós](#definição-3b-relações-entre-nós)
      - [i) Nós Filhos](#i-nós-filhos)
      - [ii) Nó Pai](#ii-nó-pai)
      - [iii) Nó Irmão](#iii-nó-irmão)
      - [iv) Nós Folha](#iv-nós-folha)
      - [v) Nó Raiz](#v-nó-raiz)
   - [Definição 3C: Árvore Binária de Busca](#definição-3c-árvore-binária-de-busca)
   - [Definição 3D: Altura de Árvores Binárias](#definição-3d-altura-de-árvores-binárias)
   - [Teorema 3E: A computação da altura de uma árvore tem complexidade linear no pior caso](#teorema-3e-a-computação-da-altura-de-uma-árvore-tem-complexidade-linear-no-pior-caso)
   - [Implementação 3F: Algoritmo de Busca](#implementação-3f-algoritmo-de-busca)
      - [Análise de Complexidade](#análise-de-complexidade-2)
   - [Implementação 3G: Algoritmo de inserção](#implementação-3g-algoritmo-de-inserção)
      - [Análise de Complexidade](#análise-de-complexidade-3)
- [4 Árvore Binária AVL](#4-árvore-binária-avl)
   - [Definição 4A: Fator de Balanceamento](#definição-4a-fator-de-balanceamento)
   - [Definição 4B: Árvore Binária Balanceada](#definição-4b-árvore-binária-balanceada)
   - [Definição e Implementação 4C: Rotações](#definição-e-implementação-4c-rotações)
      - [i) Rotação Simples à Esquerda](#i-rotação-simples-à-esquerda)
      - [ii) Rotação Simples à Direita](#ii-rotação-simples-à-direita)
      - [iii) Rotação Dupla Direita-Esquerda](#iii-rotação-dupla-direita-esquerda)
      - [iv) Rotação Dupla Esquerda-Direita](#iv-rotação-dupla-esquerda-direita)
      - [Análise de Complexidade](#análise-de-complexidade-4)
   - [Teorema 4D: Uma operação de rotação, quando executada propriamente, retorna um nó menor que o nó de entrada](#teorema-4d-uma-operação-de-rotação-quando-executada-propriamente-retorna-um-nó-menor-que-o-nó-de-entrada)
   - [Corolário 4E: Uma operação de rotação sempre é suficiente para restaurar o balanceamento perdido após a inserção de um único nó](#corolário-4e-uma-operação-de-rotação-sempre-é-suficiente-para-restaurar-o-balanceamento-perdido-após-a-inserção-de-um-único-nó)
   - [Implementação 4F: Inserção em Árvore AVL](#implementação-4f-inserção-em-árvore-avl)
      - [Análise de Complexidade](#análise-de-complexidade-5)
   - [Teorema 4G: Complexidade Logarítmica de Tempo da Busca numa Árvore AVL](#teorema-4g-complexidade-logarítmica-de-tempo-da-busca-numa-árvore-avl)

<strong>[Referências](#referências)</strong>

<strong>[Notas de Rodapé](#notas-de-rodapé)</strong>

# Como Usar

## Como compilar

Há um árquivo próprio para a compiliação, que faz, parcialmente, a função de um linker, este é o arquivo localizado em ./build/build.cpp, para compilá-lo pode-se executar:

```sh
g++ ./build/build.cpp -O2 -o jast
```

Ou pode-se usar o make.sh (para sistemas Linux) ou o make.bat (para Windows).

## Executando o programa

A aplicação é baseada em shell básico que interpreta uma séria predefinida de comandos, sendo esses:

* `chfocus`: Coloca uma estrutura em foco;
* `create`: Cria um novo registro;
* `exit`: Encerra a aplicação;
* `help`: Mostra os comando disponíveis;
* `init`: Mostra a tela de início;
* `load`: Carrega registro de um arquivo;
* `new`: Cria uma nova estrutura;
* `print`: Imprime uma estrutura;
* `quit`: Encerra a aplicação;
* `save`: Salva os dados em um arquivo;
* `test`: Realiza testes.

Para mais detalhes, recomenda-se utilizar a aplicação, use `help <comando>` para obter ajuda sobre um comando especifico.

### Realizando testes

Como requerido pelo trabalho, séries de testes devem ser realizadas com a estruturas de dados implementadas, o exemplo mostrado a seguir será relativo ao teste com estruturas com 100 registros, entretanto o funcionamento é análogo a números diferentes de registros. Ademais, para a maioria dos comandos, existirão multiplas formas de obter o mesmo resultado, aqui, entretanto, será mostrado apenas uma forma.

Os acrônimos para as estruturas de dados são:
- Árvore Binária (tradicional):`tree`;
- Árvore AVL: `avl` ou `avl_tree`;
- Lista Encadeada: `ll` ou `linked_list`,

Esses serão referidos como `<struct>`, para simplificação. Para criar uma estrutura com 100 registros aleatórios, executa-se:

```
> new <struct> 100 random
```

Essa estrutura terá uma distribuição densa de chaves, isto é, todas as chaves inteiras de 0 até 100 - 1, para mitigar tal fato (possuir chaves inexistentes não externas), pode executar-se:

```
> new <struct> 100 random <order>
```

Assim, se `<order>` for 1, esse terá o mesmo efeito que sem o argumento, já com `<order>` maior que um, a faixa de chaves escalona por `<order>`, mais precisamente, chave são geradas de 0 até `<order>` * número de registros - 1. `<order>` é assumido 1 quando não explicitamente declarado.

Agora, encontra-se o id da estrutura guardando os 100 registros, para isso:

```
> print all
```

Assim, o id, tipo da estrutura e primeiro nó (cabeça na lista encadeada e raiz nas árvores). Sabendo o id da estrutura que se deseja testar, seja esse `n` (um inteiro em notação decimal), executa-se:

```
> test $n <tamanho da amostra>
```

O tamanho da amostra, por definição do trabalho, é 15, entretanto, esse pode ser escolhido dinamicamente quando realizandos os testes.

Uma saída da seguite forma é esperada:

```
Teste de 15 chaves

Chaves presentes:
   Número médio de comparações: 10.0769
   Tempo médio: 0.461538 microssegundos
   Desvio padrão: 0.598999 microssegundos

Chaves inexistentes:
   Número médio de comparações: 12.3846
   Tempo médio: 0.0769231 microssegundos
   Desvio padrão: 0.0764679 microssegundos
```

Há um limite de tentativas para gerar as chaves, nomeadamente 64 * `<tamanho da amostra>`, se não forem geradas chaves que atendem os requisitos, a seguinte mensagem é impressa:

```
Não foram encontradas chaves de teste suficientes!
```

Para gerar uma estrutura com insersão em ordem, o mesmo é dado, se não por:

```
> new <struct> 100 ordered <order>
```

Os passos a seguir seguem a mesma lógica.

Se for preferível carregar dados de um arquivo, usa-se:

```
> load <struct> <filename>
```

O projeto terá 6 arquivos de leitura, sendo esses:

- `test-100-o.rc`
- `test-100-r.rc`
- `test-500-o.rc`
- `test-500-r.rc`
- `test-1000-o.rc`
- `test-1000-r.rc`

O nome do arquivo é estruturado `test-<número de registros>-<regra de inserção>.rc`.

# Estrutura das Dependências

## Diagrama da estrutura de dependências da aplicação

```mermaid
flowchart BT;

   subgraph syslibs[*Bibliotecas de Sistema*]
      subgraph UNIX[Baseado em UNIX]
         sys/ioctl.h
      end

      subgraph Windows
         intrin.h
         Windows.h
      end
   end
   
   subgraph stdlibs[*Bibliotecas Padronizadas*]
      base_incl[stdint.h <br> stdlib.h <br> stdio.h <br> time.h <br> chrono <br> iostream]
      random_incl[stdint.h]
      terminal_incl[stdint.h <br> math.h <br> stdio.h]
      stack_incl[stdlib.h <br> stdint.h <br> malloc.h]
      bittools_incl[stdlib.h <br> stdint.h <br> new]
   end

   subgraph usrlibs[*Bibliotecas Implementadas*]
      random.h
      terminal.h
      stack.h
      bittools.h
   end

   bittools.h[
      bittools.h
      bittools.cpp
   ]

   record.h[
      record.h
      record.cpp
   ]
   
   terminal.h[
      terminal.h
      terminal.cpp
      color.h
   ]

   file.h[
      file.h
      file.cpp
   ]

   linked_list.h[
      linked_list.h
      linked_list.cpp
   ]

   application.h[
      application.h
      application.cpp
   ]

   tree.h[
      tree.h
      tree.cpp
   ]

   main.cpp --> base.h
   main.cpp --> file.h
   main.cpp --> linked_list.h
   main.cpp --> application.h
   main.cpp --> tree.h
   main.cpp --> system.h

   file.h --> base.h
   file.h --> record.h
   
   linked_list.h --> base.h
   linked_list.h --> record.h
   linked_list.h ---> strings.cpp
   
   application.h --> terminal.h
   application.h ---> strings.cpp
   application.h ---> stack.h

   tree.h --> record.h
   tree.h ---> strings.cpp
   tree.h --> base.h
   tree.h ---> stack.h
   tree.h ---> bittools.h

   record.h ---> base.h
   record.h --> names.cpp

   base.h --> base_incl
   base.h --> random.h

   system.h --> Windows.h
   system.h --> sys/ioctl.h
   
   terminal.h --> terminal_incl
   
   random.h --> random_incl

   stack.h --> stack_incl

   bittools.h --> bittools_incl
   bittools.h --> intrin.h
   
   style syslibs fill:#0000, stroke-dasharray: 5
   style stdlibs fill:#0000, stroke-dasharray: 5
   style usrlibs fill:#0000, stroke-dasharray: 5

   l6:::level ~~~ 
   l5:::level ~~~
   l4:::level ~~~
   l3:::level ~~~
   l2:::level ~~~
   l1:::level ~~~
   l0:::level

   l0["**Nível 0**"]
   l1["**Nível 1**"]
   l2["**Nível 2**"]
   l3["**Nível 3**"]
   l4["**Nível 4**"]
   l5["**Nível 5**"]
   l6["**Nível 6**"]

   classDef level fill:#0000,stroke:#0000,font-size:large
```

O diagrama acima é uma versão visual das clausulas `#include` encontradas por todo o projeto, organizadas em níveis. Esses níveis, aproximadamente, indicam a ordem de indepencência de outras partes do projeto:

- **Nível 0** é completamento independente do projeto e existirá após esse;
- **Nível 1** foi desenvolvido para o projeto, entretanto não é específico para o esse, podendo se manter relavante para o futuro. Ademais, system.h trata a questão de compatibilidade de terminais com UTF-8 e com código ANSI de escape;
- **Nível 2** carrega definições importantes para todos os níveis abaixo;
- **Nível 3** foge à regra de independência, sendo seus arquivos puramente arquivos de recursos, names.cpp sendo autoexplicativo (carrega exemplos de nomes) e strings.cpp, que carrega cadeias de caracteres usadas pela aplicação;
- **Nível 4** está aqui posicianado por ser a estrutura à qual as estruturas do nível acima revolvem;
- **Nível 5** define as três estruturas de dados requeridas pelo trabalho, sendo árvore de busca binária tradicional e AVL definidas em tree.h e a estrutura sequencial (lista encadeada) em linked_list.h. Ademais, o arquivo file.h define uma estrutura que abstrae o manejamento de arquivos da aplicação principal e o arquivo application.h que lida com interações com o usuário;
- **Nível 6** compreende a entrada da aplicação assim como os desdobramento já despostos em [Como Usar](#como-usar-e-disposições-do-trabalho).

# Estruturas de Dados

## 1 Registros

Como requerido pelo trabalho, a estrutura de registro é definida:

```C++
const uint64_t NAME_SIZE = 1000;

typedef struct Record {
   typedef long key_t;
   
   key_t key;
   int   data;
   char  name[NAME_SIZE + 1];
} Record;
```

Sendo o maior comprimento do nome para acomodar um `\0` (terminador nulo), caso necessário, mantendo `NAME_SIZE` caracteres úteis.<br>

A ordenação total do conjunto de `Record`'s, denotada $`\lt`$, é dada, para `Record`'s $`R`$ e $`S`$:

```math
R < S \iff R.key < S.key
```

Quando $`R \lt S`$, $`R`$ é dito _menor_ que $`S`$, analogamente, se $`R \gt S`$, $`R`$ é dito _maior_ que $`S`$. Para esse trabalho, toda árvore $`T = \langle v, E, D \rangle`$ possuirá $`v`$ do tipo `Record`. Quando diz-se um nó é menor/maior que outro, refere-se aos registros contidos nesses nós.

## 2 Listas Encadeadas

### Definição 2A: Lista Encadeada

Uma lista encadeada é um conjunto vazio, $` \emptyset `$, ou um par ordenado $`L = \langle v, M \rangle`$, onde é $`M`$ é uma lista encadeada. Formalmente:

```math
Ll(L) = \iff \emptyset \vee ( L = \langle v, M \rangle \wedge Ll(M) )
```

Em C++, a estrutura de um nó de uma lista encadeada é definida:

```C++
typedef struct Node {
   Record* content;
   Node* next_node;
} Node;
```

### Definição e Implementação 2B: Algoritmo de Busca

De forma simples, a busca em listas encadeadas é dada:

```math
S(L, key) = \begin{cases}
   S(M, key) & \text{| } T = \langle v, M \rangle \wedge v.key \ne key \\
   M & \text{| } T = \langle v, M \rangle \wedge v.key = key
\end{cases}
```

Em código:

```C++
Record* LinkedList::search(Node* node, Record::key_t key) {
   while (node) {
      if (node->content->key == key)
         return node->content;

      node = node->next_node;
   }

   return nullptr;
}
```

#### Análise de Complexidade

A complexidade de tempo da busca, no pior caso, é evidentemente $`O(n + 1)`$, que é o mesmo que $`O(n)`$.

### Definição e Implementação 2C: Algoritmo de Inserção

Assim, em listas encadeadas, a função $`+`$ para a inserção de um novo registro $`N`$ numa lista encadeada é dada:

```math
+(L, N) = \langle N, L \rangle
```

Em C++:

```C++
exit_t LinkedList::insert(Node** node, Record* record) {
   Node* new_node = new (std::nothrow) Node{ record, *node };
   if (!new_node) return BAD_ALLOCATION;

   *node = new_node;
   return SUCCESS;
}
```

#### Análise de Complexidade

A complexidade de tempo da inserção será sempre contante, $`O(1)`$.

## 3 Árvores Binárias

### Definição 3A: Árvore Binária

Uma árvore binária, aqui definida, é um conjunto vazio, $` \emptyset `$, ou uma tripla ordenada $`T = \langle v, E, D \rangle`$, onde $`E`$ e $`D`$ são árvores, $`E`$ é chamada _sub-árvore esquerda_ e $`D`$ é chamada _sub-árvore direita_, e $`v`$ uma variável de conjunto totalmente ordenado<sup>[[1]](#user-content-fnote1)</sup>. Formalmente:

```math
Tree(T) \iff T = \emptyset \vee \left(T = \langle v, E, D \rangle \wedge Tree(D) \wedge Tree(E) \right)
```

Para simplificação, seja $`T = \langle v, E, D \rangle`$, $`T_E`$ denota a sub-árvore esquerda, $`E`$; $`T_D`$ denota a sub-àrvore direita, $`D`$; e $`v[T]`$ denota a variável $`v`$ contida em $`T`$.

Em C++, a estrutura de um nó de uma árvore binária é definida:

```C++
typedef struct Node {
   Record* content;
   Node* left_child;
   Node* rght_child;
   int64_t height;
} Node;
```

### Definição 3B: Relações entre nós

A relação de descendência $`\lhd`$ entre nós ($`T \lhd S`$ lê-se "$`T`$ é descendente de $`S`$") tem intrepretação verdadeira se, e somente se, para $`T \lhd S`$, $`T`$ é filho de $`S`$, ou é filho de um filho de $`S`$ e assim por diante. Recusivamente, isto é, para $`T`$ e $`S`$ árvore não nulas:

* $`\emptyset \lhd \emptyset \iff False`$;
* $`\emptyset \lhd S \iff True`$;
* $`T \lhd \emptyset \iff False`$;
* $`T \lhd S \iff v[T] = v[S_D] \vee v[T] = v[S_E] \vee T \lhd S_D \vee T \lhd S_E`$.

A relação $`\unlhd`$ é definida como descendência ou igualdade, definida da seguinte maneira:

```math
T \unlhd S \iff v[T] = v[S] \vee T \lhd S
```

Seguindo da definição de descendência, alguma nomenclatura é definida:

#### i) Nós Filhos
Nós filhos são nós imediatamente descendêntes de uma outro nó, por exemplo, $`T_E`$ e $`T_D`$ são _nós filhos_ de um nó $`T`$.

#### ii) Nó Pai
Analogamente, um nó é pai de algum outro nó se o segundo é descendente imediato do primeiro, em outras palavras o primeiro é _ascendente_ imediato do segundo, por exemplo, $`T`$ é referido como _nó pai_ dos nós $`T_E`$ e $`T_D`$.

#### iii) Nó Irmão
Um _nó irmão_ é o nó complementar àquele mencionado, $`T_D`$ é nó irmão de $`T_E`$ e vice-versa. Um nó não é irmão de si mesmo.

#### iv) Nós Folha
Um nó é denominado _nó folha_ se todos seus nós filhos forem $`\emptyset`$. O nó $`T = \langle v, \emptyset, \emptyset \rangle`$ é dito um nó folha. 

#### v) Nó Raiz
Por fim, um _nó raiz_ é aquele nó ascendente a todos os outros nós de uma árvore específica, ou seja, todo nó numa árvore é descendente do nó raiz ou é o próprio nó raiz.

### Definição 3C: Árvore Binária de Busca

Uma árvore binária de busca é uma árvore binaria que satisfaz a seguinte propriedade, para todo nó $`T = \langle v, E, D \rangle`$, todo nó na sub-árvore esquerda é menor que $`v`$, e todo nó na sub-árvore direita é maior que $`v`$. É entendido que cada nó tenha uma chave única por árvore, isto é, uma chave nunca repete. Recursivamente:

```math
STree(T) \iff T = \emptyset \vee \left(( T_E = \emptyset \vee v[T_E] < v[T] ) \wedge (T_D = \emptyset \vee v[T_D] > v[T]) \wedge STree(T_E) \wedge STree(T_D) \right)
```

### Definição 3D: Altura de Árvores Binárias

A altura de uma árvore binária é dada pela quantidade de nós no caminho do raiz até o nó folha mais distante. A altura de uma árvore $`T`$ é denotada $`h(T)`$, definida formalmente:

```math
h(T) = \begin{cases}
   -1 & \text{| } T = \emptyset\\
   1 + \max \lbrace h(T_E), h(T_D) \rbrace & \text{| caso contrário}.
\end{cases}
```

### Teorema 3E: A computação da altura de uma árvore tem complexidade linear no pior caso

Pelas instancias recursivas da função $`h`$, é visível que pelo menos todo nó definido é visitado, e aqueles nós que têm um único filho ainda adicionam uma vericação a um nó $`\emptyset`$. No pior caso, todo nó tem um único filho, exceto por um nó (a existência de um nó folha é obrigatória numa árvore com nós finitos), assim, com $`n`$ nós, seriam feitas $`2(n - 1) + 1`$ iterações da função, assim, a complexidade é $`O(n)`$. Esse fato motiva a inclusão do atributo `height` na estrutura `Node`.

### Implementação 3F: Algoritmo de Busca

Grande parte das operações sobre uma árvore vão se basear em alguma forma de algoritmo de busca, para isso, assume-se que entradas fornecidas são árvores binárias de busca. Como uma árvore de buscar porta a propriedade que todo nó à esquerda é menor e à direita é maior, similar à busca binária, o espaço de busca é reduzido em blocos, continuando a busca apenas na sub-árvore que pode conter o dado nó.

```math
S(T, key) = \begin{cases}
   S(T_E, key) & \text{| } key < v[T].key\\ 
   S(T_D, key) & \text{| } key > v[T].key\\ 
   v[T] & \text{| } v[T].key = key
\end{cases} 
```

Em C++ algo similar é dado:

```C++
Record* Tree::search(Tree::Node* node, Record::key_t key) {

   while (node) {

      if (false);

      else if (key < node->content->key)
         node = node->left_child;

      else if (key > node->content->key)
         node = node->rght_child;

      else /* key == node->content->key */
         return node->content;
   }

   return nullptr;
}
```

Analogo à função $`S`$, que é indefinida se a chave não existir na árvore, a função `Tree::search` retorna um ponteiro nulo nesse caso.

#### Análise de Complexidade

A natureza de divisão e conquista, mascarada pela iteratividade, mas ainda presente, pode indicar erroneamente a complexidade de `Tree::search` como $`O(\log n)`$, entretando, no pior caso, uma árvore pode ser configurada como uma _lista encadeada_, como por exemplo

```math
T = \langle v_0, \emptyset, \langle v_1, \emptyset, \langle  v_2, \emptyset, \langle  v_3, \emptyset, \emptyset \rangle \rangle \rangle \rangle
```

tem 4 nós sempre arranjandos à sub-árvore direita, a busca de nó ausente maior que $`v_3`$ tomaria ao menos 4 interações do laço. Assim a complexidade de `Tree::search` é $`O(n)`$. A complexidade de espaço é contante, $`O(1)`$, pois a quantidade de variáveis usadas não muda com base na entrada.

### Implementação 3G: Algoritmo de inserção

Para inserir um novo nó numa árvore binária de busca, é realizada uma busca tradicional e, quando se encotrar um nó nulo, esse nó é posto nessa posição. Seja $`+`$ a função de inserção, $`T`$ uma árvore e $`N`$ o novo registro:

```math
+(T, N) = \begin{cases}
   \langle v, +(E, N), D \rangle & \text{| } T = \langle v, E, D \rangle \wedge N < v \\
   \langle v, E, +(D, N) \rangle & \text{| } T = \langle v, E, D \rangle \wedge N > v \\
   \langle v, \emptyset, \emptyset \rangle & \text{| } T = \emptyset
\end{cases}
```

Em C++:

```C++
exit_t Tree::insert(Node** node, Record* record) {

   Node* new_node = new Node{ record, nullptr, nullptr, 0 };
   if (!new_node) return BAD_ALLOCATION;

   while (*node) {

      if (false);

      else if (record->key < (*node)->content->key)
         node = &(*node)->left_child;
      
      else if (record->key > (*node)->content->key) 
         node = &(*node)->rght_child;
      
      else /* record->key == (*node)->content->key */
         return KEY_ALREADY_EXISTS;
   }

   *node = new_node;
   return SUCCESS;
}
```

Entretanto, se é recordado, em código, a estrutura das árvores, `Node`, possuem um campo de altura, `height`, motivado pela complexidade de $`h`$. Após a inserção de um nó, a altura dessa árvore pode precisar ser atualizada. Note que o único _caminho_ que pode ter sua altura aumentada é aquele pelo qual o nó "passou", desde a raiz até a ponta onde foi inserido, esse caminho é chamado _caminho de incremento_. Ademais, se nó irmão de algum nó no caminho de incremento for mais alto, então, daquele nó para raiz a altura se manterá inalterada.

Seja $`T`$ o nó no caminho de incremento, $`T_I`$ seu irmão e $`P`$ seu pai. Sabe-se que $`T`$ se tornará a nova origem do caminho de incremento se, e somente se $`h(T_I) \gt h(T)`$. Como o nó irmão não é sempre garantido ser definido, uma verificação teria que ser feita, entretando, a altura do nó pai é definida $`1 + \max \lbrace h(T), h(T_I) \rbrace `$. Assim, tem-se informação suficiente para dizer que $`h(P) = 1 + h(T_I) \implies h(P) - 1 = h(T_I)`$, substituindo, tem-se $`h(P) - 1 \gt h(T) \implies h(P) \gt h(T) + 1`$. Logo, a nova origem é determinada quando $`h(T) + 1 < h(P)`$ tenha interpretação verdadeira.

Dessa forma, em C++:

```C++
exit_t Tree::insert(Node** node, Record* record) {

   Node* new_node = new Node{ record, nullptr, nullptr, 0 };
   if (!new_node) return BAD_ALLOCATION;

   Node* increment_path = *node;
   int64_t parent_height = safe_access(increment_path, height, -1);

   while (*node) {

      if ((*node)->height + 1 < parent_height)
         increment_path = *node;

      parent_height = (*node)->height;
      if (false);

      else if (record->key < (*node)->content->key)
         node = &(*node)->left_child;
      else if (record->key > (*node)->content->key) 
         node = &(*node)->rght_child;
      else /* record->key == (*node)->content->key */
         return KEY_ALREADY_EXISTS;
   }

   if (!parent_height) while (increment_path) {
      increment_path->height++;

      increment_path = record->key < increment_path->content->key ?
         increment_path->left_child : increment_path->rght_child;
   }

   *node = new_node;
   return SUCCESS;
}
```

Uma última observação, o loop de incrementação só é entrado se a altura do nó pai do novo nó é 0, pois esse caso não é identificado (e eliminado) pela condicional adicionada.

#### Análise de Complexidade

Analogo ao constatado na [Análise de Complexidade do Algoritmo de Busca](#análise-de-complexidade), a complexidade de inserção é $`O(n)`$, visitando $`2n`$ nós, numa árvore com $`n`$ nós, no pior caso. A complexidade de espaço é, também, contante, $`O(1)`$.

## 4 Árvore Binária AVL

Nomeada por seus criadores Georgy Maximovich **A**delson-**V**elsky e Evgenii Mikhailovich **L**andis.

### Definição 4A: Fator de Balanceamento

Dado um nó $`T`$ qualquer, seu fator de balanceamento é dado, $`fb(T) = h(T_D) - h(T_E)`$, uma versão analoga, definida $`fb(T) = h(T_E) - h(T_D)`$, também é válida e apenas inverteria o sinal a respeito do fator de balanceamento. Aqui, será usado:

```math
fb(T) = h(T_D) - h(T_E)
```

### Definição 4B: Árvore Binária Balanceada

Uma árvore binária balanceada é uma árvore binária de busca que todo nó $`T`$ tem fator de balancemanto $`fb(T) \in \lbrace -1, 0, 1 \rbrace`$

Quando uma árvore AVL possui algum nó com fator de balanceamento fora do conjunto $`\lbrace -1, 0, 1 \rbrace`$, um balanceamento do nó tem que ser feito. Balanceamentos são feito das folhas para a raiz, isto é, nós mais baixos desbalanceados são balenceados primeiro. O balanceamento é dado por meio das chamadas _rotações_ nesses nós.

### Definição e Implementação 4C: Rotações

Rotações, como o nome sugere, são reajamentos de nós de uma forma predefinida, há dois tipos básicos de rotação, a rotação esquerda e a rotação direita, e dois tipo compostos rotação direita-esquerda e rotação esquerda-direita, definidas a seguir. Os casos de desbalanceamento tratados abaixo são aquele gerados após a inserção de um único nó, assim, um nó $`T`$ desbalanceado nessa condição tem $`fb(T) = -2`$ ou $`fb(T) = 2`$.

#### i) Rotação Simples à Esquerda

A rotação esquerda, denotada pela função $`R_E`$ é dada:

```math
R_E(\langle v_A, T_0, \langle v_B, T_1, T_2 \rangle \rangle) = \langle v_B, \langle v_A, T_0, T_1 \rangle, T_2 \rangle
```

Nota-se que $`R_E`$ é indefinido para um nó $`T`$ com $`T_D = \emptyset`$.

Seja a árvore $`A = \langle v, T_0, B \rangle`$, $`B = \langle u, T_1, T_2 \rangle`$, sua rotação esquerda, $`R_E(A)`$ é dada:

```
   A                                         B
  / \          A - B          A - B         / \
 T0  B   =>   /   / \   =>   / \   \  =>   A  T2
    / \      T0  T1 T2      T0 T1  T2     / \
   T1 T2                                 T0 T1
```

É notável que o nó $`T_2`$ subiu um nível na árvore e o nó $`T_0`$ desceu um nível, como $`A`$ é nó desbalanceado antes da rotação, $`fb(A) = 2`$. O nó $`B`$ deve ser balanceado, pois balanceamentos ocorrem das folhas para a raiz, se $`T_1`$ fosse o nó mais alto, por ele manter sua influência de altura, fazendo o nó $`R_E(A)`$ ser desbalanceado, assim, $` h(T_1) \le h(T_2) `$, entretanto, se $`T_1`$ precisa ter modificado a altura da árvore $`A`$, ou seja, $` h(T_1) < h(T_2) \implies 0 < h(T_2) - h(T_1) = fb(B) `$ é uma condição para a aplicação de uma rotação direita. No total, a configuração das alturas antes da rotação é:

Fixa-se $`h(T_2)`$ como base após a inserção que gerou desbalanceamento.

Como $` 0 \lt fb(B) `$ e $` fb(B) \in \lbrace -1, 0, 1 \rbrace `$, tem-se $`fb(B) = h(T_2) - h(T_1) = 1 `$. <br>
Logo, $` h(T_1) = h(T_2) - 1 `$;

Como $` h(B) = 1 + \max \lbrace h(T_1), h(T_2) \rbrace  = 1 + \max \lbrace h(T_2) - 1, h(T_2) \rbrace `$.<br>
Assim, $` h(B) = h(T_2) + 1 `$;

Como $` fb(A) = 2 = h(B) - h(T_0) = h(T_2) + 1 - h(T_0) `$.<br>
Dessa forma $` h(T_0) = h(T_2) - 1 `$;

Assim $` h(A) = 1 + \max \lbrace h(T_0), h(B) \rbrace = 1 + \max \lbrace h(T_2) - 1, h(T_2) + 1 \rbrace `$,<br>
$` h(A) = h(T_2) + 2 `$.

Após a rotação, tem-se:

* $` h(A \unlhd R_E(A)) = 1 + \max \lbrace h(T_0), h(T_1) \rbrace  = 1 + h(T_2) - 1 = h(T_2) `$
* $` h(B \unlhd R_E(A)) = 1 + \max \lbrace h(A \unlhd R_E(A)), h(T_2) \rbrace  = 1 + h(T_2) `$

Note que a altura das subárvores $`T_0`$, $`T_1`$ e $`T_2`$ não são modificadas pela rotação. 

Assim, como $`T_2 =`$`(*node)->rght_child->rght_child`, o código da rotação é dado:

```C++
void Tree::AVL::smpl_left_rotation(Node** node) {
   Node* rght_subtree = (*node)->rght_child;

   (*node)->height = rght_subtree->rght_child->height;
   rght_subtree->height = 1 + (*node)->height;

   (*node)->rght_child = rght_subtree->left_child;
   rght_subtree->left_child = *node;
   *node = rght_subtree;
}
```

#### ii) Rotação Simples à Direita

A rotação esquerda, denotada pela função $`R_D`$ é dada:

```math
R_D(\langle v_A, \langle v_B, T_0, T_1 \rangle, T_2 \rangle) = \langle v_B, T_0, \langle v_A, T_1, T_2 \rangle \rangle
```

```
     A                                  B
    / \       A - B        A - B       / \
   B  T2 =>  / \   \  =>  /   / \  => T0  A
  / \       T0 T1  T2    T0  T1 T2       / \
 T0 T1                                  T1 T2
```

Nota-se que $`R_D`$ é indefinido para um nó $`T`$ se $`T_E = \emptyset`$. Ademais, $`R_D`$ é a função inversa de $`R_E`$. Assim, de forma analoga, uma rotação direita deve ser feita quando um nó $`T`$ tem $`fb(T) = -2`$ e $`fb(T_E) = -1`$. O código é dado:

```C++
void Tree::AVL::smpl_rght_rotation(Node** node) {
   Node* left_subtree = (*node)->left_child;

   (*node)->height = left_subtree->left_child->height;
   left_subtree->height = 1 + (*node)->height;

   (*node)->left_child = left_subtree->rght_child;
   left_subtree->rght_child = *node;
   *node = left_subtree;
}
```

#### iii) Rotação Dupla Direita-Esquerda

A rotação direita-esquerda, $`R_{DE}`$, supre o caso onde, para um nó $`T`$, $`fb(T) = 2`$ e $`fb(T_D) = -1`$, dada com base nas rotações simples mostradas em **i)** e **ii)**:

```math
R_{DE}(\langle v, E, D \rangle) = R_E(\langle v, E, R_D(D) \rangle)
```

```
     A            A
    / \          / \          _C_
   B  T3        C  T3        /   \
  / \    =>    / \     =>   B     A
 T0  C        B  T2        / \   / \
    / \      / \          T0 T1 T2 T3
   T1 T2    T0 T1
```

Apesar de ser definida como um aninhamento de rotações, em código, essa será definida de maneira diferente, que encapsula (simplifica) as operações feitas. Os detalhes para o ajustamento da altura são deixados como exercício para o leitor, dado que esse segue diretamente dos resultados anteriores, o mesmo será válido para a próxima rotação. Em código:

```C++
void Tree::AVL::rght_left_rotation(Node** node) {
   Node* midd_subtree = (*node)->rght_child->left_child;

   (*node)->rght_child->left_child = midd_subtree->rght_child;
   midd_subtree->rght_child = (*node)->rght_child;

   (*node)->rght_child = midd_subtree->left_child;
   midd_subtree->left_child = *node;

   midd_subtree->left_child->height = midd_subtree->height;
   midd_subtree->rght_child->height = midd_subtree->height;
   midd_subtree->height++;

   *node = midd_subtree;
}
```

#### iv) Rotação Dupla Esquerda-Direita

A rotação esquerda-direita, $`R_{ED}`$, supre o caso onde, para um nó $`T`$, $`fb(T) = -2`$ e $`fb(T_D) = 1`$, dada, também com base nas rotações simples mostradas em **i)** e **ii)**:

```math
R_{ED}(\langle v, E, D \rangle) = R_D(\langle v, R_E(E), D \rangle)
```

```
   A          A
  / \        / \             _C_
 T0  B      T0  C           /   \
    / \  =>    / \    =>   A     B
   C  T3      T1  B       / \   / \
  / \            / \     T0 T1 T2 T3
 T1 T2          T2 T3
```

Seguindo do já dito anteriormente, tem-se:

```C++
void Tree::AVL::left_rght_rotation(Node** node) {
   Node* midd_subtree = (*node)->left_child->rght_child;

   (*node)->left_child->rght_child = midd_subtree->left_child;
   midd_subtree->left_child = (*node)->left_child;

   (*node)->left_child = midd_subtree->rght_child;
   midd_subtree->rght_child = *node;

   midd_subtree->left_child->height = midd_subtree->height;
   midd_subtree->rght_child->height = midd_subtree->height;
   midd_subtree->height++;

   *node = midd_subtree;
}
```

#### Análise de Complexidade

Toda operação de rotação executa em tempo constante, isto é, $`O(1)`$, assim com em espaço constante, $`O(1)`$.

### Teorema 4D: Uma operação de rotação, quando executada propriamente, retorna um nó menor que o nó de entrada

Com operação de rotação, entende-se dizer qualquer uma dentre $`R_D`$, $`R_E`$, $`E_{DE}`$ e $`R_{ED}`$, mesmo que as duas últimas seja duplas das duas primeiras. Ademais, com executada propriamente, quer-se dizer que é executada quando as condições requeridas são satisfeitas.

Para as rotações simples, esquerda e direita, a altura de um $`T`$ desbalanceada é $`2 + h(T_{DD})`$ e $`2 + h(T_{EE})`$, respectivamente, já a altura de $`R_E(T)`$ e $`R_D(T)`$ são, respectivamente, $`1 + h(T_{DD})`$ e $`1 + h(T_{EE})`$. Logo, a altura diminui uma unidade.

Para a rotaçõa dupla direita-esquerda, seja $`T`$ o nó desbalanceado, $`h(R_D(T_D)) = 1 + h(T_{DEE})`$, $`h(T_D) = 2 + h(T_{DEE})`$ e $`h(T_E) < h(T_D)`$, ou seja, a altura final, também, diminui por uma unidade. Analogamente, o mesmo se dá para a rotação dupla esquerda-direita.

### Corolário 4E: Uma operação de rotação sempre é suficiente para restaurar o balanceamento perdido após a inserção de um único nó

Seguindo do resultado anterior, uma operação de rotação sempre diminui a altura de alguma subárvore, tal subárvore que teve a altura incrementada pela inserção de um novo nó, ou seja, a altura é preservada acima do nó mais baixo que passou por balanceamento. Logo, a afirmação é verdadeira.

### Implementação 4F: Inserção em Árvore AVL

Pelo Corolário anterior, é evidente que apenas um nó precisa ser lembrado à propósito de balanceamento, assim, pertindo que um algoritmo iterativo _in-place_, isto é, complexidade de espaço $`O(1)`$. Todo conceito relacionado ao caminho de incremento é mantido para este algoritmo. Um novo conceito introduzido é o _nó de balanceamento_, este sendo o nó que sofre as rotações para balanceamento da árvore. Como indentificar esse?

Se o leitor recorda da [definição de fator de balanceamento](#definição-4a-fator-de-balanceamento) e de [árvores binárias balanceadas](#definição-4b-árvore-binária-balanceada), um nó $`T`$ precisa de balancemento quando $`fb(T) \notin \lbrace -1, 0, 1 \rbrace`$, ou seja, a magnitude da diferença de altura com seu irmão é maior ou igual a 2.

Com base na altura do pai e nó atual, como na inserção típica, não há informação suficiente para determinar se um está desbalanceado, assim o nó irmão, ou melhor, sua altura, terá que ser considerada. Considere a inserção $`+(P, N)`$ seguirá para $`+(T, N)`$, sendo $`T`$ filho de $`P`$, assumindo que está-se (!) sobre um caminho de incremento, tem-se $`h(P) - 1 = h(T) \ge h(T_I) `$, da condição de desbalanceamento seque: 

```math
\begin{align*}
   h(T) - h(T_I) > 1
      &\implies h(P) - 1 - h(T_I) > 1 \\
      &\implies h(P) > 2 + h(T_I)
\end{align*}
```

Como o incremento na altura de $`P`$ não teria sido aplicado ainda, a condição $`h(P) > 1 + h(T_I)`$ a avaliada.

O raciocínio acima baseia-se na suposição que a avaliação ocorre dentro de um caminho de incremento, o que não é o caso, nem todo inserção incrementará o tamanho da árvore, para resolver esse problema, toda vez que o caminho de incremento muda de origem, a necessidade de balanceamento é tornada falsa e, se a altura do nó o qual o registro $`N`$ foi inserido é diferente de zero, nenhum incremento ou balanceamento é considerado.

Assim, segue o, demasiado longo, mas funcional, código:

```C++
exit_t Tree::AVL::insert(Tree::Node** node, Record* record) {
   
   Node* new_node = new Node{ record, nullptr, nullptr, 0 };
   if (!new_node) return BAD_ALLOCATION;

   Node** balance_node = node;
   Node** increment_path = node;

   int64_t parent_height = safe_access(*node, height, -1);
   bool balance = false;
   bool side = false;

   while (*node) {

      if ((*node)->height + 1 < parent_height) {
         increment_path = node;
         balance = false;
      }

      parent_height = (*node)->height;

      if (false) {

      } else if (record->key < (*node)->content->key) {

         if (parent_height > 1 + safe_access((*node)->rght_child, height, -1)) {
            balance_node = node;
            balance = true;
            side = true;
         }

         node = &(*node)->left_child;

      } else if (record->key > (*node)->content->key) {

         if (parent_height > 1 + safe_access((*node)->left_child, height, -1)) {
            balance_node = node;
            balance = true;
            side = false;
         }

         node = &(*node)->rght_child;

      } else /* record->key == (*node)->content->key */ {
         return KEY_ALREADY_EXISTS;
      }
   }

   if (parent_height) {
      *node = new_node;
      return SUCCESS;
   }

   if (balance)
      increment_path = balance_node;

   while (*increment_path) {
      (*increment_path)->height++;

      increment_path = record->key < (*increment_path)->content->key ?
         &(*increment_path)->left_child : &(*increment_path)->rght_child;
   }

   *node = new_node;

   if (balance) {

      if (side) {

         if (record->key > (*balance_node)->left_child->content->key)
            left_rght_rotation(balance_node);
         else smpl_rght_rotation(balance_node);

      } else {

         if (record->key < (*balance_node)->rght_child->content->key)
            rght_left_rotation(balance_node);
         else smpl_left_rotation(balance_node);
      }
   }

   return SUCCESS;
}
```

Um último detalhe a ressaltar, se a árvore precisa de balanceamento, ou seja, `balance` é `true`, o incremento ocorrerá apenas a partir do nó desbalancedo, algo que a efetividade é garantida pelo [Teorema 4D](#teorema-4d-uma-operação-de-rotação-quando-executada-propriamente-retorna-um-nó-menor-que-o-nó-de-entrada).

#### Análise de Complexidade

A complexidade de tempo é $`O(\log n)`$, que será discutido a frente, já a complexidade de espaço é constante, $`O(1)`$.

### Teorema 4G: Complexidade Logarítmica de Tempo da Busca numa Árvore AVL

O [algoritmo de busca](#implementação-3a-algoritmo-de-busca) definido para árvores de busca é o mesmo para árvores AVL, entretanto, pela estruturação da árvore AVL, a complexidade de tempo é diferente daquela da árvore de busca arbitrária.

É evidente que a complexidade de tempo da função de busca é $`O(h + 1)`$, para um nó inexistente que seque pelo caminho mais longo, sendo $`h`$ a da altura da árvore, logo, para classificar a complexidade para AVL's, é preciso estabelecer limites para sua altura. Seja $`n`$ a quantidade de nós daqui em diante.

O limite inferior é obtido agrupando perfeitamente, cada nível $`V`$ (sendo o nível da raiz $`0`$) possui $`2^V`$ nós, assim, ao todo, uma árvore completa (todo nó possui dois filhos até um nível $`U`$ onde todo nó é folha) de altura $`h`$ possui a seguinte quantidade de nós:

```math
\sum_{i = 0}^{h}{2^i} = 2^{h + 1} - 1
```

Assim, $`n = 2^{h + 1} - 1 \implies \log_2(n + 1) = h + 1 \implies h = \log_2(n + 1) - 1`$, entretanto, como $`h`$ e $`n`$ são natural, tem-se $`h = \lceil \log_2(n + 1) - 1 \rceil = \lceil \log_2 n \rceil`$. Assim, tem-se o $`h`$ mínimo. Para o $`h`$ máximo, seja a sequência $`(H_h)`$, cujo $`h`$-ésimo termo diz o mínimo de nós que, mantendo a árvore balanceada, deixam a árvore daquela altura. Tem-se $`H_0 = 1`$ e $`H_1 = 2`$ como base, seguindo, para que o fator de balanceamento seja sempre $`-1`$ ou $`1`$, $`H_h = 1 + H_{h - 1} + H_{h - 2}`$, sendo $`1`$ referente à raiz que conecta os dois ramos e $`H_{h - 1}`$ e $`H_{h - 2}`$ têm um diferença de magnitude $`1`$. Assim:

* $`H_0 = 1`$
* $`H_1 = 2`$
* $`H_{h} = 1 + H_{h - 1} + H_{h + 1} `$

É evidente que a sequência $`(H_n)`$ é próxima à sequência de Fibonacci, $`(F_n)`$, definida $`F_0 = F_1 = 1`$ e $`F_n = F_{n - 1} + F_{n - 2}`$. Seja $`(G_n)`$ uma sequência definida a partir da sequência $`(H_n)`$, dado $`G_n - 1 = H_n`$. Assim, no passo recursivo:

```math
\begin{align*}
   H_{n} = 1 + H_{n - 1} + H_{n - 2} 
      &\implies G_{n} - 1 = 1 + (G_{n - 1} - 1) + (G_{n - 2} - 1) \\
      &\implies G_{n} - 1 = G_{n - 1} + G_{n - 2} - 1 \\
      &\implies G_{n} = G_{n - 1} + G_{n - 2}
\end{align*}
```

Já nos passos base, $`G_0 = H_0 + 1 = 1 + 1 = 2`$ e $`G_1 = H_1 + 1 = 2 + 1 = 3`$, assim, tem-se que $`G_n = F_{n + 2}`$. Portanto $`H_n = F_{n + 2} - 1`$. O $`n`$-ésimo termo da sequência de Fibonacci é dado por:

```math
F_{n + 1} = \frac{\phi^n - (-\phi)^{-n}}{\sqrt{5}}
```

Sendo $`\phi = \frac{1 + \sqrt{5}}{2}`$. Assim, tem-se:

```math
\begin{aligned}
   H_{h - 1} &= \frac{\phi^h - (-\phi)^{-h}}{\sqrt{5}} - 1 \\
      &\implies H_h = \frac{\phi^{h + 1} - (-\phi)^{-(h + 1)}}{\sqrt{5}} - 1 \\
      &\implies (H_h + 1) \sqrt{5} = \phi^{h + 1} - (-\phi)^{-(h + 1)} \\
      &\implies \phi^{h + 1} (H_h + 1) \sqrt{5} = \phi^{2(h + 1)} - (-1)^{-(h + 1)} \\
      &\implies 0 = \phi^{2(h + 1)} - \phi^{h + 1} (H_h + 1) \sqrt{5} + (-1)^{h} \\
      &\implies \phi^{h + 1} = \frac{(H_h + 1) \sqrt{5} + \sqrt{ ((H_h + 1) \sqrt{5})^2 - 4 (-1)^{h} }}{2} \\
      &\implies \phi^{h + 1} = \frac{(H_h + 1) \sqrt{5} + \sqrt{ 5 (H_h + 1)^2 - 4 (-1)^{h} }}{2} \\
      &\implies h + 1 = \log_\phi\frac{(H_h + 1) \sqrt{5} + \sqrt{ 5 (H_h + 1)^2 - 4 (-1)^{h} }}{2} \\
      &\implies h = \log_\phi\frac{(H_h + 1) \sqrt{5} + \sqrt{ 5 (H_h + 1)^2 - 4 (-1)^{h} }}{2} - 1\\
\end{aligned}
```

$`h`$ não está verdadeiramente isolado, entretanto, naquela forma, esse contribui apenas como um sinal, logo, o limite máximo é dado, novamente, por um termo da ordem logaritmica, logo, pelo _Teorema do confronto_:

Primeiramente, para o limite inferior:

```math
\begin{aligned}
   O(\lceil \log_2(n) \rceil)
      &\subset O(\log_2(n)) \\
      &\subset O(\log(n)) \\
      &\subset O(h) \\
\end{aligned}
```

Por fim, para o limite superior:

```math
\begin{aligned}
   O\left(\log_\phi\frac{(H_h + 1) \sqrt{5} + \sqrt{ 5 (H_h + 1)^2 - 4 (-1)^{h} }}{2} - 1\right)
      &\supset O\left(\log_\phi \left( (H_h + 1) \sqrt{5} + \sqrt{ 5 (H_h + 1)^2 - 4 (-1)^{h}} \right) \right) \\
      &\supset O\left(\log_\phi \left( (H_h + 1) \sqrt{5} + \sqrt{ 5 (H_h + 1)^2 } \right) \right) \\
      &\supset O(\log_\phi (H_h + 1)) \\
      &\supset O(\log_\phi H_h) \\
      &\supset O(\log_\phi n) \\
      &\supset O(\log n) \\
      &\supset O(h) \\
\end{aligned}
```

Assim, a complexidade de busca (e inserção) em Árvores AVL's é $`O(\log n)`$.

# Referências

- https://pages.cs.wisc.edu/~ealexand/cs367/NOTES/AVL-Trees/index.html
- https://docs.ufpr.br/~hoefel/ensino/CM304_CompleMat_PE3/livros/Enderton_Elements%20of%20set%20theory_%281977%29.pdf

# Notas de Rodapé

1. <span id="fnote1">Um conjunto $`S`$ é dito totalmente ordenado por um relação $`\prec \space \subset S \times S`$ se, e somente se, para quaisquer $`x, y, z \in S `$: [1] $`\prec`$ é uma relação transitiva, isto é, se $`x \prec y`$ e $`y \prec z`$, então $`x \prec z`$; e [2] satisfaz tricotomia, isto é, ou $`x \prec y`$ ou $`y \prec x`$ ou $`x = y`$. Um exemplo de ordenação total é dada pela relação $`\lt`$ na reta real $`\text{ℝ}`$.</span> [↩︎](#definição-3a-árvore-binária)
