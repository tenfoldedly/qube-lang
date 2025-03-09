#pragma once
#include <unordered_map>
#include <string>
#include <iostream>
#undef EOF
enum class TokenType {
  // Multi-char Tokens!
  INTLIT, FLOATLIT, SYMBOL,

  // Operations!
  PLUS, DASH, STAR, SLASH,
  EQEQ, BANGEQ, GREATEREQ, LESSEREQ,
  GREATER, LESSER,

  // Grouping!
  LEFTPAR, RIGHTPAR,
  LEFTCURLY, RIGHTCURLY,
  LEFTBRACK, RIGHTBRACK,

  // Misc!
  EQ, BANG, DOT, COMMA, SEMI, COLON,

  // Types!
  BYTE, INT, FLOAT, DOUBLE,
  
  // Keywords!
  FUNC, RETURN,
  STRUCT,
  IF, ELSE,
  MATCH, CASE,
  WHILE, FOR, FOREACH,

  // End of File!
  EOF
};

const std::unordered_map<std::string, TokenType> RESERVED = {
  {"func", TokenType::FUNC},
  {"return", TokenType::RETURN},
  {"struct", TokenType::STRUCT},
  {"if", TokenType::IF},
  {"else", TokenType::ELSE},
  {"match", TokenType::MATCH},
  {"case", TokenType::CASE},
  {"while", TokenType::WHILE},
  {"for", TokenType::FOR},
  {"foreach", TokenType::FOREACH},
  {"int", TokenType::INT},
  {"float", TokenType::FLOAT},
  {"byte", TokenType::BYTE},
  {"double", TokenType::DOUBLE},
};

struct Token {
  TokenType type;
  std::string value; // manually convert this to int/float later if needed
};

inline Token makeToken(TokenType type, std::string value = "") {
  Token tk;
  tk.type = type;
  tk.value = value;
  return tk;
}

inline void prettyPrint(Token tk) {
  std::cout << "TYPE: (" << (int)tk.type << ") " << "VALUE: (" << tk.value << ") " << "\n";
}