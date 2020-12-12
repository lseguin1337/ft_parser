#ifndef __FT_PARSER__
# define __FT_PARSER__

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct         s_parser_match {
  void                 *data;
  void                 (*destroy)(void *data);
}                      t_parser_match;

typedef t_parser_match *(*t_map)(t_parser_match *match);

typedef struct         s_parser_ctx {
  t_parser_match       *(*fn)(struct s_parser_ctx *self, char **s);
  struct s_parser_ctx  *child;
  void                 *data;
  void                 (*destroy)(void *data);
}                      t_parser_ctx;

typedef t_parser_ctx   *(*t_sub_ctx)();
typedef t_parser_match *(*t_parse_fn)(t_parser_ctx *ctx, char **s);

t_parser_ctx           *createContext(t_parse_fn fn, t_parser_ctx *child, void *data, size_t size);
void                   destroyContext(t_parser_ctx *ctx);

t_parser_match         *createMatch(void *data, void (*del)(void *));
void                   destroyMatch(t_parser_match *self);

t_parser_ctx           *oneOrMore(t_parser_ctx *child);
t_parser_ctx           *zeroOrMore(t_parser_ctx *child);
t_parser_ctx           *zeroOrOne(t_parser_ctx *child);
t_parser_ctx           *anyOf(t_parser_ctx *firstChild, ...);
t_parser_ctx           *sequenceOf(t_parser_ctx *firstChild, ...);
t_parser_ctx           *not(t_parser_ctx *child);
t_parser_ctx           *exact(char *text);
t_parser_ctx           *characters(char *chars);
t_parser_ctx           *repeat(t_parser_ctx *child, int min, int max);
t_parser_ctx           *eof();

t_parser_ctx           *map(t_parser_ctx *child, t_map fn);
t_parser_ctx           *pick(t_parser_ctx *child, int index);
t_parser_ctx           *mapTo(t_parser_ctx *child, void *data);
t_parser_ctx           *joinCharacters(t_parser_ctx *child);
t_parser_ctx           *integer();
t_parser_ctx           *recursive(t_sub_ctx sub);

t_parser_ctx           *debug(char *label, t_parser_ctx *child);

void                   *parse(t_parser_ctx *ctx, char *s);

void                   *create_chunk(size_t size);
void                   del_chunk(void *ptr);
void                   *get_next_chunk(void *ptr);
void                   set_next_chunk(void *ptr, void *next);
void                   push_chunk(void **first, void *last);
int                    count_chunk(void *ptr);
void                   *get_chunk(void *ptr, int index);

// libft
char                   *ft_strndup(char *s, int size);
void                   *ft_memcpy(void *dest, void *src, size_t size);
void                   *ft_memset(void *dest, char c, size_t size);
int                    ft_strlen(char *s);

#endif