#ifndef __FT_PRINTF_EXPRESSION__
# define __FT_PRINTF_EXPRESSION__

#include <stdio.h>
#include "ft_parser.h"

#define NEXT(x) ((t_parser_match *)(x = get_next_chunk(x)))

typedef struct s_flag_options {
  int          zero;
  int          plus;
  int          minus;
  int          space;
}              t_flag_options;

typedef struct   s_flag {
  int            marge;
  int            precision;
  int            long_flag;
  void           *format;
  t_flag_options options;
}                t_flag;

t_parser_ctx *flag();
t_parser_ctx *text();
t_parser_ctx *printf_parser();

char *format_string(t_flag *flag, va_list *args);
char *format_char(t_flag *flag, va_list *args);
char *format_hex(t_flag *flag, va_list *args);
char *format_integer(t_flag *flag, va_list *args);
char *format_ptr(t_flag *flag, va_list *args);
char *format_float(t_flag *flag, va_list *args);

void ft_printf(char *s, ...);

#endif