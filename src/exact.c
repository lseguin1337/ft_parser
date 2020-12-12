#include "ft_parser.h"

static t_parser_match *exactFn(t_parser_ctx *ctx, char **s) {
  char *value = (char *)ctx->data;
  int i = 0;

  while ((*s)[i] == value[i] && value[i])
    i++;
  if (!value[i]) {
    (*s) += i;
    return (createMatch(value, NULL, 0));
  }
  return (NULL);
}

t_parser_ctx *exact(char *value) {
  return (createContext(&exactFn, NULL, value, ft_strlen(value) + 1));
}