#pragma once

#include <expected>
#include <memory>

#include "AST.hpp"
#include "Diagnostic.hpp"
#include "Lexer.hpp"
#include "Token.hpp"

class Parser {
public:
  explicit Parser(Lexer lexer, DiagnosticCollector &dcollector)
      : lexer_(std::move(lexer)), dcollector_(dcollector) {
    advance();
  }

  std::expected<std::unique_ptr<Statement>, Diagnostic> parse_statement() {
    if (current_.kind == TokenKind::Chygar) {
      return parse_chygar_statement();
    } else {
    }
  }

private:
  Lexer lexer_;
  Token current_;
  DiagnosticCollector &dcollector_;

  void advance() {
    std::expected<Token, Diagnostic> new_token = lexer_.nextToken();
    if (!new_token) {
      dcollector_.record(new_token.error());
      advance();
    }

    current_ = new_token.value();
  }

  std::expected<void, Diagnostic> consume_expected(TokenKind expected) {
    if (current_.kind != expected) {
      return std::unexpected(
          Diagnostic({lexer_.get_pos_()}, "Parser: Unexpected token"));
    }

    advance();
    return {};
  }

  std::unique_ptr<Statement> parse_chygar_statement() {
    auto lparen = consume_expected(TokenKind::LeftParen);
    if (!lparen) {
      dcollector_.record(lparen.error());
    }
    auto tamsab = consume_expected(TokenKind::String);
    if (!tamsab) {
      dcollector_.record(tamsab.error());
    }
    auto rparen = consume_expected(TokenKind::RightParen);
    if (!rparen) {
      dcollector_.record(rparen.error());
    }

    return std::unique_ptr<PrintStatement>(
        std::unique_ptr<StringExpr>(current_.value));
  }
};
