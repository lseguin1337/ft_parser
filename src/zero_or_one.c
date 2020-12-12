#include "ft_parser.h"

static t_parser_match *zeroOrOneFn(t_parser_ctx *ctx, char **s) {
  t_parser_ctx *child = ctx->child;
  t_parser_match *match;

  if ((match = child->fn(child, s)))
    return (match);
  return (createMatch(NULL, NULL, 0));
}

t_parser_ctx *zeroOrOne(t_parser_ctx *child) {
  return (createContext(&zeroOrOneFn, child, NULL, 0));
}