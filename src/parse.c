#include "ft_parser.h"

t_parser_match *ft_parse_from_ctx(t_parser_ctx *ctx, char *s) {
  return ctx->fn(ctx, &s);
}

t_parser_match *ft_parse(t_parser_factory factory, char *s) {
  t_parser_ctx *ctx;
  t_parser_match *match;

  ctx = factory();
  match = ft_parse_from_ctx(ctx, s);
  destroyContext(ctx);
  return match;
}