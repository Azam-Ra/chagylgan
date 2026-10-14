#pragma once

#include <cstddef>
#include <string>

struct SourceSpan {
  std::size_t begin;
  std::size_t end = -1;
};

struct Diagnostic {
  SourceSpan span;
  std::string message;
};
