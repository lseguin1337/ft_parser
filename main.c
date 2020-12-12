#include "./printf/ft_printf.h"

int main() {
  char *s = "text %% %43.23s %c %-111.lld %s %f %+012.4i hello";

  printf("String: %s\n", s);
  ft_printf(s);
}
