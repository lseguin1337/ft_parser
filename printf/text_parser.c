#include "ft_printf.h"

static t_parser_match *create_text(t_parser_match *match) {
  char buffer[sizeof(t_text) + ft_strlen(match->data) + 1];
  t_text *text;

  ft_memcpy(&buffer[sizeof(t_text)], match->data, sizeof(buffer) - sizeof(t_text));
  destroyMatch(match);
  if (!(match = createMatch(buffer, NULL, sizeof(buffer))))
    return (NULL);
  text = (t_text *)match->data;
  text->type = TEXT;
  text->value = (void *)&text[1];
  return (match);
}

static t_parser_ctx *character() {
  return (anyOf(
    exact("%%"),
    pick(sequenceOf(
      not(exact("%")),
      characters(NULL),
      NULL
    ), 1),
    NULL
  ));
}

t_parser_ctx *text() {
  return (map(joinCharacters(oneOrMore(character())), &create_text));
}