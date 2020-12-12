#include "ft_printf.h"

t_parser_ctx *printf_parser() {
  return (pick(
    sequenceOf(
      zeroOrMore(anyOf(
        text(),
        flag(),
        NULL
      )),
      eof(),
      NULL
    ),
    0
  ));
}