#include <vector>
#include <string>
#include <cctype>
#include "token.hpp"

class Lexer {
  private:
    std::string source;
    size_t pos = 0;
    std::vector<Token> tokens;
  
  public:
    Lexer(const std::string& source) : source(source) {}

    bool isEnd() const {
      return pos >= source.length();
    }

    char at() const {
      return isEnd() ? '\0' : source.at(pos);
    }

    std::string slice(int n) const {
      return isEnd() ? "" : source.substr(pos, n);
    }

    void addTok(const Token& tk) {
      tokens.push_back(tk);
    }

    void advance(int n = 1) {
      pos = std::min(pos + n, source.length());
    }

    void handleNum() {
      std::string buffer;
      int dotCount = 0;
      while (!isEnd() && (isdigit(at()) || at() == '.')) {
        if (at() == '.') dotCount++;
        buffer.push_back(at());
        advance();
      }
      if (dotCount > 1)
        exit(1); //error here
      else if (dotCount == 1)
        addTok(makeToken(TokenType::FLOATLIT, buffer));
      else
        addTok(makeToken(TokenType::INTLIT, buffer));
    }

    void handleSymbol() {
      std::string buffer;
      while (!isEnd() && isalnum(at())) {
        buffer.push_back(at());
        advance();
      }
      if (RESERVED.find(buffer) != RESERVED.end())
        addTok(makeToken(RESERVED.at(buffer)));
      else
        addTok(makeToken(TokenType::SYMBOL, buffer));
    }

    std::vector<Token> tokenize() {
      while (!isEnd()) {
        char current = at();

        if (isspace(current)) {
          advance();
          continue;
        }

        // 2-character tokens!
        if (slice(2) == "==") { addTok(makeToken(TokenType::EQEQ)); advance(2); continue; }
        if (slice(2) == "!=") { addTok(makeToken(TokenType::BANGEQ)); advance(2); continue; }
        if (slice(2) == ">=") { addTok(makeToken(TokenType::GREATEREQ)); advance(2); continue; }
        if (slice(2) == "<=") { addTok(makeToken(TokenType::LESSEREQ)); advance(2); continue; }

        // 1-character tokens!
        switch (current) {
          case '+': addTok(makeToken(TokenType::PLUS)); break;
          case '-': addTok(makeToken(TokenType::DASH)); break;
          case '*': addTok(makeToken(TokenType::STAR)); break;
          case '/': addTok(makeToken(TokenType::SLASH)); break;
          case '(': addTok(makeToken(TokenType::LEFTPAR)); break;
          case ')': addTok(makeToken(TokenType::RIGHTPAR)); break;
          case '[': addTok(makeToken(TokenType::LEFTBRACK)); break;
          case ']': addTok(makeToken(TokenType::RIGHTBRACK)); break;
          case '{': addTok(makeToken(TokenType::LEFTCURLY)); break;
          case '}': addTok(makeToken(TokenType::RIGHTCURLY)); break;
          case '=': addTok(makeToken(TokenType::EQ)); break;
          case '!': addTok(makeToken(TokenType::BANG)); break;
          case '>': addTok(makeToken(TokenType::GREATER)); break;
          case '<': addTok(makeToken(TokenType::LESSER)); break;
          case '.': addTok(makeToken(TokenType::DOT)); break;
          case ',': addTok(makeToken(TokenType::COMMA)); break;
          case ':': addTok(makeToken(TokenType::COLON)); break;
          case ';': addTok(makeToken(TokenType::SEMI)); break;
          default:
            if (isdigit(current)) {
              handleNum();
              continue;
            } else if (isalpha(current)) {
              handleSymbol();
              continue;
            } else {
              // error
              exit(1);
            }
        }
        advance();
      }
      addTok(makeToken(TokenType::EOF));
      return tokens;
    }
};
