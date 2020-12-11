#include "ft_parser.h"

#define NEXT(x) ((t_parser_match *)(x = get_next_chunk(x)))

typedef struct s_options
{
  int          zero;
  int          plus;
  int          minus;
  int          space;
}              t_options;

typedef struct s_flag {
  int          marge;
  int          precision;
  void         *format;
  t_options    options;
}              t_flag;

char *format_string() {
  return NULL;
}

char *format_char() {
  return NULL;
}

char *format_hex() {
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

void set_options(t_options *options, t_parser_match *match) {
  char c;
  options->zero = 0;
  options->space = 0;
  options->plus = 0;
  options->minus = 0;
  while (match) {
    c = ((char *)match->data)[0];
    if (c == '0')
      options->zero = 1;
    else if (c == ' ')
      options->space = 1;
    else if (c == '+')
      options->plus = 1;
    else if (c == '-')
      options->minus = 1;
    match = get_next_chunk(match);
  }
}

t_parser_match *create_flag(t_parser_match *match) {
  t_parser_match *item = match->data;
  t_flag *flag;

  if (!(flag = malloc(sizeof(t_flag))))
    return (NULL);
  set_options(&flag->options, NEXT(item)->data);
  flag->marge = (int)(NEXT(item)->data);
  flag->precision = (int)(NEXT(item)->data);
  flag->format = NEXT(item)->data;
  return (createMatch(flag, &free));
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
  return (joinCharacters(oneOrMore(character())));
}

t_parser_ctx *flagType() {
  return (anyOf(
    mapTo(characters("s"), &format_string),
    mapTo(characters("c"), &format_char),
    mapTo(characters("di"), &format_integer),
    mapTo(characters("p"), &format_ptr),
    mapTo(characters("f"), &format_float),
    mapTo(characters("x"), &format_hex),
    NULL
  ));
}

t_parser_ctx *flagOptions() {
  return (zeroOrMore(characters("+- 0")));
}

t_parser_ctx *flag() {
  return (map(sequenceOf(
    exact("%"),
    flagOptions(),
    zeroOrOne(integer()),
    zeroOrOne(precision()),
    flagType(),
    NULL
  ), &create_flag));
}

t_parser_ctx *printf_expression() {
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

void ft_printf(char *s, ...) {
  t_parser_ctx *ctx;
  t_parser_match *match;

  ctx = printf_expression();
  match = parse(ctx, s);
  if (match) {
    printf("succeed\n");
  } else {
    printf("failure\n");
  }
}

int main() {
  char *s = "text %% %43.23s %c %-111.d %s %f %+012.4i hello";

  printf("String: %s\n", s);
  ft_printf(s);
}