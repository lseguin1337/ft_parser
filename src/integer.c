#include "ft_parser.h"

static t_parser_match *toInteger(t_parser_match *match) {
  t_parser_match *digit = match->data;
  long value = 0;

  while (digit) {
    value = (value * 10) + (((char *)digit->data)[0] - '0');
    digit = get_next_chunk(digit);
  }
  destroyMatch(match);
  return (createMatch((void *)value, NULL));
}

t_parser_ctx *integer() {
  return (map(oneOrMore(
    characters("0123456789")
  ), &toInteger));
}