#include <iostream>
#include "frontend/lexer.cpp"
#include "frontend/token.hpp"
#include <vector>
int main() {
  // REPL
  std::string code;
  std::vector<Token> toks;
  std::cout << "REPL" << '\n' << "enter 'quit' to exit" << '\n';
  for (;;) {
    std::cout << ">> ";
    std::getline(std::cin, code);
    if (code.empty()) continue;
    if (code == "quit")
      exit(0);
    Lexer lex(code);
    toks = lex.tokenize();
    for (auto tok : toks) {
      prettyPrint(tok);
    }
  }
  
}