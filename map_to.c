#include "ft_parser.h"

static t_parser_match *mapToFn(t_parser_ctx *ctx, char **s) {
  t_parser_ctx *child = ctx->child;
  t_parser_match *match;

  if ((match = child->fn(child, s))) {
    destroyMatch(match);
    return (createMatch(ctx->data, NULL));
  }
  return (NULL);
}

t_parser_ctx *mapTo(t_parser_ctx *child, void *res) {
  return (createContext(&mapToFn, child, res, 0));
}