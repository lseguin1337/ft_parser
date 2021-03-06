#include "ft_parser.h"

static t_parser_match *notFn(t_parser_ctx *ctx, char **s) {
  t_parser_ctx *child;
  t_parser_match *match;
  char *orig;

  child = ctx->child;
  orig = *s;
  if (!(match = child->fn(child, s)))
    return (createMatch(NULL, NULL, 0));
  destroyMatch(match);
  *s = orig;
  return (NULL);
}

t_parser_ctx *not(t_parser_ctx *child) {
  return (createContext(&notFn, child, NULL, 0));
}