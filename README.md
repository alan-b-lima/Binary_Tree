$$
\newcommand{\angbr}[1]{\langle #1 \rangle}
$$

# Trabalho Prático I

## Autores

@Alan Barbosa Lima [AlanLima287](https://github.com/AlanLima287)             <br>
@Breno Augusto Braga Oliveira                                                <br>
@Juan Pablo Ferreira Costa [juanzinhobs18](https://github.com/juanzinhobs18) <br>
@Luiz Felipe Melo Oliveira                                                   <br>
@Otávio Gomes Calazans

# Do Trabalho

Esse Trabalho foi desenvolvido como projeto acadêmico da disciplina de ALGORITMOS E ESTRUTURAS DE DADOS III, com o uso da linguagem de programação C++, do Curso de Graduação em Sistemas de Informação da Universidade Federal dos Vales do Jequitinhonha e Mucuri, sob comando da Professora Luciana de Assis.

# Árvores Binárias

## Definições Básicas

### Definição 1: Árvore Binária
Uma árvore binária, aqui definida, é um conjunto vazio, $\empty$, ou uma tripla ordenada $T = \langle v, E, D \rangle$, onde $E$ e $D$ são árvores ($E$ é chamada _sub-árvore esquerda_ e $D$ é chamada _sub-árvore direita_), e $v$ uma variável de conjunto totalmente ordenado. Formalmente:<br>

$$BTree(T) \iff T = \empty \vee \left(T = \langle v, E, D \rangle \wedge BTree(D) \wedge BTree(E) \right)$$

Para simplificação, seja $T = \angbr{v, E, D}$, $T_E$ denota a sub-árvore esquerda, $T_D$ denota a sub-àrvore direita e $v[T]$ denota a variável $v$ contida em $T$.

Em C++, a estrutura de um nó de uma árvore binária é definida:

```C++
typedef struct Node {
   Record* content;
   Node* left_child;
   Node* rght_child;
   uint64 height;
} Node;
```

### Definição 2: Relações entre nós

A relação de descendência $\lhd$ entre nós ($T \lhd S$ lê-se "$T$ é descendente de $S$") tem intrepretação verdadeira se, e somente se, para $T \lhd S$, T é descendente de S, isto é:

$$T \lhd S \iff T = S_D \vee T = S_E \vee T \lhd S_D \vee T \lhd S_E $$

Ademais, a relação $\unlhd$ é definida como descendência ou igualdade, definida da seguinte maneira:

$$T \unlhd S \iff T = S \vee T \lhd S $$

Seguindo da definição de descendência, alguma nomenclatura é definida:

#### a) Nós Filhos
Nós filhos são nós imediatamente descendêntes de uma outro nó, por exemplo, $T_E$ e $T_D$ são _nós filhos_ de um nó $T$.

#### b) Nó Pai
Analogamente, um nó é pai de algum outro nó se o segundo é descendente imediato do primeiro, em outras palavras o primeiro é _ascendente_ do segundo, por exemplo, $T$ é referido como _nó pai_ dos nós $T_E$ e $T_D$.

#### c) Nó Irmão
Um _nó irmão_ é o nó complementar àquele mencionado, $T_D$ é nó irmão de $T_E$ e vice-versa. Um nó não é irmão de si mesmo.

#### d) Nós Folha
Um nó é denominado _nó folha_ se todos seus nós filhos forem $\empty$. O nó $T = \angbr{ v, \empty, \empty }$ é dito um nó folha. 

#### e) Nó Raiz
Por fim, um _nó raiz_ é aquele nó ascendente a todos os outros nós de uma árvore específica, ou seja, todo nó numa árvore é descendente do nó raiz ou é o próprio nó raiz.

### Definição 3: Registro

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

### Definição 4: Árvore Binária de Busca

Uma árvore binária de busca é uma árvore binaria que satisfaz a seguinte propriedade, para todo nó $T = \langle v, E, D \rangle$, todo nó na sub-árvore esquerda é menor que $v$, e todo nó na sub-árvore direita é maior que $v$. É entendido que cada nó tenha uma chave única por árvore, isto é, uma chave nunca repete. Recursivamente:

$$BSTree(T) \iff T = \empty \vee \left(( T_E = \empty \vee v[T_E] < v[T] ) \wedge (T_D = \empty \vee v[T_D] > v[T]) \wedge BSTree(T_E) \wedge BSTree(T_D) \right)$$

### Definição 5: Altura de Árvores Binárias

A altura de uma árvore binária é dada pela distância do nó raiz até o nó mais distante. A altura de uma árvore $T$ é denotada $h(T)$, definida formalmente:

$$ h(T) = \begin{cases}
   0 & \text{| } T = \empty\\ 
   0 & \text{| } T_E = T_D = \empty\\ 
   1 + max\{ h(T_E), h(T_D) \} & \text{| caso contrário}.
\end{cases} $$

### Teorema 1: A computação da altura de uma árvore tem a complexidade do pior caso $O(n)$

Pelas instancias recursivas da função $h$, é visível que pelo menos todo nó definido é visitado, e aqueles nós que têm um único filho ainda adicionam uma vericação a um nó $\empty$. No pior caso, todo nó tem um único filho, exceto por um nó (a existência de um nó folha é obrigado numa árvore com nó finitos), assim, com $n$ nós, seriam feitas $2(n - 1) + 1$ iterações da função, assim, a complexidade é $O(n)$. Esse fato motiva a inclusão do atributo `height` na estrutura `Node`.

## Implementação de Funcionalidades para os Registros

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

      }
      else std::cout.put(*format);

      format++;
   }
}
```

## Implementação da Árvore Binária de Busca

### Implementação 1: Algoritmo de Busca

Grande parte das operações sobre uma árvore vão se basear em alguma forma de algoritmo de busca, para isso, assume-se que entradas fornecidas são árvores binárias de busca. Como uma árvore de buscar porta a propriedade que todo nó à esquerda é menor e à direita é maior, similar à busca binária, o espaço de busca é reduzido em blocos, continuando a busca apenas na sub-árvore que pode conter o dado nó.

$$ S(T, key) = \begin{cases}
   S(T_E, key) & \text{| } key < v[T].key\\ 
   S(T_D, key) & \text{| } key > v[T].key\\ 
   v[T] & \text{| } v[T].key = key
\end{cases} $$

Em C++ algo similar é dado:

```C++
Record* Tree::search(Tree::Node* node, key_t key) {

   while (node) {

      if (key < node->content->key)
         node = node->left_child;

      if (key > node->content->key)
         node = node->rght_child;

      else /* key == node->content->key */
         return node->content;
   }

   return nullptr;
}
```

Analogo à função $S$, que é indefinida se a chave não existir na árvore, a função `Tree::search` retorna um ponteiro nulo nesse caso.

#### Análise de Complexidade:

A natureza de divisão e conquista, mascarada pela iteratividade, mas ainda presente, pode indicar erroneamente a complexidade de `Tree::search` como $O(\log n)$, entretando, no pior caso, uma árvore pode ser configurada como uma _lista encadeada_, como por exemplo

$$ T = \angbr{ v_0, \empty, \angbr{ v_1, \empty, \angbr{ v_2, \empty, \angbr{ v_3, \empty, \empty } } } } $$

tem 4 nós sempre arranjandos à sub-árvore direta, a busca de nó ausente maior que $v_3$ tomaria ao menos 4 interações do laço. Assim a complexidade de `Tree::search` é $O(n)$.

### Implementação 2: Algoritmo de inserção

Para inserir um novo nó numa árvore binária de busca, é realizada uma busca tradicional e, quando se encotrar um nó nulo, esse nó é posto nessa posição. Seja $+$ a função de inserção, $T$ uma árvore e $N$ o novo registro:

$$ +(T, N) = \begin{cases}
   \angbr{ v, +(E, N), D } & \text{| } T = \angbr{v, E, D} \wedge N < v \\
   \angbr{ v, E, +(D, N) } & \text{| } T = \angbr{v, E, D} \wedge N > v \\
   \angbr{ v, \empty, \empty } & \text{| } T = \empty
\end{cases} $$

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

Entretanto, se é recordado, em código, a estrutura das árvores, `Node`, possuem um campo de altura, `height`, motivado pela complexidade de $h$. Após a inserção de um nó, a altura dessa árvore pode precisar ser atualizada. Note que o único _caminho_ que pode ter sua altura aumentada é aquele pelo qual o nó "passou", desde a raiz até a ponta onde foi inserido, esse caminho é chamado _caminho de incremento_. Ademais, se nó irmão de algum nó no caminho de incremento for mais alto, então, daquele nó para raiz a altura se manterá inalterada. 

Como o nó irmão não é sempre garantido ser definido, uma verificação teria que ser feita, entretando, a altura do nó pai, com filhos, é definida $1 + max\{ h(T_E), h(T_D) \}$ e, como basta identificar se o irmão é mais alto, a negação disso é o nó no caminho de incremento ter a altura do pai menos 1. Assim, em código, a altura do pai é armazenada e comparada à do filho para definir o novo começo do caminho de incremento, e, para evitar underflow, 1 é somado à altura do filho, ao invés de subtraído da altura do pai. Dessa forma, em C++:

```C++
bool Tree::insert(Tree::Node** node, Record* record) {

   Node* new_node = new Node{ record, nullptr, nullptr, 0 };
   if (!new_node) return false;

   Node* increment_path = *node;
   uint64 height = increment_path ? increment_path->height : 0;

   while (*node) {

      if ((*node)->height + 1 < height)
         increment_path = *node;

      node = record->key < (*node)->content->key ?
         &(*node)->left_child : &(*node)->rght_child;

   }
   
   if (!height) while (increment_path) {
      increment_path->height++;

      increment_path = record->key < increment_path->content->key ?
         increment_path->left_child : increment_path->rght_child;
   }

   *node = new_node;
   return true;
}
```

Uma última observação, o loop de incrementação só é entrado se a altura do nó pai do novo nó é 0, pois esse caso não é identificado pela condicional adicionada.

#### Análise de Complexidade

Analogo ao constatado na [Análise de Complexidade do Algoritmo de Busca](#análise-de-complexidade), a complexidade de inserção é $O(n)$, visitando $2n$ nós, numa árvore com $n$ nós, no pior caso.

## Árvore Binária AVL

Nomeada por seus criadores Georgy Maximovich **A**delson-**V**elsky e Evgenii Mikhailovich **L**andis [Breno, elabore!].

### Definição 6: Fator de Balanceamento

Dado um nó $T$ qualquer, seu fator de balanceamento é dado, $fb(T) = h(T_D) - h(T_E)$, uma versão analoga, definida $fb(T) = h(T_E) - h(T_D)$, também é válida e apenas inverteria o sinal de tudo a respeito do fator de balanceamento. Aqui, será usado:

$$fb(T) = h(T_D) - h(T_E)$$

### Definição 7: Árvore Binária Balanceada

Uma árvore binária balanceada é uma árvore binária de busca que todo nó $T$ tem fator de balancemanto $fb(T) \in \{-1, 0, 1\}$

### Teorema : Uma operação de rotação sempre é suficiente para restaurar o balanceamento perdido após a inserção de um único nó

$$H \unlhd G$$

# Referências

https://pages.cs.wisc.edu/~ealexand/cs367/NOTES/AVL-Trees/index.html