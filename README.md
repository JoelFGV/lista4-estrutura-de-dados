# Trabalho 4 - Sistema de Autocomplete de Jogos com Trie

## Descrição do projeto

Este projeto implementa um sistema de autocomplete de jogos utilizando a estrutura de dados Trie (Prefix Tree), conforme proposto no Trabalho 4 da disciplina.

O sistema armazena um catálogo de jogos e permite realizar buscas por prefixo nos títulos dos jogos. Cada jogo possui um título, uma descrição curta e uma popularidade.

A Trie é utilizada para armazenar os títulos dos jogos e possibilitar buscas eficientes por prefixo, sem percorrer toda a base de dados a cada consulta.

O sistema permite:

- inserir jogos na Trie;
- verificar se um título existe no catálogo;
- realizar buscas por prefixo;
- retornar sugestões de autocomplete;
- ordenar os resultados por popularidade;
- ignorar diferenças entre letras maiúsculas e minúsculas;
- ignorar espaços em branco durante as buscas.

---

## Organização dos arquivos

O projeto está organizado nos seguintes arquivos:

```text
main.cpp
Game.hpp
Game.cpp
Trie.hpp
Trie.cpp
GamesDatabase.hpp
GamesDatabase.cpp
```

### Função de cada arquivo

- **main.cpp**: ponto de entrada do programa. Carrega a base de jogos, constrói a Trie, realiza a busca e exibe os resultados.
- **Game.hpp / Game.cpp**: declaração e implementação da classe `Game`.
- **Trie.hpp / Trie.cpp**: declaração e implementação das classes `Trie` e `TrieNode`.
- **GamesDatabase.hpp / GamesDatabase.cpp**: base de jogos utilizada pelo sistema.

---

## Estrutura utilizada

A estrutura principal do projeto é uma Trie.

Cada nó da Trie possui:

- um vetor de ponteiros para os filhos;
- um indicador de fim de título;
- um ponteiro para o objeto `Game` associado ao título.

Os jogos não são copiados para a Trie.

A Trie armazena apenas ponteiros para os objetos já existentes no array `games` definido em `GamesDatabase.cpp`.

---

## Chave de busca

Antes de inserir ou buscar um título, o texto é convertido para uma chave de busca.

A conversão:

- transforma letras maiúsculas em minúsculas;
- remove espaços em branco;
- preserva letras e números.

Exemplos:

```text
"Hades"      -> "hades"
"HALF LIFE"  -> "halflife"
"Portal 2"   -> "portal2"
```

Dessa forma:

```cpp
contains("Half Life");
contains("HALF LIFE");
contains("halflife");
```

produzem o mesmo resultado.

---

## Critério de ordenação

Os resultados do autocomplete são ordenados pelos seguintes critérios:

1. maior popularidade;
2. em caso de empate, ordem alfabética da chave de busca.

Exemplo:

```text
Half Life (90)
Halo (90)
```

Como:

```text
halflife < halo
```

o jogo Half Life aparece antes de Halo.

---

## Instruções de compilação

Para compilar o projeto utilize:

```bash
g++ main.cpp Game.cpp Trie.cpp GamesDatabase.cpp -o app
```

---

## Instruções de execução

Após compilar:

```bash
./app k prefixo
```

onde:

- `k` é a quantidade máxima de sugestões;
- `prefixo` é o texto utilizado na busca.

Exemplos:

```bash
./app 3 ha
```

```bash
./app 5 portal
```

Caso o prefixo possua espaços:

```bash
./app 5 "half l"
```

---

## Exemplos de execução

### Busca por prefixo

Comando:

```bash
./app 3 ha
```

Saída obtida:

```text
Hades | Defy the god of the dead as you hack and slash out of the Underworld in this rog... | 213542
Halo The Master Chief Collection | The Master Chief s iconic journey includes six games built for PC and collected ... | 192219
Halo Infinite | The legendary Halo series returns with the most expansive Master Chief campaign ... | 160647
```

### Busca ignorando espaços

Comando:

```bash
./app 5 "half l"
```

O sistema encontra títulos cujo prefixo corresponde a:

```text
halfl
```

ignorando os espaços da entrada.

### Nenhum resultado encontrado

Comando:

```bash
./app 3 zelda
```

Saída:

```text
No results found
```

---

## Funcionamento geral

### Inserção

O método `insert`:

1. converte o título para a chave de busca;
2. percorre a Trie caractere por caractere;
3. cria novos nós quando necessário;
4. marca o último nó como final de título;
5. armazena o ponteiro para o jogo.

### Busca exata

O método `contains`:

1. converte o título para a chave de busca;
2. percorre a Trie;
3. verifica se o último nó representa um título completo.

### Autocomplete

O método `autocomplete`:

1. converte o prefixo para a chave de busca;
2. percorre a Trie até o nó correspondente ao prefixo;
3. explora a subárvore desse nó;
4. coleta todos os jogos encontrados;
5. ordena os resultados;
6. retorna até `k` sugestões.
