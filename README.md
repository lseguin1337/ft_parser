# ft_parser

This library is a generic Grammar Library for the C language.

That can be use to parse any text you want. As example there is some small grammar to parse a printf string or a calc.

```c
#include <stdio.h>
#include "ft_parser.h"

t_parser_ctx *whitespace() {
  return (
    oneOrMore(characters(" \t\n\r"))
  );
}

t_parser_ctx *word() {
  return (
    joinCharacters(oneOrMore(sequenceOf(
      not(whitespace()),
      characters(NULL),
      NULL
    )))
  );
}

t_parser_ctx *helloGrammar() {
  return (
    pick(sequenceOf(
      exact("hello"),
      whitespace(),
      word(),
      zeroOrOne(whitespace()),
      exact("!"),
      eof(),
      NULL
    ), 2)
  );
}

int main() {
  t_parser_match *match;

  if ((match = ft_parser_2(helloGrammar, "hello world!")))
    printf("Result: %s\n", match->data); // Output -> "Result: world"
  else
    printf("String doesn't match\n");
  return (0);
}
```