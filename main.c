#include "ft_parser.h"

char *format_string() {
  return NULL;
}

char *format_integer() {
  return NULL;
}

char *format_ptr() {
  return NULL;
}

char *format_float() {
  return NULL;
}

t_parser_match *toInteger(t_parser_match *match) {
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

t_parser_ctx *precision() {
  return (pick(sequenceOf(
    exact("."),
    zeroOrOne(integer()),
    NULL
  ), 1));
}

t_parser_ctx *character() {
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
  return (debug("text", oneOrMore(character())));
}

t_parser_ctx *flagType() {
  return (anyOf(
    mapTo(characters("s"), &format_string),
    mapTo(characters("di"), &format_integer),
    mapTo(characters("p"), &format_ptr),
    mapTo(characters("f"), &format_float),
    NULL
  ));
}

t_parser_ctx *flag() {
  return (debug("flag", sequenceOf(
    exact("%"),
    zeroOrOne(integer()),
    zeroOrOne(precision()),
    flagType(),
    NULL
  )));
}

t_parser_ctx *printf_expression() {
  return (sequenceOf(
    zeroOrMore(anyOf(
      text(),
      flag(),
      NULL
    )),
    eof(),
    NULL
  ));
}

int main() {
  char *s = "text %% %43.23s %111.d hello";
  t_parser_ctx *ctx;
  t_parser_match *match;

  ctx = printf_expression();
  printf("String: %s\n", s);
  match = parse(ctx, s);
  if (match) {
    printf("succeed\n");
  } else {
    printf("failure\n");
  }
}