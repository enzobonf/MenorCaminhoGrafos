#ifndef GRAFO_H
#define GRAFO_H

#include <stdlib.h>
#include <stdio.h>

#define MAX 50
enum {BRANCO, CINZA, PRETO};

typedef struct {
  int vet[MAX];
  int inicio, fim;
} Fila;

typedef struct {
  int v;
  int w;
  int custo;
} Aresta;

struct grafo {
  int V;
  int A;
  int **adj;
};

void enqueue(Fila *q, int x);
void dequeue(Fila *q);

// cria uma aresta (v,w)
Aresta ARESTA(int v, int w, int custo);

typedef struct grafo* Grafo;

// inicializa um grafo com |V| vertices
Grafo inicializa(int V);

// Insere a aresta e no grafo g de forma não orientada
void grafoInsere(Grafo g, Aresta e);

// Insere a aresta e no grafo g de forma orientada
void grafoInsereOrientado(Grafo g, Aresta e);

// Remove a aresta e do grafo g de forma não orientada
void grafoRemove(Grafo g, Aresta e);

// Remove a aresta e do grafo g de forma orientada
void grafoRemoveOrientado(Grafo g, Aresta e);

// Preenche o vetor com as arestas de g
// Retorna |E|
int grafoArestas(Aresta a[], Grafo g);

// imprime um grafo G = (V,E);
void imprimirGrafo(Grafo g);

// Retorna 1 caso a aresta pertença a g, ou 0 caso não
int pertence(Grafo g, Aresta e);

// Mostra o grafo
void mostrarGrafo(Grafo g);

// Executa busca em largura
void buscaLargura(Grafo g, int s);

// Executa busca em profundidade
void buscaProfundidade(Grafo g, int s);

// Imprime o caminho mais próximo entre 2 vértices
void imprimeCaminho(Grafo g, int s, int v, int *distancia);

// Retorna 1 caso o grafico seja euleriano, ou 0 caso não
int eh_euleriano(Grafo g);

void dijkstra(Grafo g, int s);

#endif