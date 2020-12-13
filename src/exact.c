#include "ft_parser.h"

static t_parser_match *exactFn(t_parser_ctx *ctx, char **s) {
  char *value;
  int i = 0;

  value = (char *)ctx->data;
  while ((*s)[i] == value[i] && value[i])
    i++;
  if (value[i])
    return (NULL);
  (*s) += i;
  return (createMatch(value, NULL, i + 1));
}

t_parser_ctx *exact(char *value) {
  return (createContext(&exactFn, NULL, value, ft_strlen(value) + 1));
}