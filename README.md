# Trabalho Prático I

## Autores

@Alan Barbosa Lima [AlanLima287](https://github.com/AlanLima287)             <br>
@Breno Augusto Braga Oliveira                                                <br>
@Juan Pablo Ferreira Costa [juanzinhobs18](https://github.com/juanzinhobs18) <br>
@Luiz Felipe Melo Oliveira                                                   <br>
@Otávio Gomes Calazans

# Do Trabalho

Esse Trabalho foi desenvolvido como projeto acadêmico da disciplina de ALGORITMOS E ESTRUTURAS DE DADOS III, do Curso de Graduação em Sistemas de Informação da Universidade Federal dos Vales do Jequitinhonha e Mucuri, sob comando da Professora Luciana de Assis.

# Sumário

<strong>[Como Usar](#como-usar)</strong>

<strong>[Árvores Binárias](#árvores-binárias)</strong>

- [1 Definições Básicas](#1-definições-básicas)
   - [Definição 1A: Árvore Binária](#definição-1a-árvore-binária)
   - [Definição 1B: Relações entre nós](#definição-1b-relações-entre-nós)
      - [i) Nós Filhos](#i-nós-filhos)
      - [ii) Nó Pai](#ii-nó-pai)
      - [iii) Nó Irmão](#iii-nó-irmão)
      - [iv) Nós Folha](#iv-nós-folha)
      - [v) Nó Raiz](#v-nó-raiz)
   - [Definição 1C: Registro](#definição-1c-registro)
   - [Definição 1D: Árvore Binária de Busca](#definição-1d-árvore-binária-de-busca)
   - [Definição 1E: Altura de Árvores Binárias](#definição-1e-altura-de-árvores-binárias)
   - [Teorema 1F: A computação da altura de uma árvore tem a complexidade do pior caso $`O(n)`$](#teorema-1f-a-computação-da-altura-de-uma-árvore-tem-a-complexidade-do-pior-caso)
- [2 Implementação de Funcionalidades para os Registros](#2-implementação-de-funcionalidades-para-os-registros)
- [3 Implementação da Árvore Binária de Busca](#3-implementação-da-árvore-binária-de-busca)
   - [Implementação 3A: Algoritmo de Busca](#implementação-3a-algoritmo-de-busca)
      - [Análise de Complexidade](#análise-de-complexidade)
   - [Implementação 3B: Algoritmo de inserção](#implementação-3b-algoritmo-de-inserção)
      - [Análise de Complexidade](#análise-de-complexidade-1)
- [4 Árvore Binária AVL](#4-árvore-binária-avl)
   - [Definição 4A: Fator de Balanceamento](#definição-4a-fator-de-balanceamento)
   - [Definição 4B: Árvore Binária Balanceada](#definição-4b-árvore-binária-balanceada)
   - [Definição e Implementação 4C: Rotações](#definição-e-implementação-4c-rotações)
      - [i) Rotação Esquerda](#i-rotação-esquerda)
      - [ii) Rotação Direita](#ii-rotação-direita)
      - [iii) Rotação Direita-Esquerda](#iii-rotação-direita-esquerda)
      - [iv) Rotação Esquerda-Direita](#iv-rotação-esquerda-direita)
      - [Análise de Complexidade](#análise-de-complexidade-2)
   - [Teorema 4D: Uma operação de rotação, quando executada propriamente, retorna um nó menor que o nó de entrada](#definição-4b-árvore-binária-balanceada)
   - [Corolário 4E: Uma operação de rotação sempre é suficiente para restaurar o balanceamento perdido após a inserção de um único nó](#corolário-4e-uma-operação-de-rotação-sempre-é-suficiente-para-restaurar-o-balanceamento-perdido-após-a-inserção-de-um-único-nó)
   - [Implementação 4F: Inserção em Árvore AVL](#implementação-4f-inserção-em-árvore-avl)

<strong>[Estrutura das dependências](#estrutura-das-dependências)</strong>

<strong>[Referências](#referências)</strong>

# Como Usar

# Árvores Binárias

## 1 Definições Básicas

### Definição 1A: Árvore Binária
Uma árvore binária, aqui definida, é um conjunto vazio, $` \emptyset `$, ou uma tripla ordenada $`T = \langle v, E, D \rangle`$, onde $`E`$ e $`D`$ são árvores, $`E`$ é chamada _sub-árvore esquerda_ e $`D`$ é chamada _sub-árvore direita_, e $`v`$ uma variável de conjunto totalmente ordenado[^1]. Formalmente:<br>

[^1]: Um conjunto $S$ é dito totalmente ordenado por um relação $\prec \space \subset S \times S$ se, e somente se, para quaisquer $x, y, z \in S $: [1] $\prec$ é uma relação transitiva, isto é, se $x \prec y$ e $y \prec z$, então $x \prec z$; e [2] satisfaz tricotomia, isto é, ou $x \prec y$ ou $y \prec x$ ou $x = y$. Um exemplo de ordenação total é dada pela relação $\lt$ no conjunto $\R$.

```math
Tree(T) \iff T = \emptyset \vee \left(T = \langle v, E, D \rangle \wedge Tree(D) \wedge Tree(E) \right)
```

Para simplificação, seja $`T = \langle v, E, D \rangle`$, $`T_E`$ denota a sub-árvore esquerda, $`T_D`$ denota a sub-àrvore direita e $`v[T]`$ denota a variável $`v`$ contida em $`T`$.

Em C++, a estrutura de um nó de uma árvore binária é definida:

```C++
typedef struct Node {
   Record* content;
   Node* left_child;
   Node* rght_child;
   int64 height;
} Node;
```

### Definição 1B: Relações entre nós

A relação de descendência $`\lhd`$ entre nós ($`T \lhd S`$ lê-se "$`T`$ é descendente de $`S`$") tem intrepretação verdadeira se, e somente se, para $`T \lhd S`$, $`T`$ é filho de $`S`$, ou é filho de um filho de $`S`$ e assim por diante. Recusivamente, isto é:

* $`T \lhd \emptyset \iff False`$;<br>
* $`T \lhd S \iff v[T] = v[S_D] \vee v[T] = v[S_E] \vee T \lhd S_D \vee T \lhd S_E`$, para $`S \ne \emptyset`$.

Nota-se que o $`\emptyset`$ é descendente de todo nó que não seja $`\emptyset`$. Ademais, a relação $`\unlhd`$ é definida como descendência ou igualdade, definida da seguinte maneira:

```math
T \unlhd S \iff T = S \vee T \lhd S
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

### Definição 1C: Registro

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

A ordenação total do conjunto de `Record`'s, denotada $`\lt`$, é dada, para `Record`'s $`R`$ e $`S`$:

```math
R < S \iff R.key < S.key
```

Quando $`R \lt S`$, $`R`$ é dito _menor_ que $`S`$, analogamente, se $`R \gt S`$, $`R`$ é dito _maior_ que $`S`$. Para esse trabalho, toda árvore $`T = \langle v, E, D \rangle`$ possuirá $`v`$ do tipo `Record`. Quando diz-se um nó é menor/maior que outro, refere-se aos registros contidos nesses nós.

### Definição 1D: Árvore Binária de Busca

Uma árvore binária de busca é uma árvore binaria que satisfaz a seguinte propriedade, para todo nó $`T = \langle v, E, D \rangle`$, todo nó na sub-árvore esquerda é menor que $`v`$, e todo nó na sub-árvore direita é maior que $`v`$. É entendido que cada nó tenha uma chave única por árvore, isto é, uma chave nunca repete. Recursivamente:

```math
STree(T) \iff T = \emptyset \vee \left(( T_E = \emptyset \vee v[T_E] < v[T] ) \wedge (T_D = \emptyset \vee v[T_D] > v[T]) \wedge STree(T_E) \wedge STree(T_D) \right)
```

### Definição 1E: Altura de Árvores Binárias

A altura de uma árvore binária é dada pela quantidade de nós no caminho do raiz até o nó folha mais distante. A altura de uma árvore $`T`$ é denotada $`h(T)`$, definida formalmente:

```math
h(T) = \begin{cases}
   -1 & \text{| } T = \emptyset\\
   1 + \max \lbrace h(T_E), h(T_D) \rbrace & \text{| caso contrário}.
\end{cases}
```

### Teorema 1F: A computação da altura de uma árvore tem a complexidade do pior caso $`O(n)`$

Pelas instancias recursivas da função $`h`$, é visível que pelo menos todo nó definido é visitado, e aqueles nós que têm um único filho ainda adicionam uma vericação a um nó $`\emptyset`$. No pior caso, todo nó tem um único filho, exceto por um nó (a existência de um nó folha é obrigatória numa árvore com nós finitos), assim, com $`n`$ nós, seriam feitas $`2(n - 1) + 1`$ iterações da função, assim, a complexidade é $`O(n)`$. Esse fato motiva a inclusão do atributo `height` na estrutura `Node`.

## 2. Implementação de Funcionalidades para os Registros

Duas funções para manejamento de instâncias do tipo `Record` serão implementadas:
* Escrever para um registro, com tratamento para caso o nome fornecido tenha mais de mil caracteres:

```C++
void write_record(Record* record, int data, const char* name) {

   for (uint64 i = 0; name[i]; i++) {

      if (i >= NAME_SIZE) {
         record->name[i] = '\0';
         break;
      }

      record->name[i] = name[i];
   }

   record->data = data;

}
```

* Imprimir um registro seguindo um formato fornecido:
   * o formato é configurado:
      * `$0` refere-se ao atributo chave, `key`,
      * `$1` refere-se ao atributo dado, `data`,
      * `$2` refere-se ao atributo nome, `name`,
      * para imprimir o caractere `$`, usa-se a combinação `$$`;
   * o código é dado:

```C++
void print_record(Record* record, const char* format = "{$0, $1, $2}") {

   while (*format) {

      if (*format == '$') {

         format++;
         switch (*format) {

            case '0': std::cout << record->key; break;
            case '1': std::cout << record->data; break;
            case '2': std::cout << record->name; break;

            default:
               std::cout.put(*format);
               break;
         }

      } else std::cout.put(*format);
      format++;
   }
}
```

## 3. Implementação da Árvore Binária de Busca

### Implementação 3A: Algoritmo de Busca

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
Record* Tree::search(Tree::Node* node, key_t key) {

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

### Implementação 3B: Algoritmo de inserção

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
bool Tree::insert(Tree::Node** node, Record* record) {

   Node* new_node = new Node{ record, nullptr, nullptr, 0 };
   if (!new_node) return false;

   while (*node) {

      node = record->key < (*node)->content->key ?
         &(*node)->left_child : &(*node)->rght_child;

   }
   
   *node = new_node;
   return true;
}
```

Entretanto, se é recordado, em código, a estrutura das árvores, `Node`, possuem um campo de altura, `height`, motivado pela complexidade de $`h`$. Após a inserção de um nó, a altura dessa árvore pode precisar ser atualizada. Note que o único _caminho_ que pode ter sua altura aumentada é aquele pelo qual o nó "passou", desde a raiz até a ponta onde foi inserido, esse caminho é chamado _caminho de incremento_. Ademais, se nó irmão de algum nó no caminho de incremento for mais alto, então, daquele nó para raiz a altura se manterá inalterada.

Seja $`T`$ o nó no caminho de incremento, $`T_I`$ seu irmão e $`P`$ seu pai. Sabe-se que $`T`$ se tornará a nova origem do caminho de incremento se, e somente se $`h(T_I) \gt h(T)`$. Como o nó irmão não é sempre garantido ser definido, uma verificação teria que ser feita, entretando, a altura do nó pai é definida $`1 + \max \lbrace h(T), h(T_I) \rbrace `$. Assim, tem-se informação suficiente para dizer que $`h(P) = 1 + h(T_I) \implies h(P) - 1 = h(T_I)`$, substituindo, tem-se $`h(P) - 1 \gt h(T) \implies h(P) \gt h(T) + 1`$. Logo, a nova origem é determinada quando $`h(T) + 1 < h(P)`$ tenha interpretação verdadeira.

Dessa forma, em C++:

```C++
bool Tree::insert(Tree::Node** node, Record* record) {

   Node* new_node = new Node{ record, nullptr, nullptr, 0 };
   if (!new_node) return false;

   Node* increment_path = *node;
   int64 parent_height = increment_path ? increment_path->height : -1;

   while (*node) {

      if ((*node)->height + 1 < parent_height)
         increment_path = *node;

      parent_height = (*node)->height;
      node = record->key < (*node)->content->key ?
         &(*node)->left_child : &(*node)->rght_child;

   }
   
   if (!parent_height) while (increment_path) {
      increment_path->height++;

      increment_path = record->key < increment_path->content->key ?
         increment_path->left_child : increment_path->rght_child;
   }

   *node = new_node;
   return true;
}
```

Uma última observação, o loop de incrementação só é entrado se a altura do nó pai do novo nó é 0, pois esse caso não é identificado (e eliminado) pela condicional adicionada.

#### Análise de Complexidade

Analogo ao constatado na [Análise de Complexidade do Algoritmo de Busca](#análise-de-complexidade), a complexidade de inserção é $`O(n)`$, visitando $`2n`$ nós, numa árvore com $`n`$ nós, no pior caso. A complexidade de espaço é, também, contante, $`O(1)`$.

## 4 Árvore Binária AVL

Nomeada por seus criadores Georgy Maximovich **A**delson-**V**elsky e Evgenii Mikhailovich **L**andis **_[Breno, elabore!]_**.

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

#### i) Rotação Esquerda

A rotação esquerda, denotada pela função $`R_E`$ é dada:

```math
R_E(\langle v_A, T_0, \langle v_B, T_1, T_2 \rangle \rangle) = \langle v_B, \langle v_A, T_0, T_1 \rangle, T_2 \rangle
```

Nota-se que $`R_E`$ é indefinido para um nó $`T`$ com $`T_D = \emptyset`$.

Seja a árvore $`A = \langle v, T_0, B \rangle`$, $`B = \langle u, T_1, T_2 \rangle`$, sua rotação esquerda, $`R_E(A)`$ é dada:

Rotação simples à esquerda

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
void Tree::AVL::left_rotation(Node** node) {
   Node* rght_subtree = (*node)->rght_child;

   (*node)->height = 1 + (rght_subtree->rght_child ? rght_subtree->rght_child->height : 0);
   rght_subtree->height = 1 + (*node)->height;

   (*node)->rght_child = rght_subtree->left_child;
   rght_subtree->left_child = *node;
   *node = rght_subtree;
}
```

#### ii) Rotação Direita

A rotação esquerda, denotada pela função $`R_D`$ é dada:

```math
R_D(\langle v_A, \langle v_B, T_0, T_1 \rangle, T_2 \rangle) = \langle v_B, T_0, \langle v_A, T_1, T_2 \rangle \rangle
```

Nota-se que $`R_D`$ é indefinido para um nó $`T`$ se $`T_E = \emptyset`$. Ademais, $`R_D`$ é a função inversa de $`R_E`$. Assim, de forma analoga, uma rotação direita deve ser feita quando um nó $`T`$ tem $`fb(T) = -2`$ e $`fb(T_E) = -1`$. O código é dado:

```C++
void Tree::AVL::rght_rotation(Node** node) {
   Node* left_subtree = (*node)->left_child;

   (*node)->height = left_subtree->left_child ? left_subtree->left_child->height : 0;
   left_subtree->height = 1 + (*node)->height;

   (*node)->left_child = left_subtree->rght_child;
   left_subtree->rght_child = *node;
   *node = left_subtree;
}
```

#### iii) Rotação Direita-Esquerda

A rotação direita-esquerda, $`R_{DE}`$, supre o caso onde, para um nó $`T`$, $`fb(T) = 2`$ e $`fb(T_D) = -1`$, dada com base nas rotações simples mostradas em **i)** e **ii)**:

```math
R_{DE}(\langle v, E, D \rangle) = R_E(\langle v, E, R_D(D) \rangle)
```

#### iv) Rotação Esquerda-Direita

A rotação esquerda-direita, $`R_{ED}`$, supre o caso onde, para um nó $`T`$, $`fb(T) = -2`$ e $`fb(T_D) = 1`$, dada, também com base nas rotações simples mostradas em **i)** e **ii)**:

```math
R_{ED}(\langle v, E, D \rangle) = R_D(\langle v, R_E(E), D \rangle)
```

#### Análise de Complexidade

Toda operação de rotação executa em tempo constante, isto é, $`O(1)`$, assim com em espaço constante, $`O(1)`$.

### Teorema 4D: Uma operação de rotação, quando executada propriamente, retorna um nó menor que o nó de entrada

Com operação de rotação, entende-se dizer qualquer uma dentre $`R_D`$, $`R_E`$, $`E_{DE}`$ e $`R_{ED}`$, mesmo que as duas últimas seja duplas das duas primeiras. Ademais, com executada propriamente, quer-se dizer que é executada quando as condições requeridas são satisfeitas.

Para as rotações simples, esquerda e direita, a altura de um $`T`$ desbalanceada é $`2 + h(T_{DD})`$ e $`2 + h(T_{EE})`$, respectivamente, já a altura de $`R_E(T)`$ e $`R_D(T)`$ são, respectivamente, $`1 + h(T_{DD})`$ e $`1 + h(T_{EE})`$. Logo, a altura diminui uma unidade.

Para a rotaçõa dupla direita-esquerda, seja $`T`$ o nó desbalanceado, $`h(R_D(T_D)) = 1 + h(T_{DEE})`$, $`h(T_D) = 2 + h(T_{DEE})`$ e $`h(T_E) < h(T_D)`$, ou seja, a altura final, também, diminui por uma unidade. Analogamente, o mesmo se dá para a rotação dupla esquerda-direita.

### Corolário 4E: Uma operação de rotação sempre é suficiente para restaurar o balanceamento perdido após a inserção de um único nó

Seguindo do resultado anterior, uma operação de rotação sempre diminui a altura de alguma subárvore, tal subárvore que teve a altura incrementada pela inserção de um novo nó, ou seja, a altura é preservada acima do nó mais baixo que passou por balanceamento. Logo, o corolário é verdadeiro.

### Implementação 4F: Inserção em Árvore AVL

Diferentemente das implementações 

# Estrutura das Dependências

```mermaid
flowchart BT;
   
   subgraph syslibs[*Bibliotecas de Sistema*]
      subgraph Windows
         Windows.h
         intrin.h
      end
   end
   
   subgraph stdlibs[*Bibliotecas Padronizadas*]
      bittools_incl[
         stdlib.h
         stdint.h
         new
      ]
      stack_incl[
         stdlib.h
         stdint.h
         malloc.h
      ]
      base_incl[
         stdint.h
         stdlib.h
         stdio.h
         iostream
         random
      ]
   end

   subgraph usrlibs[*Bibliotecas Implementadas*]
      stack.h
      bittools.h
   end

   bittools.h[
      bittools.h
      bittools.cpp
   ]

   file.h[
      file.h
      file.cpp
   ]

   linked_list.h[
      linked_list.h
      linked_list.cpp
   ]

   record.h[
      record.h
      record.cpp
   ]

   tree.h[
      tree.h
      tree.cpp
   ]

   base.h --> base_incl

   system.h -- "se Windows" --> Windows.h
      
   stack.h --> stack_incl

   bittools.h --> bittools_incl
   bittools.h -- "se Windows" --> intrin.h

   record.h --> base.h
   
   file.h --> base.h
   file.h --> record.h
   
   linked_list.h --> record.h
   linked_list.h --> base.h
   linked_list.h ---> system.h
   
   tree.h --> record.h
   tree.h --> base.h
   tree.h ---> system.h
   tree.h ---> stack.h
   tree.h ---> bittools.h

   main.cpp --> base.h
   main.cpp --> file.h
   main.cpp --> linked_list.h
   main.cpp --> tree.h
   
   style syslibs fill:#0000, stroke-dasharray: 5
   style stdlibs fill:#0000, stroke-dasharray: 5
   style usrlibs fill:#0000, stroke-dasharray: 5
```

# Referências

https://pages.cs.wisc.edu/~ealexand/cs367/NOTES/AVL-Trees/index.html
https://docs.ufpr.br/~hoefel/ensino/CM304_CompleMat_PE3/livros/Enderton_Elements%20of%20set%20theory_%281977%29.pdf
