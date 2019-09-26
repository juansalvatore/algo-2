typedef struct nodo_lista
{
  struct nodo_lista *prox;
  void *dato;
} nodo_lista_t;

typedef struct lista
{
  nodo_lista_t *prim;
} lista_t;

void eliminar_pos_pares(lista_t *lista)
{
  nodo_lista_t *act = lista->prim;
  nodo_lista_t *prox = lista->prim->prox;
  int i = 1;
  while (prox)
  {
    if (i % 2 != 0)
      act->prox = prox->prox;
    act = prox;
    prox = prox->prox;
    i++;
  }
}