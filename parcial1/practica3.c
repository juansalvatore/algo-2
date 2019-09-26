// 3. Implementar una funci ́on en C que reciba un arreglo de n enteros sin repetir y ordenados ascendentemente,
// y determine en O(logn) si es m ́agico. Un arreglo es m ́agico si existe alg ́un valor i (entre 0 y n - 1) tal que arr[i] = i.
// Ejemplos:
// • A = [ -3, 0, 1, 3, 7, 9 ] es m ́agico porque A[3] = 3.
// • B = [ 1, 2, 4, 6, 7, 9 ] no es m ́agico porque B[i] != i para todo i.
// Justificar el orden del algoritmo.

bool es_magico(int *arr, size_t n)
{
  return _es_magico(arr, 0, n - 1);
}

bool _es_magico(int *arr, int ini, int fin)
{
  if (ini > fin)
    return false;
  size_t medio = (ini + fin) / 2;
  if (medio == arr[medio])
    return true;
  if (arr[medio] < medio)
    return _es_magico(arr, medio + 1, fin);
  return _es_magico(arr, ini, medio - 1);
}
