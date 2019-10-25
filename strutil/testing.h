#ifndef TESTING_H
#define TESTING_H

#include <stdbool.h>

#define print_test(mensaje, result)                                \
  do                                                               \
  {                                                                \
    real_print_test(mensaje, result, __FILE__, __LINE__, #result); \
  } while (0)

void real_print_test(const char *mensaje, bool ok,
                     const char *file, int line, const char *failed_expr);

int failure_count(void);

#endif
