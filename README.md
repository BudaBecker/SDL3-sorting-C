# Visualizador de Algoritmos de Ordenação — C + SDL3

Animação em tempo real de algoritmos de ordenação, escrita em **C puro com SDL3**.
Cada barra representa um valor do vetor; a cada iteração o quadro é redesenhado e um
tom é emitido com **frequência proporcional ao valor** que está sendo comparado — dá
para *ouvir* o vetor se ordenando.

---

## Como funciona

O estado inteiro do programa vive em uma única struct, `SortingAlgorithm`
([`sorting_algorithm.h`](build/include/sorting_algorithm.h)): a janela e o renderer do
SDL, o vetor, o índice do pivô, o índice comparado e até onde o vetor já está ordenado.

Cada algoritmo implementa a **mesma função**, `sorting_iteration(prog, audio)`, que
executa **um único passo** da ordenação e devolve o controle. O laço principal em
[`src/main.c`](src/main.c) é, então, comum a todos:

```c
while (prog.is_running && !prog.sorting_complete) {
    sdl_events(&prog);
    sorting_iteration(&prog, &audio);
}
```

Isso mantém a animação responsiva sem thread nenhuma: o algoritmo não roda até o fim
para depois desenhar — ele avança um passo por quadro, e o desenho acontece dentro
da própria iteração. Trocar de algoritmo é trocar qual implementação de
`sorting_iteration` entra no *link*.

As barras são coloridas por papel: **azul** para o pivô, destaque para o elemento em
comparação, e a região já ordenada com cor própria — ver
[`src/render.c`](src/render.c).

## Algoritmos

| Algoritmo | Estado |
| :--- | :--- |
| Bubble sort | ✅ implementado |
| Insertion sort | ✅ implementado |
| Quick sort | 🚧 esqueleto — `sorting_iteration` ainda vazia |

## Compilando

Requer **GCC** e a **SDL3** (os cabeçalhos já acompanham o repositório em
`build/include/`; a biblioteca compilada vai em `build/lib/`).

A partir de `src/`, um binário por algoritmo:

```bash
gcc *.c ./algorithms/bubble_sort.c    -o ../output/Bubble.exe    -I../build/include -L../build/lib -lSDL3
gcc *.c ./algorithms/insertion_sort.c -o ../output/Insertion.exe -I../build/include -L../build/lib -lSDL3
```

> **Atenção:** o `#include` do algoritmo em [`src/main.c`](src/main.c) precisa
> corresponder ao `.c` que você está linkando — troque a linha
> `#include "insertion_sort.h"` antes de compilar outro algoritmo.

## Configuração

Todos os parâmetros ficam em [`build/include/config.h`](build/include/config.h):

| Constante | Padrão | O que faz |
| :--- | :--- | :--- |
| `ARRAY_SIZE` | `70` | Quantidade de barras |
| `WINDOW_WIDTH` / `HEIGHT` | `1920` × `1080` | Resolução da janela |
| `DELAY_MS` | `10` | Pausa entre quadros — controla a velocidade |
| `INIT_FREQ` / `FINAL_FREQ` | `1.0` → `4.0` | Faixa de frequência do som, escalada pelo valor |

## Estrutura

```
src/
├── main.c              # laço principal
├── render.c            # desenho das barras e cores por papel
├── sdl_wrapper.c       # init, tratamento de eventos, áudio e free
└── algorithms/
    ├── bubble_sort.c
    ├── insertion_sort.c
    └── quick_sort.c    # esqueleto
build/include/          # config.h, headers do projeto e da SDL3
```

## Créditos

Baseado no guia de SDL3 em C de
**[Programming Rainbow](https://github.com/ProgrammingRainbow/Beginners-Guide-to-SDL3-in-C)**
e inspirado pelos vídeos de **[Hirsch Daniel](https://www.youtube.com/@HirschDaniel)**.

## Licença

MIT.
