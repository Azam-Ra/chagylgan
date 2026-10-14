#pragma once

#include <expected>
#include <string>

#include <utf8.h>

#include "Error.hpp"
#include "Token.hpp"

class Lexer {
public:
  explicit Lexer(std::string text) : text_(std::move(text)) {}

  std::expected<Token, Diagnostic> nextToken() {
    if (pos_ >= text_.size())
      return Token(TokenKind::End, "");

    char32_t t = advance();
    if (t == '(') {
      return Token(TokenKind::LeftParen, "");
    } else if (t == ')') {
      return Token(TokenKind::RightParen, "");
    } else if (t == '"') {
      return obtain_string_token();
    } else if (is_kyrgyz_char(t)) {
      return obtain_keyword_token();
    } else {
      return std::unexpected(Diagnostic({pos_}, "Lexer: Non-valid char"));
    }
  }

private:
  size_t pos_ = 0;
  const std::string text_;

  const bool at_end() { return (text_.cbegin() + pos_) == text_.cend(); }

  const char32_t peek() {
    auto cursor = text_.cbegin() + pos_;
    char32_t code_point = utf8::peek_next(cursor, text_.cend());
    return code_point;
  }

  char32_t advance() {
    auto cursor = text_.cbegin() + pos_;
    char32_t code_point = utf8::next(cursor, text_.cend());
    pos_ = static_cast<std::size_t>(cursor - text_.cbegin());
    return code_point;
  }

  std::expected<Token, Diagnostic> obtain_string_token() {
    auto cursor = text_.cbegin() + pos_;
    size_t start_pos = static_cast<std::size_t>(cursor - text_.cbegin());

    while (!at_end()) {
      char32_t code_point = advance();
      if (code_point == '"') {
        // TODO: if " written in Cyrillic, then -1 might not offset correctly
        // -1 because we know that prev char is "
        return Token(TokenKind::String,
                     text_.substr(start_pos, pos_ - start_pos - 1));
      }
    }

    return std::unexpected(
        Diagnostic({start_pos, pos_}, "Lexer: Non terminated string"));
  }

  std::expected<Token, Diagnostic> obtain_keyword_token() {
    auto cursor = text_.cbegin() + pos_;
    utf8::prior(cursor,
                text_.cbegin()); // restore 1st char processed by advance()
    size_t start_pos = static_cast<std::size_t>(cursor - text_.cbegin());

    while (is_kyrgyz_char(peek()) && !at_end()) {
      advance();
    }
    return verified_keyword_token(text_.substr(start_pos, pos_ - start_pos), start_pos);
  }

  std::expected<Token, Diagnostic> verified_keyword_token(std::string keyword,
                                                          size_t start_pos) {
    if (keyword == "чыгар") {
      return Token(TokenKind::Chygar, "");
    } else {
      return std::unexpected(
          Diagnostic({start_pos, pos_}, "Lexer: Non-valid keyword statement"));
    }
  }

  // unfortunate default clangd formatting
  constexpr bool is_kyrgyz_char(char32_t ch) {
    return (ch >= 0x0410 && ch <= 0x044F) || ch == 0x04A2 ||
           ch == 0x04A3 ||                 // Ң ң
           ch == 0x04E8 || ch == 0x04E9 || // Ө ө
           ch == 0x04AE || ch == 0x04AF || // Ү ү
           ch == 0x0401 || ch == 0x0451;   // Ё ё
  }
};
