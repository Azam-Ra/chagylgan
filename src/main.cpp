#include <iostream>

int main(int argc, char* argv[]) {
    Lexer lexer("чыгар(\"Салам!\")");

    while (true) {
        Token token = lexer.nextToken();
        std::cout << static_cast<int>(token) << " : " << token.value << std::endl;

        if (token.kind == TokenKind::End)
            break;
    }
    
    return 0;
}

