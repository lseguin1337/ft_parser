#include "ft_parser.h"

static t_parser_match *eofFn(t_parser_ctx *ctx, char **s) {
  (void)ctx;
  if ((*s)[0] != '\0')
    return (NULL);
  return (createMatch(NULL, NULL));
}

t_parser_ctx *eof() {
  return (createContext(&eofFn, NULL, NULL, 0));
}