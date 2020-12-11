#include "ft_parser.h"

void destroyContext(t_parser_ctx *self) {
  t_parser_ctx *next;

  if ((next = get_next_chunk(self)))
    destroyContext(next);
  if (self->child)
    destroyContext(self->child);
  if (self->destroy)
    self->destroy(self->data);
  del_chunk(self);
}