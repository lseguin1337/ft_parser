#include "ft_parser.h"

static t_parser_match *oneOrMoreFn(t_parser_ctx *ctx, char **s) {
  t_parser_match *first;
  t_parser_match *match;
  t_parser_ctx *child;

  first = NULL;
  child = ctx->child;
  while ((match = child->fn(child, s)))
    push_chunk((void **)&first, match);
  if (!first)
    return (NULL);
  return (createMatch(first, (void *)&destroyMatch, 0));
}

t_parser_ctx *oneOrMore(t_parser_ctx *child) {
  return (createContext(&oneOrMoreFn, child, NULL, 0));
}