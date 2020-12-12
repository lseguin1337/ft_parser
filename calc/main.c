#include "calc.h"

static int operation(char operator, int left, int right) {
  if (operator == '-') {
    return left - right;
  } else if (operator == '+') {
    return left + right;
  } else if (operator == '*') {
    return left * right;
  } else if (operator == '/') {
    return left / right;
  }
  return -1;
}

static t_parser_match *compute(t_parser_match *match) {
  t_parser_match *first_term = match->data;
  t_parser_match *seq;
  t_parser_match *op;
  t_parser_match *right_term;
  int value = *((int *)first_term->data);
  
  seq = ((t_parser_match *)get_next_chunk(first_term))->data;
  while (seq) {
    op = get_chunk((t_parser_match *)seq->data, 1);
    right_term = get_chunk((t_parser_match *)seq->data, 3);
    value = operation(((char *)op->data)[0], value, *(int *)right_term->data);
    seq = get_next_chunk(seq);
  }
  destroyMatch(match);
  return (createMatch(&value, NULL, sizeof(value)));
}

t_parser_ctx *whitespace() {
  return (zeroOrMore(characters(" \t\n\r")));
}

t_parser_ctx *Factor() {
  return (anyOf(
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
  ));
}

t_parser_ctx *Term() {
  return (map(sequenceOf(
    Factor(),
    zeroOrMore(sequenceOf(
      whitespace(),
      characters("*/"),
      whitespace(),
      Factor(),
      NULL
    )),
    NULL
  ), &compute));
}

t_parser_ctx *Expression() {
  return (map(sequenceOf(
    Term(),
    zeroOrMore(sequenceOf(
      whitespace(),
      characters("+-"),
      whitespace(),
      Term(),
      NULL
    )),
    NULL
  ), &compute));
}

t_parser_ctx *Calc() {
  return (pick(sequenceOf(
    Expression(),
    eof(),
    NULL
  ), 0));
}

int main() {
  t_parser_match *match;

  if ((match = ft_parse_2(Calc, "2 * (3 + 4)"))) {
    printf("Result: %d\n", *(int *)match->data);
  } else {
    printf("parsing error\n");
  }
}