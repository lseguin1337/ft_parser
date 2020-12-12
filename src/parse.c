#include "ft_parser.h"

t_parser_match *parse(t_parser_ctx *ctx, char *s) {
  return ctx->fn(ctx, &s);
}