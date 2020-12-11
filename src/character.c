#include "ft_parser.h"

static t_parser_match *charactersFn(t_parser_ctx *ctx, char **s) {
  char *value = (char *)ctx->data;
  int i = 0;

  if (!value) {
    if (!(*s)[0])
      return (NULL);
    return (createMatch((*s)++, NULL));
  }
  while ((*s)[0] != value[i] && value[i])
    i++;
  if (!value[i])
    return (NULL);
  return (createMatch((*s)++, NULL));
}

t_parser_ctx *characters(char *value) {
  int len;

  len = 0;
  if (value)
    len = ft_strlen(value) + 1;
  return (createContext(&charactersFn, NULL, value, len));
}