# Exercício 2 – Algoritmos de Ordenação: Merge Sort e Quick Sort

Este exercício tem como objetivo a implementação e análise de dois algoritmos eficientes de ordenação: Merge Sort e Quick Sort. Diferentemente dos algoritmos da lista anterior, estes apresentam complexidade assintótica média de ordem n log n, sendo amplamente utilizados em aplicações reais.

A aplicação realiza a leitura de arquivos de entrada contendo conjuntos de dados, executa os algoritmos selecionados e registra tanto o vetor ordenado quanto o tempo de execução.

---

# Algoritmos Implementados

## Merge Sort

O Merge Sort é um algoritmo baseado na estratégia de divisão e conquista. Ele divide recursivamente o vetor em subvetores menores até que cada parte tenha tamanho unitário, e então realiza a fusão (merge) dessas partes de forma ordenada.

### Características

* Baseado em divisão e conquista
* Estável
* Desempenho consistente independentemente da entrada

### Complexidade Assintótica

* Melhor caso: Ω(n log n)
* Caso médio: O(n log n)
* Pior caso: O(n log n)
* Complexidade de espaço: O(n)

O algoritmo mantém comportamento previsível em todos os cenários, ao custo de uso adicional de memória para o processo de merge.

---

## Quick Sort

O Quick Sort também utiliza a estratégia de divisão e conquista, porém baseia-se na escolha de um pivô para particionar o vetor em elementos menores e maiores que ele.

### Características

* Geralmente mais rápido na prática
* In-place (não requer memória adicional significativa)
* Não estável

### Complexidade Assintótica

* Melhor caso: Ω(n log n)
* Caso médio: O(n log n)
* Pior caso: O(n²)
* Complexidade de espaço: O(log n) (devido à recursão)

O pior caso ocorre quando o pivô escolhido resulta em partições altamente desbalanceadas, como em vetores já ordenados quando se utiliza um pivô fixo.

---

# Estrutura do Projeto

```id="v3j6o9"
exercicio_2/
├── input/
├── output/
├── src/
│   ├── main.cpp
│   ├── sort_algorithms.cpp
│   └── sort_algorithms.h
├── Makefile
└── README.md
```

---

# Formato do Arquivo de Entrada

Os arquivos devem seguir o padrão:

```id="ctep8p"
n
v1 v2 v3 ... vn
```

Exemplo:

```id="i0mb4k"
5
4 2 5 1 3
```

---

# Saída Gerada

Para cada execução, são gerados arquivos na pasta `output/`:

```id="ibw5qg"
output/<nome_arquivo>_merge.output
output/<nome_arquivo>_quick.output
```

Cada arquivo contém:

* O vetor ordenado
* O tempo de execução em milissegundos

---

# Compilação

```id="7iv0xq"
make
```

---

# Execução

## Executar ambos os algoritmos

```id="nqzqgq"
make run FILE=input/arquivo.in
```

## Executar apenas Merge Sort

```id="gpp8sr"
make run FILE=input/arquivo.in ALG=merge
```

## Executar apenas Quick Sort

```id="f7p9vz"
make run FILE=input/arquivo.in ALG=quick
```

## Executar todos os arquivos de entrada

```id="hmxj4o"
make run_all
```

Este comando executa o programa para todos os arquivos presentes na pasta `input/`.

---

# Medição de Tempo

O tempo de execução é medido utilizando `std::chrono::high_resolution_clock`. Os resultados são exibidos no terminal e armazenados nos arquivos de saída.

---

# Considerações

Cada algoritmo opera sobre uma cópia independente do vetor original, garantindo uma comparação justa entre as abordagens.

O Merge Sort apresenta desempenho consistente, enquanto o Quick Sort tende a ser mais eficiente na prática, embora esteja sujeito a degradação no pior caso dependendo da escolha do pivô.

---

# Possíveis Extensões

* Implementação de estratégias de escolha de pivô (aleatório, mediana de três)
* Comparação com algoritmos da lista anterior
* Geração de métricas agregadas para análise estatística
* Integração com ferramentas de visualização de desempenho

---

# Autor

Projeto desenvolvido para fins acadêmicos na disciplina de Análise e Projeto de Algoritmos.
