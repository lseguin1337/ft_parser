#include "ft_parser.h"

void  *parse(t_parser_ctx *ctx, char *s) {
  t_parser_match *match;

  if (!(match = ctx->fn(ctx, &s)))
    return (NULL);
  return (match);
}