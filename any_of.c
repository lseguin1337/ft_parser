#include "ft_parser.h"

static t_parser_match *anyOfFn(t_parser_ctx *ctx, char **s) {
  t_parser_ctx *child;
  t_parser_match *match;

  child = ctx->child;
  while (child) {
    if ((match = child->fn(child, s)))
      return (match);
    child = get_next_chunk(child);
  }
  return (NULL);
}

t_parser_ctx *anyOf(t_parser_ctx *first, ...) {
  va_list args;
  t_parser_ctx *child;
  
  va_start(args, first);
  while ((child = va_arg(args, t_parser_ctx *)))
    push_chunk((void **)&first, child);
  return (createContext(&anyOfFn, first, NULL, 0));
}