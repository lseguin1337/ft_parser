#include "ft_parser.h"

t_parser_match *createMatch(
  void *data,
  void (*destroy)(void *),
  size_t size
) {
  t_parser_match *self;

  if (size < 0)
    return (NULL);
  if (!(self = create_chunk(sizeof(t_parser_match) + size)))
    return (NULL);
  self->data = data;
  self->destroy = destroy;
  if (size > 0) {
    self->data = &self[1];
    ft_memcpy(self->data, data, size);
  }
  return (self);
}
