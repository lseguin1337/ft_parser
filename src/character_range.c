#include "ft_parser.h"

typedef struct s_character_range_param {
  char start;
  char end;
}              t_character_range_param;

static t_parser_match *characterRangeFn(t_parser_ctx *ctx, char **s) {
  t_character_range_param *param;
  char c;

  param = ctx->data;
  c = param->start;
  while (c <= param->end) {
    if (c == **s)
      return (createMatch((*s)++, NULL, sizeof(char)));
    c++;
  }
  return (NULL);
}

t_parser_ctx *characterRange(char start, char end) {
  t_character_range_param param;
  
  param.start = start;
  param.end = end;
  return (createContext(&characterRangeFn, NULL, &param, sizeof(param)));
}
