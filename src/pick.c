#include "ft_parser.h"

static t_parser_match *pickFn(t_parser_ctx *ctx, char **s) {
  t_parser_match *match;
  t_parser_match *previous;
  t_parser_match *target;
  int index;

  index = *((int *)ctx->data);
  if (!(match = ctx->child->fn(ctx->child, s)))
    return (NULL);
  previous = NULL;
  target = (t_parser_match *)match->data;
  while (index-- > 0 && target) {
    previous = target;
    target = get_next_chunk(target);
  }
  if (!target) {
    destroyMatch(match);
    return (createMatch(NULL, NULL));
  }
  if (!previous)
    match->data = get_next_chunk(target);  
  else
    set_next_chunk(previous, get_next_chunk(target));
  set_next_chunk(target, NULL);
  destroyMatch(match);
  return (target);
}

t_parser_ctx *pick(t_parser_ctx *child, int index) {
  return (createContext(&pickFn, child, &index, sizeof(int)));
}