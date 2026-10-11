#include <iostream>

#include "Lexer.hpp"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "Usage: Provide a string to parse!\n";
    return 1;
  }

  Lexer lexer(argv[1]);

  while (true) {
    Token token = lexer.nextToken();
    std::cout << static_cast<int>(token.kind) << " : " << token.value
              << std::endl;

    if (token.kind == TokenKind::End)
      break;
  }

  return 0;
}
