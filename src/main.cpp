#include <iostream>
#include "frontend/lexer.cpp"
#include "frontend/token.hpp"
#include <vector>
int main() {
  std::string code = "int num = (10 + 20) * 5 / 2";
  Lexer lex(code);
  std::vector<Token> toks = lex.tokenize();

  for (auto tok : toks) {
    prettyPrint(tok);
  }
  return 0;
}