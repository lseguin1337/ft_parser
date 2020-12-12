#include "ft_parser.h"

t_parser_match *recursiveFn(t_parser_ctx *ctx, char **s) {
  t_sub_ctx ctx_builder = ctx->data;
  t_parser_ctx *child = ctx_builder();
  t_parser_match *match;

  match = child->fn(child, s);
  destroyContext(child);
  return (match);
}

t_parser_ctx *recursive(t_sub_ctx sub) {
  return createContext(&recursiveFn, NULL, sub, 0);
}