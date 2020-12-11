#include <stdlib.h>

int ft_strlen(char *s) {
  int i = 0;

  while (s[i])
    i++;
  return i;
}

void *ft_memcpy(void *dest, void *src, size_t size) {
  int i;

  i = 0;
  while (i < size) {
    ((char *)dest)[i] = ((char *)src)[i];
    i++;
  }
  return (dest);
}

void *ft_memset(void *dest, char c, size_t size) {
  int i;

  i = 0;
  while (i < size)
    ((char *)dest)[i++] = c;
  return (dest);
}

char *ft_strndup(char *s, int size) {
  char *n;
  int i = 0;

  if (!(n = malloc(sizeof(char) * (size + 1))))
    return (NULL);
  while (s[i] && i < size) {
    n[i] = s[i];
    i++;
  }
  n[i] = '\0';
  return (n);
}
