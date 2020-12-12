#include "ft_printf.h"

void ft_printf(char *s, ...) {
  t_parser_match *match;

  match = ft_parse_2(printf_parser, s);
  if (match) {
    printf("succeed\n");
  } else {
    printf("failure\n");
  }
}