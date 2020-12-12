#include "ft_parser.h"

t_parser_match *recursiveFn(t_parser_ctx *ctx, char **s) {
  t_parser_factory factory = ctx->data;
  t_parser_ctx *child = factory();
  t_parser_match *match;

  match = child->fn(child, s);
  destroyContext(child);
  return (match);
}

t_parser_ctx *recursive(t_parser_factory sub) {
  return createContext(&recursiveFn, NULL, sub, 0);
}