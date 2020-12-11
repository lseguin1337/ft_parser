#include "ft_parser.h"

static t_parser_match *joinCharactersMap(t_parser_match *match) {
  t_parser_match *character = (t_parser_match *)match->data;
  char *dest;
  int i;

  i = 0;
  character = (t_parser_match *)match->data;
  if (!(dest = malloc(sizeof(char) * (count_chunk(character) + 1))))
    return (NULL);
  while (character) {
    dest[i++] = ((char *)character->data)[0];
    character = get_next_chunk(character);
  }
  dest[i] = '\0';
  destroyMatch(match);
  return (createMatch(dest, &free));
}

t_parser_ctx *joinCharacters(t_parser_ctx *child) {
  return (map(child, &joinCharactersMap));
}
