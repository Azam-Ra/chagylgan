#pragma once

#include <cstddef>
#include <string>
#include <vector>

struct SourceSpan {
  std::size_t begin;
  std::size_t end = -1;
};

struct Diagnostic {
  SourceSpan span;
  std::string message;
};

class DiagnosticCollector {
public:
  void record(Diagnostic diagnostic) {
    history_.push_back(std::move(diagnostic));
  }

private:
  std::vector<Diagnostic> history_;
};
