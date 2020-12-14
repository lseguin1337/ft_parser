#include <stdio.h>
#include "ft_parser.h"

/**
 * This file is not use by default
 * in order to use it please run the following command:
 *   $> make DEBUG=true
 * 
 * The purpose of this function is to be able to easily debug your parser
 * during your development.
 */
static t_parser_match *debugFn(t_parser_ctx *ctx, char **s) {
  char *start;
  char *label;
  t_parser_match *match;

  start = *s;
  label = (char *)ctx->data;
  if (!(match = ctx->child->fn(ctx->child, s)))
    printf("[%s]: Doesn't Match: \"%.1s\" \n", label, *s);
  else
    printf("[%s]: Match: \"%.*s\"\n", label, (int)(*s - start), start);
  return (match);
}

t_parser_ctx *debug(char *label, t_parser_ctx *child) {
  return (createContext(&debugFn, child, label, 0));
}