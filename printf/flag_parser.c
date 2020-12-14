#include "ft_printf.h"

static void set_options(t_flag_options *options, t_parser_match *match) {
  char c;

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

static int get_number(t_parser_match *match) {
  if (!match->data)
    return (0);
  return *(int *)match->data;
}

static t_parser_match *create_flag(t_parser_match *match) {
  t_parser_match *item;
  t_flag flag;

  item = match->data;
  ft_memset(&flag, '\0', sizeof(flag));
  set_options(&flag.options, ((t_parser_match *)get_chunk(item, 1))->data);
  flag.type = FLAG;
  flag.marge = get_number(get_chunk(item, 2));
  flag.precision = get_number(get_chunk(item, 3));
  flag.long_flag = count_chunk(((t_parser_match *)get_chunk(item, 4))->data);
  flag.format = ((t_parser_match *)get_chunk(item, 5))->data;
  destroyMatch(match);
  return (createMatch(&flag, NULL, sizeof(flag)));
}

static t_parser_ctx *precision() {
  return (pick(sequenceOf(
    exact("."),
    zeroOrOne(anyOf(
      integer(),
      characters("*"),
      NULL
    )),
    NULL
  ), 1));
}

static t_parser_ctx *flagType() {
  return (anyOf(
    mapTo(characters("s"), &format_string),
    mapTo(characters("c"), &format_char),
    mapTo(characters("di"), &format_integer),
    mapTo(characters("p"), &format_ptr),
    mapTo(characters("f"), &format_float),
    mapTo(characters("x"), &format_hex),
    mapTo(characters("%"), &format_percent),
    NULL
  ));
}

t_parser_ctx *flag() {
  return (map(sequenceOf(
    exact("%"),
    repeat(characters("+- 0"), 0, 4),
    zeroOrOne(integer()),
    zeroOrOne(precision()),
    zeroOrOne(anyOf(
      repeat(exact("h"), 1, 2),
      repeat(exact("l"), 1, 2),
      NULL
    )),
    flagType(),
    NULL
  ), &create_flag));
}