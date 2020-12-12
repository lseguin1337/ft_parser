#include "ft_parser.h"

static t_parser_match *joinCharactersMap(t_parser_match *match) {
  char buffer[count_chunk(match->data) + 1];
  t_parser_match *character;
  int i;

  i = 0;
  character = (t_parser_match *)match->data;
  while (character) {
    buffer[i++] = *(char *)character->data;
    character = get_next_chunk(character);
  }
  buffer[i] = '\0';
  destroyMatch(match);
  return (createMatch(buffer, NULL, sizeof(buffer)));
}

t_parser_ctx *joinCharacters(t_parser_ctx *child) {
  return (map(child, &joinCharactersMap));
}