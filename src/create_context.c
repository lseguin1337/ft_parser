#include "ft_parser.h"

t_parser_ctx *createContext(
  t_parse_fn fn,
  t_parser_ctx *child,
  void *data,
  size_t data_size
) {
  t_parser_ctx *ctx;

  if (data_size < 0)
    return (NULL);
  if (!(ctx = create_chunk(sizeof(t_parser_ctx) + data_size)))
    return (NULL);
  ctx->fn = fn;
  ctx->child = child;
  ctx->destroy = NULL;
  ctx->data = data;
  if (data_size > 0)
    ctx->data = ft_memcpy(&ctx[1], data, data_size);
  return (ctx);
}
