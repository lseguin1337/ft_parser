# ft_parser

This library is a generic Grammar Library for the C language.

That can be use to parse any input you want. As example there is some small grammar to parse a printf string or a calc.

```c
#include <stdio.h>
#include "ft_parser.h"

t_parser_ctx *whitespace() {
  return (
    oneOrMore(character(" \t\n\r"))
  );
}

t_parser_ctx *word() {
  return (
    joinCharacters(oneOrMore(sequenceOf(
      not(whitespace()),
      anyCharacter(),
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

  if ((match = ft_parse(helloGrammar, "hello world!")))
    printf("Result: %s\n", match->data); // Output -> "Result: world"
  else
    printf("String doesn't match\n");
  return (0);
}
```
## How to debug your grammar?

Re-build the library
```shell
make DEBUG=1
```

then you will be able to use the debug function like this:

```c
t_parser_ctx *my_grammar() {
  return (
    debug(
      "my_rule",
      sequenceOf(
        exact("word"),
        oneOrMore(charactersInList(" \t\n")),
        oneOrMore(character("0-9")),
        NULL
      )
    )
  );
}

int main() {
  ft_parse(my_grammar, "word 23!"); // Stdout: [my_rule]: Match: "word 23"
  return (0);
}
```