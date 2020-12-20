#include "ft_parser.h"

static t_parser_match *match_range(t_parser_match *match) {
  t_parser_match *first;
  t_parser_match *second;
  t_parser_ctx *range;

  first = match->data;
  second = get_chunk(first, 2);
  range = characterRange(*(char *)first->data, *(char *)second->data);
  destroyMatch(match);
  return createMatch(range, NULL, 0);
}

static t_parser_match *match_char(t_parser_match *match) {
  char c;

  c = *(char *)match->data;
  destroyMatch(match);
  return (createMatch(characterRange(c, c), NULL, 0));
}

static t_parser_match *create_any(t_parser_match *match) {
  t_parser_match *item;
  t_parser_ctx *first;

  first = NULL;
  item = match->data;
  while (item) {
    push_chunk((void **)&first, item->data);
    item = get_next_chunk(item);
  }
  destroyMatch(match);
  return (createMatch(anyOf(first, NULL), NULL, 0));
}

static t_parser_ctx *compiler() {
  return (
    map(oneOrMore(
      anyOf(
        pick(sequenceOf(
          not(exact("\\")),
          anyOf(
            map(sequenceOf(
              anyCharacter(),
              exact("-"),
              anyCharacter(),
              NULL
            ), &match_range), // map to range
            map(anyCharacter(), &match_char),
            NULL
          ),
          NULL
        ), 1),
        pick(sequenceOf(
          exact("\\"),
          map(anyCharacter(), &match_char),
          NULL
        ), 1),
        NULL
      )
    ), &create_any)
  );
}

t_parser_ctx *character(char *pattern) {
  t_parser_match *match;
  t_parser_ctx *compiled;
  
  match = ft_parse(compiler, pattern);
  compiled = match->data;
  destroyMatch(match);
  return (compiled);
}