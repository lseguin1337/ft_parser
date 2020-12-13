#include "ft_parser.h"

static t_parser_match *sequenceOfFn(t_parser_ctx *ctx, char **s) {
  char *orig;
  t_parser_ctx *child;
  t_parser_match *first;
  t_parser_match *match;
   
  orig = *s;
  first = NULL;
  child = ctx->child;
  while (child) {
    if (!(match = child->fn(child, s))) {
      destroyMatch(first);
      *s = orig;
      return (NULL);
    }
    push_chunk((void **)&first, match);
    child = get_next_chunk(child);
  }
  return (createMatch(first, (void *)&destroyMatch, 0));
}

t_parser_ctx *sequenceOf(t_parser_ctx *first, ...) {
  va_list args;
  t_parser_ctx *child;

  va_start(args, first);
  while ((child = va_arg(args, t_parser_ctx *)))
    push_chunk((void **)&first, child);
  return (createContext(&sequenceOfFn, first, NULL, 0));
}