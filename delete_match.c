#include "ft_parser.h"

void destroyMatch(t_parser_match *self) {
  t_parser_match *next;
  
  if ((next = get_next_chunk(self)))
    destroyMatch(next);
  if (self->destroy && self->data)
    self->destroy(self->data);
  del_chunk(self);
}