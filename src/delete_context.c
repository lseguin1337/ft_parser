#include "ft_parser.h"

void destroyContext(t_parser_ctx *self) {
  if (!self)
    return;
  destroyContext(get_next_chunk(self));
  destroyContext(self->child);
  if (self->destroy)
    self->destroy(self->data);
  del_chunk(self);
}