# Projeto de Ordenação e Benchmark em C++

Este projeto tem como objetivo implementar e analisar algoritmos clássicos de ordenação, com foco em desempenho e comparação empírica. A aplicação lê dados de arquivos, executa algoritmos de ordenação e registra tanto o resultado ordenado quanto o tempo de execução.

---

# Algoritmos Implementados

## Selection Sort

O Selection Sort funciona selecionando, a cada iteração, o menor elemento do vetor e posicionando-o corretamente.

### Características

* Algoritmo simples e determinístico
* Não depende da ordem inicial dos dados

### Complexidade Assintótica

* Melhor caso: Ω(n²)
* Caso médio: O(n²)
* Pior caso: O(n²)

O algoritmo percorre todo o vetor a cada iteração, independentemente da entrada, o que justifica seu comportamento quadrático em todos os casos.

---

## Insertion Sort

O Insertion Sort constrói a lista ordenada de forma incremental, inserindo cada elemento na posição correta.

### Características

* Eficiente para dados quase ordenados
* Estável e simples de implementar

### Complexidade Assintótica

* Melhor caso: Ω(n)
* Caso médio: O(n²)
* Pior caso: O(n²)

No melhor caso (vetor já ordenado), o algoritmo realiza apenas uma passagem linear. No pior caso (vetor em ordem inversa), há necessidade de múltiplos deslocamentos, resultando em comportamento quadrático.

---

# Estrutura do Projeto

```
.
├── input/         # Arquivos de entrada
├── output/        # Arquivos gerados (resultados e tempos)
├── src/
│   ├── main.cpp
│   ├── sort_algorithms.cpp
│   └── sort_algorithms.h
├── Makefile
└── README.md
```

---

# Formato do Arquivo de Entrada

Os arquivos devem seguir o seguinte padrão:

```
n
v1 
v2
v3 
...
vn
```

Exemplo:

```
5
4
2
5
1
3
```

---

# Saída Gerada

Para cada execução, o programa cria arquivos na pasta `output/`:

```
output/<nome_arquivo>_insertion.output
output/<nome_arquivo>_selection.output
```

Cada arquivo contém:

* A lista ordenada
* O tempo de execução em milissegundos

---

# Compilação

```
make
```

---

# Execução

## Executar ambos os algoritmos

```
make run FILE=input/arquivo.in
```

## Executar apenas Insertion Sort

```
make run FILE=input/arquivo.in ALG=insertion
```

## Executar apenas Selection Sort

```
make run FILE=input/arquivo.in ALG=selection
```

## Executar todos os arquivos de entrada

```
make run_all
```

Esse comando executa o programa para todos os arquivos presentes na pasta `input/`.

---

# Medição de Tempo

O tempo de execução é medido utilizando `std::chrono::high_resolution_clock`.
Os resultados são exibidos no terminal e armazenados nos arquivos de saída.

---

# Considerações

Cada algoritmo opera sobre uma cópia independente do vetor original. Isso garante uma comparação justa, evitando viés decorrente da execução sequencial sobre dados já ordenados.

O projeto estabelece uma base para análise experimental de algoritmos de ordenação e pode ser estendido para incluir abordagens mais eficientes.

As implementações deste exercício foram insparadas nos pseudocódigos dos videos disponibilizados no proprio exercício:

[InsertionSort](https://www.youtube.com/watch?v=DFG-XuyPYUQ)

[SelectionSort](https://www.youtube.com/watch?v=f8hXR_Hvybo)

---

# Autor

Projeto desenvolvido para fins acadêmicos em nível de mestrado, com foco em análise de algoritmos e desempenho computacional.
