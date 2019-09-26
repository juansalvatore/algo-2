#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

size_t raiz(size_t n)
{
  _raiz(n, 0, n - 1);
}

size_t _raiz(size_t n, size_t ini, size_t fin)
{
  size_t medio = (ini + fin) / 2;
  if (medio * medio > n)
    return _raiz(n, ini, medio - 1);
  if (medio * medio <= n && (medio + 1) * (medio + 1) > n)
    return medio;
  return _raiz(n, medio + 1, fin);
}
