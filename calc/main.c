#include "calc.h"

static int mult_operator(int left, int right) {
  return left * right;
}

static int div_operator(int left, int right) {
  return left / right;
}

static int add_operator(int left, int right) {
  return left + right;
}

static int sub_operator(int left, int right) {
  return left + right;
}

static t_parser_match *compute(t_parser_match *match) {
  t_parser_match *first_term = match->data;
  t_parser_match *seq;
  t_parser_match *tmp_term;
  int (*operator)(int, int);
  int value;
  
  value = *(int *)first_term->data;
  seq = ((t_parser_match *)get_next_chunk(first_term))->data;
  while (seq) {
    operator = ((t_parser_match *)get_chunk((t_parser_match *)seq->data, 1))->data;
    tmp_term = get_chunk((t_parser_match *)seq->data, 3);
    value = operator(value, *(int *)tmp_term->data);
    seq = get_next_chunk(seq);
  }
  destroyMatch(match);
  return (createMatch(&value, NULL, sizeof(value)));
}

t_parser_ctx *whitespace() {
  return (zeroOrMore(characters(" \t\n\r")));
}

t_parser_ctx *Factor() {
  return (debug("factor", anyOf(
    pick(sequenceOf(
      exact("("),
      whitespace(),
      recursive(&Expression),
      whitespace(),
      exact(")"),
      NULL
    ), 2),
    integer(),
    NULL
  )));
}

t_parser_ctx *Term() {
  return (debug("term", map(sequenceOf(
    Factor(),
    zeroOrMore(sequenceOf(
      whitespace(),
      anyOf(
        mapTo(exact("*"), &mult_operator),
        mapTo(exact("/"), &div_operator),
        NULL
      ),
      whitespace(),
      Factor(),
      NULL
    )),
    NULL
  ), &compute)));
}

t_parser_ctx *Expression() {
  return (debug("expression", map(sequenceOf(
    Term(),
    zeroOrMore(sequenceOf(
      whitespace(),
      anyOf(
        mapTo(exact("+"), &add_operator),
        mapTo(exact("-"), &sub_operator),
        NULL
      ),
      whitespace(),
      Term(),
      NULL
    )),
    NULL
  ), &compute)));
}

t_parser_ctx *CalcGrammar() {
  return (pick(sequenceOf(
    Expression(),
    eof(),
    NULL
  ), 0));
}

int main() {
  t_parser_match *match;

  if ((match = ft_parse(CalcGrammar, "2 * (3 + 4)"))) {
    printf("Result: %d\n", *(int *)match->data); // Output -> "Result: 14"
  } else {
    printf("parsing error\n");
  }
}