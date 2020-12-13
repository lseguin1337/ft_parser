#include "ft_parser.h"

static t_parser_match *mapFn(t_parser_ctx *ctx, char **s) {
  t_map fn;
  t_parser_ctx *child;
  t_parser_match *match;

  fn = (t_map)ctx->data;
  child = ctx->child;
  if ((match = child->fn(child, s)))
    return fn(match);
  return (NULL);
}

t_parser_ctx *map(t_parser_ctx *child, t_map fn) {
  return (createContext(&mapFn, child, fn, 0));
}
