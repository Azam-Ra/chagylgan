#include <expected>

#include "AST.hpp"
#include "CodeGenerator.hpp"
#include "Diagnostic.hpp"

std::expected<void, Diagnostic>
CodeGenerator::generate_statement(const Statement &statement) {
  // TODO: Introduce visitor pattern
  const auto *print_statement =
      dynamic_cast<const PrintStatement *>(&statement);

  if (!print_statement) {
      return std::unexpected(Diagnostic());
  }


}
