#pragma once

#include <memory>
#include <string>

/*
 *
 * program
 *  := printStatement EOF
 *
 * printStatement
 *  := "чыгар" "(" ТАМСАБ ")"
 *
 */

struct Expr {
  virtual ~Expr() = default;
};

struct StringExpr : Expr {
  std::string value_;

  explicit StringExpr(std::string value) : value_(std::move(value)) {}
};

struct Statement {
  virtual ~Statement() = default;
};

struct PrintStatement : Statement {
  std::unique_ptr<Expr> expression_;

  explicit PrintStatement(std::unique_ptr<Expr> expression)
      : expression_(std::move(expression)) {}
};

