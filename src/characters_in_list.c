#include "ft_parser.h"

static t_parser_match *characterInListFn(t_parser_ctx *ctx, char **s) {
  char *value;
  int i = 0;

  value = (char *)ctx->data;
  while ((*s)[0] != value[i] && value[i])
    i++;
  if (!value[i])
    return (NULL);
  return (createMatch((*s)++, NULL, sizeof(char)));
}

t_parser_ctx *characterInList(char *value) {
  int len;

  len = ft_strlen(value) + 1;
  return (createContext(&characterInListFn, NULL, value, len));
}