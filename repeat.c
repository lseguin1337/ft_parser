#include "ft_parser.h"

static t_parser_match *repeatFn(t_parser_ctx *ctx, char **s) {
  int count = *((int *)ctx->data);
  t_parser_match *first;
  t_parser_match *match;
  t_parser_ctx *child = ctx->child;

  first = NULL;
  while ((match = child->fn(child, s)) && count > 0) {
    push_chunk((void **)&first, match);
    count--;
  }
  if (count != 0) {
    destroyMatch(first);
    return (NULL);
  }
  return (createMatch(first, (void *)&destroyMatch));
}

t_parser_ctx *repeat(t_parser_ctx *child, int count) {
  return (createContext(&repeatFn, child, &count, sizeof(int)));
}