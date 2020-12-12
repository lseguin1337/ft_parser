#include "ft_parser.h"

void  *create_chunk(size_t size) {
  char     *ptr;
  size_t   rsize;

  rsize = sizeof(void *) + size;
  if (!(ptr = malloc(rsize)))
    return (NULL);
  ft_memset(ptr, '\0', rsize);
  return (&((void **)ptr)[1]);
}

void set_next_chunk(void *ptr, void *next) {
  void **pptr = ptr;

  pptr[-1] = next;
}

void *get_next_chunk(void *ptr) {
  void **pptr = ptr;

  return (pptr[-1]);
}

void push_chunk(void **first, void *last) {
  void *tmp;

  if (!*first) {
    *first = last;
    return;
  }
  tmp = *first;
  while (get_next_chunk(tmp))
    tmp = get_next_chunk(tmp);
  set_next_chunk(tmp, last);
}

void del_chunk(void *ptr) {
  void **pptr = ptr;

  free(&pptr[-1]);
}

int count_chunk(void *ptr) {
  int i = 0;

  while (ptr) {
    ptr = get_next_chunk(ptr);
    i++;
  }
  return i;
}

void *get_chunk(void *ptr, int index) {
  while (index-- && ptr)
    ptr = get_next_chunk(ptr);
  return (ptr);
}