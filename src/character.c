#include "ft_parser.h"

static t_parser_match *charactersFn(t_parser_ctx *ctx, char **s) {
  char *value;
  int i = 0;

  value = (char *)ctx->data;
  if (!value) {
    if (!(*s)[0])
      return (NULL);
    return (createMatch((*s)++, NULL, sizeof(char)));
  }
  while ((*s)[0] != value[i] && value[i])
    i++;
  if (!value[i])
    return (NULL);
  return (createMatch((*s)++, NULL, sizeof(char)));
}

t_parser_ctx *characters(char *value) {
  int len;

  len = 0;
  if (value)
    len = ft_strlen(value) + 1;
  return (createContext(&charactersFn, NULL, value, len));
}