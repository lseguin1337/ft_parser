#include "ft_printf.h"

t_parser_ctx *printf_parser() {
  return (pick(
    sequenceOf(
      zeroOrMore(anyOf(
        debug("text", text()),
        debug("flag", flag()),
        NULL
      )),
      eof(),
      NULL
    ),
    0
  ));
}