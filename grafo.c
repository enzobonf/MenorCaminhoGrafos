#include "grafo.h"

int cor[MAX];
int pai[MAX];
int d[MAX];
int f[MAX];
int timestamp;

int vazia(Fila *f) { return f->inicio == f->fim; }
int cheia(Fila *f) { return f->fim >= MAX; }

Fila *cria_fila_vazia() {
  Fila *f = (Fila *)malloc(sizeof(Fila));
  f->inicio = 0;
  f->fim = 0;
  return f;
}

void enqueue(Fila *q, int x) {
  if (!cheia(q)) {
    q->vet[q->fim] = x;
    q->fim++;
  }
}

void dequeue(Fila *q) {
  if (!vazia(q)) {
    q->inicio++;
  }
}

int **criaMatrizAdj(int l, int c) {

  int i, j;
  int **m = malloc(l * sizeof(int *));

  for (i = 0; i < l; i++)
    m[i] = malloc(c * sizeof(int));

  for (i = 0; i < l; i++)
    for (j = 0; j < c; j++)
      m[i][j] = 0;

  return m;
}

Grafo inicializa(int V) {
  Grafo g = malloc(sizeof(Grafo *));
  g->adj = criaMatrizAdj(V, V);
  g->V = V;
  g->A = 0;
  return g;
}

Aresta ARESTA(int v, int w, int custo) {
  Aresta *a = (Aresta *)malloc(sizeof(Aresta));
  a->v = v;
  a->w = w;
  a->custo = custo;
  return *a;
}

void grafoInsere(Grafo g, Aresta e) {
  int v = e.v;
  int w = e.w;
  int custo = e.custo;

  if (g->adj[v][w] == 0) {
    g->adj[v][w] = custo;
    g->adj[w][v] = custo;
    g->A++;
  }
}

void grafoInsereOrientado(Grafo g, Aresta e) {
  int v = e.v;
  int w = e.w;
  int custo = e.custo;

  if (g->adj[v][w] == 0) {
    g->adj[v][w] = custo;
    g->A++;
  }
}

void grafoRemoveOrientado(Grafo g, Aresta e) {
  int v = e.v;
  int w = e.w;

  if (g->adj[v][w] >= 1) {
    g->adj[v][w] = 0;
    g->A--;
  }
}

int pertence(Grafo g, Aresta e) {
  int v = e.v;
  int w = e.w;
  return g->adj[v][w] != 0;
}

void mostrarGrafo(Grafo g) {
  int v, w;
  for (v = 0; v < g->V; ++v) {
    printf("%2d:", v);
    for (w = 0; w < g->V; ++w)
      if (g->adj[v][w] >= 1)
        printf(" %2d (%2d)", w, g->adj[v][w]);
    printf("\n");
  }
  printf("\n\n");
}

void buscaLargura(Grafo g, int s) {
  Fila *f = cria_fila_vazia();
  int u, v;

  for (u = 0; u < g->V; u++) {
    cor[u] = BRANCO;
    d[u] = 9999;
    pai[u] = -1;
  }

  cor[s] = CINZA;
  d[s] = 0;
  pai[s] = -1;

  enqueue(f, s);

  while (!vazia(f)) {
    u = f->vet[f->inicio];
    int *adj = g->adj[u];

    for (v = 0; v < g->V; v++) {
      if (adj[v] == 0)
        continue;

      if (cor[v] == BRANCO) {
        cor[v] = CINZA;
        d[v] = d[u] + adj[v];
        pai[v] = u;
        enqueue(f, v);
      }
    }

    dequeue(f);
    cor[u] = PRETO;
  }

  for (v = 0; v < g->V; v++) {
    printf("%4d %2d\n", d[v], pai[v]);
  }
}

void buscaProfundidade_aux(Grafo g, int u) {

  cor[u] = CINZA;
  timestamp++;

  d[u] = timestamp;
  int *adj = g->adj[u];

  int v;
  for (v = 0; v < g->V; v++) {
    if (adj[v] == 0)
      continue;

    if (cor[v] == BRANCO) {
      pai[v] = u;
      buscaProfundidade_aux(g, v);
    }
  }

  cor[u] = PRETO;
  timestamp++;
  f[u] = timestamp;
}

void buscaProfundidade(Grafo g, int s) {
  int u, v;

  for (u = 0; u < g->V; u++) {
    cor[u] = BRANCO;
    pai[u] = -1;
  }

  timestamp = 0;

  buscaProfundidade_aux(g, s);

  for (v = 0; v < g->V; v++) {
    printf("%d\n", d[v]);
  }
}

void imprimeCaminho(Grafo g, int s, int v, int *distancia) {
  if (v == s) {
    printf("%d -> ", s);
  } else if (pai[v] == -1) {
    printf("Nao existe caminho de s p/ v");
  } else {
    imprimeCaminho(g, s, pai[v], distancia);
    if(pai[v] != s) printf("-> ");
    printf("%d ", v);
    *distancia = d[v];
  }
}

int buscaIndexMenorDistancia(int *cor, int *d, int n) {
  int i, menor = -1, primeiro = 1;
  for (i = 0; i < n; i++) {
    if (d[i] >= 0 && cor[i] == BRANCO) {
      if (primeiro) {
        menor = i;
        primeiro = 0;
      } else {
        if (d[menor] > d[i])
          menor = i;
      }
    }
  }
  return menor;
}

void dijkstra(Grafo g, int s) {

  int u, i, distancia = -1;

  for (u = 0; u < g->V; u++) {
    cor[u] = BRANCO;
    d[u] = -1;
    pai[u] = -1;
  }

  d[s] = 0;
  cor[s] = CINZA;

  for (i = 0; i < g->V; i++) {
    if (g->adj[s][i] >= 1) {
      d[i] = g->adj[s][i];
      pai[i] = s;
    }
  }

  int menorDistancia = buscaIndexMenorDistancia(cor, d, g->V);
  while (menorDistancia != -1) {
    u = menorDistancia;

    for (i = 0; i < g->V; i++) {
      if (g->adj[u][i] >= 1) {

        int distancia = d[u] + g->adj[u][i];
        if(d[i] == -1 || (distancia < d[i])){
          d[i] = distancia;
          pai[i] = u;
        } // relaxação
        
      }
    }

    cor[u] = CINZA;
    menorDistancia = buscaIndexMenorDistancia(cor, d, g->V);
  }

  for (u = 0; u < g->V; u++) {
    printf("%d pai: %d\n", u, pai[u]);
  }

}
