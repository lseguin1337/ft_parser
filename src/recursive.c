#include "ft_parser.h"

t_parser_match *recursiveFn(t_parser_ctx *ctx, char **s) {
  t_parser_factory factory;
  t_parser_ctx *child;
  t_parser_match *match;

  factory = ctx->data;
  child = factory();
  match = child->fn(child, s);
  destroyContext(child);
  return (match);
}

t_parser_ctx *recursive(t_parser_factory sub) {
  return createContext(&recursiveFn, NULL, sub, 0);
}