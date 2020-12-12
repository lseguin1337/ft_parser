#include "ft_printf.h"

void ft_printf(char *s, ...) {
  t_parser_ctx *grammar;
  t_parser_match *match;

  grammar = printf_parser();
  match = parse(grammar, s);
  destroyContext(grammar);
  if (match) {
    printf("succeed\n");
  } else {
    printf("failure\n");
  }
}