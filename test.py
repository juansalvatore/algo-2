# pylint: disable-all


def pila_crear():
    return True


def cola():
    return True


def tiene_ciclos(grafo):
    visitados = set()
    padre = {}
    for v in grafo:
        if v in visitados:
            continue
        if _ciclos_dfs(grafo, v, padre, visitados):
            return True
    return False


def _ciclos_dfs(grafo, vertice, padre, visitados):
    visitados.add(vertice)
    for e in grafo.ver_adyacentes(vertice):
        if e in visitados:
            if padre[e] != vertice:
                return True
        padre[e] = vertice
        return _ciclos_dfs(grafo, e, padre, visitados)
    return False


def tiene_ciclos_bfs(grafo, origen):
    visitados = set()
    visitados.add(origen)
    padres = {}
    cola = cola()
    cola.encolar(origen)

    while not cola.esta_vacia():
        v = cola.desencolar()
        for e in grafo.ver_adyacentes(v):
            if e not in visitados:
                visitados.add(e)
                cola.encolar(e)
                padre[e] = v
            else:
                if padre[e] != v:
                    return True
    return False


def cumple_tercer_condicion(grafo):
    grados = {}
    for v in grafo:
        for e in grafo.ver_adyacentes(v):
            grados[e] = grados.get(e, 0) + 1
    contador = 0
    for grado in grados:
        if grado != 1:
            contador += 1
    return contador == 1


def es_conexo(grafo):
    cola = crear_cola()
    cola.encolar(grafo.obtener_vertice_random())
    visitados = set()
    while not cola.esta_vacia():
        cola.desencolar()
        for e in grafo.ver_adyacentes(v):
            if e not in visitados:
                visitados.add(e)
                cola.encolar(e)
    return len(visitados) == len(grafo)


def es_conexo_dfs(grafo):
    cola = crear_cola()
    visitados = set()
    v = grafo.obtener_vertice_random()
    _es_conexo_dfs(grafo, v, visitados)
    return len(visitados) == len(grafo)


def _es_conexo_dfs(grafo, v, visitados):
    return True


def es_arbol(grafo):
    # para que sea arbol tiene que cumplir:
    # 1 - no tener ciclos
    # 2 - ser conexo
    # 3 - V = E - 1
    return not tiene_ciclos(grafo) and cumple_tercer_condicion(grafo) and es_conexo(grafo)


# 8. Implementar un algoritmo que reciba un grafo dirigido, un vértice V y un número N, y devuelva una lista con
# todos los vértices que se encuentren a exactamente N aristas de distancias del vértice V. Indicar el tipo de
# recorrido utilizado y el orden del algoritmo. Justificar.

def vertices_a_n_aristas(grafo, v, n):
    ordenes = {}
    ordenes[v] = 0
    cola = crear_cola()
    cola.encolar(v)
    lista = crear_lista()
    visitados = set()

    while not cola.esta_vacia():
        v = cola.desencolar()
        if orden[v] == n:
            lista.insertar(v)
            continue
        for e in grafo.ver_adyacentes(v):
            if e not in visitados:
                visitados.add(e)
                cola.encolar(e)
                ordenes[e] = ordenes[v] + 1
