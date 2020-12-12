#include "ft_parser.h"

/**
 * TODO: Add private data like we have inside the context
 */
t_parser_match *createMatch(
  void *data,
  void (*destroy)(void *)
) {
  t_parser_match *self;

  if (!(self = create_chunk(sizeof(t_parser_match))))
    return (NULL);
  self->data = data;
  self->destroy = destroy;
  return (self);
}
