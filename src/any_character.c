#include "ft_parser.h"

static t_parser_match *anyCharacterFn(t_parser_ctx *ctx, char **s) {
  (void)ctx;
  if (**s)
    return createMatch((*s)++, NULL, 1);
  return (NULL);
}

t_parser_ctx *anyCharacter() {
  return (createContext(&anyCharacterFn, NULL, NULL, 0));
}