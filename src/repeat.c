#include "ft_parser.h"

typedef struct s_repeat_param {
  int max;
  int min;
}              t_repeat_param;

static t_parser_match *repeatFn(t_parser_ctx *ctx, char **s) {
  t_repeat_param *p = ((t_repeat_param *)ctx->data);
  t_parser_match *first;
  t_parser_match *match;
  t_parser_ctx *child = ctx->child;
  int i;

  i = 0;
  first = NULL;
  while ((match = child->fn(child, s)) && (p->max == 0 || i < p->max)) {
    push_chunk((void **)&first, match);
    i++;
  }
  if (i < p->min) {
    destroyMatch(first);
    return (NULL);
  }
  return (createMatch(first, (void *)&destroyMatch, 0));
}

t_parser_ctx *repeat(t_parser_ctx *child, int min, int max) {
  t_repeat_param param;
  param.min = min;
  param.max = max;
  return (createContext(&repeatFn, child, &param, sizeof(t_repeat_param)));
}