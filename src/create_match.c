#include "ft_parser.h"

t_parser_match *createMatch(
  void *data,
  void (*destroy)(void *),
  size_t data_size
) {
  t_parser_match *self;

  if (data_size < 0)
    return (NULL);
  if (!(self = create_chunk(sizeof(t_parser_match) + data_size)))
    return (NULL);
  self->data = data;
  self->destroy = destroy;
  if (data_size > 0)
    self->data = ft_memcpy(&self[1], data, data_size);
  return (self);
}
