#include "ft_parser.h"

static t_parser_match *zeroOrMoreFn(t_parser_ctx *ctx, char **s) {
  t_parser_ctx *child = ctx->child;
  t_parser_match *first;
  t_parser_match *match;
  
  first = NULL;
  while ((match = child->fn(child, s)))
    push_chunk((void **)&first, match);
  if (!first)
    return (createMatch(NULL, NULL));
  return (createMatch(first, (void *)&destroyMatch));
}

t_parser_ctx *zeroOrMore(t_parser_ctx *child) {
  return (createContext(&zeroOrMoreFn, child, NULL, 0));
}