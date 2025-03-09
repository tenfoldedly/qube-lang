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

    bool isEnd() {
      return !(pos < source.length());
    }

    char at() {
      return source.at(pos);
    }

    std::string slice(int n) {
      return source.substr(pos, n);
    }

    void addTok(Token tk) {
      tokens.push_back(tk);
    }

    void advance(int n = 1) {
      pos += n;
    }

    void handleNum() {
      std::string buffer;
      int dotCount;
      while (!isEnd() && (isdigit(at()) || at() == '.')) {
        buffer.push_back(at());
        if (at() == '.')
          dotCount++;
        advance();
      }
      if (dotCount == 0)
        addTok(makeToken(TokenType::INTLIT, buffer));
      else if (dotCount == 1)
      addTok(makeToken(TokenType::FLOATLIT, buffer));
      // else error
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
        // 2 character tokens first!
        while (at() == ' ' || at() == '\n' || at() == '\t') {
          advance();
        }

        if (slice(2) == "==") {
          addTok(makeToken(TokenType::EQEQ));
          advance(2);
        } else if (slice(2) == "!=") {
          addTok(makeToken(TokenType::BANGEQ));
          advance(2);
        } else if (slice(2) == ">=") {
          addTok(makeToken(TokenType::GREATEREQ));
          advance(2);
        } else if (slice(2) == "<=") {
          addTok(makeToken(TokenType::LESSEREQ));
          advance(2);
        }

        // single character tokens!
        switch (at()) {
          case '+':
            addTok(makeToken(TokenType::PLUS));
            advance();
            break;
          case '-':
            addTok(makeToken(TokenType::DASH));
            advance();
            break;
          case '*':
            addTok(makeToken(TokenType::STAR));
            advance();
            break;
          case '/':
            addTok(makeToken(TokenType::SLASH));
            advance();
            break;
          case '(':
            addTok(makeToken(TokenType::LEFTPAR));
            advance();
            break;
          case ')':
            addTok(makeToken(TokenType::RIGHTPAR));
            advance();
            break;
          case '[':
            addTok(makeToken(TokenType::LEFTBRACK));
            advance();
            break;
          case ']':
            addTok(makeToken(TokenType::RIGHTBRACK));
            advance();
            break;
          case '{':
            addTok(makeToken(TokenType::LEFTCURLY));
            advance();
            break;
          case '}':
            addTok(makeToken(TokenType::RIGHTCURLY));
            advance();
            break;
          case '=':
            addTok(makeToken(TokenType::EQ));
            advance();
            break;
          case '!':
            addTok(makeToken(TokenType::BANG));
            advance();
            break;
          case '>':
            addTok(makeToken(TokenType::GREATER));
            advance();
            break;
          case '<':
            addTok(makeToken(TokenType::LESSER));
            advance();
            break;
          case '.':
            addTok(makeToken(TokenType::DOT));
            advance();
            break;
          case ',':
            addTok(makeToken(TokenType::COMMA));
            advance();
            break;
          case ':':
            addTok(makeToken(TokenType::COLON));
            advance();
            break;
          case ';':
            addTok(makeToken(TokenType::SEMI));
            advance();
            break;
          default:
            break;
        }

        if (isdigit(at())) {
          handleNum();
        } else if (isalpha(at())) {
          handleSymbol();
        }
      }
      addTok(makeToken(TokenType::EOF));
      return tokens;
    }
};