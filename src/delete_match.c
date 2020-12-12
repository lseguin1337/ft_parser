#include "ft_parser.h"

void destroyMatch(t_parser_match *self) {  
  if (!self)
    return;
  destroyMatch(get_next_chunk(self));
  if (self->destroy && self->data)
    self->destroy(self->data);
  del_chunk(self);
}