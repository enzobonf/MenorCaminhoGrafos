
#include "grafo.h"

int main(void) {

  Grafo g = NULL;
  g = inicializa(13);

  grafoInsere(g, ARESTA(0, 1, 2));
  grafoInsere(g, ARESTA(0, 4, 8));

  grafoInsere(g, ARESTA(1, 3, 3));
  grafoInsere(g, ARESTA(1, 2, 4));
  grafoInsere(g, ARESTA(1, 5, 11));
  grafoInsere(g, ARESTA(1, 4, 17));

  grafoInsere(g, ARESTA(2, 3, 5));

  grafoInsere(g, ARESTA(3, 5, 2));

  grafoInsere(g, ARESTA(4, 7, 2));

  grafoInsere(g, ARESTA(7, 6, 5));
  grafoInsere(g, ARESTA(7, 10, 3));

  grafoInsere(g, ARESTA(6, 9, 7));
  grafoInsere(g, ARESTA(6, 11, 13));


  grafoInsere(g, ARESTA(11, 10, 4));
  grafoInsere(g, ARESTA(11, 12, 9));

  grafoInsere(g, ARESTA(9, 12, 2));

  mostrarGrafo(g);

  //buscaLargura(g, 3);

  dijkstra(g, 3);

  int distancia = 0;
  imprimeCaminho(g, 3, 12, &distancia);
  printf("\ndistancia: %d", distancia);

  return 0;
}