#include "ft_printf.h"

static t_parser_ctx *character() {
  return (anyOf(
    exact("%%"),
    pick(sequenceOf(
      not(exact("%")),
      characters(NULL),
      NULL
    ), 1),
    NULL
  ));
}

t_parser_ctx *text() {
  return (joinCharacters(oneOrMore(character())));
}