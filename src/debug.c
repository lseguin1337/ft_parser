#include "ft_parser.h"

static t_parser_match *debugFn(t_parser_ctx *ctx, char **s) {
  char *start = *s;
  char *label = (char *)ctx->data;
  t_parser_match *match;

  if (!(match = ctx->child->fn(ctx->child, s)))
    printf("[%s]: Doesn't Match: \"%.1s\" \n", label, *s);
  else
    printf("[%s]: Match: \"%.*s\"\n", label, (int)(*s - start), start);
  return (match);
}

t_parser_ctx *debug(char *label, t_parser_ctx *child) {
  return (createContext(&debugFn, child, label, 0));
}