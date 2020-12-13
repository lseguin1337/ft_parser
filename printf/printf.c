#include "ft_printf.h"

void ft_printf(char *s, ...) {
  t_parser_match *match;
  t_parser_match *chunk;
  t_text *text;
  t_flag *flag;

  if ((match = ft_parse_2(printf_parser, s))) {
    chunk = match->data;
    while (chunk) {
      if (*(t_match_type *)chunk->data == TEXT) {
        text = (t_text *)chunk->data;
        printf("TEXT \"%s\"\n", text->value);
      } else {
        flag = (t_flag *)chunk->data;
        printf("FLAG marge: %d; precision: %d; long_flag %d;\n", flag->marge, flag->precision, flag->long_flag);
      }
      chunk = get_next_chunk(chunk);
    }
    
    printf("succeed\n");
  } else {
    printf("failure\n");
  }
}