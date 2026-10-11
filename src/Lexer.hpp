#pragma once

#include <string>

#include <utf8.h>

#include "Token.hpp"

class Lexer {
public:
  explicit Lexer(std::string text) : text_(std::move(text)) {}

  Token nextToken() {
    if (pos_ >= text_.size())
      return {TokenKind::End, ""};

    char32_t t = advance();
    if (t == '(') {
      return {TokenKind::LeftParen, ""};
    } else if (t == ')') {
      return {TokenKind::RightParen, ""};
    } else if (t == '"') {
      return obtain_string_token();
    } else if (is_kyrgyz_char(t)) {
      return obtain_keyword_token();
    } else {
      return {TokenKind::Invalid, ""};
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

  Token obtain_string_token() {
    auto cursor = text_.cbegin() + pos_;
    size_t start_pos = static_cast<std::size_t>(cursor - text_.cbegin());

    while (!at_end()) {
      char32_t code_point = advance();
      if (code_point == '"') {
        // -1 because we know that prev char is "
        return {TokenKind::String,
                text_.substr(start_pos, pos_ - start_pos - 1)};
      }
    }

    return {TokenKind::Invalid, ""};
  }

  Token obtain_keyword_token() {
    auto cursor = text_.cbegin() + pos_;
    utf8::prior(cursor,
                text_.cbegin()); // restore 1st char processed by advance()
    size_t start_pos = static_cast<std::size_t>(cursor - text_.cbegin());

    while (is_kyrgyz_char(peek()) && !at_end()) {
      advance();
    }
    return verified_keyword_token(text_.substr(start_pos, pos_ - start_pos));
  }

  Token verified_keyword_token(std::string keyword) {
    if (keyword == "чыгар") {
      return {TokenKind::Chygar, ""};
    } else {
      return {TokenKind::Invalid, ""};
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
