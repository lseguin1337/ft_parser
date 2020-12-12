#ifndef __FT_CALC__
# define __FT_CALC__

#include <stdio.h>
#include "ft_parser.h"

t_parser_ctx *Calc();
t_parser_ctx *Expression();
t_parser_ctx *Term();
t_parser_ctx *whitespace();
t_parser_ctx *Factor();

#endif