#include "ft_parser.h"

static t_parser_match *debugFn(t_parser_ctx *ctx, char **s) {
  char *start = *s;
  char *label = (char *)ctx->data;
  char *matched;
  t_parser_match *match;

  if (!(match = ctx->child->fn(ctx->child, s)))
    printf("[%s]: Doesn't Match: \"%.1s\" \n", label, *s);
  else {
    matched = ft_strndup(start, *s - start);
    printf("[%s]: Match: \"%s\"\n", label, matched);
    free(matched);
  }
  return (match);
}

t_parser_ctx *debug(char *label, t_parser_ctx *child) {
  return (createContext(&debugFn, child, label, 0));
}