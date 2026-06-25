# Problema de Coloração de Grafos (GCP) - Otimização Combinatória

Este repositório contém a implementação em C++ da Atividade A2 da disciplina de Estrutura de Dados e Complexidade de Algoritmos (Mestrado em Informática - UFPB). O projeto documenta a evolução algorítmica desde heurísticas gulosas simples até meta-heurísticas de estado da arte para resolução do Problema de Coloração de Grafos (GCP).

## Detalhes da Implementação

### 1. Representação da Solução
A solução foi modelada através de um vetor unidimensional de inteiros (`std::vector<int> cores`), onde o índice representa o identificador do vértice ($v \in V$) e o valor armazenado representa a cor atribuída.

### 2. Heurística de Construção (A Evolução)
O projeto iniciou com o clássico **Welsh-Powell** (ordenação estática por grau), mas evoluiu para uma abordagem mais robusta:
* **DSatur (Degree of Saturation):** Heurística dinâmica que a cada passo escolhe o vértice com o maior "grau de saturação" (maior quantidade de cores distintas já atribuídas aos seus vizinhos). Esta alteração reduziu imediatamente a solução inicial de instâncias densas (ex: `DSJC500.5.col` saltou de 69 cores no Welsh-Powell para 65 cores no DSatur).

### 3. Busca Local e Seus Limites (VND e ILS)
Na segunda fase, implementou-se o algoritmo **VND (Variable Neighborhood Descent)** embarcado em um **ILS (Iterated Local Search)**, utilizando movimentos clássicos ($N_1$: mudar cor, $N_2$: trocar cores) e vizinhanças agressivas ($N_3$: Cadeias de Kempe).
* **Limitação Empírica:** A exigência de manter a factibilidade (coloração 100% válida) a cada movimento tornou a busca extremamente custosa. O ILS levou mais de 4 minutos (267.000 ms) na instância `DSJC500.5.col` para reduzir a coloração para apenas 62 cores, ficando preso em ótimos locais profundos.

### 4. A Solução: Meta-heurística TabuCOL (Estado da Arte)
Para romper a barreira da Busca Local, o paradigma foi invertido utilizando a meta-heurística **TabuCOL** (Hertz & de Werra, 1987).
* **Relaxamento de Restrições:** O algoritmo fixa o número de cores em uma meta ($k$) e permite que a solução seja temporariamente inválida. A função objetivo minimizada passa a ser o **número de conflitos** (arestas conectando vértices da mesma cor).
* **Matriz Gamma ($\gamma$):** Para garantir performance extrema, foi implementada uma matriz incremental $O(|V| \times k)$ que calcula o delta de conflitos de qualquer movimento em frações de microssegundos.
* **Lista Tabu:** Impede que o algoritmo desfaça uma mudança recente, com um *Tenure* (tempo de punição) dinâmico baseado no número de conflitos, forçando a exploração de novas áreas do espaço de busca.

---

## Resultados Computacionais Finais

Os testes foram conduzidos utilizando as instâncias clássicas do desafio internacional **DIMACS**. A tabela abaixo reflete os resultados do pipeline otimizado: **DSatur (Construção) + TabuCOL (Refinamento)** com critério de *Early Exit* ao atingir o *Best Known Solution* (BKS).

| Instância | Vértices | Arestas | BKS (Ótimo) | Inicial (DSatur) | Final (TabuCOL) | Tempo Total (ms) |
| :--- | :---: | :---: | :---: | :---: | :---: | :---: |
| `mulsol.i.1` | 197 | 3.925 | **49** | 49 | **49** | < 1 ms |
| `mulsol.i.2` | 188 | 3.885 | **31** | 31 | **31** | < 1 ms |
| `mulsol.i.3` | 184 | 3.916 | **31** | 31 | **31** | < 1 ms |
| `mulsol.i.4` | 185 | 3.946 | **31** | 31 | **31** | < 1 ms |
| `mulsol.i.5` | 186 | 3.973 | **31** | 31 | **31** | < 1 ms |
| `fpsol2.i.1` | 496 | 11.654 | **65** | 65 | **65** | < 1 ms |
| `fpsol2.i.2` | 451 | 8.691 | **30** | 30 | **30** | < 1 ms |
| `fpsol2.i.3` | 425 | 8.688 | **30** | 30 | **30** | < 1 ms |
| `le450_15c` | 450 | 16.680 | **15** | 23 | **20** | 340 ms |
| `DSJC500.5.col`| 500 | 62.624 | **48** | 65 | **54** | 319 ms |

---

##  Conclusão

A experimentação documenta com clareza o comportamento de diferentes topologias perante os algoritmos:
1. **Grafos Estruturados (Alocação de Registradores):** Instâncias da família `mulsol` e `fpsol` (baseadas em compiladores) demonstraram ser trivialmente resolvidas pela heurística construtiva DSatur. O mecanismo de *Early Exit* garantiu o encerramento em tempo $O(1)$ sub-milissegundo, visto que o Ótimo Global foi atingido imediatamente.
2. **Grafos Aleatórios e Complexos:** Nas instâncias `DSJC` e `le450`, desenhadas para possuírem múltiplos ótimos locais profundos, a Busca Local rigorosa (VND/ILS) falhou devido ao alto custo de explorar vizinhanças válidas. A aplicação da **Busca Tabu (TabuCOL)** mostrou-se devastadora: ao relaxar a restrição de factibilidade e operar sobre uma Matriz $\gamma$, o algoritmo reduziu a coloração do `DSJC500.5` para impressionantes **54 cores em apenas 319 milissegundos**, superando largamente a barreira de tempo e qualidade das fases anteriores.

---

## Histórico de Tentativas e Evolução do Projeto

Para alcançar os tempos de execução sub-segundo e a qualidade de solução do TabuCOL apresentados na tabela final, este projeto passou por uma rigorosa trilha de experimentação. O registro dessas tentativas documenta o esforço investigativo para superar as barreiras de complexidade do problema:

1. **Tentativa 1: Heurística Construtiva Básica (Welsh-Powell)**
   * **O que foi feito:** Implementação inicial ordenando os vértices por grau decrescente.
   * **O que foi osbervado:** Eficiente apenas para grafos simples. Em grafos com densidade moderada/alta, gerou um número excessivo de cores (ex: 69 cores no `DSJC500.5`). Serviu como *baseline* (linha de base).

2. **Tentativa 2: Refinamento Construtivo (DSatur)**
   * **O que foi feito:** Substituição do Welsh-Powell pelo grau de saturação dinâmico.
   * **O que foi osbervado:** Representou um salto imediato de qualidade (reduziu o baseline do `DSJC500.5` de 69 para 65 cores). Comprovou que a ordem de construção importa criticamente para o espaço de busca subsequente.

3. **Tentativa 3: Busca Local Estrita (VND Clássico)**
   * **O que foi feito:** Implementação do *Variable Neighborhood Descent* usando $N_1$ (mudança de cor de 1 vértice) e $N_2$ (troca de cor entre 2 vértices).
   * **O que foi osbervado:** O algoritmo ficou rapidamente preso em "planícies" (ótimos locais onde nenhuma vizinhança reduzia o número total de cores, apenas remanejava vértices).

4. **Tentativa 4: Força Bruta Estrutural (ILS + Cadeias de Kempe)**
   * **O que foi feito:** A tentativa mais agressiva de manter a restrição de factibilidade. Implementou-se um *Iterated Local Search* (ILS) rodando 50 iterações com perturbações, e adicionou-se a vizinhança $N_3$ (**Cadeias de Kempe**) para inverter as cores de subgrafos bicolores inteiros de uma só vez.
   * **O que foi osbervado (O Gargalo):** Apesar da elegância matemática do Kempe, o custo de buscar essas cadeias validando cada vizinho gerou uma **explosão combinatorial de tempo**. O tempo de execução saltou de ~2 segundos para impressionantes **267 segundos** (mais de 4 minutos), com uma melhoria pífia de apenas 3 cores. 
   
**O Veredito:** A "Tentativa 4" foi o divisor de águas da pesquisa. Ela provou empiricamente que insistir na factibilidade estrita (cores 100% válidas a cada passo) em instâncias forjadas era ineficiente. Isso fundamentou e justificou a migração final para o **TabuCOL** (que relaxa a factibilidade e minimiza conflitos), culminando nos resultados de estado da arte consolidados neste repositório.